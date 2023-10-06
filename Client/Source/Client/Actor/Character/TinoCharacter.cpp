#include "Actor/Character/TinoCharacter.h"
#include "Actor/Controller/TinoController.h"
#include "Global.h"

#include "Network/Network.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actor/Character/CharacterAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "MenuUI/InGameUIWidget.h"

ATinoCharacter::ATinoCharacter()
	:MaxTumbledTime(1.0f),
	MovementState(EMovementState::EMS_Normal)
{
	PrimaryActorTick.bCanEverTick = true;
	UHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	UHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
}

void ATinoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATinoCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATinoCharacter::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizonLock", this, &ATinoCharacter::OnHorizonLock);
	PlayerInputComponent->BindAxis("VerticalLock", this, &ATinoCharacter::OnVerticalLock);

	PlayerInputComponent->BindAction("CreateDummy", EInputEvent::IE_Pressed, this, &ATinoCharacter::CreateDummy);
	PlayerInputComponent->BindAction("Align", EInputEvent::IE_Pressed, this, &ATinoCharacter::Align);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ATinoCharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ATinoCharacter::StopJumping);
	PlayerInputComponent->BindAction("Dive", EInputEvent::IE_Pressed, this, &ATinoCharacter::Dive);
}

// Called when the game starts or when spawned
void ATinoCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!!GetController())
	{
		if (GetController()->IsPlayerController())
		{
			UInGameUIWidget* InGameUIWidgetInstance = CreateWidget<UInGameUIWidget>(GetWorld(), UInGameUIWidget::StaticClass());
			FSoftClassPath WidgetSource(TEXT("WidgetBlueprint'/Game/MenuUI/InGame/InGameUI.InGameUI_C'"));
			auto WidgetClass = WidgetSource.TryLoadClass<UUserWidget>();
			if (nullptr == WidgetClass)
			{

			}

			InGameWidgetInstance = CreateWidget<UInGameUIWidget>(GetWorld(), WidgetClass);
			InGameWidgetInstance->AddToViewport();
		}
		else
		{
			GetCharacterMovement()->BrakingDecelerationWalking = 0;
			GetCharacterMovement()->BrakingFrictionFactor = 0;
			GetCharacterMovement()->GravityScale = 0.0;
		}
	}

}

void ATinoCharacter::EndPlay(EEndPlayReason::Type Reason)
{
	Network::GetNetwork()->release();
}

// Called every frame
void ATinoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayTumbleMontage(DeltaTime);
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();

		float PitchClamp = FMath::ClampAngle(Rotation.Pitch, -45.f, 30.f);
		FRotator RotationControl(PitchClamp, Rotation.Yaw, Rotation.Roll);
		SleepEx(0, true);

		if (Network::GetNetwork()->bIsConnected)
		{
			if (GetController())
			{
				if (!GetController()->IsPlayerController())
				{
					//서버랑 연결 돼 있을 때만 상대 캐릭터 보간하려 시도. 
					//Update GroundSpeedd (22-04-05)
					//GroundSpeedd = ServerStoreGroundSpeed;
					//Update Interpolation (23-09-27)
					GetCharacterMovement()->Velocity = ServerCharMovingSpeed;

				}
				else {
					if (Network::GetNetwork()->bGameIsStart)
					{
						auto pos = GetTransform().GetLocation();
						auto rot = GetTransform().GetRotation();

						ServerSyncElapsedTime += DeltaTime;
						if (ServerSyncDeltaTime < ServerSyncElapsedTime)
						{
							send_move_packet(Network::GetNetwork()->s_socket, Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance())->bIsAir, pos.X, pos.Y, pos.Z, rot, GetVelocity().Size2D(), GetCharacterMovement()->Velocity);
							ServerSyncElapsedTime = 0.0f;
						}

						float CharXYVelocity = ((ACharacter::GetCharacterMovement()->Velocity) * FVector(1.f, 1.f, 0.f)).Size();
					}

				}
			}
			
		}


		// 10/04 가만히 있을 때 충돌하지 않는 부분을 해결하기 위한 코드 추가
		FHitResult OutHit;
		GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(0.f, 0.f, 0.01f), GetActorRotation(), true, OutHit);
		GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(0.f, 0.f, -0.01f), GetActorRotation(), true, OutHit);

	}
}
bool ATinoCharacter::CanTumble(float DeltaTime)
{
	bool ret = true;

	ret &= GetCharacterMovement()->IsFalling();
	//ret &= (GetVelocity().Z != FMath::IsNearlyZero());

	if (ret && MaxTumbledTime > CurrentTumbledTime) CurrentTumbledTime += DeltaTime;
	bCanTumbled = (CurrentTumbledTime >= MaxTumbledTime);

	return ret;
}


