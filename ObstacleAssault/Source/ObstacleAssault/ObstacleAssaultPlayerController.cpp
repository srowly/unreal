// Copyright Epic Games, Inc. All Rights Reserved.

#include "ObstacleAssaultPlayerController.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "ObstacleAssault.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "GameFramework/GameModeBase.h"
#include "EnhancedInputComponent.h"

void AObstacleAssaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogObstacleAssault, Error, TEXT("Could not spawn mobile controls widget."));

		}
	}

	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	if (GameMode)
	{
		AActor* PlayerStart = GameMode->FindPlayerStart(this);
		if (PlayerStart)
		{
			RespawnTransform = PlayerStart->GetActorTransform();
		}
	}
}

void AObstacleAssaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(ResetAction, ETriggerEvent::Started, this, &AObstacleAssaultPlayerController::ResetPlayer);
	}
}

void AObstacleAssaultPlayerController::ResetPlayer()
{
	if (APawn* MyPawn = GetPawn())
	{
		MyPawn->SetActorTransform(RespawnTransform);
	}
}


void AObstacleAssaultPlayerController::SetRespawnTransform(const FTransform& NewRespawn)
{
	// save the new respawn transform
	RespawnTransform = NewRespawn;
}
