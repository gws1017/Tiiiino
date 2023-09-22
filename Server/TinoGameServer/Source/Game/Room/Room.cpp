#include "Room.h"
#include "../Object/Player/Player.h"
#include "../Object/MapObject/MapObject.h"

Room::Room()
	: mRoomStageKindof(eRoomStage::ST_AVOID)
	,mObjects()
{

}

Room::~Room()
{
	for (auto object : mObjects)
	{
		delete object;
		object = nullptr;
	}
}

void Room::Init()
{

}

void Room::AddObject(Object* object)
{
	Player* player = dynamic_cast<Player*>(object);
	if (player)
	{
		AddPlayer(player);
		return;
	}
	MapObject* mapObject = dynamic_cast<MapObject*>(object);
	if (mapObject)
	{
		AddMapObject(mapObject);
		return;
	}
}

void Room::RemovePlayer(Player* player)
{
	for (int i = 0; i < MAX_ROOM_USER; ++i)
	{
		Player* p = dynamic_cast<Player*>(mObjects[i]);
		if (p->GetSocketID() == player->GetSocketID())
		{
			mObjects[i] = nullptr;
			return;
		}
	}
}


void Room::ResetGameRoom()
{
	for (auto object : mObjects)
	{
		object = nullptr;
	}
}

void Room::AddPlayer(Player* player)
{
	for (int i = 0; i < MAX_ROOM_USER; ++i)
	{
		//�̺κп��� �����ͷ��̽��� ���� �÷��̾������� ���ļ� ������� ġ���� ������ �߻���.
		//���� lock���� ����.
		//�������� ������ ������, �������� ���� ID�� �����ϱ� ������ �д°� ���� ��������.
		//�÷��̾ �ִ� ������ ���� ������ �� �� �ѹ� Or ƨ���� ������ �� �� �̱� ������ �д°Ŷ� ����.
		//�׸��� �д� ������ SocketState�� �����ϱ� ������, Ȥ�ó� �����ͷ��̽��� �ɸ��ٰ� �ĵ� socketstate���� �ɸ�. �� ������.
		mObjectsLock.lock();
		if (nullptr == mObjects[i])
		{
			mObjects[i] = player;
			mObjectsLock.unlock();
			player->GetStateLockRef().lock();
			player->SetSocketState(eSocketState::ST_INGAME);
			player->GetStateLockRef().unlock();
			return;
		}
		mObjectsLock.unlock();
	}
}

void Room::AddMapObject(MapObject* mapObject)
{
	for (int i = MAX_ROOM_USER; i < MAX_OBJECT; ++i)
	{
		//map object���� ���� �������� ���������� �ֱ� ������ �����ͷ��̽� ���� X
		mObjectsLock.lock();
		if (nullptr == mObjects[i])
		{
			mObjects[i] = mapObject;
			mObjectsLock.unlock();
			return;
		}
		mObjectsLock.unlock();
	}
}
