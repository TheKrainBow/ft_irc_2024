/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:29:43 by krain             #+#    #+#             */
/*   Updated: 2024/09/02 19:18:11 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
std::ostream& operator<<(std::ostream& os, Channel& channel);

Server::~Server()
{
	for (std::map<std::string, User *>::iterator it = _users.begin(); it !=  _users.end(); it++)
		delete (*it).second;
	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		delete (*it).second;
}

void Server::startServerSocket(void)
{
	std::cout << CYAN << "Server" << WHITE << "::startServerSocket()" << std::endl;
	_server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_socket == -1)
		throw Server::ServerInitException("Error while creating server socket");

	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(_port);

	if (bind(_server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		close(_server_socket);
		throw Server::ServerInitException("Error while binding server socket");
	}

	if (listen(_server_socket, 100) == -1) {
		close(_server_socket);
		throw Server::ServerInitException("Error while starting server listen");
	}
	pollfd  newfd;
	newfd.fd = _server_socket;
	newfd.events = POLLIN;
	newfd.revents = 0;
	_sockets.push_back(newfd);
}

Server::Server(int port, std::string password) : _password(password), _port(port)
{
	std::cout << CYAN << "Server" << WHITE << "::Server(" << BLUE << port << WHITE << ", " << BLUE << password << WHITE << ")" << WHITE << std::endl;
	_need_channel_cleanup = "";
}

void Server::addUser(std::string username, std::string nickname)
{
	std::cout << CYAN << "Server" << WHITE << "::addUser(" << GREEN << "\"" << username << "\"" << WHITE << ", " << GREEN << "\"" << nickname << "\"" << WHITE << ")" << std::endl;
	if (_users[username])
		_users[username]->setActive(true);
	else
		_users[username] = new User(username, nickname, *this);
}

void Server::cleanup()
{
	std::cout << CYAN << "Server" << WHITE << "::cleanup()" << std::endl;
	for (std::map<std::string, User *>::iterator it = _users.begin(); it !=  _users.end(); it++)
	{
		delete (*it).second;
		_users.erase(it);
		it = _users.begin();
	}
	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		delete (*it).second;
		_channels.erase(it);
		it = _channels.begin();
	}
	for (std::vector<pollfd>::iterator it = _sockets.begin(); it < _sockets.end(); it++) {
		close((*it).fd);
	}
}

void Server::closeClientSocket(std::vector<pollfd>::iterator &client)
{
	std::cout << CYAN << "Server" << WHITE << "::closeClientSocket(" << BLUE << client->fd << WHITE << ")" << std::endl;
	std::vector<pollfd>::iterator prev = client - 1;
	_clients.erase(client->fd);
	close(client->fd);
	_sockets.erase(client);
	client = prev;
}

void Server::acceptClientSocket(int client_socket)
{
	std::cout << CYAN << "Server" << WHITE << "::acceptClientSocket(" << BLUE << client_socket << WHITE << ")" << std::endl;
	pollfd  newfd;

	newfd.fd = client_socket;
	newfd.events = POLLIN;
	newfd.revents = 0;
	_sockets.push_back(newfd);
	_clients[client_socket] = new ClientSocket(*this);
}

void Server::receiveClientMessage(std::vector<pollfd>::iterator &client)
{
	std::cout << CYAN << "Server" << WHITE << "::receiveClientMessage(" << BLUE << client->fd << WHITE << ")" << std::endl;

	char buffer[1025];
	memset(buffer, 0, 1025);

	int bytes_received = recv(client->fd, buffer, 1024, 0);
	if (bytes_received <= 0) {
		closeClientSocket(client);
		return ;
	} else {
		std::cout << buffer;
		_clients[client->fd]->receiveMessage(std::string(buffer));
		//send(client->fd, buffer, bytes_received, 0);
	}
}

void Server::start()
{
	std::cout << CYAN << "Server" << WHITE << "::start()" << std::endl << "  ";
	try { startServerSocket(); } catch (ServerInitException &e)
	{
		std::cerr << BRED << "    Exception catched: " << RED << e.what() << std::endl;
		std::cerr << BRED << "                       " << RED << "> Check port is not already in use" << std::endl;
		return ;
	}
	while (true) {
		int poll_count = poll(_sockets.data(), _sockets.size(), 10);
		if (poll_count == -1)
			throw ServerInitException("Error while using poll");
		for (std::vector<pollfd>::iterator it = _sockets.begin(); it < _sockets.end(); it++) {
			if (it->revents & POLLIN) {
				if (it->fd == _server_socket) {
					sockaddr_in client_addr;
					socklen_t client_len = sizeof(client_addr);
					int client_socket = accept(_server_socket, (sockaddr*)&client_addr, &client_len);
					if (client_socket == -1) {
						std::cerr << "Error while receiving a client." << std::endl;
						continue;
					}
					if (it->revents & (POLLHUP | POLLERR))
						closeClientSocket(it);
					else
						acceptClientSocket(client_socket);
					it = _sockets.begin();
				} else {
					receiveClientMessage(it);
				}
			}
		}
	}
}

void Server::addChannel(std::string name)
{
	std::cout << CYAN << "Server" << WHITE << "::addChannel(" << PURPLE << name << WHITE << ")" << std::endl;
	if (!_channels[name])
		_channels[name] = new Channel(name, *this);
}

void Server::deleteUser(std::string username)
{
	std::cout << CYAN << "Server" << WHITE << "::deleteUser(" << GREEN << username << WHITE << ")" << std::endl;
	delete _users[username];
}

void Server::deleteChannel(std::string name)
{
	std::cout << CYAN << "Server" << WHITE << "::deleteChannel(" << PURPLE << name << WHITE << ")" << std::endl;
	delete _channels[name];
	_channels.erase(name);
	_need_channel_cleanup = "";
}

User *Server::getUser(std::string username)
{
	return (_users[username]);
}

Channel *Server::getChannel(std::string channelName)
{
	Channel *dest = _channels[channelName];
	if (!dest)
		_channels.erase(channelName);
	return (dest);
}

void Server::askCleanup(std::string name)
{
	_need_channel_cleanup = name;
}


/* DEBUG */

