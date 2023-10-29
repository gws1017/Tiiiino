// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreUIWidget.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EQualifyingPurchase : uint8
{
	EQP_AlreadyPurchase,	// �̹� ������
	EDC_GradeLimit,			// ���� ����
	EDC_Possible,			// ���� ����
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
	bool QualifyingPurchase();
	
	// ������ ���� �Ұ� ���� Dialog
	UFUNCTION(BluePrintImplementableEvent, Category = "UMG_Game")
	void ShowPurchaseWarning(bool check);

	// StoreDialog
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	TSubclassOf<class UStoreUIWidget> StoreDialogWidgetClass;
	UPROPERTY()
	class UStoreUIWidget* StoreDialogInstance = nullptr;

public:
	// ��/�� ������ ĭ �̵�
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void MoveLeft();
	UFUNCTION(Blueprintcallable, Category = "UMG_Game")
	void MoveRight();

private:
	UPROPERTY(EditAnywhere, Category = "UMG_Game")
	EQualifyingPurchase QualifyCheck = EQualifyingPurchase::EDC_Possible;
};
