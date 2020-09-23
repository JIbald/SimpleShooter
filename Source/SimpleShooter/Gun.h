// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

	UFUNCTION(BlueprintPure)
	bool IsEmpty() const;

	void AddAmmo(int32 AmmoAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 GetBullets() const;

	int32 GetAmmoBag() const;

	void ReloadGunMag();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	float MaxRange{ 10000 };

	UPROPERTY(EditAnywhere)
	float Damage{ 25 };

	UPROPERTY(EditAnywhere)
	int MaxAmmo{ 60 };

	UPROPERTY(EditAnywhere)
	int MagCapacity{ 20 };

	UPROPERTY(VisibleAnywhere)
	int AmmoBag;

	UPROPERTY(VisibleAnywhere)
	int Bullets;

	bool  GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;
};
