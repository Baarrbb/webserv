/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 22:03:34 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 01:17:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <arpa/inet.h>

// std::string	fileToSend(std::string request);
std::string	badRequest( std::string file );
std::string	reqResponse(RequestClient &req);
std::string	notAllowed( std::string file );
std::string	badVersion( std::string file);

int sockfd;

void handle_sigint(int sig) {
	std::cerr << "Caught signal " << sig << ", closing socket and exiting..." << std::endl;
	close(sockfd);
	exit(0);
}

int main(void)
{
	// int	sockfd;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		std::cerr << "ERROR1: " << strerror(errno) << std::endl;
		return 1;
	}

	 int opt = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		std::cerr << "ERROR: setsockopt failed: " << strerror(errno) << std::endl;
		close(sockfd);
		return 1;
	}

	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;

	std::cout << std::endl;
	if (bind(sockfd, (sockaddr *)&addr, (socklen_t)sizeof(addr)) == -1)
	{
		std::cerr << "ERROR2: " << strerror(errno) << std::endl;
		close(sockfd);
		return 1;
	}
	if (listen(sockfd, 1024) == -1)
	{
		std::cerr << "ERROR3: " << strerror(errno) << std::endl;
		close(sockfd);
		return 1;
	}

	signal(SIGINT, handle_sigint);

	while (1)
	{
		sockaddr_storage clientAddr;
		socklen_t clientAddrLen = sizeof(clientAddr);
		
		int newSock;
		if ((newSock = accept(sockfd, (sockaddr *)&clientAddr, &clientAddrLen)) == -1)
		{
			std::cerr << "ERROR4: " << strerror(errno) << std::endl;
			close(sockfd);
			return 1;
		}

		int valread;
		char buffer[30000] = {0};
		std::string reqString;
		bool keepAlive = false;
		while (1)
		{
			valread = recv(newSock, buffer, 30000, 0);
			if (valread > 0)
			{
				std::string bufString(buffer, 30000);
				// reqString.append(buffer, bufString.find("\n") + 1);
				reqString.append(buffer, valread);
				std::cout << reqString << std::endl;
				if (reqString.find_first_not_of("\r\n") == std::string::npos)
				{
					reqString.clear();
					continue;
				}

				if (reqString.find("\r\n\r\n") != std::string::npos
					|| reqString.find("\n\n") != std::string::npos)
				{
					RequestClient	req(reqString);
					std::string		response;
					if (req.getError() == 400)
						response = badRequest( req.getTarget() );
					else if (req.getError() == 405)
						response = notAllowed( req.getTarget() );
					else if (req.getError() == 505)
						response = badVersion( req.getTarget() );
					else
						response = reqResponse(req);
					
					if (response.find("keep-alive") != std::string::npos)
						keepAlive = true;
					else
						keepAlive = false;

					std::cout << response << std::endl;
					send(newSock, response.c_str(), response.length(), 0);

					if (keepAlive)
						reqString.clear();
					else
						break ;
				}
			}
		}

		close(newSock);
	}
	close(sockfd);
	return 0;
}

std::string	getLengthFile(std::string file)
{
	std::ifstream fileStream(file.c_str());
	std::ostringstream fileContentStream;
	fileContentStream <<  fileStream.rdbuf();
	std::string fileContent = fileContentStream.str();

	std::string	headerLength;
	std::ostringstream lengthStream;
	lengthStream << fileContent.length();
	headerLength = "Content-Length: " + lengthStream.str() + "\r\n";

	return headerLength;
}

std::string	badVersion( std::string file)
{
	std::ifstream	fileStream(file.c_str());
	std::string		mimeType = "Content-Type: text/html\r\n";
	std::string		reqResponse = "HTTP/1.1 505 HTTP Version Not Supported\r\n";
	std::string		connectionStatus = "Connection: close\r\n";

	reqResponse += mimeType;

	std::ostringstream fileContentStream;
	fileContentStream <<  fileStream.rdbuf();
	std::string fileContent = fileContentStream.str();

	reqResponse += getLengthFile(file);
	reqResponse += connectionStatus;
	reqResponse += "\r\n";
	reqResponse += fileContent;

	return reqResponse;
}

std::string	badRequest( std::string file )
{
	std::ifstream	fileStream(file.c_str());
	std::string		mimeType = "Content-Type: text/html\r\n";
	std::string		reqResponse = "HTTP/1.1 400 Bad Request\r\n";
	std::string		connectionStatus = "Connection: close\r\n";

	reqResponse += mimeType;

	std::ostringstream fileContentStream;
	fileContentStream <<  fileStream.rdbuf();
	std::string fileContent = fileContentStream.str();

	reqResponse += getLengthFile(file);
	reqResponse += connectionStatus;
	reqResponse += "\r\n";
	reqResponse += fileContent;

	return reqResponse;
}

std::string	notAllowed( std::string file )
{
	std::ifstream	fileStream(file.c_str());
	std::string		mimeType = "Content-Type: text/html\r\n";
	std::string		reqResponse = "HTTP/1.1 405 Not Allowed\r\n";
	std::string		connectionStatus = "Connection: keep-alive\r\n";

	reqResponse += mimeType;

	std::ostringstream fileContentStream;
	fileContentStream <<  fileStream.rdbuf();
	std::string fileContent = fileContentStream.str();

	reqResponse += getLengthFile(file);
	reqResponse += connectionStatus;
	reqResponse += "\r\n";
	reqResponse += fileContent;

	return reqResponse;
}

