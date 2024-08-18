/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:49:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/18 20:51:05 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCServer.hpp"

IRCServer::~IRCServer() {}
IRCServer::IRCServer(int port, std::string password) : _password(password), _port(port)
{
}

void IRCServer::addUser(std::string username, std::string nickname)
{
	if (_users[username])
		_users[username]->setActive(true);
	else
		_users[username] = new User(username, nickname);
}

void IRCServer::addChannel(std::string name)
{
	if (!_channels[name])
		_channels[name] = new Channel(name, *this);
}

User *IRCServer::getUser(std::string username)
{
	return (_users[username]);
}

void IRCServer::start()
{
	addUser("Bob", "Booobobo");
	addUser("H4nry", "Hanry");
	addChannel("SomeChannel");
	addChannel("SomeEmptyChannel");
	_channels["SomeChannel"]->addUser("Bob");
#ifdef DEBUG
	listUser();
	listChannel();
#endif
}
