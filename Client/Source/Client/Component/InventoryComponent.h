#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemData.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

struct FItemData;
class AAccessoryItem;

//�÷��̾ ������ ������ �����ܿ�
//�������ο� ���� �߰����� ������ �ʿ��ϴٸ�
//�� ����ü�� �߰��ٶ�
USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

public:

	FInventoryItem() = default;
	FInventoryItem(const FItemData& ItemData, bool bEquipped) 
		: ItemInstance(nullptr),ItemInfo(ItemData), bEquipped(bEquipped) 
	{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryData")
		AAccessoryItem* ItemInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryData")
		FItemData ItemInfo; //������������ ������ִ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InventoryData")
		bool bEquipped;  //��������

	bool operator==(const FInventoryItem& OtherData) const
	{
		return this->ItemInfo.ItemCode == OtherData.ItemInfo.ItemCode;
	}
};

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
	//�뵵�� ������ ������Ʈ�� UI���ڵ�������Ʈ�Ǳ�����(UIȣ�������ʰ� �̺�Ʈ�� �˾Ƽ�ó��)
	FOnInventoryUpdated OnInventoryUpdated;

	//�κ��丮�� �����ϴ� �������� ���� �����ִ� �Լ�
	TArray<FInventoryItem> GetInventoryContents() const;
	//
	FInventoryItem GetItemFromItemCode(const int64& ItemCode) const;

	void AddItem(const FItemData& ItemData, bool bEquipped = false);
	void ClearInventory();
	void ClearEquippedInfo();

	UFUNCTION(BlueprintCallable)
	void SetEquipped(const int64& ItemCode, bool bEquipped);
	UFUNCTION(BlueprintCallable)
	bool GetEquipped(const int64& ItemCode) const;
	UFUNCTION(BlueprintCallable)
	AAccessoryItem* GetInstnace(const int64& ItemCode) const;
	UFUNCTION(BlueprintCallable)
	void SetInstnace(const int64& ItemCode, AAccessoryItem* Item);

protected:
	// �÷��̾� �κ��丮
	UPROPERTY(VisibleAnywhere,Category="Inventory")
	TMap<int64,FInventoryItem> InventoryContents;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
		TMap<EEquipType, AAccessoryItem*> EquipInfo;

		
};