std::string	reqResponse(RequestClient &req)
{
	std::string	mimeType;
	std::string	connectionStatus = "Connection: keep-alive\r\n";
	std::string	reqResponse = "HTTP/1.1 ";
	std::string	filename = req.getTarget();

	std::ifstream fileStream(filename.c_str());
	if (!fileStream.is_open())
	{
		req.setError(404);
		req.setTarget("not_found/404.html");
		filename = req.getTarget();
		fileStream.open(filename.c_str());
	}

	std::string ext = filename.substr(filename.find(".") + 1, filename.length() - filename.find("."));
	if (!ext.compare("html"))
		mimeType = "Content-Type: text/html\r\n";
	if (!ext.compare("css"))
		mimeType = "Content-Type: text/css\r\n";
	if (!ext.compare("js"))
		mimeType = "Content-Type: application/javascript\r\n";
	if (!ext.compare("json"))
		mimeType = "Content-Type: application/json\r\n";
	if (!ext.compare("png"))
		mimeType = "Content-Type: image/png\r\n";

	if (!req.getError())
		reqResponse.append("200 OK\r\n");
	else if (req.getError() == 404)
		reqResponse.append("404 JSPLUS\r\n");
		
	reqResponse += mimeType;

	std::ostringstream fileContentStream;
	fileContentStream <<  fileStream.rdbuf();
	std::string fileContent = fileContentStream.str();

	reqResponse += getLengthFile(filename);
	reqResponse += connectionStatus;
	reqResponse += "\r\n";
	reqResponse += fileContent;

	return reqResponse;
}


// std::string	fileToSend(std::string request)
// {
// 	std::string	file;
// 	std::cout << request << std::endl;
// 	std::istringstream reqStream(request);
// 	std::string line;
// 	std::getline(reqStream, line);
// 	int	root = line.find("/");
// 	int	http = line.find("HTTP");
// 	file = request.substr(root, http - root - 1);
// 	std::ifstream htmlFile;
// 	std::string mimeType;
// 	std::string resultPHP;
// 	if (!file.compare("/"))
// 	{
// 		htmlFile.open("./www/index.html");
// 		// htmlFile.open("./public/index.html");
// 		mimeType = "Content-Type: text/html\r\n";
// 	}
// 	else
// 	{
// 		std::string rootPath = "./www";
// 		// std::string rootPath = "./public";
// 		std::string path = rootPath.append(file);
// 		htmlFile.open(path.c_str());
// 		std::string ext = file.substr(file.find(".") + 1, file.length() - file.find("."));
// 		// if (!htmlFile.is_open())
// 		// 	htmlFile.open("./not_found/404.html");
// 		if (!ext.compare("css"))
// 			mimeType = "Content-Type: text/css\r\n";
// 		if (!ext.compare("js"))
// 			mimeType = "Content-Type: application/javascript\r\n";
// 		if (!ext.compare("json"))
// 			mimeType = "Content-Type: application/json\r\n";
// 		if (!ext.compare("png"))
// 			mimeType = "Content-Type: image/png\r\n";
// 		if (!ext.compare("php"))
// 		{
// 			int fd[2];
// 			if (pipe(fd) == -1)
// 				std::cerr << "PB" << std::endl;
// 			pid_t pid = fork();
// 			if (pid == -1)
// 				std::cerr << "PB2" << std::endl;
// 			if (pid == 0)
// 			{
// 				close(fd[0]);
// 				dup2(fd[1], STDOUT_FILENO);
// 				close(fd[1]);
// 				const char *phpExec = "/usr/bin/php";
// 				const char *phpFile = path.c_str();
// 				const char *args[] = {phpExec, phpFile, 0};
// 				execve(phpExec, const_cast<char* const*>(args), 0);
// 			}
// 			else
// 			{
// 				close(fd[1]);
// 				char buffer[4096];
// 				ssize_t bytesRead;
// 				while ((bytesRead = read(fd[0], buffer, sizeof(buffer))) > 0) {
// 					resultPHP.append(buffer, bytesRead);
// 				}
// 				close(fd[0]);
// 				int status;
// 				waitpid(pid, &status, 0);
// 			}
// 		}
// 	}
// 	if (!htmlFile.is_open())
// 	{
// 		htmlFile.open("./not_found/404.html");
// 	}
// 	std::stringstream htmlStream;
// 	if (!resultPHP.empty())
// 		htmlStream << resultPHP;
// 	else
// 		htmlStream << htmlFile.rdbuf();
// 	std::string htmlContent = htmlStream.str();
// 	std::string httpResponse = "HTTP/1.1 200 OK\r\n";
// 	httpResponse += mimeType;
// 	std::ostringstream lengthStream;
// 	lengthStream << htmlContent.length();
// 	httpResponse += "Content-Length: " + lengthStream.str() + "\r\n";
// 	httpResponse += "\r\n";
// 	httpResponse += htmlContent;
// 	return httpResponse;
// }
