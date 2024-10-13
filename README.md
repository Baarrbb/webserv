
## Subject

[FR subject](https://cdn.intra.42.fr/pdf/pdf/140050/fr.subject.pdf)

[EN subject](https://cdn.intra.42.fr/pdf/pdf/140049/en.subject.pdf)




## Telnet

`telnet <host> <port>`

```
GET <path> HTTP/1.1
Host: <host>
```

## RFC

[HTTP Semantics](https://datatracker.ietf.org/doc/html/rfc9110)

[HTPP Caching](https://datatracker.ietf.org/doc/html/rfc9111)

[HTTP/1.1](https://datatracker.ietf.org/doc/html/rfc9112)

[The Common Gateway Interface (CGI) v1.1](https://datatracker.ietf.org/doc/html/rfc3875)


## Others ressources

[Understanding Nginx Server and Location Block Selection Algorithms](https://www.digitalocean.com/community/tutorials/understanding-nginx-server-and-location-block-selection-algorithms)

[GitHub nginx](https://github.com/nginx/nginx)

[HTTP](https://http.dev/)

[Socket in computer network](https://www.geeksforgeeks.org/socket-in-computer-network/)

[Socket programming in c++](https://www.geeksforgeeks.org/socket-programming-in-cpp/)

[Github http_server in C](https://github.com/Dungyichao/http_server)

[FreeBSD sockets essentials functions](https://docs.freebsd.org/en/books/developers-handbook/sockets/#sockets-essential-functions)

[Mime type](https://developer.mozilla.org/en-US/docs/Web/HTTP/MIME_types/Common_types)

[client serve model](https://www.linuxhowtos.org/C_C++/socket.htm)

## Nginx HEAD

```
HEAD / HTTP/1.1
Host: localhost

HTTP/1.1 200 OK
Server: nginx/1.22.1
Date: Tue, 08 Oct 2024 13:26:33 GMT
Content-Type: text/html
Content-Length: 2030
Last-Modified: Tue, 08 Oct 2024 13:15:57 GMT
Connection: keep-alive
ETag: "6705308d-7ee"
Accept-Ranges: bytes
```


## Exemple nginx log

```
172.18.0.1 - - [09/Oct/2024:13:46:47 +0000] "GET / HTTP/1.1" 200 2030 "-" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:46:47 +0000] "GET /style.css HTTP/1.1" 200 1841 "http://localhost/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:46:47 +0000] "GET /map.js HTTP/1.1" 200 3579 "http://localhost/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:46:47 +0000] "GET /stats.js HTTP/1.1" 200 5359 "http://localhost/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:46:47 +0000] "GET /campus.json HTTP/1.1" 200 7323 "http://localhost/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:46:47 +0000] "GET /campus.json HTTP/1.1" 200 7323 "http://localhost/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:46:47 +0000] "GET /campus.json HTTP/1.1" 200 7323 "http://localhost/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:46:47 +0000] "GET /images//mark_42.png HTTP/1.1" 200 815 "http://localhost/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:46:48 +0000] "GET /images/42_Logo.png HTTP/1.1" 200 974 "http://localhost/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:46:53 +0000] "GET / HTTP/1.1" 200 2030 "-" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:46:54 +0000] "GET / HTTP/1.1" 304 0 "-" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:47:07 +0000] "GET / HTTP/1.1" 200 2030 "-" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:47:10 +0000] "GET / HTTP/1.1" 200 2030 "-" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:47:10 +0000] "GET /style.css HTTP/1.1" 200 1841 "http://bsuc.42.fr/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:47:10 +0000] "GET /map.js HTTP/1.1" 200 3579 "http://bsuc.42.fr/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:47:10 +0000] "GET /stats.js HTTP/1.1" 200 5359 "http://bsuc.42.fr/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:47:10 +0000] "GET /campus.json HTTP/1.1" 200 7323 "http://bsuc.42.fr/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:47:10 +0000] "GET /campus.json HTTP/1.1" 200 7323 "http://bsuc.42.fr/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:47:10 +0000] "GET /campus.json HTTP/1.1" 200 7323 "http://bsuc.42.fr/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:47:10 +0000] "GET /images//mark_42.png HTTP/1.1" 200 815 "http://bsuc.42.fr/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
172.18.0.1 - - [09/Oct/2024:13:47:10 +0000] "GET /images/42_Logo.png HTTP/1.1" 200 974 "http://bsuc.42.fr/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0"
```


Connexion avec curl puis telnet

```
172.18.0.1 - - [09/Oct/2024:13:48:49 +0000] "GET / HTTP/1.1" 200 2030 "-" "curl/7.81.0"
172.18.0.1 - - [09/Oct/2024:13:49:16 +0000] "HEAD / HTTP/1.1" 200 0 "-" "-"
172.18.0.1 - - [09/Oct/2024:13:49:43 +0000] "GET / HTTP/1.1" 200 2030 "-" "-"
172.18.0.1 - - [09/Oct/2024:13:50:12 +0000] "GET / HTTP/1.1" 200 2030 "-" "-"
172.18.0.1 - - [09/Oct/2024:13:50:28 +0000] "GET / HTTP/1.1" 200 2030 "-" "-"
```

## Notes

Each socket has a specific address. This address is composed of an IP address and a port number.

The server creates a socket, attaches it to a network port addresses then waits for the client to contact it. The client creates a socket and then attempts to connect to the server socket. When connection is established, transfer of data takes place.

<br>

Server keep listening any message it received, then need to analyse what the useful information in the message by parsing it. The useful informaition is : the filne name (with path) and file extension. Open file according to the path and put the content of the file into a reply-message which we will late send to the client. Before sending the reply-message, we should first tell the client what kind of file content we are goind to send (MIME types). Then we can send tje reply-message to the client.

<br>

#### Code structure

1. Create socket and identify
2. Listen incoming message
3. Parse the message
4. According to parse result
	- Client ask for index.html
		- reply index.html
			1. tell client what the file type
			2. Open the file and read content
			3. Get the info of the file
			4. while(not finish){send part of the content}
	- Client ask for image
		- reply .jpg file
	- Client ask for ico
		- reply .png file
	- Client ask for font
		- reply .ttf file
	- Client ask for js
		- reply .js file
	- Client ask for css
		- reply .css file
	- ...
	- Else
		- reply .txt file
5. Close socket



## TO DO

 - Parser requete entrante

Format minimun avec :
```
GET <path> HTTP/1.1
Host: <name>
```

-> sinon 400 Bad request

 - Format sortie

same shit


Simuler plusieurs clients
```
for i in {1..1000}; do
    curl -s http://127.0.0.1:8080/ &
done
wait
```

```
GET 
HEAD
POST
DELETE
```


## Requests

#### Request depuis mozilla 

```
GET / HTTP/1.1
Host: localhost:8080
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:131.0) Gecko/20100101 Firefox/131.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/png,image/svg+xml,*/*;q=0.8
Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3
Accept-Encoding: gzip, deflate, br, zstd
DNT: 1
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: none
Sec-Fetch-User: ?1
Sec-GPC: 1
Priority: u=0, i
```


#### Request depuis curl

```
GET / HTTP/1.1
Host: localhost:8080
User-Agent: curl/7.81.0
Accept: */*
```

#### Request depuis telnet

Pas bon doit parser avec 2 \n\n

minimum `Host:`

```
GET / HTTP/1.1
```

A revoir actuellement comme ca pcq serveur pas bien implementé.

#### Example from ietf

```
Client request:

GET /hello.txt HTTP/1.1
User-Agent: curl/7.64.1
Host: www.example.com
Accept-Language: en, mi

Server response:

HTTP/1.1 200 OK
Date: Mon, 27 Jul 2009 12:28:53 GMT
Server: Apache
Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT
ETag: "34aa387-d-1568eb00"
Accept-Ranges: bytes
Content-Length: 51
Vary: Accept-Encoding
Content-Type: text/plain

Hello World! My content includes a trailing CRLF.

```

## Notes from ietf HTTP/1.1

The scheme and host are case-insensitive and normally provided in lowercase; all other components are compared in a case-sensitive manner.

Characters other than those in the "reserved" set are equivalent to their percent-encoded octets: the normal form is to not encode them

For example, the following three URIs are equivalent:

```
   http://example.com:80/~smith/home.html
   http://EXAMPLE.com/%7Esmith/home.html
   http://EXAMPLE.com:/%7esmith/home.html
```

Two HTTP URIs that are equivalent after normalization (using any method) can be assumed to identify the same resource, and any HTTP component MAY perform normalization. As a result, distinct resources SHOULD NOT be identified by HTTP URIs that are equivalent after normalization

#

The "origin" for a given URI is the triple of scheme, host, and port after normalizing the scheme and host to lowercase and normalizing the port to remove any leading zeros. If port is elided from the URI, the default port for that scheme is used. For example, the URI

   `https://Example.Com/happy.js`

would have the origin

   `{ "https", "example.com", "443" }`

which can also be described as the normalized URI prefix with port always present:

   `https://example.com:443`

Each origin defines its own namespace and controls how identifiers within that namespace are mapped to resources. In turn, how the origin responds to valid requests, consistently over time, determines the semantics that users will associate with a URI, and the usefulness of those semantics is what ultimately transforms these mechanisms into a resource for users to reference and access in the future.

Two origins are distinct if they differ in scheme, host, or port. Even when it can be verified that the same entity controls two distinct origins, the two namespaces under those origins are distinct unless explicitly aliased by a server authoritative for that origin.


##

Tokens are short textual identifiers that do not include whitespace or delimiters.

```
  token          = 1*tchar

  tchar          = "!" / "#" / "$" / "%" / "&" / "'" / "*"
                 / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~"
                 / DIGIT / ALPHA
                 ; any VCHAR, except delimiters
```

Many HTTP field values are defined using common syntax components, separated by whitespace or specific delimiting characters. Delimiters are chosen from the set of US-ASCII visual characters not allowed in a token (DQUOTE and "(),/:;<=>?@[\]{}").


##

### Whitespace

This specification uses three rules to denote the use of linear whitespace: OWS (optional whitespace), RWS (required whitespace), and BWS ("bad" whitespace).

The OWS rule is used where zero or more linear whitespace octets might appear. For protocol elements where optional whitespace is preferred to improve readability, a sender SHOULD generate the optional whitespace as a single SP; otherwise, a sender SHOULD NOT generate optional whitespace except as needed to overwrite invalid or unwanted protocol elements during in-place message filtering.

The RWS rule is used when at least one linear whitespace octet is required to separate field tokens. A sender SHOULD generate RWS as a single SP.

OWS and RWS have the same semantics as a single SP. Any content known to be defined as OWS or RWS MAY be replaced with a single SP before interpreting it or forwarding the message downstream.

The BWS rule is used where the grammar allows optional whitespace only for historical reasons. A sender MUST NOT generate BWS in messages. A recipient MUST parse for such bad whitespace and remove it before interpreting the protocol element.

BWS has no semantics. Any content known to be defined as BWS MAY be removed before interpreting it or forwarding the message downstream.

```
  OWS            = *( SP / HTAB )
                 ; optional whitespace
  RWS            = 1*( SP / HTAB )
                 ; required whitespace
  BWS            = OWS
                 ; "bad" whitespace
```

##

### Quoted Strings

A string of text is parsed as a single value if it is quoted using double-quote marks.

```
  quoted-string  = DQUOTE *( qdtext / quoted-pair ) DQUOTE
  qdtext         = HTAB / SP / %x21 / %x23-5B / %x5D-7E / obs-text
```

The backslash octet ("\") can be used as a single-octet quoting mechanism within quoted-string and comment constructs. Recipients that process the value of a quoted-string MUST handle a quoted-pair as if it were replaced by the octet following the backslash.

```
  quoted-pair    = "\" ( HTAB / SP / VCHAR / obs-text )
```

A sender SHOULD NOT generate a quoted-pair in a quoted-string except where necessary to quote DQUOTE and backslash octets occurring within that string. A sender SHOULD NOT generate a quoted-pair in a comment except where necessary to quote parentheses ["(" and ")"] and backslash octets occurring within that comment.


##

### Comments

Comments can be included in some HTTP fields by surrounding the comment text with parentheses. Comments are only allowed in fields containing "comment" as part of their field value definition.

```
  comment        = "(" *( ctext / quoted-pair / comment ) ")"
  ctext          = HTAB / SP / %x21-27 / %x2A-5B / %x5D-7E / obs-text
```


## 

### Date/Time Formats

An example of the preferred format is
```
  Sun, 06 Nov 1994 08:49:37 GMT
```

Examples of the two obsolete formats are
```
  Sunday, 06-Nov-94 08:49:37 GMT   ; obsolete RFC 850 format
  Sun Nov  6 08:49:37 1994         ; ANSI C's asctime() format
```
A recipient that parses a timestamp value in an HTTP field MUST accept all three HTTP-date formats. When a sender generates a field that contains one or more timestamps defined as HTTP-date, the sender MUST generate those timestamps in the IMF-fixdate format.

[SEE RFC 9110 Name date time formats](https://datatracker.ietf.org/doc/html/rfc9110#name-date-time-formats)



##

### Identifying Content

[See identifying content](https://datatracker.ietf.org/doc/html/rfc9110#name-identifying-content)

### Host and :authority

The "Host" header field in a request provides the host and port information from the target URI, enabling the origin server to distinguish among resources while servicing requests for multiple host names.

```
  Host = uri-host [ ":" port ] ; Section 4
```

The target URI's authority information is critical for handling a request. A user agent MUST generate a Host header field in a request unless it sends that information as an ":authority" pseudo-header field. A user agent that sends Host SHOULD send it as the first field in the header section of a request. For example, a GET request to the origin server for `<http://www.example.org/pub/WWW/>` would begin with:

```
GET /pub/WWW/ HTTP/1.1
Host: www.example.org
```

Since the host and port information acts as an application-level routing mechanism, it is a frequent target for malware seeking to poison a shared cache or redirect a request to an unintended server. An interception proxy is particularly vulnerable if it relies on the host and port information for redirecting requests to internal servers, or for use as a cache key in a shared cache, without first verifying that the intercepted connection is targeting a valid IP address for that host.

##

### Cache

If the client has a cache and the request can be satisfied by it, then the request is usually directed there first.

##

### Rejecting Misdirected Requests

``` 421 (Misdirected Request)```

[See section Rejecting Misdirected Requests](https://datatracker.ietf.org/doc/html/rfc9110#name-rejecting-misdirected-reque)



# CGI

### Sites statiques et dynamique

Statiques juste besoin d'envoyer les pages demandes.
Dynamiques le serveur doit generer la page avant de l'envoyer au client. 
(role de PHP est de generer du code HTML, qui est ensuite envoye au client comme un site statique. Execute par le serveur).

##

Serveur doit interpreter avant de renvoyer donc php avec php python avec python
ruby avec ruby
perl

