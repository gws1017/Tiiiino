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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//
	virtual void EndPlay(EEndPlayReason::Type Reason) override;

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

private:
	//키입력 관련 함수
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizonLock(float Axis);
	void OnVerticalLock(float Axis);

	void OnRunning();
	void OffRunning();

	virtual void Jump() override;
	virtual void StopJumping() override;

	void CreateDummy();

private:

	bool CanTumble(float DeltaTime);
	void PlayTumbleMontage(float DeltaTime);

private:

	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		class UAnimMontage* TumbleMontage;

	UPROPERTY(VisibleDefaultsOnly, Category = "Animation")
		float CurrentTumbledTime;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		float MaxTumbledTime;

	bool bCanTumbled;
};
