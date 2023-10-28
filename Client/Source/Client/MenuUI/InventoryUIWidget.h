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
public:

};
