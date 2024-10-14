/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestClient.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:45:26 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 01:21:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestClient.hpp"

void	printOptions(std::map<std::string, std::string> options);

// PRENDRE LE PARSING DE CONFIG ET COMPARER METHODS ACCEPTE
// EN FONCTION DE LA LOC AUSSI (JPP)
// SI PAS ACCEPTE RENVOYER ERREUR 403
// AVANT DE CHECK SI METHOD EXIST (DONC AVANT ERREUR 405 NOT ALLOWED)

RequestClient::RequestClient(std::string &req) : error(0)
{
	req.erase(req.length() - 1);
	std::string line = req.substr(0, req.find("\n"));

	try
	{
		this->badSyntax(line);

		size_t	space = line.find(" ");
		this->addMethod(line.substr(0, space));

		req.erase(0, req.find("\n") + 1);
		if (req.length() == 1 && (req[0] == '\n' || req[0] == '\r'))
			throw RequestClient::ErrorRequest(400, "not_found/400.html");

		this->othersOptions(req);
		// printOptions(this->options);

		this->addHost();
	}
	catch(RequestClient::ErrorRequest &e)
	{
		this->error = e.getError();
		this->target = e.getTarget();
		return ;
	}

	std::cout << "method :" + this->method + "." << std::endl;
	std::cout << "file :" + this->target + "." << std::endl;
}

RequestClient::~RequestClient( void )
{}

std::string	eraseSpace(std::string str)
{
	while(str[0] == ' ')
		str.erase(0, 1);
	return str;
}

std::string eraseSpaceAtTheEnd(std::string str)
{
	std::string::iterator it = str.end();
	while(it != str.begin() && isspace(*(it - 1)))
		--it;
	str.erase(it, str.end());
	return str;
}

// std::string	eraseAllSpace(std::string str)
// {
// 	while(isspace(str[0]))
// 		str.erase(0, 1);
// 	return str;
// }

int	checkUpCase(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isupper(str[i]))
			return 0;
	}
	return 1;
}

int	spaceInside( std::string &str )
{
	if (str.find(" ") != std::string::npos || str.find("\t") != std::string::npos)
		return 1;
	return 0;
}

void	RequestClient::badSyntax( std::string line )
{
	std::string tmp = line;
	tmp.erase(tmp.length() - 1);

	size_t		space = tmp.find(" ");
	std::string	method = tmp.substr(0, space);
	if (!checkUpCase(method) || space == std::string::npos || space == 0)
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
	tmp.erase(0, space);
	tmp = eraseSpace(tmp);
	if (tmp[0] != '/' && tmp.find("http://", 0, 7) == std::string::npos)
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
	space = tmp.find(" ");
	if (!this->addTarget(tmp.substr(0, space)))
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
	tmp.erase(0, space);
	tmp = eraseSpace(tmp);
	size_t	version = tmp.find("HTTP/");
	if (version == std::string::npos)
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
	tmp.erase(0, 5);
	space = tmp.find_last_not_of(' ');
	if (space != std::string::npos)
		tmp = tmp.substr(0, space + 1);
	if (tmp.find("\t") != std::string::npos)
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
	if (tmp[0] != '1' && isdigit(tmp[0]))
		throw RequestClient::ErrorRequest(505, "not_found/505.html");
	if (tmp.compare(0, 2, "1.") || tmp.length() != 3)
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
	if (!tmp.compare(0, 2, "1.") && !isdigit(tmp[2]))
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
}

void	RequestClient::addMethod( std::string arg)
{
	std::string allow_methods[4] = {"GET", "HEAD", "POST", "DELETE"};
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
		throw RequestClient::ErrorRequest(405, "not_found/405.html");
}

int	RequestClient::addTarget( std::string arg )
{
	size_t	delim;
	this->target = arg;
	if (arg[0] == '/')
	{
		this->target = arg;
		return 1;
	}
	arg.erase(0, 7);
	if (arg.empty() || arg[0] == '/')
		return 0;
	delim = arg.find("/");
	if (delim == std::string::npos)
		this->target = "/";
	else
		this->target = arg.substr(delim, arg.length());
	return 1;
}

void	RequestClient::addOptions( std::string line )
{
	std::string	name;
	std::string	val;

	size_t pos = line.find(":");
	if (pos == std::string::npos)
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
	name = line.substr(0, pos);
	if (spaceInside(name))
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
	for(size_t i = 0; i < name.length(); i++)
		name[i] = std::tolower(name[i]);
	line.erase(0, pos + 1);
	// line = eraseAllSpace(line);
	line = eraseSpace(line);
	if (line.empty()) // est ce que si il ya des tab je considere faux ?? nginx non
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
	line = eraseSpaceAtTheEnd(line);
	val = line;
	if (!val.compare("host") && checkIfHost())
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
	this->options.insert(std::make_pair(name, val));
}

int	RequestClient::checkIfHost( void )
{
	std::map<std::string, std::string>::const_iterator	it = this->options.find("host");

	if (it != this->options.end())
		return 1;
	return 0;
}

void	RequestClient::addHost( void )
{
	std::map<std::string, std::string>::const_iterator	it = this->options.find("host");
	
	if (it != this->options.end() && !it->second.empty() && it->second.find("\t") == std::string::npos)
		this->host = it->second;
	else
		throw RequestClient::ErrorRequest(400, "not_found/400.html");
}

void	RequestClient::othersOptions( std::string next )
{
	next.erase(next.length() - 1);
	while (!next.empty())
	{
		try
		{
			this->addOptions(next.substr(0, next.find("\n")));
		}
		catch(RequestClient::ErrorRequest &e)
		{
			this->error = e.getError();
			this->target = e.getTarget();
			return ;
		}
		next.erase(0, next.find("\n") + 1);
	}
}

// Return errors

// void	RequestClient::badVersion( void )
// {
// 	this->error = 505;
// 	this->target = "not_found/505.html";
// }

// void	RequestClient::badRequest( void )
// {
// 	this->error = 400;
// 	this->target = "not_found/400.html";
// }

// void	RequestClient::notAllowed( void )
// {
// 	this->error = 405;
// 	this->target = "not_found/405.html";
// }

// void RequestClient::forbidden( void )
// {
// 	this->error = 403;
// 	this->target = "not_found/403.html";
// }

// Getters

int RequestClient::getError( void )
{
	return this->error;
}

std::string	RequestClient::getTarget( void )
{
	return this->target;
}


// Setters

void	RequestClient::setTarget( std::string file )
{
	this->target = file;
}

void	RequestClient::setError(int err)
{
	this->error = err;
}


// A SUPP

void	printOptions(std::map<std::string, std::string> options)
{
	for (std::map<std::string, std::string>::iterator it = options.begin(); it != options.end(); ++it)
	{
		std::cout << it->first << " = " << it->second << std::endl;
	}
}
