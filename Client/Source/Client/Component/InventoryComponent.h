#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

class AAccessoryItem;
struct FItemData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLIENT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	

	//�κ��丮�� ������ �߰��ǰų� ���Ž� ��ε�ĳ��Ʈ�� ��
	FOnInventoryUpdated OnInventoryUpdated;

	FORCEINLINE TArray<FItemData> GetInventoryContents() const { return InventoryContents; }

	void AddItem(const FItemData& ItemData);

protected:

	// �÷��̾� �κ��丮
	UPROPERTY(EditDefaultsOnly,Category="Inventory")
	TArray<FItemData> InventoryContents;
		
};
