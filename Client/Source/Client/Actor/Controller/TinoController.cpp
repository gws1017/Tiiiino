#include "Actor/Controller/TinoController.h"
#include "Actor/Character/TinoCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Network/Network.h"
#include "MenuUI/DialogUIWidget.h"
#include "MenuUI/FinishGameUIWidget.h"
#include "LobbyUIWidget.h"

#include "Global.h"

ATinoController::ATinoController()
	:MaxDummyCount(8),
	DummyOffset(200)
{
}

void ATinoController::BeginPlay()
{
	Super::BeginPlay();

	//로비 인스턴스 생성(인스턴스 한번만 생성하고 재사용)
	SetLobbyInstance();

	DialogUI = Cast<UDialogUIWidget>(CreateWidget(GetWorld(), DialogUIClass));
	if (StartingWidgetClass != nullptr && UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Lobby")
	{
		if (false == Network::GetNetwork()->bIsConnectedLobby)
		{
			if(bIsLobbyConnected)
				ChangeMenuWidget(StartingWidgetClass);		
			else 
				DisconnectNetwork();
		}
		else {
			SetInputUIMode();
		}
	}
	//ChangeMenuWidget(StartingWidgetClass);
	
}

void ATinoController::SetLobbyInstance()
{
	if (!!LobbyWidgetClass)
	{
		LobbyUIInstance = CreateWidget<ULobbyUIWidget>(GetWorld(), LobbyWidgetClass);
	}
}

void ATinoController::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ATinoController::CreateDummy()
{
	return;
	if (TinoCharacterClass)
	{
		ATinoCharacter* Dummy = GetWorld()->SpawnActor<ATinoCharacter>(TinoCharacterClass);

		if (MaxDummyCount > DummyArray.Num())
		{
			FVector Location = GetPawn()->GetActorLocation();
			FVector Dir = GetPawn()->GetActorForwardVector();
			Location += FVector(Dir.X * (DummyArray.Num()+1) * DummyOffset,0.f,0.f);
			Dummy->SetActorLocation(Location);
			DummyArray.Add(Dummy);
		}
	}
}

void ATinoController::SetInputUIMode()
{
	FInputModeUIOnly LobbyInputMode;
	SetInputMode(LobbyInputMode);
	SetShowMouseCursor(true);
}

void ATinoController::SetInputGameMode()
{
	FInputModeGameOnly GameInputMode;
	SetInputMode(GameInputMode);
	SetShowMouseCursor(false);
}

void ATinoController::OpenInGameUI()
{
	if (!!DialogUI)
	{
		DialogUI->RenderInGameMenuUI();
		DialogUI->AddToViewport();
	}
}

void ATinoController::RemoveDialogUI()
{
	if (!!DialogUI)
	{
		DialogUI->ResetWindow();
		DialogUI->RemoveFromParent();
	}
}

void ATinoController::UIAlertMessage(EDialogUICheck check)
{
	if (!!DialogUI)
	{
		DialogUI->FixedAlertMessage();
		if (check == EDialogUICheck::EDC_LoginFailed)
		{
			DialogUI->SetLoginFailedUI();
		}
		else if (check == EDialogUICheck::EDC_CASuccess)
		{
			DialogUI->SetCreateAccountSuccessUI();
		}
		else if (check == EDialogUICheck::EDC_CAFailed)
		{
			DialogUI->SetCreateAccountFailedUI();
		}

		DialogUI->RenderUIAlertMessage();
		DialogUI->AddToViewport();
	}
}

void ATinoController::SetGradeUI(float GradeValue)
{
	if (LobbyUIInstance)LobbyUIInstance->Grade = GradeValue;
}

float ATinoController::GetGradeUI()
{
	if (LobbyUIInstance) return LobbyUIInstance->Grade;
	return 0.f;
}

void ATinoController::DisconnectNetwork()
{
	// if Network is disconnected 

	if (!!DialogUI)
	{
		DialogUI->RenderDisconnectNetworkWindow();
		DialogUI->AddToViewport();
	}
}

void ATinoController::ShowGameResult(int level, int rank, double grade, int point)
{
	FinishGameUI = Cast<UFinishGameUIWidget>(CreateWidget(GetWorld(), FinishGameUIClass));
	if (!!FinishGameUI)
	{
		FinishGameUI->ShowResult(level, rank, grade, point);
		FinishGameUI->AddToViewport();
	}
}
