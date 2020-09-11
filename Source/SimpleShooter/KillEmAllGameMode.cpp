// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "ShooterAIController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	//UE_LOG(LogTemp, Warning, TEXT("A Pawn was killed"));

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()) )
	{
		if (!AIController->IsDead() )
		{
			return;
		}
	}
	
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// bool IsPlayerController = Controller->IsPlayerController();
		bool bIsWinner = ( Controller->IsPlayerController() == bIsPlayerWinner ); // smart line
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}