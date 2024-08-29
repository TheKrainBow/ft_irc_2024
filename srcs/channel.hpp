/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:45:54 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/28 20:35:04 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Server;
class User;

#include <string>
#include <vector>
#include "user.hpp"
#include "server.hpp"

class Channel
{
	private:
		Server							&_server;
		const std::string				_name;
		std::string						_topic;
		std::map<std::string, User *>	_users;
		std::map<std::string, bool>		_mods;
		std::map<std::string, bool>		_invitations;
		bool							_is_invite_only;
		bool							_is_mod_only_topic;
		bool							_has_password;
		std::string						_password;
		bool							_has_user_limit;
		std::size_t						_user_limit;
	public:
		Channel(std::string name, Server &server);
		~Channel();

		void addUser(std::string username);
		void addUser(std::string username, std::string password);
		void removeUser(std::string username);

		void setTopic(std::string topic);

		void inviteUser(std::string username);
		void opUser(std::string username, bool value);

		bool isOp(std::string username);
		bool isUserInChannel(std::string username);
		bool isInviteOnly(void);
		bool hasPassword(void);
		bool hasUserLimit(void);
		bool isModOnlyTopic(void);
	
		void setInviteOnly(bool value);
		void setPassword(std::string password);
		void setUserLimit(int limit);
		void setModOnlyTopic(bool value);

		std::string getName(void) const;
		std::string getTopic(void) const;
		std::map<std::string, User *> getUsers(void) const;

		class CantJoinChannelException : virtual public std::exception
		{
			private:
				std::string error_message;
			public:
				CantJoinChannelException(const std::string &msg);
				virtual ~CantJoinChannelException() throw ();
				const char *what() const throw();
		};
		class InvalidPermissionException : virtual public std::exception
		{
			private:
				std::string error_message;
			public:
				InvalidPermissionException(const std::string &msg);
				virtual ~InvalidPermissionException() throw ();
				const char *what() const throw();
		};
};
