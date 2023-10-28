// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API UStoreUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

	// �κ�� ���ư���
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void TryBack();
public:
	// ���� ������ ����
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void PurchaseItem();

public:
	// ��/�� ������ ĭ �̵�
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void MoveLeft();
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void MoveRight();

private:

};
