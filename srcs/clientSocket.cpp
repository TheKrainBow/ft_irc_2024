/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:03:26 by maagosti          #+#    #+#             */
/*   Updated: 2024/09/03 02:08:18 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clientSocket.hpp"

ClientSocket::ClientSocket(Server &server, int socket) : _server(server)
{
	_socket = socket;
	_cap_received = false;
	_pass_received = false;
	_nick_received = false;
	_user_received = false;
	_buffer = "";
	_nickname = "";
	_username = "";
}

ClientSocket::~ClientSocket() {}

void ClientSocket::logClient(std::string cmd)
{
	if (_cap_received == false)
	{
		if (cmd.compare(0, 7, "CAP LS") != 0)
			throw ClientSocket::ClientLogginException("Wrong input order, expected \"CAP LS\", got \"" + cmd + "\"");
		_cap_received = true;
	}
	else if (_pass_received == false)
	{
		if (cmd.compare(0, 5, "PASS ") != 0)
			throw ClientSocket::ClientLogginException("Wrong input order");
		std::string pass = cmd.substr(5, cmd.size() - 5);
		if (_server.checkPassword(pass) != true)
			throw ClientSocket::ClientLogginException("Wrong password");
		_pass_received = true;
	}
	else if (_nick_received == false)
	{
		if (cmd.compare(0, 5, "NICK ") != 0)
			throw ClientSocket::ClientLogginException("Wrong input order");
		_nickname = cmd.substr(5, cmd.size() - 5);
		_nick_received = true;
	}
	else if (_user_received == false)
	{
		if (cmd.compare(0, 5, "USER ") != 0)
			throw ClientSocket::ClientLogginException("Wrong input order");
		_username = cmd.substr(5, cmd.find(' ', 6) - 5);
		_user_received = true;
		_server.validateUser(*this);
	}
	else
	{
		if (cmd.compare(0, 8, "CAP END") != 0)
			throw ClientSocket::ClientLogginException("Wrong input order");
		_isLogged = true;
		std::string capend_msg = ":maagostirc " + _nickname + " CAP END\r\n";
		send(_socket, capend_msg.c_str(), capend_msg.length(), 0);
		std::string welcome_msg = ":maagostirc 001 " + _nickname + " :Welcome to the IRC server " + _nickname + "!" + _nickname + "@localhost\r\n";
		send(_socket, welcome_msg.c_str(), welcome_msg.length(), 0);
	}
}

void ClientSocket::receiveMessage(std::string message)
{
	size_t		pos;
	std::string	cmd;

	_buffer.append(message);
	pos = _buffer.find('\n');
	while (pos != std::string::npos)
	{
		cmd = _buffer.substr(0, pos);
		cmd.replace(cmd.find('\r'), 1, "");
		_buffer.erase(_buffer.begin(), _buffer.begin() + pos + 1);
		pos = _buffer.find('\n');
		if (_isLogged == false)
		{
			try { logClient(cmd); } catch (std::exception &e) { std::cerr << e.what() << std::endl; }
		}
	}
}

bool ClientSocket::isLogged() const { return _isLogged; }
std::string ClientSocket::getUsername(void) const { return _username; }
std::string ClientSocket::getNickname(void) const { return _nickname; }
int ClientSocket::getSocket(void) const { return _socket; }

ClientSocket::ClientLogginException::ClientLogginException(const std::string &msg) : error_message(msg) {}
ClientSocket::ClientLogginException::~ClientLogginException() throw () {}
const char *ClientSocket::ClientLogginException::what() const throw() { return error_message.c_str(); }