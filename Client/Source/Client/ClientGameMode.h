// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ClientGameMode.generated.h"

enum class EBGMType : uint8;
class UDataTable;
struct FItemData;

UCLASS(minimalapi)
class AClientGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AClientGameMode();
	
public:

	FItemData* GetItemData(const int64& ItemCode) const;
	//FItemData* GetShopProductData(const int64& ItemCode) const;

	void SetItemDataTable();
	//void SetShopDataTable();

	void GetShopProductTable(TArray<int>& f_out);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//모든 아이템 데이터 집합(= 상점 데이터)
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	UDataTable* ItemData;

	//UPROPERTY(EditDefaultsOnly, Category = "Data")
	//UDataTable* ShopData;

	UPROPERTY(EditDefaultsOnly, Category = "Class")
	TSubclassOf<class ASoundManager> SoundMangerClass;

	UPROPERTY(EditDefaultsOnly, Category = "LevelName")
	TMap<FString, EBGMType> ConvertBGMTypeMap;

	
};



