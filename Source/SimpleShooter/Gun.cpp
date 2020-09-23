// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject <USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject <USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	Bullets = MagCapacity;
	AmmoBag = MaxAmmo;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (!IsEmpty() )
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
		
		--Bullets;
		UE_LOG(LogTemp, Warning, TEXT("Bullets in Mag left: %i"), Bullets);

		FHitResult Hit;
		FVector ShotDirection;
		bool bSuccess = GunTrace(Hit, ShotDirection);
		if (bSuccess)
		{
		
			//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
			AActor* HitActor{ Hit.GetActor() };
			if (HitActor != nullptr)
			{
				FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Ammo left") );
	}

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
	{
		return false;
	}

	FVector Location; // out parameter
	FRotator Rotation; // out parameter
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = (Location + Rotation.Vector() * MaxRange);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}
	return OwnerPawn->GetController();
}

bool AGun::IsEmpty() const
{
	if (Bullets <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int32 AGun::GetBullets() const
{
	return Bullets;
}

int32 AGun::GetAmmoBag() const
{
	return AmmoBag;
}

void AGun::ReloadGunMag()
{
	int Difference{ MagCapacity - Bullets };

	if (Difference <= AmmoBag)
	{
		Bullets += Difference;
		AmmoBag -= Difference;
	}
	else if ( Difference > AmmoBag )
	{
		Bullets += AmmoBag;
		AmmoBag = 0;
	}

}

void AGun::AddAmmo(int32 AmmoAmount)
{
	if (AmmoBag + AmmoAmount >= MaxAmmo)
	{
		AmmoBag = MaxAmmo;
	}
	else
	{
		AmmoBag += AmmoAmount;
	}
}