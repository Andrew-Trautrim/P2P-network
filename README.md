# P2P-Client
Peer to peer client written in C

A P2P client works by created a connection over the internet directly from computer to computer (or peer to peer). The connection is done without the need for a central server as each connected device acts as both server and client to maintain the network. Once a connection is created, devices can send and recieve messages, run commands, and search directories.

Command line usage:
<pre>
root@linux:~/P2P-Client/bin# ./session 
usage: ./session &ltoptions&gt
type '-h' for help
root@linux:~/P2P-Client/bin# ./session -h
usage: ./session &ltoptions&gt

Options:
	-a address : target address
	-h	   : display help options
	-l	   : listen for incoming connections
	-p port	   : port
</pre>

Program execution:  
listening for incoming connections,
<pre>
root@linux:~/P2P-Client/bin# ./session -l -p 18 -t 8080
Establishing server side connection...connected
Sending local information
Establishing client side connection...connected
Session (type 'X' to exit): 
What makes you think she's a witch?
[*] She turned me into a newt.
A newt?
[*] ...I got better.
X
</pre>
connect to target address,
<pre>
root@linux:~/P2P-Client/bin# ./session -a 127.0.0.1 -p 8080 -t 18
Establishing client side connection...connected
Reading incoming data...recieved
Establishing server side connection...connected
Session (type 'X' to exit): 
[*] What makes you think she's a witch?
She turned me into a newt.
[*] A newt?
...I got better.
</pre>
