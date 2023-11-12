// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUIWidget.generated.h"

/**
 * 

 */
class ATinoCharacter;

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

	UFUNCTION(BluePrintImplementableEvent, Category = "UMG_Game")
	void UpdateEquippedAccessory();

	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	FString GetAccessoryItemCode();

public:
	// ������ ������ Ŭ��
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void ClickItemIcon(const int itemcode);
	
	// Ŭ���� ������ ����
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void EquipClickedItem(const int itemcode);
	
	// Ŭ���� ������ ����
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void UnEquipClickedItem(const int itemcode);


	// ������ �������� Ȯ��
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	bool CheckItemEquiped(const int64 itemcode);

private:
	void InitInstance();

	ATinoCharacter* PlayerInstance;
};
