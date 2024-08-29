/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:49:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/28 23:13:44 by krain            ###   ########.fr       */
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

void Server::start()
{
#ifdef DEBUG
	{               // ADD USER
		std::cout << BWHITE << "🧪 Adding user for tests 🧪" << std::endl;
		addUser("Bob", "Bob_The_Builder");
		addUser("Tom", "Fantom0000");
		addUser("Mathieu", "Krain");
		addUser("Achille", "Biizox");
		addUser("Moumoune", "TheStupidOne");
		addUser("Nyraak", "TheFatOne");
		addUser("Henry", "Xx_H4nry_xX");
		addUser("Alice", "JobPass4Ever");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // JOIN CHANNELS
		std::cout << BWHITE << "🧪 Make user join new channel 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomeTestChannel");
		_users["Henry"]->joinChannel("SomeTestChannel");
		this->deleteChannel("SomeTestChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // INVITE USERS
		std::cout << BWHITE << "🧪 Invite Tests 🧪" << std::endl;
		_users["Moumoune"]->joinChannel("WeNeedFood");
		_users["Nyraak"]->joinChannel("WeNeedFood");
		_users["Moumoune"]->ChannelModeInvite("WeNeedFood", true);
		_users["Mathieu"]->joinChannel("WeNeedFood");
		_users["Nyraak"]->ChannelInviteUser("WeNeedFood", "Mathieu");
		_users["Mathieu"]->joinChannel("WeNeedFood");
		this->deleteChannel("WeNeedFood");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // LEAVE CHANNELS
		std::cout << BWHITE << "🧪 Leave tests 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomeFullChannel");
		_users["Mathieu"]->joinChannel("SomeFullChannel");
		_users["Bob"]->joinChannel("SomeEmptyChannel");
		_users["Mathieu"]->leaveChannel("SomeFullChannel");
		if (!_need_channel_cleanup.empty())
		{
			std::cout << "  " << YELLOW << _need_channel_cleanup << " is empty!" << std::endl << "  ";
			deleteChannel(_need_channel_cleanup);
		}
		_users["Bob"]->leaveChannel("SomeEmptyChannel");
		if (!_need_channel_cleanup.empty())
		{
			std::cout << "  " << YELLOW << _need_channel_cleanup << " is empty!" << std::endl << "  ";
			deleteChannel(_need_channel_cleanup);
		}
		this->deleteChannel("SomeFullChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // KICK USERS
		std::cout << BWHITE << "🧪 Kick tests 🧪" << std::endl;
		this->addChannel("SomeKickTestChannel");
		_users["Moumoune"]->joinChannel("SomeKickTestChannel");
		_users["Nyraak"]->joinChannel("SomeKickTestChannel");
		try
		{
			_users["Nyraak"]->ChannelKickUser("SomeKickTestChannel", "Moumoune");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Moumoune"]->ChannelKickUser("SomeKickTestChannel", "Nyraak");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Moumoune"]->ChannelKickUser("SomeKickTestChannel", "Unknown");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Moumoune"]->ChannelKickUser("SomeTestChannel", "Bob");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		this->deleteChannel("SomeKickTestChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // CHANGE TOPIC
		std::cout << BWHITE << "🧪 Topic tests 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomeTopicTestChannel");
		_users["Henry"]->joinChannel("SomeTopicTestChannel");
		try
		{
			_users["Henry"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some really normal user topic");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Bob"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some really op user topic");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Moumoune"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some really external user topic");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Henry"]->ChannelModeTopic("SomeTopicTestChannel", true);
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Henry"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some really normal user topic");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Bob"]->ChannelModeTopic("SomeTopicTestChannel", true);
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Henry"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some forbidden normal user topic");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		try { _users["Bob"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some op user topic"); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		this->deleteChannel("SomeTopicTestChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // PASSWORD TESTS
		std::cout << BWHITE << "🧪 Password tests 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomePasswordTestChannel");
		_users["Bob"]->ChannelModePassword("SomePasswordTestChannel", "1234");
		_users["Henry"]->joinChannel("SomePasswordTestChannel");
		_users["Henry"]->joinChannel("SomePasswordTestChannel", "123");
		try { _users["Henry"]->ChannelModePassword("SomePasswordTestChannel", "123"); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		_users["Henry"]->joinChannel("SomePasswordTestChannel", "1234");
		try { _users["Henry"]->ChannelModePassword("SomePasswordTestChannel", "123"); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		_users["Bob"]->ChannelModePassword("SomePasswordTestChannel", "");
		_users["Mathieu"]->joinChannel("SomePasswordTestChannel", "test");
		_users["Mathieu"]->joinChannel("SomePasswordTestChannel");
		this->deleteChannel("SomePasswordTestChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // LIMIT TESTS
		std::cout << BWHITE << "🧪 Limit tests 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomeLimitTestChannel");
		_users["Bob"]->ChannelModeLimit("SomeLimitTestChannel", 1);
		_users["Henry"]->joinChannel("SomeLimitTestChannel");
		_users["Bob"]->ChannelModeLimit("SomeLimitTestChannel", 0);
		_users["Henry"]->joinChannel("SomeLimitTestChannel");
		this->deleteChannel("SomeLimitTestChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}

	printStatus();
#endif
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