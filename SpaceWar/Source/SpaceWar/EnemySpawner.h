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
	int m_RectWidth;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int m_RectHeight;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int m_EnemySpawnAmount;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	UDataTable* m_DataTable;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AEnemyBoss> m_BPEnemyBoss;
	TArray<FVector> m_SpawnPoints;
	TArray<AEnemyBoss*> m_Enemies;
	//TArray<FName> m_RowNamesDataTable;
	TArray<FAllBulletAndEnemyData*> m_AllEnemyData;

	//Functions
	void AddSpawnPoints();
	void AddRowNames();
	void SpawnEnemy();
};
