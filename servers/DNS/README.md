# Rusty network's DNS servers & client discovery

The DNS servers in the Rusty network provide a list of known addresses in the network. They are also able to resolve `.rusty` domains to their respective wallet addresses, functioning like a basic version of [ENS](https://docs.ens.domains/) from the Ethereum network.

## Node startup & client discovery

Upon startup, if peer node discovery is needed, the client must issue a DNS request to learn about the addresses of the other peer nodes. The client has a list of hostnames for DNS servers to use. As of July 2022, the list includes the following servers:

- rustydns00.ddns.net
- rustydns01.ddns.net
- rustydns02.ddns.net

## DNS Server startup

On startup, the name server will fetch the file system for a startup config file. The default location for this file depends on the host OS: `C:\rusty-coin\dns\startup\startup.rcfg` for Windows, and `/etc/rusty-coin/dns/startup.rcgf` for Linux.

The startup config file (`startup.rcfg`) contains information regarding the startup of the server. It contains a variable that points to the main config file (`dns.rcfg`). The main config file stores all the relevant information regarding the server; such as:

- Server address family (IPv4/IPv6)
- Socket service (TCP/UDP)
- Protocol
- Port
- Listening Interface
- Backlog
- Threads

If no startup file is found, the user will be prompted to configure the server and boot it from scratch. The server has a default set of configurations in the code which are used if the user chooses so.