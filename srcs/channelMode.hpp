/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelMode.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:45:54 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/18 20:59:17 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class ChannelMode;

#include <string>
#include <vector>
#include "user.hpp"

class ChannelMode
{
	private:
		bool				_is_invite_only;
		bool				_is_mod_only_topic;
		bool				_has_password;
		bool				_has_user_limit;
		int					_user_limit;
		std::string			_password;
		std::vector<User>	_mods;
	public:
		ChannelMode();
		~ChannelMode();
};
