#pragma once
#include "../Server.h"
class LobbyServer : public Server
{
public:
	LobbyServer() = default;
	virtual ~LobbyServer();
	void init();


protected:
	//SOCKADDR_IN server_addr;
	//WSA_OVER_EX recv_expover;
	//int		_prev_size;
	//bool bIsConnected;	//�ӽ� ����
	const char* LOOBYSERVER_ADDR = "127.0.0.1";
};

