## Functions

```C
struct sockaddr {
	sa_family_t	sa_family;      /* Address family */
	char		sa_data[];      /* Socket address */
};
```

```C
struct addrinfo {
	int				ai_flags;
	int				ai_family;
	int				ai_socktype;
	int				ai_protocol;
	socklen_t		ai_addrlen;
	struct sockaddr *ai_addr;
	char			*ai_canonname;
	struct addrinfo *ai_next;
};
```

```C
int getaddrinfo(const char *node, const char *service,
				const struct addrinfo *hints,
				struct addrinfo **res);
```

Given *node* and *service*, which identify an Internet host and a service, `getaddrinfo()` returns one or more *addrinfo* structures, each of which contains an Internet address that can be specified in a call to `bind()` or `connect()`.

```C
void freeaddrinfo(struct addrinfo *res);
```

```C
const char *gai_strerror(int errcode);
```

[Man getaddrinfo, freeaddrinfo, gai_strerror](https://www.man7.org/linux/man-pages/man3/getaddrinfo.3.html)
<br>
<br>

```C
int socket(int domain, int type, int protocol);
```

`socket()` creates an endpoint for communication and returns a file descriptor that refers to that endpoint.

[Man socket](https://www.man7.org/linux/man-pages/man2/socket.2.html)
<br>
<br>

```C
int bind(int sockfd, const struct sockaddr *addr,
		 socklen_t addrlen);
```
When a socket is created with `socket()`, it exists in a name space (address family) but has no address assigned to it. `bind()` assigns the address specified by *addr* to the socket referred to by the file descriptor *sockfd*.

[Man bind](https://www.man7.org/linux/man-pages/man2/bind.2.html)


```C
int connect(int sockfd, const struct sockaddr *addr,
			socklen_t addrlen);
```
The `connect()` system call connects the socket referred to by the file descriptor *sockfd* to the address specified by *addr*.

[Man connect](https://www.man7.org/linux/man-pages/man2/connect.2.html)
<br>
<br>


```C
int socketpair(int domain, int type, int protocol, int sv[2]);
```
The `socketpair()` call creates an unnamed pair of connected sockets in the specified *domain*, of the specified *type*, and using the optionally specified *protocol*.

[Man socketpair](https://www.man7.org/linux/man-pages/man2/socketpair.2.html)
<br>
<br>

```C
int setsockopt(int socket, int level, int option_name,
				const void *option_value, socklen_t option_len);
```
The `setsockopt()` function shall set the option specified by the *option_name* argument, at the protocol level specified by the *level* argument, to the value pointed to by the *option_value* argument for the socket associated with the file descriptor specified by the *socket* argument.

[Man setsockopt](https://www.man7.org/linux/man-pages/man3/setsockopt.3p.html)
<br>
<br>

```C
int getsockname(int sockfd, struct sockaddr *restrict addr,
				socklen_t *restrict addrlen);
```
`getsockname()` returns the current address to which the socket *sockfd* is bound, in the buffer pointed to by *addr*. The *addrlen* argument should be initialized to indicate the amount of space (in bytes) pointed to by *addr*. On return it contains the actual size of the socket address.

[Man getsockname](https://www.man7.org/linux/man-pages/man2/getsockname.2.html)
<br>
<br>

```C
struct protoent *getprotobyname(const char *name);
```
`getprotobyname()` returns a protoent structure for the entry from the database that matches the protocol name *name*. A connection is opened to the database if necessary.

Shall return a pointer to a `protoent` structure, the members of which shall contain the fields of an entry in the network protocol database.

```C
struct protoent {
	char	*p_name;       /* official protocol name */
	char	**p_aliases;    /* alias list */
	int		p_proto;      /* protocol number */
};
```


[Man getprotobyname](https://www.man7.org/linux/man-pages/man3/endprotoent.3p.html)

[Man getprotoent](https://www.man7.org/linux/man-pages/man3/getprotoent.3.html)
<br>
<br>


<details>
	<summary>select()</summary>

```C
int select(int nfds, fd_set *_Nullable restrict readfds,
			fd_set *_Nullable restrict writefds,
			fd_set *_Nullable restrict exceptfds,
			struct timeval *_Nullable restrict timeout);
```
WARNING: select() can monitor only file descriptors numbers that are less than FD_SETSIZE (1024)—an unreasonably low limit for many modern applications—and this limitation will not change. All modern applications should instead use `poll()` or `epoll()`, which do not suffer this limitation.

[Man select](https://www.man7.org/linux/man-pages/man2/select.2.html)
</details>

<br>


```C
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

`poll()` waits for one of a set of file descriptors to become ready to perform I/O.

The set of file descriptors to be monitored is specified in the fds argument, which is an array of structures of the following form:

```C
struct pollfd {
	int		fd;         /* file descriptor */
	short	events;     /* requested events */
	short	revents;    /* returned events */
};
```



#### epoll

`epoll` monitoring multiple file descriptors to see if I/O is possible on any of them.  The `epoll` API can be used either as an edge-triggered or a level-triggered interface and scales well to large numbers of watched file descriptors.

[Man epoll](https://www.man7.org/linux/man-pages/man7/epoll.7.html)

```C
int epoll_create(int size);
```

`epoll_create()` creates a new *epoll* instance.

`epoll_create()` returns a file descriptor referring to the new *epoll* instance.  This file descriptor is used for all the subsequent calls to the *epoll* interface.

[Man epoll_create](https://www.man7.org/linux/man-pages/man2/epoll_create.2.html)

```C
int epoll_ctl(int epfd, int op, int fd,
				struct epoll_event *_Nullable event);
```

This system call is used to add, modify, or remove entries in the interest list of the *epoll* instance referred to by the file descriptor *epfd*.  It requests that the operation *op* be performed for the target file descriptor, *fd*.

[Man epoll_ctl](https://www.man7.org/linux/man-pages/man2/epoll_ctl.2.html)

```C
int epoll_wait(int epfd, struct epoll_event *events,
				int maxevents, int timeout);
```

The `epoll_wait()` system call waits for events on the *epoll* instance referred to by the file descriptor *epfd*. The buffer pointed to by *events* is used to return information from the ready list about file descriptors in the interest list that have some events available.  Up to *maxevents* are returned by `epoll_wait()`. The *maxevents* argument must be greater than zero.

[Man epoll_wait()](https://www.man7.org/linux/man-pages/man2/epoll_wait.2.html)

<br>
<br>

```C
int kevent(int kq, const struct kevent *changelist, int nchanges,
			struct kevent *eventlist, int nevents,
			const struct timespec *timeout);
```
`kevent()` is used to register events with the queue, and return any pending events to the user.

```C
int kqueue(void);
```
`kqueue()` provides a generic method of notifying the user when an event happens or a condition holds, based on the results of small pieces of kernel code termed “filters”.

`kqueue()` creates a new kernel event queue and returns a descriptor.

```C
struct kevent {
	uintptr_t	ident;	/* identifier for this event */
	short		filter;	/* filter for event */
	u_short		flags;	/* action flags for kqueue */
	u_int		fflags;	/* filter flag value */
	int64_t		data;	/* filter data value */
	void		*udata;	/* opaque user data identifier */
};
```

[Man kevent, kqueue](https://man.openbsd.org/kqueue.2)
<br><br>

```C
int accept(int sockfd, struct sockaddr *_Nullable restrict addr,
			socklen_t *_Nullable restrict addrlen);
```
The `accept()` system call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET).  It extracts the first connection request on the queue of pending connections for the listening socket, *sockfd*, creates a new connected socket, and returns a new file descriptor referring to that socket.  The newly created socket is not in the listening state.  The original socket *sockfd* is unaffected by this call.

[Man accpect](https://www.man7.org/linux/man-pages/man2/accept.2.html)
<br><br>

```C
int listen(int sockfd, int backlog);
```

`listen()` marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept incoming connection requests using `accept()`.

[Man listen](https://www.man7.org/linux/man-pages/man2/listen.2.html)
<br><br>

```C
ssize_t send(int sockfd, const void buf[.len], size_t len, int flags);
```
 The system calls `send()` is used to transmit a message to another socket.

[Man send](https://www.man7.org/linux/man-pages/man2/send.2.html)
<br><br>

```C
ssize_t recv(int sockfd, void buf[.len], size_t len,
			 int flags);
```

The `recv()` calls is used to receive messages from a socket.  They may be used to receive data on both connectionless and connection-oriented sockets.

[Man recv](https://www.man7.org/linux/man-pages/man2/recv.2.html)
<br><br>

```C
int fcntl(int fd, int op, ... /* arg */ );
```

`fcntl()` performs one of the operations described below on the open file descriptor *fd*. The operation is determined by *op*.

[Man fctnl](https://www.man7.org/linux/man-pages/man2/fcntl.2.html)
<br><br>

```C
uint16_t htons(uint16_t hostshort);
```

```C
uint32_t htonl(uint32_t hostlong);
```

```C
uint16_t ntohs(uint16_t netshort);
```

```C
uint32_t ntohl(uint32_t netlong);
```

The `htonl()` and `htons()` functions shall return the argument value converted from host to network byte order.

The `ntohl()` and `ntohs()` functions shall return the argument value converted from network to host byte order.
