#include "Player.h"

Player::Player()
	:mNickName(L"")
	,mDepartment(0.0f)
	,mItem(eItemFlags::None)
	,mRoomID(INVALID_ROOM_ID)
{
}

Player::~Player()
{
}

bool Player::CanMakeID()
{
	mStateLock.lock();
	if (eSocketState::ST_FREE == mSocketState)
	{
		mSocketState = eSocketState::ST_ACCEPT;
		mStateLock.unlock();
		//cout << i <<"��° ĳ���� ����"<< endl;
		return true;;
	}
	mStateLock.unlock();
	return false;
}
