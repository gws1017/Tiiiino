// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ClientGameMode.generated.h"

enum class EBGMType : uint8;
class UDataTable;
struct Item;
struct FItemData;

UCLASS(minimalapi)
class AClientGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AClientGameMode();
	
public:

	FItemData* GetItemData(const int64& ItemCode) const;
	FItemData* GetShopProductData(const int64& ItemCode) const;

	void SetItemDataTable();
	void SetShopDataTable();

	void GetShopProductTable(TArray<int>& f_out);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GenerateItemDataFromServer(FItemData& OutData,const Item& data);

	//��� ������ ������ ���� -> ������ : �� �ƴ϶��ϴ� �Ф�
	UPROPERTY(EditDefaultsOnly, Category = "Accessory | Data")
	UDataTable* ItemData;

	//�������� �� ������ �����͵��� ���� -> CBT ���� ���� ������ ������ �������� �ȸ� �ȵ�.
	UPROPERTY(EditDefaultsOnly, Category = "Accessory | Data")
	UDataTable* ShopData;

	UPROPERTY(EditDefaultsOnly, Category = "Sound | Class")
	TSubclassOf<class ASoundManager> SoundMangerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sound | LevelName")
	TMap<FString, EBGMType> ConvertBGMTypeMap;

	
};



