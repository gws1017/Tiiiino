// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUIWidget.generated.h"

/**
 * 
 */



UCLASS()
class CLIENT_API ULobbyUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
public:
	// ���� �غ�
	UPROPERTY(meta = (BindWidget))
	class UButton* GameStartButton;

	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void TryGameStart();

	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void TryGameReady();

	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void TryGameReadyCancel();

	

public:
	// �α��� ȭ������ ���ư���
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void TryBack();
	
	// �������� �̵�
	UPROPERTY(meta = (BindWidget))
	class UButton* StoreButton;

	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void TryEnterStore();

	// �κ��丮�� �̵�
	UPROPERTY(meta = (BindWidget))
	class UButton* InventoryButton;

	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void TryEnterInventory();
	
	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
		float Grade;
	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
		int32 Point;
public:
	// ��ũ �ý���

	// �������� �����ִ� ��ũ������ ����
	void GetRankData(char DepartmentName[], char DepartmentPoint[]);

	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
	TArray<int> DepartmentNameArray = { 0,1,2,3,4,5,6,7,8,9 };

	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
	TArray<int> DepartmentPointArray = { 0,1,2,3,4,5,6,7,8,9 };
};
