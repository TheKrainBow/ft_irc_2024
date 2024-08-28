/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:49:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/21 17:01:06 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

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
	return (_channels[channelName]);
}

void Server::askCleanup(std::string name)
{
	_need_channel_cleanup = name;
}

void Server::start()
{
#ifdef DEBUG
	addUser("Bob", "Bob_The_Builder");
	addUser("Tom", "Fantom0000");
	addUser("Mathieu", "Krain");
	addUser("Achille", "Biizox");
	addUser("Moumoune", "TheStupidOne");
	addUser("Nyraak", "TheFatOne");
	addUser("Henry", "Xx_H4nry_xX");
	addUser("Alice", "JobPass4Ever");
	_users["Bob"]->joinChannel("SomeTestChannel");
	_users["Henry"]->joinChannel("SomeTestChannel");
	_users["Mathieu"]->joinChannel("SomeStupidLeagueChannel");
	_users["Bob"]->joinChannel("SomeOtherChannel");
	_users["Tom"]->joinChannel("SomeStupidLeagueChannel");
	_users["Achille"]->joinChannel("SomeStupidLeagueChannel");
	_users["Moumoune"]->joinChannel("WeNeedFood");
	_users["Nyraak"]->joinChannel("WeNeedFood");
	_users["Nyraak"]->ChannelInviteUser("WeNeedFood", "Mathieu");

	_users["Mathieu"]->leaveChannel("SomeStupidLeagueChannel");
	if (!_need_channel_cleanup.empty())
	{
		std::cout << "  " << YELLOW << _need_channel_cleanup << " is empty!" << std::endl << "  ";
		deleteChannel(_need_channel_cleanup);
	}

	_users["Bob"]->leaveChannel("SomeOtherChannel");
	if (!_need_channel_cleanup.empty())
	{
		std::cout << "  " << YELLOW << _need_channel_cleanup << " is empty!" << std::endl << "  ";
		deleteChannel(_need_channel_cleanup);
	}
	printStatus();
#endif
}


/* DEBUG */

std::ostream& operator<<(std::ostream& os, const Channel& channel)
{
	os << PURPLE << "channel" << WHITE " #" << channel.getName() << ":" << std::endl;
	std::map<std::string, User *> tmp = channel.getUsers();
	if (tmp.size() == 0)
	{
		os << BGREEN << " ➜ user:" << WHITE << " None" << std::endl;
		return (os);
	}
	for (std::map<std::string, User *>::iterator it = tmp.begin(); it != tmp.end(); it++)
		std::cout << "     ➜ " << *(*it).second << std::endl;
	return (os);
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << GREEN << " user: " << WHITE << user.getUsername() << "," << GREEN << "\tnick: " WHITE << user.getNickname();
	return (os);
}

void Server::printStatus(void)
{
	std::cout << BCYAN << std::endl << "Server:" << WHITE << std::endl;
	std::cout << "   ➜ " << CYAN << "Port: " << WHITE << _port << std::endl;
	std::cout << "   ➜ " << CYAN << "Pass: " << WHITE << _password << std::endl << std::endl;
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
	std::cout << BPURPLE << "ChannelList:" << WHITE << std::endl;
	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		std::cout << "   ➜ " << *it->second;
	std::cout << std::endl;
}