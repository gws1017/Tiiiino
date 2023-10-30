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
	// Buy버튼 클릭
	int32 price = 100;
	Point -= price;
	ChangePoint();
	// StoreDialog 창 띄움
}

bool UStoreUIWidget::QualifyingPurchase()
{
	// 학점 제한여부 확인
	if (true)
	{
		
		ShowPurchaseWarning(false);
	}

	// 보유 여부 확인
	if (true)
	{

		ShowPurchaseWarning(true);
	}

	return true;
}

void UStoreUIWidget::MoveLeft()
{
	// 좌측 이동버튼 클릭

	ItemNum--;
	
}

void UStoreUIWidget::MoveRight()
{
	// 우측 이동버튼 클릭
	ItemNum++;
}
