// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUI/InventoryUIWidget.h"
#include "MenuUI/LobbyUIWidget.h"
#include "Actor/Controller/TinoController.h"
#include "Actor/Character/TinoCharacter.h"
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
	//0~8 ǥ�� (1������), 9 ~ 17 (2������)
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

void UInventoryUIWidget::ClickItemIcon()
{
	//����� ��ư �ܰ��� ����
	//������ ��ư �ε��� ����
}
