#pragma once
#include <array>
#include <mutex>
#include <map>
#include <vector>

#include "../Utility/Utility.h"
#include "../Network/Network.h"

class Object;
class Player;
class MapObject;
class Room
{
public:
	Room(int id);
	~Room();

	void Init();
	// Add Object - Player, MapObject, Anything else
	void AddObject(Object* object);
	// Remove Player - If Room want Reset
	void RemovePlayer(Player* player);
		
	//The Game Is End, Reset Room ex)clear mObjects
	void ResetGameRoom();
	std::mutex& GetRoomStateLockRef();
	void ActiveRoom();
	void ShufflePlayerInfo();

	bool IsRoomReady();
	bool IsRoomReadyComplete();
	bool IsAllPlayerReady();
	void RoomStartForce();
	bool IsRoomStartForce();
	void SetRoomEnd();
	//�� �Լ��� ���� �ɰ� ����ؾ���.
	eRoomState GetRoomState() const { return mRoomState; }
	void PlayerCntIncrease();
	void PlayerMaxDecrease();

	bool SettingRoomPlayer(const sPlayerInfo& playerInfo, const int& playerMaxNum);
	int GetPlayerRoomSyncID(const int uID);
	sPlayerInfo GetPlayerInfo(const int uID);
	Player* GetPlayerWithUID(const int uID);
	void PlayerArrive(Player* player);
	void AllPlayerArrived();
	//Object order
	//0~7 - player 
	//8~ (MAX_OBJECT-1) - mapobject
	std::array<Object*, MAX_OBJECT>& GetObjectsRef() { return mObjects;}
	void setGameStartTimerStartOnce();
	bool IsGameEndOnce();
protected:
	void addPlayer(Player* player);
	void addMapObject(MapObject* mapObject);
	//���� �� ���¸� Free���� ������.

	void setPlayerInfo(const sPlayerInfo& playerInfo, const int& playerMaxNum);
	void setPlayerInfoWithCnt(const sPlayerInfo& playerInfo, const int& playerMaxNum, int& playerCnt);

	void setGameEndTimerStartOnce();
protected:
	std::mutex mObjectsLock;
	std::array<Object*,MAX_OBJECT> mObjects;

	std::mutex mPlayerInfoLock;
	std::vector<std::pair<int, sPlayerInfo>> mPlayerInfo;

	std::mutex mPlayerArriveLock;
	int	mPlayerArrivedCnt;	//�� ������ ��� ��

	std::mutex mRoomStateLock;
	eRoomState mRoomState;
	int	mRoomID;	//�� ID
	int mPlayerSettingCnt;	//���� �濡 player�� ��� ���� �ƴ���.
	std::atomic_int mPlayerCnt;	//���� �濡 player�� �� �� ���Դ���.
	std::mutex mRoomReadyLock;
	std::atomic_int mPlayerMax;	//�� �ִ� �ο�
	bool mGameEndFlag;	// The Room Game is Over	 (USing CAS)
	bool mGameEndTimer;	//The Room Game is Over Timer (Using CAS)
	bool mGameStartTimer;	//The Room Game is Start Timer (Using CAS)
	eRoomStage mRoomStageKindof;	//���߿� ������ �𸣴� ������ �������� ����.

};

