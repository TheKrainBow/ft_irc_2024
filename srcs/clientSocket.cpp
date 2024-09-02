/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:03:26 by maagosti          #+#    #+#             */
/*   Updated: 2024/09/02 19:26:10 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clientSocket.hpp"

ClientSocket::ClientSocket(Server &server) : _server(server)
{
	_buffer = "";
	_nickname = "";
	_username = "";
}

ClientSocket::~ClientSocket() {}

void ClientSocket::logClient(std::string cmd)
{
	if (_cap_received == false && cmd.compare("CAP LS") != 0)
		throw ClientSocket::ClientLogginException("Wrong input");
}

void ClientSocket::receiveMessage(std::string message)
{
	size_t		pos;
	std::string	cmd;

	_buffer.append(message);
	pos = _buffer.find('\n');
	while (pos != std::string::npos)
	{
		cmd = _buffer.substr(0, pos - 1);
		_buffer.erase(_buffer.begin(), _buffer.begin() + pos + 1);
		pos = _buffer.find('\n');
		if (_isLogged == false)
			logClient(cmd);
	}
}

bool ClientSocket::isLogged() const { return _isLogged; }
std::string ClientSocket::getUsername(void) const { return _username; }
std::string ClientSocket::getNickname(void) const { return _nickname; }

ClientSocket::ClientLogginException::ClientLogginException(const std::string &msg) : error_message(msg) {}
ClientSocket::ClientLogginException::~ClientLogginException() throw () {}
const char *ClientSocket::ClientLogginException::what() const throw() { return error_message.c_str(); }