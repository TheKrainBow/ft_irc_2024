/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:02:03 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/28 20:36:45 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define ERR_USER_NOT_OPERATOR "User is not an operator"
#define ERR_USER_NOT_IN_CHANNEL "User is not in channel"
#define ERR_USER_NOT_INVITED "User not invited to channel"

#define ERR_CHANNEL_SELF_KICK_FORBIDDEN "User trying to kick himself"
#define ERR_CHANNEL_NOT_EXIST "Channel doesn't exist"
#define ERR_CHANNEL_IS_FULL "Channel is full"
#define ERR_CHANNEL_WRONG_PW "Wrong password provided"
#define ERR_CHANNEL_NO_PW "No password provided"
#define ERR_JOINING_NON_PW_CHANNEL_WITH_PW "Channel doesn't have password set, but password is provided"