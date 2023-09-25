// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Level/CustomLevel_Test.h"
#include "Network/Network.h"
#include "Actor/Character/TinoCharacter.h"
#include "Utilities/CLog.h"


void ACustomLevel_Test::BeginPlay() {

	Super::BeginPlay();
	Network::GetNetwork()->bLevelOpenTriggerEnabled = false;	//���� ���۵����� Ʈ���� ����.
	/*
	1. ĳ���͸� �����ϰ� Network mMyCharacter�� ����
	2. ������ ������
	3. �α��� ui
	4. �α��� ������ ui������ �κ� ����.
	*/
	FName path = TEXT("Blueprint'/Game/Characters/Tino/BP_TinoCharacter.BP_TinoCharacter_C'"); //_C�� �� �ٿ��� �ȴٰ� ��.
	UClass* GeneratedCharacterBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *path.ToString()));
	FTransform trans;
	trans.SetLocation(trans.GetLocation() + mMyCharacterSpawnPosition);
	auto mc1 = GetWorld()->SpawnActorDeferred<ATinoCharacter>(GeneratedCharacterBP, trans);
	mc1->SpawnDefaultController();
	mc1->AutoPossessPlayer = EAutoReceiveInput::Player0;
	mc1->FinishSpawning(trans);
	Network::GetNetwork()->mMyCharacter = mc1;
	Conn();

	//To Loading ...

	//To Do SomeThing ...

}


bool ACustomLevel_Test::Conn()
{
	Super::Conn();
	Network::GetNetwork()->init();

	if (bGameserverConn)
		return ConnGameServer();
	else
		return ConnLobbyServer();

}

bool ACustomLevel_Test::ConnGameServer()
{
	auto player = Network::GetNetwork()->mMyCharacter;
	if (nullptr != player)
	{
		if (Network::GetNetwork()->ConnectServerGame())
		{
			CLog::Log("Connect Successfully");
			send_movetogame_packet(Network::GetNetwork()->s_socket,Network::GetNetwork()->mDBUID,
				TCHAR_TO_ANSI(*Network::GetNetwork()->MyCharacterName), 0);
			return true;
		}
		else {

			CLog::Log("Connect Fail!");
		}
	}
	return false;
}

bool ACustomLevel_Test::ConnLobbyServer()
{
	auto player = Network::GetNetwork()->mMyCharacter;
	if (nullptr == player) return false;

	if (true == Network::GetNetwork()->ConnectServerLobby())
	{
		if (false == Network::GetNetwork()->bLoginFlag)
		{
			//send_login_packet(Network::GetNetwork()->l_socket, "dd", "Dd");
			//player->ShowLoginHUD();
		}
		else
		{
			//const char* tmpid = TCHAR_TO_ANSI(*Network::GetNetwork()->MyCharacterName);
			//const char* tmppass = TCHAR_TO_ANSI(*Network::GetNetwork()->MyCharacterPassWord);
			//if (nullptr != Network::GetNetwork()->mMyCharacter)
			//	send_login_lobby_packet(Network::GetNetwork()->mMyCharacter->l_socket, tmpid, tmppass);
		}
		CLog::Log("Connect Lobby Successfully");
		return true;
	}
	else {

		CLog::Log("Connect Fail!");
	}

	//UE_LOG(LogTemp, Log, TEXT("Player Try Conn"));
	return false;
}










