// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceWar/EnemySpawner.h"
#include "EnemyBoss.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	m_SpawnPositionXZ = GetActorLocation();
	m_SpawnPositionXZ.Z = m_SpawnPositionXZ.Z + m_SpawnHeight;
	
	AddRowNames();
	for(int i = 0; i < m_EnemySpawnAmount; i++)
	{
		SpawnEnemy();
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawner::AddRowNames()
{
	const FString contextWarning ={"Row not Found in data Table" };
	for(int i = 0; i < 4; i++)
	{
		//Chat gpt helped with the FName
		FName enemy = FName(*("Enemy" + FString::FromInt(i)));
		if(auto data = m_DataTable->FindRow<FAllBulletAndEnemyData>(enemy, contextWarning, true))
			m_AllEnemyData.Add(data);
	}
}

void AEnemySpawner::SpawnEnemy()
{
	FTransform spawnTransform;
	float randPos = m_Rand.FRandRange(m_SpawnPositionXZ.Y - m_SpawnWidth / 2, m_SpawnPositionXZ.Y + m_SpawnWidth / 2);
	spawnTransform.SetLocation(FVector(m_SpawnPositionXZ.X, randPos, m_SpawnPositionXZ.Z));
	if(auto enemy = GetWorld()->SpawnActorDeferred<AEnemyBoss>(m_BPEnemyBoss, spawnTransform))
	{
		int32 idx = m_Rand.RandRange(0, m_AllEnemyData.Num() - 1);
		enemy->InitializeEnemy(m_AllEnemyData[idx]);
		enemy->FinishSpawning(spawnTransform);
		enemy->m_OnEnemyDeath.AddDynamic(this, &AEnemySpawner::SpawnEnemy);
		m_Enemies.Add(enemy);
	}
}
