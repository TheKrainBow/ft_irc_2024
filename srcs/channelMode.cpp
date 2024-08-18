/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:51:33 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/18 21:38:42 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channelMode.hpp"

ChannelMode::~ChannelMode() {}

ChannelMode::ChannelMode()
{
	_is_invite_only = false;
	_is_mod_only_topic = false;
	_has_password = false;
	_has_user_limit = false;
	_user_limit = 0;
}