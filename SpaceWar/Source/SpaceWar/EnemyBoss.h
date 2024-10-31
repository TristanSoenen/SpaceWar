// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBoss.generated.h"





class ABulletData;
struct FAllBulletAndEnemyData;
class ABullet;
UCLASS()
class SPACEWAR_API AEnemyBoss : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBoss();
	//void InitializeParameters();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	TSubclassOf<ABullet> m_BPBullet;
	void KillEnemy();
private:
	//Behavior functions
	void SimpleSeekBehavior(float deltaTime);

	//Timer
	FTimerHandle m_BulletSpawnerTimer;
	bool m_CanFire = true;
	void ResetBulletSpawnTimer();
	
	FAllBulletAndEnemyData* m_Data{};
	UPROPERTY(EditAnywhere, Category = "Data")
	UDataTable* m_DataTable;
	float m_Radius = 100.0f;
	float m_RotationAngle = 0.0f;

	//Spawner
	void SpawnBullets();
};
