//
// Created by ���� on 2017/3/7.
//

using namespace std;


#include "webc/webc.hpp"
using namespace webc;

//����socket
int webc::utils::sock::socket_e(int protofamily, int type, int protocol) {
	//���windows
#ifdef WIN32
	WSADATA wsd;            //WSADATA����
	//��ʼ���׽��ֶ�̬��
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		return -1;
	}
#endif
	return socket(protofamily, type, protocol);
}

//�ͷ�windows��Դ
void webc::utils::sock::release_e() {
#ifdef WIN32
	WSACleanup();
#endif
}


//��
int webc::utils::sock::bind_e(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	return bind(sockfd, addr, addrlen);
}


//����
int webc::utils::sock::listen_e(int sockfd, int backlog) {
	return listen(sockfd, backlog);
}


//����
int webc::utils::sock::connect_e(int sockfd, const struct sockaddr *addr, int addrlen) {
	return connect(sockfd, addr, addrlen);
}


//����
int webc::utils::sock::accept_e(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
	return accept(sockfd, addr, addrlen);
}

//����
int webc::utils::sock::send_e(int sockfd, const char *buf, size_t len, int flags) {
	return send(sockfd, buf, len, flags);
}

int webc::utils::sock::sendto_e(int sockfd, const char *buf, size_t len, int flags, const struct  sockaddr *dest_addr, int addrlen) {
	return sendto(sockfd, buf, len, flags, dest_addr, addrlen);
}

//����
int webc::utils::sock::recv_e(int sockfd, char *buf, size_t len, int flags) {
	return recv(sockfd, buf, len, flags);
}

int webc::utils::sock::recvfrom_e(int sockfd, char *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {
	return recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
}



int webc::utils::sock::close_r(int fd) {
	int ret = close(fd);
	webc::utils::sock::release_e();
	return ret;
}

int webc::utils::sock::close_e(int fd) {
	return close(fd);
}