/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:47:23 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/18 22:21:01 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"
#include "IRCServer.hpp"
#include "channelMode.hpp"
#include "user.hpp"
#include <iostream>

#ifdef DEBUG

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << " user: " << user.getUsername() << ",\tnick: " << user.getNickname();
	return (os);
}

std::ostream& operator<<(std::ostream& os, const Channel& channel)
{
	os << "channel #" << channel.getName() << ":" << std::endl;
	std::vector<User> tmp = channel.getUsers();
	if (tmp.size() == 0)
	{
		os << "     ➜ Userlist: None" << std::endl;
		return (os);
	}
	os << "     ➜ Userlist: " << std::endl;
	for (std::vector<User>::iterator it = tmp.begin(); it != tmp.end(); it++)
		std::cout << "        ➜ " << *it << std::endl;
	return (os);
}

void IRCServer::listUser(void)
{
	std::cout << "Userlist:" << std::endl;
	for (std::map<std::string, User *>::iterator it = _users.begin(); it != _users.end(); it++)
		std::cout << "   ➜ " << *it->second << std::endl;
}

void IRCServer::listChannel(void)
{
	std::cout << "ChannelList:" << std::endl;
	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		std::cout << "   ➜ " << *it->second;
}

#endif