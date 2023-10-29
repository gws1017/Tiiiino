// Fill out your copyright notice in the Description page of Project Settings.



#include "MenuUI/StoreUIWidget.h"
#include "MenuUI/LobbyUIWidget.h"
#include "Actor/Controller/TinoController.h"
#include "Network/Network.h"
#include "Global.h"


void UStoreUIWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
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
	// StoreDialog â ���
}

bool UStoreUIWidget::QualifyingPurchase()
{
	// ���� ���ѿ��� Ȯ��
	if (true)
	{
		ShowPurchaseWarning(false);
	}

	// ���� ���� Ȯ��
	if (true)
	{
		ShowPurchaseWarning(true);
	}

	return true;
}

void UStoreUIWidget::MoveLeft()
{
	// ���� �̵���ư Ŭ��
}

void UStoreUIWidget::MoveRight()
{
	// ���� �̵���ư Ŭ��
}
