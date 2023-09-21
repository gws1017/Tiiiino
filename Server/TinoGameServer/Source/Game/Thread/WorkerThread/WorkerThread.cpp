#include "WorkerThread.h"
#include "../../Object/Player/Player.h"
#include "../../Server/MainServer/MainServer.h"
#include "../../Network/Network.h"

WorkerThread::WorkerThread(MainServer* Server)
	:mMainServer(Server)
{
}

WorkerThread::~WorkerThread()
{
}

void WorkerThread::doThread()
{

	for (;;) {
		DWORD bytes;
		LONG64 iocp_key;
		WSAOVERLAPPED* overlapped;
		BOOL ret = GetQueuedCompletionStatus(mMainServer->GetIOCPHandle(), &bytes, (PULONG_PTR)&iocp_key, &overlapped, INFINITE);
		int client_id = static_cast<int>(iocp_key);
		WSA_OVER_EX* wsa_ex = reinterpret_cast<WSA_OVER_EX*>(overlapped);
		if (FALSE == ret) {
			int err_no = WSAGetLastError();
			//std::cout << "GQCS Error";
			mMainServer->ErrorDisplay(err_no);
			if (wsa_ex->GetCmd() == eCOMMAND_IOCP::CMD_SEND)
				delete wsa_ex;
			continue;
		}

		switch (wsa_ex->GetCmd()) {
		case eCOMMAND_IOCP::CMD_RECV: {
			if (bytes == 0) {
				auto t = dynamic_cast<Player*>(mMainServer->getObjects()[client_id]);
				if (t) t->DisConnect();
				//Disconnect(client_id);
				break;
			}

			Player* player = dynamic_cast<Player*>(mMainServer->getObjects()[client_id]);
			int To_Process_Bytes = bytes + player->GetPrevSize();
			unsigned char* packets = wsa_ex->GetBuf();	//wsa_ex == player->wsa_ex.buf

			if (To_Process_Bytes >= packets[0])
			{
				do {
					mMainServer->ProcessPacket(client_id, packets);
					To_Process_Bytes -= packets[0];
					packets += packets[0];
				} while ((To_Process_Bytes & ~0) && (To_Process_Bytes >= packets[0]));
			}
			//To_Process_Bytes != 0 �̸� packets���� ū�� Ȯ���ؾ� �� �� ������
			//to_Process_Bytes�� packets���� ũ��, To_Process_Bytes != 0�ΰ� Ȯ���ϹǷ�, �̶��� �ʿ���� ����
			//�ޱ����� �����ο��°� �ǹ̰� ����. �ձ������� �����Ͽ� cmp�� �� �� ������ ���� �� �ִ� ���ȿ��
			player->PreRecvPacket(packets, To_Process_Bytes);
			player->RecvPacket();
			break;
		}
		case eCOMMAND_IOCP::CMD_ACCEPT: {
			std::cout << "Accept Completed.\n";
			SOCKET c_socket = *(reinterpret_cast<SOCKET*>(wsa_ex->GetBuf()));
			int new_id = mMainServer->GenerateID();
			if (new_id != -1)
			{
				Player* player = reinterpret_cast<Player*>(mMainServer->getObjects()[new_id]);
				player->SetSocketID(new_id);
				player->AcceptSetting(eSocketState::ST_ACCEPT, eCOMMAND_IOCP::CMD_RECV, c_socket);

				CreateIoCompletionPort(reinterpret_cast<HANDLE>(c_socket), mMainServer->GetIOCPHandle(), new_id, 0);
				player->PreRecvPacket(NULL, 0);
				player->RecvPacket();
			}
			else if (new_id == -1)
			{
				closesocket(c_socket);
			}

			ZeroMemory(&wsa_ex->GetWsaOver(), sizeof(wsa_ex->GetWsaOver()));
			c_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
			*(reinterpret_cast<SOCKET*>(wsa_ex->GetBuf())) = c_socket;
			AcceptEx(mMainServer->GetSocket(), c_socket, wsa_ex->GetBuf() + 8, 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, NULL, &wsa_ex->GetWsaOver());
			break;
		}
		
		}
	}
}
