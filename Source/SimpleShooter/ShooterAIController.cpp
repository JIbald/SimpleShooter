// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "ShooterCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacer = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacer != nullptr)
	{
		return ControlledCharacer->IsDead();
	}

	return true;
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//FVector StartLocation = GetPawn()->GetPawnViewLocation(); //worked as well but not sure of difference
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation() );
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//
	//if (LineOfSightTo(PlayerPawn))
	//{
	//	SetFocus(PlayerPawn, EAIFocusPriority::Gameplay); //EAIFocusPriority defaults used
	//	MoveToActor(PlayerPawn, AcceptanceRadius, true);
	//}
	//else
	//{
	//	ClearFocus(EAIFocusPriority::Gameplay);
	//	StopMovement();
	//}

	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//if (LineOfSightTo(PlayerPawn) )
	//{
	//	// Setting PlayerLocation
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation() );
	//	// Setting lastknown
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation() );
	//}
	//else
	//{
	//	// clear PlayerLocation
	//	GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	//}
}