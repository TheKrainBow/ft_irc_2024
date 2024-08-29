/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:03:26 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/28 23:13:20 by krain            ###   ########.fr       */
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
	bool	isNewChannel = _server.getChannel(channelName) == NULL;
	std::cout << GREEN << _username << WHITE << "::joinChannel(" << PURPLE << channelName << WHITE << ")" << std::endl;
	if (isNewChannel)
	{
		std::cout << "  " << YELLOW << channelName << " doesn't exist!" << std::endl << "  ";
		_server.addChannel(channelName);
	}
	try {
		_server.getChannel(channelName)->addUser(_username);
		if (isNewChannel)
		{
			std::cout << "  ";
			_server.getChannel(channelName)->opUser(_username, true);
		}
	} catch (Channel::CantJoinChannelException &e) {
		std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
	}
}

void User::joinChannel(std::string channelName, std::string password)
{
	std::cout << GREEN << _username << WHITE << "::joinChannel(" << PURPLE << channelName << WHITE << ", " << BLUE << password << WHITE << ")" << std::endl;
	bool	isNewChannel = _server.getChannel(channelName) == NULL;
	if (isNewChannel)
		throw Channel::InvalidPermissionException(ERR_CHANNEL_NOT_EXIST);
	try {
		_server.getChannel(channelName)->addUser(_username, password);
	} catch (Channel::CantJoinChannelException &e) {
		std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
	}
}

void User::leaveChannel(std::string channelName)
{
	std::cout << GREEN << _username << WHITE << "::leaveChannel(" << PURPLE << channelName << WHITE << ")" << std::endl;
	_server.getChannel(channelName)->removeUser(_username);
}

void User::ChannelKickUser(std::string channelName, std::string userToKick)
{
	std::cout << GREEN << _username << WHITE << "::ChannelKickUser(" << PURPLE << channelName << WHITE ", " << GREEN << userToKick << WHITE << ")" << std::endl;
	Channel *channel = _server.getChannel(channelName);
	
	if (!channel)
		throw (Channel::InvalidPermissionException(ERR_CHANNEL_NOT_EXIST));
	if (_username.compare(userToKick) == 0)
		throw (Channel::InvalidPermissionException(ERR_CHANNEL_SELF_KICK_FORBIDDEN));
	if (channel->isOp(_username) == false)
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_OPERATOR));
	if (!channel->isUserInChannel(userToKick))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_IN_CHANNEL));
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
	std::cout << GREEN << _username << WHITE << "::ChannelChangeTopic(" << PURPLE << channelName << WHITE << ", " << BLUE << topic << WHITE << ")" << std::endl;
	Channel *channel = _server.getChannel(channelName);

	if (!channel->isUserInChannel(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_IN_CHANNEL));
	if (channel->isModOnlyTopic() && !channel->isOp(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_OPERATOR));
	channel->setTopic(topic);
}

void User::ChannelModeTopic(std::string channelName, bool value)
{
	std::cout << GREEN << _username << WHITE << "::ChannelModeTopic(" << PURPLE << channelName << WHITE << ", " << BLUE << value << WHITE << ")" << std::endl;
	Channel *channel = _server.getChannel(channelName);
	
	if (!channel->isUserInChannel(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_IN_CHANNEL));
	if (!channel->isOp(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_OPERATOR));
	channel->setModOnlyTopic(value);
}

void User::ChannelModeInvite(std::string channelName, bool value)
{
	std::cout << GREEN << _username << WHITE << "::ChannelModeInvite(" << PURPLE << channelName << WHITE << ", " << BLUE << value << WHITE << ")" << std::endl;
	Channel *channel = _server.getChannel(channelName);
	
	if (!channel->isUserInChannel(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_IN_CHANNEL));
	if (!channel->isOp(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_OPERATOR));
	channel->setInviteOnly(value);
}

void User::ChannelModePassword(std::string channelName, std::string password)
{
	std::cout << GREEN << _username << WHITE << "::ChannelModePassword(" << PURPLE << channelName << WHITE << ", " << BLUE << "\"" << password << "\"" << WHITE << ")" << std::endl;
	Channel *channel = _server.getChannel(channelName);
	
	if (!channel->isUserInChannel(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_IN_CHANNEL));
	if (!channel->isOp(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_OPERATOR));
	channel->setPassword(password);
}

void User::ChannelModeLimit(std::string channelName, int limit)
{
	std::cout << GREEN << _username << WHITE << "::ChannelModeLimit(" << PURPLE << channelName << WHITE << ", " << BLUE << limit << WHITE << ")" << std::endl;
	Channel *channel = _server.getChannel(channelName);
	
	if (!channel->isUserInChannel(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_IN_CHANNEL));
	if (!channel->isOp(_username))
		throw (Channel::InvalidPermissionException(ERR_USER_NOT_OPERATOR));
	channel->setUserLimit(limit);
}
