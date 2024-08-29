/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:49:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/29 15:23:15 by maagosti         ###   ########.fr       */
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

Server::Server(int port, std::string password) : _password(password), _port(port)
{
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
}

void Server::start()
{
	std::cout << CYAN << "Server" << WHITE << "::start()" << std::endl;
	// Start reading sockets
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
		std::cout << "     ➜ " << std::setiosflags(std::ios::left) << *(*it).second << WHITE << std::endl;

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