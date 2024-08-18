/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:46:32 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/18 22:08:05 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class User;

#include <string>
#include <iostream>
#include <map>
#include "channel.hpp"

class User
{
	public:
	private:
		const std::string				_username;
		std::string						_nickname;
		bool							_isActive;
	public:
		User(std::string username, std::string nickname);
		~User();
		bool isActive();
		void setActive(bool val);
		std::string getUsername(void) const;
		std::string getNickname(void) const;
};

#ifdef DEBUG
std::ostream& operator<<(std::ostream& os, const User& user);
#endif