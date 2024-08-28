/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:49:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/21 16:40:32 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::~Channel() {}
Channel::Channel(std::string name, Server &server) : _server(server), _name(name)
{
	_is_invite_only = false;
	_is_mod_only_topic = false;
	_has_password = false;
	_has_user_limit = false;
	_user_limit = 0;
}

void Channel::inviteUser(std::string username)
{
	_invitations[username] = true;
}

void Channel::addUser(std::string username)
{
	User *newUser = _server.getUser(username);

	if (_has_user_limit && _users.size() + 1 >= _user_limit)
		throw (Channel::CantJoinChannelException("Channel is full"));
	if (_is_invite_only && _invitations[username] != true)
		throw (Channel::CantJoinChannelException("User is not invited to channel"));
	if (newUser)
		_users[username] = newUser;
	_mods[username] = false;
}

void Channel::removeUser(std::string username)
{
	_users.erase(username);
	_mods.erase(username);
	_invitations.erase(username);
	if (_users.size() == 0)
		_server.askCleanup(_name);
}


/* Getter/Setter */

void Channel::opUser(std::string username, bool value) { _mods[username] = value; }
bool Channel::isOp(std::string username) { return _mods[username]; }
bool Channel::isInviteOnly(void) { return _is_invite_only; }
bool Channel::hasPassword(void) { return _has_password; }
bool Channel::hasUserLimit(void) { return _has_user_limit; }
bool Channel::isModOnlyTopic(void) { return _is_mod_only_topic; }
bool Channel::isUserInChannel(std::string username) { return (_users[username] != NULL); }

void Channel::setTopic(std::string topic) { _topic = topic; };

std::string Channel::getName(void) const { return _name; }
std::map<std::string, User *> Channel::getUsers(void) const { return _users; }

/* EXCEPTIONS */

Channel::CantJoinChannelException::CantJoinChannelException(const std::string &msg) : error_message(msg) {}
Channel::CantJoinChannelException::~CantJoinChannelException() throw () {}
const char *Channel::CantJoinChannelException::what() const throw() { return error_message.c_str(); }

Channel::InvalidPermissionException::InvalidPermissionException(const std::string &msg) : error_message(msg) {}
Channel::InvalidPermissionException::~InvalidPermissionException() throw () {}
const char *Channel::InvalidPermissionException::what() const throw() { return error_message.c_str(); }