/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:37:12 by maagosti          #+#    #+#             */
/*   Updated: 2024/08/18 21:47:17 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCServer.hpp"
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
	
	IRCServer server(atoi(av[1]), std::string(av[2]));
	server.start();
}