# include <string>
# include <iomanip>
# include <iostream>
# include <cstdlib>

std::ostream& operator<<(std::ostream& os, Channel& channel)
{
	os << PURPLE << " channel:" << WHITE << " #";
	os << std::setiosflags(std::ios::left) << std::setw(25) << channel.getName().append(", ") << std::resetiosflags(std::ios::left);
	os << PURPLE << "topic: " << WHITE << "\"" << channel.getTopic() << "\"" << std::endl;
	std::map<std::string, User *> tmp = channel.getUsers();
	if (tmp.size() == 0)
	{
		os << BGREEN << " ➜ user:" << WHITE << " None" << std::endl;
		return (os);
	}
	for (std::map<std::string, User *>::iterator it = tmp.begin(); it != tmp.end(); it++)
	{
		if (channel.isOp((*it).second->getUsername()))
			std::cout << BLUE;
		std::cout << "	 ➜ " << std::setiosflags(std::ios::left) << *(*it).second << WHITE << std::endl;

	}
	return (os);
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os  << std::setiosflags(std::ios::left) << GREEN   << " user: "  << WHITE << std::setfill (' ') << std::setw(10) << user.getUsername().append(", ") << GREEN << "nick: "  <<  WHITE <<  std::setfill (' ');
	os << std::setw(15) << user.getNickname();
	return (os);
}

void Server::printStatus(void)
{
	std::cout << BWHITE << "🧪 Print server status 🧪" << std::endl;
	std::cout << BCYAN << std::endl << "Server:" << WHITE << std::endl;
	std::cout << "   ➜  " << CYAN << "Port: " << WHITE << _port << std::endl;
	std::cout << "   ➜  " << CYAN << "Pass: " << WHITE << _password << std::endl << std::endl;
	this->listUser();
	this->listChannel();
}

void Server::listUser(void)
{
	std::cout << BGREEN << "Userlist:" << WHITE << std::endl;
	for (std::map<std::string, User *>::iterator it = _users.begin(); it != _users.end(); it++)
		std::cout << "   ➜ " << *it->second << std::endl;
	std::cout << std::endl;
}

void Server::listChannel(void)
{
	if (_channels.size())
		std::cout << BPURPLE << "ChannelList:" << WHITE << std::endl;
	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		std::cout << "   ➜ " << *it->second;
	if (_channels.size())
	std::cout << std::endl;
}

Server::ServerInitException::ServerInitException(const std::string &msg) : error_message(msg) {}
Server::ServerInitException::~ServerInitException() throw () {}
const char *Server::ServerInitException::what() const throw() { return error_message.c_str(); }