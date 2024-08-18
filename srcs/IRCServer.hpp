/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:01:17 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/18 22:17:31 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG
#define DEBUG
#endif

#pragma once
#include <string>
#include "channel.hpp"
#include "user.hpp"

class Channel;

class IRCServer
{
	private:
		const std::string				_password;
		const int						_port;
		std::map<std::string, User *>		_users;
		std::map<std::string, Channel *>	_channels;
	private:
		void addUser(std::string username, std::string nickname);
		void addChannel(std::string name);
		void deleteUser(std::string username);
		void deleteChannel(ChannelID channelId);
	public:
		User *getUser(std::string username);
		IRCServer(int port, std::string password);
		~IRCServer();
		void start();
#ifdef DEBUG
	private:
		void listUser(void);
		void listChannel(void);
#endif
};