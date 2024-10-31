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

	AddRowNames();
	AddSpawnPoints();
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

void AEnemySpawner::AddSpawnPoints()
{
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Y -= m_RectWidth / 2;
	SpawnLocation.Z += m_RectHeight / 2;
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			SpawnLocation.Y += (m_RectWidth / 2) * j;
			m_SpawnPoints.Add(SpawnLocation);
		}
		SpawnLocation.Y -= m_RectWidth;
		SpawnLocation.Z -= m_RectHeight;
	}
	SpawnLocation.Y -= m_RectWidth;
	SpawnLocation.Z += m_RectHeight / 2;
	m_SpawnPoints.Add(SpawnLocation);
	SpawnLocation.Y += m_RectWidth;
	m_SpawnPoints.Add(SpawnLocation);
}

void AEnemySpawner::AddRowNames()
{
	const FString contextWarning ={"Row not Found in data Table" };
	for(int i = 0; i < 4; i++)
	{
		if(auto data = m_DataTable->FindRow<FAllBulletAndEnemyData>("Enemy0", contextWarning, true))
			m_AllEnemyData.Add(data);
	}
}

void AEnemySpawner::SpawnEnemy()
{
	FTransform spawnTransform;
	spawnTransform.SetLocation(m_SpawnPoints[rand() % m_SpawnPoints.Num()]);
	if(auto enemy = GetWorld()->SpawnActorDeferred<AEnemyBoss>(m_BPEnemyBoss, spawnTransform))
	{
		enemy->InitializeEnemy(m_AllEnemyData[rand() % 4]);
		enemy->FinishSpawning(spawnTransform);
		m_Enemies.Add(enemy);
	}
}

