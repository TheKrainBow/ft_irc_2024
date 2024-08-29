/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:19:18 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/29 16:34:19 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void Server::test()
{
	std::cout << CYAN << "Server" << WHITE << "::test()" << std::endl;
	{               // ADD USER
		std::cout << BWHITE << "🧪 Adding user for tests 🧪" << std::endl;
		addUser("Bob", "Bob_The_Builder");
		addUser("Tom", "Fantom0000");
		addUser("Mathieu", "Krain");
		addUser("Achille", "Biizox");
		addUser("Moumoune", "TheStupidOne");
		addUser("Nyraak", "TheFatOne");
		addUser("Henry", "Xx_H4nry_xX");
		addUser("Alice", "JobPass4Ever");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // JOIN CHANNELS
		std::cout << BWHITE << "🧪 Make user join new channel 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomeTestChannel");
		_users["Henry"]->joinChannel("SomeTestChannel");
		this->deleteChannel("SomeTestChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // INVITE USERS
		std::cout << BWHITE << "🧪 Invite Tests 🧪" << std::endl;
		_users["Moumoune"]->joinChannel("WeNeedFood");
		_users["Nyraak"]->joinChannel("WeNeedFood");
		_users["Moumoune"]->ChannelModeInvite("WeNeedFood", true);
		_users["Mathieu"]->joinChannel("WeNeedFood");
		_users["Nyraak"]->ChannelInviteUser("WeNeedFood", "Mathieu");
		_users["Mathieu"]->joinChannel("WeNeedFood");
		this->deleteChannel("WeNeedFood");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // LEAVE CHANNELS
		std::cout << BWHITE << "🧪 Leave tests 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomeFullChannel");
		_users["Mathieu"]->joinChannel("SomeFullChannel");
		_users["Bob"]->joinChannel("SomeEmptyChannel");
		_users["Mathieu"]->leaveChannel("SomeFullChannel");
		if (!_need_channel_cleanup.empty())
		{
			std::cout << "  " << YELLOW << _need_channel_cleanup << " is empty!" << std::endl << "  ";
			deleteChannel(_need_channel_cleanup);
		}
		_users["Bob"]->leaveChannel("SomeEmptyChannel");
		if (!_need_channel_cleanup.empty())
		{
			std::cout << "  " << YELLOW << _need_channel_cleanup << " is empty!" << std::endl << "  ";
			deleteChannel(_need_channel_cleanup);
		}
		this->deleteChannel("SomeFullChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // KICK USERS
		std::cout << BWHITE << "🧪 Kick tests 🧪" << std::endl;
		this->addChannel("SomeKickTestChannel");
		_users["Moumoune"]->joinChannel("SomeKickTestChannel");
		_users["Nyraak"]->joinChannel("SomeKickTestChannel");
		try
		{
			_users["Nyraak"]->ChannelKickUser("SomeKickTestChannel", "Moumoune");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Moumoune"]->ChannelKickUser("SomeKickTestChannel", "Nyraak");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Moumoune"]->ChannelKickUser("SomeKickTestChannel", "Unknown");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Moumoune"]->ChannelKickUser("SomeTestChannel", "Bob");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		this->deleteChannel("SomeKickTestChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // CHANGE TOPIC
		std::cout << BWHITE << "🧪 Topic tests 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomeTopicTestChannel");
		_users["Henry"]->joinChannel("SomeTopicTestChannel");
		try
		{
			_users["Henry"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some really normal user topic");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Bob"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some really op user topic");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Moumoune"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some really external user topic");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Henry"]->ChannelModeTopic("SomeTopicTestChannel", true);
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Henry"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some really normal user topic");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Bob"]->ChannelModeTopic("SomeTopicTestChannel", true);
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}	
		try
		{
			_users["Henry"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some forbidden normal user topic");
		}
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		try { _users["Bob"]->ChannelChangeTopic("SomeTopicTestChannel", "This is some op user topic"); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		this->deleteChannel("SomeTopicTestChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // PASSWORD TESTS
		std::cout << BWHITE << "🧪 Password tests 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomePasswordTestChannel");
		_users["Bob"]->ChannelModePassword("SomePasswordTestChannel", "1234");
		_users["Henry"]->joinChannel("SomePasswordTestChannel");
		_users["Henry"]->joinChannel("SomePasswordTestChannel", "123");
		try { _users["Henry"]->ChannelModePassword("SomePasswordTestChannel", "123"); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		_users["Henry"]->joinChannel("SomePasswordTestChannel", "1234");
		try { _users["Henry"]->ChannelModePassword("SomePasswordTestChannel", "123"); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		_users["Bob"]->ChannelModePassword("SomePasswordTestChannel", "");
		_users["Mathieu"]->joinChannel("SomePasswordTestChannel", "test");
		_users["Mathieu"]->joinChannel("SomePasswordTestChannel");
		this->deleteChannel("SomePasswordTestChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // LIMIT TESTS
		std::cout << BWHITE << "🧪 Limit tests 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomeLimitTestChannel");
		_users["Bob"]->ChannelModeLimit("SomeLimitTestChannel", 1);
		_users["Henry"]->joinChannel("SomeLimitTestChannel");
		_users["Bob"]->ChannelModeLimit("SomeLimitTestChannel", 0);
		_users["Henry"]->joinChannel("SomeLimitTestChannel");
		this->deleteChannel("SomeLimitTestChannel");
		std::cout << std::endl;
		std::cout << std::endl;
	}
	{               // OPERATOR TESTS
		std::cout << BWHITE << "🧪 Operators tests 🧪" << std::endl;
		_users["Bob"]->joinChannel("SomeOperatorsTestChannel");
		_users["Henry"]->joinChannel("SomeOperatorsTestChannel");
		try { _users["Henry"]->ChannelModeOps("SomeOperatorsTestChannel", "Henry", true); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		try { _users["Bob"]->ChannelModeOps("SomeOperatorsTestChannel", "Henry", true); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		try { _users["Bob"]->ChannelModeOps("SomeOperatorsTestChannel", "Henry", false); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		try { _users["Bob"]->ChannelModeOps("SomeOperatorsTestChannel", "Bob", false); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		try { _users["Bob"]->ChannelModeOps("SomeOperatorsTestChannel", "Henry", true); }
		catch(const std::exception& e)
		{
			std::cerr << BRED << "  Exception catched: " << RED << e.what() << std::endl;
		}
		this->deleteChannel("SomeOperatorsTestChannel");
	}
}