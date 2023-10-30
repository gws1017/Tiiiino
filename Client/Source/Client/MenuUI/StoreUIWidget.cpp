// Fill out your copyright notice in the Description page of Project Settings.



#include "MenuUI/StoreUIWidget.h"
#include "MenuUI/LobbyUIWidget.h"
#include "Actor/Controller/TinoController.h"
#include "Actor/Character/TinoCharacter.h"
#include "Components/TextBlock.h"
#include "Network/Network.h"
#include "Global.h"


void UStoreUIWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	//auto TinoController = Cast<ATinoController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	//auto TinoCharacter = TinoController->GetPawn<ATinoCharacter>();
	//Grade = TinoCharacter->GetGrade();
	//Point = TinoCharacter->GetPoint();
}

void UStoreUIWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UStoreUIWidget::TryBack()
{
	auto TinoController = Cast<ATinoController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	TinoController->ChangeMenuWidget(TinoController->LobbyUIInstance);
}

void UStoreUIWidget::PurchaseItem()
{
	// Buy��ư Ŭ��
	int32 price = 100;
	Point -= price;
	ChangePoint();
	send_buyitem_packet(Network::GetNetwork()->l_socket, ClickItemCode);

	// Store BuyResult â ���
	// StoreBuyResultInstance->AddToViewport();
}

bool UStoreUIWidget::QualifyingPurchase()
{
	// ���� ���ѿ��� Ȯ��
	if (true)
	{
		
		//ShowPurchaseWarning(false);
	}

	// ���� ���� Ȯ��
	if (true)
	{

		//ShowPurchaseWarning(true);
	}
	// �ӽ� ���ӵ����͸Ŵ������� �����۵����� �ҷ�����
	auto itemdata = Network::GetNetwork()->mGameDataManager->GetShopProductsList();
	for (auto &data : itemdata)
	{
		int price = data.second.price;
	}
	return true;
}

void UStoreUIWidget::AlreadyPurchase()
{
	ShowPurchaseWarning(true);
}

void UStoreUIWidget::LimitGrade()
{
	ShowPurchaseWarning(false);
}

void UStoreUIWidget::MoveLeft()
{
	// ���� �̵���ư Ŭ��
}

void UStoreUIWidget::MoveRight()
{
	// ���� �̵���ư Ŭ��
}
