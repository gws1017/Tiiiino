// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/BaseCharacter.h"
#include "TinoCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CLIENT_API ATinoCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	ATinoCharacter();

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Ű�Է� ���� �Լ�
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizonLock(float Axis);
	void OnVerticalLock(float Axis);

	void OnRunning();
	void OffRunning();

	void CreateDummy();

private:

	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;
};
