/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:03:26 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/18 22:08:19 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"

User::User(std::string username, std::string nickname) : _username(username), _nickname(nickname)
{
}

User::~User() {}

bool User::isActive() { return _isActive; }

void User::setActive(bool val) { _isActive = val; }

std::string User::getUsername(void) const { return _username; }
std::string User::getNickname(void) const { return _nickname; }
