/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:45:54 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/18 22:09:14 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef int ChannelID;
class IRCServer;
class User;

#include <string>
#include <vector>
#include "channelMode.hpp"
#include "user.hpp"
#include "IRCServer.hpp"

class Channel
{
	private:
		IRCServer						&_server;
		const std::string				_name;
		std::vector<User>				_users;
		ChannelMode						*_modes;
	public:
		Channel(std::string name, IRCServer &server);
		~Channel();
		void addUser(std::string _username);
		void removeUser(std::string _username);
		ChannelID getID(void) const;
		std::string getName(void) const;
		std::vector<User> getUsers(void) const;
};
