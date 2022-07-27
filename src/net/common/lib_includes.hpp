#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <winerror.h>
#include <arpa/inet.h>
#include <tchar.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netdb.h>
#endif