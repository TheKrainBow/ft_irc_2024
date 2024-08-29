/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:46:32 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/28 23:11:27 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class User;

#include <string>
#include <iostream>
#include <map>
#include "channel.hpp"
#include "error.hpp"
#include "color.hpp"

class User
{
	private:
		Server							&_server;
		const std::string				_username;
		std::string						_nickname;
		std::ostream					*_os; // Replace this with socket
		bool							_isActive;
	public:
		User(std::string username, std::string nickname, Server &server);
		User(const User &copy);
		~User();
		bool isActive();
		void setActive(bool val);
		std::string getUsername(void) const;
		std::string getNickname(void) const;
		Server &getServer(void) const;
		void sendClientMessage(std::string msg) const;

		void joinChannel(std::string channelName);
		void joinChannel(std::string channelName, std::string password);
		void leaveChannel(std::string channelName);
		void sendMessage(std::string target, std::string message);

		void ChannelKickUser(std::string channelName, std::string usernameToKick);
		void ChannelInviteUser(std::string channelName, std::string usernameToInvite);
		void ChannelChangeTopic(std::string channelName, std::string topic);
		void ChannelModeInvite(std::string channelName, bool value);
		void ChannelModeTopic(std::string channelName, bool value);
		void ChannelModePassword(std::string channelName, std::string password);
		void ChannelModeOps(std::string channelName, std::string username, bool value);
		void ChannelModeLimit(std::string channelName, int userLimit);
};

#ifdef DEBUG
std::ostream& operator<<(std::ostream& os, const User& user);
#endif