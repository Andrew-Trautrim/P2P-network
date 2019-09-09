#include "p2p.h"

/* function connects to an existing server node in p2p network (client side) */
int connect_p2p(int i) {

	// creates client side socket
	if ((session[i]->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "[!] Unable to create client side socket for %s - error %d\n", session[i]->ip, errno);
		return -1;
	}

	// connection settings
	session[i]->addr.sin_family = AF_INET;
	session[i]->addr.sin_port = htons(session[i]->port);

	// client side connection
	if (connect(session[i]->socket, (struct sockaddr*)&(session[i]->addr), sizeof(session[i]->addr)) == -1) {
		fprintf(stderr, "[!] Unable to connect to %s - error %d\n", session[i]->ip, errno);
		return -1;
	}

	fprintf(stdout, "Connected to %s on port %d\n", session[i]->ip, session[i]->port);
	session[i]->connected = 1;
	return 1;
}

/* allocates memory for the session and sets the port */
p2p_struct *init_p2p(int port) {
	p2p_struct *conn = (p2p_struct*)calloc(1, sizeof(p2p_struct));
	strcpy(conn->ip, "UNKNOWN");
	conn->connection = 0;
	conn->active = 0;
	conn->connected = 0;
	conn->port = port;
	return conn;
}

/* deallocates memory and closes sockets*/
void close_p2p(p2p_struct **session) {
	for (int i = 0, n = cconn+sconn; i < n; ++i) {
		close(session[i]->socket);
		close(session[i]->connection);
		free(session[i]);
	}
	free(session);
	return;
}

/* function initiates network by listening for incoming connections (server side) */
void *accept_p2p(void *arg) {
	
	p2p_struct *conn = (p2p_struct*)arg;

	// creates server side socket
	if ((conn->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "[!] Unable to create server side socket - error %d\n", errno);
		return NULL;
	}

	// connection settings
	conn->addr.sin_family = AF_INET;
	conn->addr.sin_port = htons(conn->port);
	conn->addr.sin_addr.s_addr = INADDR_ANY;

	// binds socket to port
	if (bind(conn->socket, (struct sockaddr*)&(conn->addr), sizeof(conn->addr)) < 0) {
		fprintf(stderr, "[!] Unable to bind port %d - error %d\n", conn->port, errno);
		return NULL;
	}

	// listen on socket/port
	// maximum of 1 pending connection
	if (listen(conn->socket, 1) < 0) {
		fprintf(stderr, "[!] Unable to listen on port %d - error %d\n",conn->port, errno);
		return NULL;
	}

	fprintf(stderr, "Listening on port %d\n", conn->port);

	int addrlen = sizeof(conn->addr);
	if((conn->connection = accept(conn->socket, (struct sockaddr*)&(conn->addr), (socklen_t*)&addrlen)) < 0) {
		fprintf(stderr, "[!] Connection failure - error %d\n", errno);
		return NULL;
	}

	//read(server->connection, server->ip, sizeof(server->ip));
	fprintf(stdout, "port %d connected\n", conn->port);
	conn->connected = 1;
	return NULL;
}