//
// Created by 康康 on 2017/3/7.
//

#ifndef YIZHI_SOCKET_H
#define YIZHI_SOCKET_H


//visual studio 编译
#ifdef WIN32
#define close closesocket
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

typedef int socklen_t;	/* socklen_t (duh) */
//gcc编译
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#endif



//Socket实现类
namespace webc {
	namespace utils{
		namespace sock {

			//创建socket
			int socket_e(int protofamily, int type, int protocol);

			//释放资源，主要针对windows，Linux上调用无任何效果
			void release_e();

			//绑定端口
			int bind_e(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

			//监听
			int listen_e(int sockfd, int backlog);

			//连接
			int connect_e(int sockfd, const struct sockaddr *addr, int addrlen);

			//接受
			int accept_e(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

			//发送
			int send_e(int sockfd, const char *buf, size_t len, int flags);

			//接收
			int recv_e(int sockfd, char *buf, size_t len, int flags);

			//发送
			int sendto_e(int sockfd, const char *buf, size_t len, int flags, const struct sockaddr *dest_addr, int addrlen);

			//接收
			int recvfrom_e(int sockfd, char *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

			//关闭，同时会调用release
			int close_r(int fd);

			//关闭socket，不会调用release
			int close_e(int fd);
		}
	}
}

#endif // !YIZHI_SOCKET_H