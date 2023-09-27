#pragma once
#include <string>
#include "../../Network/Network.h"
#include "../Object.h"


class Player : public Object, public Network
{
public:
    Player();
    ~Player();

    bool CanMakeID();

    int GetRoomID() const { return mRoomID; }
    void SetRoomID(int roomID) { mRoomID = roomID; }

    int GetRank() const { return mRank; }
    void SetRank(int rank) { mRank = rank; }

    bool IsPlayerArrived();
    bool CanPlayerArrive();
protected:
    //�ݵ�� ���� �ҷ��ִ� �Լ� �������� �� ��
    //�ش� �Լ��� ����Ƿ��� mPlayerStateLock.lock()�� �ɸ� ���¿��� �����. ���ô� CanPlayerArrive()�� ����
    void ChangePlayerState(const ePlayerState playerState);
protected:
    std::wstring mNickName;
    float mDepartment;
    eEquipmentFlags mEquipment;
    std::mutex      mPlayerStateLock;
    ePlayerState    mPlayerState;
    int mRoomID;
    int mRank;    //���?
};

