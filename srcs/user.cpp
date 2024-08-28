/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:03:26 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/21 16:39:52 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"

User::User(std::string username, std::string nickname, Server &server) : _server(server), _username(username), _nickname(nickname)
{
	_os = &std::cout;
}

User::User(const User &copy) : _server(copy.getServer()), _username(copy.getUsername()), _nickname(copy.getNickname())
{
}

User::~User() {}

bool User::isActive() { return _isActive; }

void User::setActive(bool val) { _isActive = val; }

std::string User::getUsername(void) const { return _username; }
std::string User::getNickname(void) const { return _nickname; }
Server &User::getServer(void) const { return _server; }

void User::sendClientMessage(std::string msg) const
{
	std::cout << "Sending message to client " << _username << ":" << std::endl;
	*_os << msg;
}

void User::joinChannel(std::string channelName)
{
	std::cout << GREEN << _username << WHITE << "::joinChannel(" << PURPLE << channelName << WHITE << ")" << std::endl;
	if (_server.getChannel(channelName) == NULL)
	{
		std::cout << "  " << YELLOW << channelName << " doesn't exist!" << std::endl << "  ";
		_server.addChannel(channelName);
	}
	try {
		_server.getChannel(channelName)->addUser(_username);
	} catch (Channel::CantJoinChannelException &e) {
		std::cerr << e.what();
	}
}

void User::leaveChannel(std::string channelName)
{
	std::cout << GREEN << _username << WHITE << "::leaveChannel(" << PURPLE << channelName << WHITE << ")" << std::endl;
	_server.getChannel(channelName)->removeUser(_username);
}

void User::ChannelKickUser(std::string channelName, std::string userToKick)
{
	Channel *channel = _server.getChannel(channelName);
	
	if (channel->isOp(_username) == false)
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_OPERATOR));
	channel->removeUser(userToKick);
}

void User::ChannelInviteUser(std::string channelName, std::string userToInvite)
{
	std::cout << GREEN << _username << WHITE << "::ChannelInviteUser(" << PURPLE << channelName << WHITE << ", " << GREEN << userToInvite << WHITE << ")" << std::endl;
	Channel *channel = _server.getChannel(channelName);
	
	if (channel->isUserInChannel(_username))
		channel->inviteUser(userToInvite);
}

void User::ChannelChangeTopic(std::string channelName, std::string topic)
{
	Channel *channel = _server.getChannel(channelName);

	if (!channel->isUserInChannel(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_IN_CHANNEL));
	if (channel->isModOnlyTopic() && !channel->isOp(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_OPERATOR));
	channel->setTopic(topic);
}