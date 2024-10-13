/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestClient.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:41:14 by marvin            #+#    #+#             */
/*   Updated: 2024/10/13 19:54:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTCLIENT_HPP
#define REQUESTCLIENT_HPP

#include "Server.hpp"

class RequestClient
{
	public:
		RequestClient(std::string &);
		~RequestClient( void );

		int			badSyntax( std::string line );
		void		badRequest( void );
		void		notAllowed( void );
		void		badVersion( void );


		std::string	getFilename( void );
		int			getError( void );

		void		setFilename(std::string);
		void		setError(int);

	private:
		RequestClient( void );
		void	addMethod( std::string arg);
		int		addHost( std::string arg );

		int				error;
		std::string		method;
		std::string		filename;
		std::string		host;

		std::string		connection;
	
};

#endif