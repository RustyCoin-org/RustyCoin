# Rusty network's DNS servers & client discovery

The DNS servers in the Rusty network provide a list of known addresses in the network. They are also able to resolve `.rusty` domains to their respective wallet addresses, functioning like a basic version of [ENS](https://docs.ens.domains/) from the Ethereum network.

## Node startup & client discovery

Upon startup, if peer node discovery is needed, the client must issue a DNS request to learn about the addresses of the other peer nodes. The client has a list of hostnames for DNS servers to use. As of July 2022, the list includes the following servers:

- rustydns00.ddns.net
- rustydns01.ddns.net
- rustydns02.ddns.net
