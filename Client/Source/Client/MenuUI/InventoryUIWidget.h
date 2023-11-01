// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UInventoryUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;


	// �κ�� ���ư���
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void TryBack();

	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
	float Grade;
	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
	float Point;

	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void UpdatePointAndPoint();

public:
	// ������ ������ Ŭ��
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void ClickItemIcon(const int itemcode);
	
	// Ŭ���� ������ ����
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void EquipClickedItem();

	// ������ �������� Ȯ��
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	bool CheckItemEquiped(const int64 itemcode);
};