void ATinoCharacter::PlayTumbleMontage(float DeltaTime)
{
	CanTumble(DeltaTime);

	if (bCanTumbled && !GetCharacterMovement()->IsFalling())
	{
		if (TumbleMontage)
		{
			CurrentTumbledTime = 0.f;
			bCanTumbled = false;
			if (GetController())
			{
				if (GetController()->IsPlayerController())
					send_action_packet(Network::GetNetwork()->s_socket, 3);
			}
			PlayAnimMontage(TumbleMontage);
		}
		else
			CLog::Log("Asset TumbleMontage is Invalid");
	}
	else if (!bCanTumbled && !GetCharacterMovement()->IsFalling())
	{
		CurrentTumbledTime = 0.f;
	}
}

void ATinoCharacter::Align()
{
	GetController()->SetControlRotation(GetActorForwardVector().Rotation());
}

void ATinoCharacter::DiveBegin()
{
}

void ATinoCharacter::DiveEnd()
{
	bIsDiving = false;
}

void ATinoCharacter::OnAccelEffect()
{
	//비네트 값을 조절해 가속 이펙트를 킴
	Camera->PostProcessSettings.bOverride_VignetteIntensity = true;
	Camera->PostProcessSettings.VignetteIntensity = CustomVignetteIntensity;
}

void ATinoCharacter::OffAccelEffect()
{
	Camera->PostProcessSettings.bOverride_VignetteIntensity = false;

}
void ATinoCharacter::TimerStart()
{
	UInGameUIWidget* InGameUIWidgetInstance = CreateWidget<UInGameUIWidget>(GetWorld(), UInGameUIWidget::StaticClass());
	FSoftClassPath WidgetSource(TEXT("WidgetBlueprint'/Game/MenuUI/InGame/InGameUI.InGameUI_C'"));
	auto WidgetClass = WidgetSource.TryLoadClass<UUserWidget>();
	if (nullptr == WidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("TimerStart Error"));
	}
	GetWorldTimerManager().SetTimer(InGameUITimerHandle, this, &ATinoCharacter::TimerEnd, 1.f, true);
	
	
}

void ATinoCharacter::TimerEnd()
{

	// 유효성 확인
	if (InGameWidgetInstance)
	{
		// UInGameUIWidget의 TimerRun 함수 호출
		InGameWidgetInstance->TimerRun();
	}
	if (InGameWidgetInstance->GetRestGameTime() < 0)
	{
		InGameWidgetInstance->TimerEnd();
		GetWorldTimerManager().ClearTimer(InGameUITimerHandle);
	}

}

void ATinoCharacter::Dive()
{
	if (DiveMontage && CanDive())
	{
		bIsDiving = true;
		if (GetController())
		{
			if (GetController()->IsPlayerController())
				send_action_packet(Network::GetNetwork()->s_socket, 2);
		}
		PlayAnimMontage(DiveMontage);
	}
}

void ATinoCharacter::OnMoveForward(float Axis)
{
	if (CanMove())
	{
		FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
		FVector dir = FQuat(rotator).GetForwardVector().GetUnsafeNormal2D();

		AddMovementInput(dir, Axis);
	}

}

void ATinoCharacter::OnMoveRight(float Axis)
{
	if (CanMove())
	{
		FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
		FVector dir = FQuat(rotator).GetRightVector().GetUnsafeNormal2D();

		AddMovementInput(dir, Axis);
	}

}

void ATinoCharacter::OnHorizonLock(float Axis)
{
	AddControllerYawInput(Axis);
}

void ATinoCharacter::OnVerticalLock(float Axis)
{
	AddControllerPitchInput(Axis);
}

void ATinoCharacter::CreateDummy()
{
	GetController<ATinoController>()->CreateDummy();
}

void ATinoCharacter::Jump()
{
	if (CanMove() && GetCharacterMovement()->IsFalling() == false)
	{
		Super::Jump();
		if (GetController())
		{
			if (GetController()->IsPlayerController())
				send_action_packet(Network::GetNetwork()->s_socket, 1);
		}

	}

	if (GetController())
	{
		if (!GetController()->IsPlayerController())
		{
			Super::Jump();
		}
	}
}

void ATinoCharacter::StopJumping()
{
	Super::StopJumping();
	SetMovementState(EMovementState::EMS_Normal);
}

void ATinoCharacter::PlayTumbleMontage()
{
	PlayAnimMontage(TumbleMontage);
}

void ATinoCharacter::DisableInputMode()
{
	DisableInput(GetController<APlayerController>());
}

void ATinoCharacter::EnableInputMode()
{
	EnableInput(GetController<APlayerController>());
}

bool ATinoCharacter::CanMove()
{
	bool ret = true;

	switch (MovementState)
	{
	case EMovementState::EMS_Normal:
	case EMovementState::EMS_Fall:
		ret = true;
		break;
	default:
		ret = false;
	}
	return ret;
}

bool ATinoCharacter::CanDive()
{
	bool ret = false;

	switch (MovementState)
	{
	case EMovementState::EMS_Normal:
	case EMovementState::EMS_Fall:
		ret = true;
		break;
	default:
		ret = false;
		break;
	}
	ret &= (bIsDiving == false);
	return ret;
}

