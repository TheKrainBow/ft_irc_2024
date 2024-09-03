/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:01:17 by maagosti          #+#    #+#             */
/*   Updated: 2024/09/03 00:06:32 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG
#define DEBUG
#endif

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>
#include "channel.hpp"
#include "user.hpp"
#include "clientSocket.hpp"

class Channel;

class Server
{
	private:
		const std::string					_password;
		const int							_port;
		std::map<std::string, User *>		_users;
		std::map<std::string, Channel *>	_channels;
		std::map<int, ClientSocket *>		_clients;
		std::string							_need_channel_cleanup;
		std::vector<pollfd>					_sockets;
		int									_server_socket;
	private:
		void addUser(std::string username, std::string nickname);
		void deleteUser(std::string username);
		void deleteChannel(std::string name);
		void startServerSocket();
		void acceptClientSocket(int client_socket);
		void closeClientSocket(std::vector<pollfd>::iterator &client);
		void receiveClientMessage(std::vector<pollfd>::iterator &client);
	public:
		bool checkPassword(std::string pass) const;
		void addChannel(std::string name);
		void askCleanup(std::string name);
		User *getUser(std::string username);
		void validateUser(ClientSocket client);
		Channel *getChannel(std::string channelName);
		Server(int port, std::string password);
		~Server();
		void start();
		void cleanup();
		void test();
		class ServerInitException : virtual public std::exception
		{
			private:
				std::string error_message;
			public:
				ServerInitException(const std::string &msg);
				virtual ~ServerInitException() throw ();
				const char *what() const throw();
		};
#ifdef DEBUG
	private:
		void printStatus(void);
		void listUser(void);
		void listChannel(void);
#endif
};