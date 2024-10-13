/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestClient.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:45:26 by marvin            #+#    #+#             */
/*   Updated: 2024/10/13 20:11:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestClient.hpp"

RequestClient::RequestClient(std::string &req) : error(0)
{
	std::cout << req << std::endl;
	std::string line = req.substr(0, req.find("\n"));

	if (badSyntax(line) == 1)
	{
		this->badRequest();
		return;
	}
	if (badSyntax(line) == 2)
	{
		this->badVersion();
		return;
	}
	
	size_t	space = line.find(" ");
	this->addMethod(line.substr(0, space));
	if (this->error)
		return ;
	line.erase(0, space);
	while (isspace(line[0]))
		line.erase(0, 1);
	space = line.find(" ");
	this->filename = line.substr(0, space);

	req.erase(0, req.find("\n") + 1);
	line = req.substr(0, req.find("\n"));
	if (!addHost(line))
	{
		this->badRequest();
		return;
	}

	std::cout << "method :" + this->method + "." << std::endl;
	std::cout << "file :" + this->filename + "." << std::endl;
	std::cout << "host :" + this->host + "." << std::endl;
}

RequestClient::~RequestClient( void )
{}

std::string eraseSpace(std::string str)
{
	while(isspace(str[0]))
		str.erase(0, 1);
	return str;
}

int	RequestClient::badSyntax( std::string line )
{
	std::string tmp = line;
	tmp.erase(tmp.length() - 1);

	size_t	space = tmp.find(" ");
	if (space == std::string::npos || space == 0)
		return 1;
	tmp.erase(0, space);
	tmp = eraseSpace(tmp);

	if (tmp[0] != '/')
		return 1;
	space = tmp.find(" ");
	this->filename = tmp.substr(0, space);
	tmp.erase(0, space);
	tmp = eraseSpace(tmp);

	size_t	version = tmp.find("HTTP/");
	if (version == std::string::npos)
		return 1;
	tmp.erase(0, 5);

	if (tmp[0] != '1' && isdigit(tmp[0]))
		return 2;
	if (tmp.compare(0, 2, "1.") || tmp.length() != 3)
		return 1;
	if (!tmp.compare(0, 2, "1.") && !isdigit(tmp[2]))
		return 1;
	
	return 0;
}

void	RequestClient::addMethod( std::string arg)
{
	std::string allow_methods[4] = {"GET", "HEAD", "POST", "DELETE"};
	std::cout << arg << "." << std::endl;
	int i = 0;
	for (; i < 4; i++)
	{
		if (!arg.compare(allow_methods[i]))
		{
			this->method = arg;
			break;
		}
	}
	if (i == 4)
		this->notAllowed();
}

int	RequestClient::addHost( std::string arg )
{
	arg.erase(arg.length() - 1);
	size_t pos = arg.find(":");
	if (pos == std::string::npos)
		return 0;
	std::string h = arg.substr(0, pos);
	for(size_t i = 0; i < h.length(); i++)
		h[i] = std::tolower(h[i]);
	if (h.compare("host"))
		return 0;
	arg.erase(0, pos + 1);
	arg = eraseSpace(arg);
	std::cout << arg.length() << std::endl;
	std::cout << arg << std::endl;
	if (arg.empty())
		return 0;
	this->host = arg;
	return 1;
}

// Return errors

void	RequestClient::badVersion( void )
{
	this->error = 505;
	this->filename = "not_found/505.html";
}

void	RequestClient::badRequest( void )
{
	this->error = 400;
	this->filename = "not_found/400.html";
}

void	RequestClient::notAllowed( void )
{
	this->error = 405;
	this->filename = "not_found/405.html";
}


// Getters

int RequestClient::getError( void )
{
	return this->error;
}

std::string	RequestClient::getFilename( void )
{
	return this->filename;
}


// Setters

void	RequestClient::setFilename( std::string file )
{
	this->filename = file;
}

void	RequestClient::setError(int err)
{
	this->error = err;
}