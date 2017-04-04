#pragma once

#ifndef WEBC_SERVER_SERVER_H
#define WEBC_SERVER_SERVER_H

#include <iostream>

namespace webc {

	namespace server {

		enum state {
			success,			//�ɹ�
			socketnotcreate,	//û�ܴ���socket
			socketnotbind,		//û�ܰ�socket
			socketnotlisten,	//û�ܼ���
		};

		class httpserver {
		public:
			//���캯��
			httpserver();
			//��������
			~httpserver();
			//����������
			state create();
			//����������
			void start();
			//�������Ƿ�������
			bool isrun();
			//ֹͣ������
			void stop();
			//����������ʱ��
			long long livetime();
		private:
			//����ʱ��
			time_t start_time;
			//�Ƿ�����
			bool is_run = false;
			//����������
			int port = 80;
			int listen_count = 10;
			//������socket
			long server = -1;
			//�Ƿ���Ҫ����
			bool torun = false;
		};

	}
}


#endif // !WEBC_SERVER_H
