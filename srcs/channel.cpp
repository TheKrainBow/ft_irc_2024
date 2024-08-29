/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:49:31 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/28 23:13:55 by krain            ###   ########.fr       */
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

	if (_has_password)
		throw (Channel::CantJoinChannelException(ERR_CHANNEL_NO_PW));
	if (_has_user_limit && _users.size() + 1 >= _user_limit)
		throw (Channel::CantJoinChannelException(ERR_CHANNEL_IS_FULL));
	if (_is_invite_only && _invitations[username] != true)
		throw (Channel::CantJoinChannelException("User is not invited to channel"));
	if (newUser)
		_users[username] = newUser;
	_mods[username] = false;
}

void Channel::addUser(std::string username, std::string password)
{
	User *newUser = _server.getUser(username);

	if (_has_password == false)
		throw (Channel::CantJoinChannelException(ERR_JOINING_NON_PW_CHANNEL_WITH_PW));
	if (_password.compare(password) != 0)
		throw (Channel::CantJoinChannelException(ERR_CHANNEL_WRONG_PW));
	if (_has_user_limit && _users.size() + 1 >= _user_limit)
		throw (Channel::CantJoinChannelException(ERR_CHANNEL_IS_FULL));
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

void Channel::opUser(std::string username, bool value)
{
	std::cout << PURPLE << _name << WHITE << "::opUser(" << GREEN << username << WHITE << ", " << BLUE << value << WHITE << ")" << std::endl;
	_mods[username] = value;
}

bool Channel::isOp(std::string username) {
	return _mods[username];
}
bool Channel::isInviteOnly(void) { return _is_invite_only; }
bool Channel::hasPassword(void) { return _has_password; }
bool Channel::hasUserLimit(void) { return _has_user_limit; }
bool Channel::isModOnlyTopic(void) { return _is_mod_only_topic; }
bool Channel::isUserInChannel(std::string username)
{
	bool resp = _users[username] != NULL;
	if (!resp)
		_users.erase(username);
	return (resp);
}

void Channel::setTopic(std::string topic) { _topic = topic; }
void Channel::setInviteOnly(bool value) { _is_invite_only = value; }
void Channel::setModOnlyTopic(bool value) { _is_mod_only_topic = value; }
void Channel::setPassword(std::string password)
{
	_password = password;
	_has_password = _password.size() > 0;
}
void Channel::setUserLimit(int limit)
{
	_user_limit = limit;
	_has_user_limit = (limit != 0);
}

std::string Channel::getName(void) const { return _name; }
std::string Channel::getTopic(void) const { return _topic; }
std::map<std::string, User *> Channel::getUsers(void) const { return _users; }

/* EXCEPTIONS */

Channel::CantJoinChannelException::CantJoinChannelException(const std::string &msg) : error_message(msg) {}
Channel::CantJoinChannelException::~CantJoinChannelException() throw () {}
const char *Channel::CantJoinChannelException::what() const throw() { return error_message.c_str(); }

Channel::InvalidPermissionException::InvalidPermissionException(const std::string &msg) : error_message(msg) {}
Channel::InvalidPermissionException::~InvalidPermissionException() throw () {}
const char *Channel::InvalidPermissionException::what() const throw() { return error_message.c_str(); }