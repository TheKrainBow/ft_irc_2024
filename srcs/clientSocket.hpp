/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:46:32 by maagosti          #+#    #+#             */
/*   Updated: 2024/09/03 00:10:02 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class ClientSocket;

#include <string>
#include <iostream>
#include <map>
#include "channel.hpp"
#include "error.hpp"
#include "color.hpp"

class ClientSocket
{
	private:
		Server				&_server;
		std::string			_buffer;
		bool				_cap_received;
		bool				_pass_received;
		bool				_nick_received;
		bool				_user_received;
		std::string			_username;
		std::string			_nickname;
		bool				_isLogged;
		int					_socket;
	public:
		ClientSocket(Server &server, int socket);
		~ClientSocket();
		void receiveMessage(std::string message);
		void logClient(std::string cmd);
		bool isLogged() const;
		std::string getBuffer(void) const;
		std::string getUsername(void) const;
		std::string getNickname(void) const;
		int getSocket(void) const;
		class ClientLogginException : virtual public std::exception
		{
			private:
				std::string error_message;
			public:
				ClientLogginException(const std::string &msg);
				virtual ~ClientLogginException() throw ();
				const char *what() const throw();
		};
};
