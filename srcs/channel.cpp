/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:49:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/18 22:09:16 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::~Channel() {}
Channel::Channel(std::string name, IRCServer &server) : _server(server), _name(name)
{
}

void Channel::addUser(std::string username)
{
	User *newUser = _server.getUser(username);

	if (newUser)
		_users.push_back(*newUser);
}


std::string Channel::getName(void) const { return _name; }
std::vector<User> Channel::getUsers(void) const { return _users; }