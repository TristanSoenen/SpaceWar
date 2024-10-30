// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletData.generated.h"


USTRUCT()
struct FAllBulletAndEnemyData : public FTableRowBase
{
	GENERATED_BODY()

	//Bullet Data
	UPROPERTY(EditAnywhere)
	int Damage{};
	
	UPROPERTY(EditAnywhere)
	float Speed{};
	
	UPROPERTY(EditAnywhere)
	float SpawnDelay{};

	UPROPERTY(EditAnywhere)
	int UnitMoveSpeed{};
	//Enemy data
	UPROPERTY(EditAnywhere)
	float RotationSpeed{};
	
	UPROPERTY(EditAnywhere)
	int BulletSpawnAmount{};

	UPROPERTY(EditAnywhere)
	int ScoreOnKill{};
};

UCLASS()
class SPACEWAR_API ABulletData : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ABulletData();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
