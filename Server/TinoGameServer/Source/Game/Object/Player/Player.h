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

    int GetUID() const { return mUID; }
    void SetUID(const int uID) { mUID = uID; }

    std::string GetNickName() const { return mNickName; }
    void SetNickName(const std::string name) { mNickName = name; }
    std::string GetID() const { return mID; }
    void SetID(const std::string id) { mID = id; }

    long long GetPing() const { return mPing; }
    void SetPing(const long long ping) { mPing = ping; }
protected:
    //Be sure to use it below the function that calls the lock. ex)CanPlayerArrive()
    //�ݵ�� ���� �ҷ��ִ� �Լ� �������� �� ��
    //�ش� �Լ��� ����Ƿ��� mPlayerStateLock.lock()�� �ɸ� ���¿��� �����. ���ô� CanPlayerArrive()�� ����
    void ChangePlayerState(const ePlayerState playerState);
protected:
    std::string mID;
    std::string mNickName;
    float mDepartment;
    eEquipmentFlags mEquipment;
    std::mutex      mPlayerStateLock;
    ePlayerState    mPlayerState;
    int mRoomID;
    int mRank;    //���?
    int mUID;       //DB���� �ο����ִ� ID
    long long mPing;    //milliseconds
};

