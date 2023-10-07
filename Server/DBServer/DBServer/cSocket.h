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

	DB* Getm_pDB() { return m_pDB; }

	bool CheckLogin(int key, const char* id, const char* password, int userid);

	void SendUserDataAfterLogin(int key, int uid, string& nickname, const char* id, double grade
		, int point, int state, char department, int userid);
	void SendLoginFail(int key, const char* id, int userKey);
	void SendUpdateNicknameOK(int key, int userKey);

	void ProcessPacket_Login(int key, unsigned char* buf);
	void ProcessPacket_SignUp(unsigned char* buf);
	void ProcessPacket_UpdateNickname(int key, unsigned char* buf); 
	void ProcessPacket_UpdateGrade(int key, unsigned char* buf);


private:
	SOCKADDR_IN mServerAddr;
	HANDLE mHcp;
	SOCKET mListenSocket;

	DB* m_pDB = NULL;

	array<Session, MAXLOBBY + 1> mSessions;


};