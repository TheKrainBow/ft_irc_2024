/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:37:12 by maagosti          #+#    #+#             */
/*   Updated: 2024/09/01 15:57:20 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>
#include <cstdlib>
#include "color.hpp"

int main(int ac, char **av)
{
	if (ac < 3)
	{
		std::cerr << BRED << "Error: " << RED << "ircserv is missing some arguments" << std::endl;
		std::cerr << BRED << "Correct usage: " << RED << "./ircserv <port> <password>" << WHITE << std::endl;
		return (1);
	}
	if (ac > 3)
		std::cerr << BYELLOW << "ircserv has too many arguments."<< YELLOW <<  " Arguments `" << av[3] << "` and any following arguments won't be handled." << WHITE  << std::endl;
	
	Server server(atoi(av[1]), std::string(av[2]));
	//server.test();
	//server.cleanup();
	server.start();
}