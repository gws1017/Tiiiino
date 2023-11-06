// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUI/InventoryUIWidget.h"
#include "MenuUI/LobbyUIWidget.h"
#include "Actor/Controller/TinoController.h"
#include "Actor/Character/TinoCharacter.h"
#include "Actor/Accessory/AccessoryItem.h"
#include "Data/ItemData.h"

#include "Network/Network.h"
#include "Global.h"

void UInventoryUIWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	//TinoCharacter���� GetInventoryContents�Լ���
	//FAssetData.Icon�� ��ư �̹����� ����
	//�������Ʈ,C++ �Ѵ� ����
	//�κ��丮 UI�� ����� ������ ��� �ε��� ����, ���������� ����
	//0~8 ǥ�� (1������), 9 ~ 17 (2������)float
	//ǥ���� ������ ��ŭ �κ��丮�� ���������� �⺻ ��ư �̹����� ��������
}

void UInventoryUIWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInventoryUIWidget::TryBack()
{
	auto TinoController = Cast<ATinoController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	TinoController->ChangeMenuWidget(TinoController->LobbyUIInstance);
	//��ư�� ����� �ε����� �κ��丮���� ������ �ڵ� ��� -> ��������� Ŭ�󿡼��ؾ���
	//������ �ڵ� ��Ŷ ����(���� �ش� �Լ��� ���µ�?)
}

void UInventoryUIWidget::UpdatePointAndPoint()
{
	auto TinoController = Cast<ATinoController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!!TinoController)
	{
		auto TinoCharacter = TinoController->GetPawn<ATinoCharacter>();
		if (!!TinoCharacter)
		{
			Point = TinoCharacter->GetPoint();
			Grade = TinoCharacter->GetGrade();
		}
	}
}

FString UInventoryUIWidget::GetAccessoryItemCode()
{
	FString fstr;
	for (auto p : Network::GetNetwork()->mMyCharacter->EquipAccessoryContainer)
	{
		FString temp = FString::FromInt(p->GetItemCode());
		fstr += temp;
		fstr += ' ';
	}
	return fstr;
}

void UInventoryUIWidget::ClickItemIcon(const int itemcode)
{
	// ������ Ŭ���� ������ �ڵ� ����
	
}

void UInventoryUIWidget::EquipClickedItem(const int itemcode)
{
	// ������ ����
	send_equip_packet(Network::GetNetwork()->l_socket, itemcode);
}

void UInventoryUIWidget::UnEquipClickedItem(const int itemcode)
{
	// ������ ����
	send_unequip_packet(Network::GetNetwork()->l_socket, itemcode);
}

bool UInventoryUIWidget::CheckItemEquiped(const int64 itemcode)
{
	
	for (auto p : Network::GetNetwork()->mMyCharacter->EquipAccessoryContainer)
	{
		//int AccessoryItemCode = p->GetItemCode();
		//if (AccessoryItemCode <= 15)
		//{
		//	if (equiptype != EEquipType::EEquipType_Back)
		//	{
		//		return true;
		//	}
		//}
		//else if (AccessoryItemCode <= 31)
		//{
		//	if (equiptype == EEquipType::EEquipType_Hand)
		//	{
		//		return true;
		//	}
		//}
		//else if (AccessoryItemCode <= 47)
		//{
		//	if (equiptype == EEquipType::EEquipType_Face)
		//	{
		//		return true;
		//	}
		//}
		//else if (AccessoryItemCode <= 63)
		//{
		//	if (equiptype == EEquipType::EEquipType_Head)
		//	{
		//		return true;
		//	}
		//}
		//else
		//{
		//	// error
		//}
		//
		if (itemcode == p->GetItemCode())
			return true;
	}
	return false;
}
