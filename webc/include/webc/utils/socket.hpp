//
// Created by ���� on 2017/3/7.
//

#ifndef YIZHI_SOCKET_H
#define YIZHI_SOCKET_H


//visual studio ����
#ifdef WIN32
#define close closesocket
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

typedef int socklen_t;	/* socklen_t (duh) */
//gcc����
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#endif



//Socketʵ����
namespace webc {
	namespace utils{
		namespace sock {

			//����socket
			int socket_e(int protofamily, int type, int protocol);

			//�ͷ���Դ����Ҫ���windows��Linux�ϵ������κ�Ч��
			void release_e();

			//�󶨶˿�
			int bind_e(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

			//����
			int listen_e(int sockfd, int backlog);

			//����
			int connect_e(int sockfd, const struct sockaddr *addr, int addrlen);

			//����
			int accept_e(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

			//����
			int send_e(int sockfd, const char *buf, size_t len, int flags);

			//����
			int recv_e(int sockfd, char *buf, size_t len, int flags);

			//����
			int sendto_e(int sockfd, const char *buf, size_t len, int flags, const struct sockaddr *dest_addr, int addrlen);

			//����
			int recvfrom_e(int sockfd, char *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

			//�رգ�ͬʱ�����release
			int close_r(int fd);

			//�ر�socket���������release
			int close_e(int fd);
		}
	}
}

#endif // !YIZHI_SOCKET_H