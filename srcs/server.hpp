/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:01:17 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/29 15:20:16 by maagosti         ###   ########.fr       */
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

class Server
{
	private:
		const std::string					_password;
		const int							_port;
		std::map<std::string, User *>		_users;
		std::map<std::string, Channel *>	_channels;
		std::string							_need_channel_cleanup;
	private:
		void addUser(std::string username, std::string nickname);
		void deleteUser(std::string username);
		void deleteChannel(std::string name);
	public:
		void addChannel(std::string name);
		void askCleanup(std::string name);
		User *getUser(std::string username);
		Channel *getChannel(std::string channelName);
		Server(int port, std::string password);
		~Server();
		void start();
		void cleanup();
		void test();
#ifdef DEBUG
	private:
		void printStatus(void);
		void listUser(void);
		void listChannel(void);
#endif
};