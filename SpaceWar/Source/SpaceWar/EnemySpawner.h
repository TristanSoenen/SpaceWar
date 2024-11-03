// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemyBoss;
struct FAllBulletAndEnemyData;
UCLASS()
class SPACEWAR_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int m_SpawnHeight;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int m_SpawnWidth;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int m_EnemySpawnAmount;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	UDataTable* m_DataTable;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AEnemyBoss> m_BPEnemyBoss;
	TArray<FAllBulletAndEnemyData*> m_AllEnemyData;
	TArray<AEnemyBoss*> m_Enemies;
	FVector m_SpawnPositionXZ;
	FRandomStream m_Rand;
	//Functions
	void AddRowNames();
	UFUNCTION()
	void SpawnEnemy();
};
