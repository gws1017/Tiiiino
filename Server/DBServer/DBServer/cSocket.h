#pragma once
#include "stdafx.h"
#include "cSession.h"
#include "cDB.h"
#include "../../ServerProtocol.h"

class Socket {
public:

	int SetKey();
	void Disconnect(int key);
	void WorkerFunc();
	void ServerReady(DB* pDB);
	void processPacket(int key, unsigned char* buf);

	void Setm_pDB(DB* pDB) { m_pDB = pDB; }

	bool CheckLogin(int key, const char* id, const char* password, int userid);

	void SendUserDataAfterLogin(int key, int uid, string& nickname, double credit, int point, bool state, int userid);
	void SendLoginFail(int key, const char* id);

	void ProcessPacket_Login(int key, unsigned char* buf);

	void ProcessPacket_Join(unsigned char* buf);

private:
	SOCKADDR_IN mServerAddr;
	HANDLE mHcp;
	SOCKET mListenSocket;

	DB* m_pDB = NULL;

	array<Session, MAXLOBBY + 1> mSessions;


};