// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreUIWidget.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPurchaseState : uint8
{
	EPS_Purchase UMETA(DisplayName = "Purchase"),
	EPS_AlreadyPurchase UMETA(DisplayName = "Already"),
	EPS_LimitGrade UMETA(DisplayName = "LimitGrade"),
	
};

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

	// ���� Buy��ư �Է½� StoreDialog â ���
	UFUNCTION(BluePrintImplementableEvent, Category = "UMG_Game")
	void ShowStoreDialog();

	// ���� ������ ���� ���� Ȯ��
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	bool QualifyingPurchase(int64 itemcode);
	
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void AlreadyPurchase();

	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void LimitGrade();

	// ������ ���� �Ұ� ���� Dialog
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void ShowPurchaseWarning(int64 itemcode);

	UFUNCTION(BluePrintImplementableEvent, Category = "UMG_Game")
	void ChangePoint();

	// StoreDialog
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	TSubclassOf<class UStoreUIWidget> StoreDialogWidgetClass;
	UPROPERTY()
	class UStoreUIWidget* StoreDialogInstance = nullptr;

	// StoreBuyResult
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	TSubclassOf<class UStoreUIWidget> StoreBuyResultWidgetClass;
	UPROPERTY()
	class UStoreUIWidget* StoreBuyResultInstance = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
	TArray<int> ShopItemCodeList;

public:
	// ��/�� ������ ĭ �̵�
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void MoveLeft();
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void MoveRight();

	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
	float Grade;
	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
	float Point;

	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
	int64 ClickItemCode;

	UPROPERTY(BlueprintReadWrite, Category = "UMG_Game")
	EPurchaseState warning;

};
