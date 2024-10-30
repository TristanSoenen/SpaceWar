// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceWar/EnemyBoss.h"

#include "Bullet.h"
#include "PlayerSpaceCraft.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBoss::AEnemyBoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyBoss::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//makes the spawn circle rotate so the spawn points arent the same
	m_RotationAngle += m_RotationSpeed * DeltaTime;
	if(m_RotationAngle > 360) m_RotationAngle =0;
	SpawnBullets();

	//goes toward the player
	SimpleSeekBehavior(DeltaTime);
}

void AEnemyBoss::SpawnBullets()
{
	if(m_CanFire == false)
		return;

	m_CanFire = false;

	for(int i = 0; i < m_SpawnPoints; i++)
	{
		float angle = (2 * PI / m_SpawnPoints) * i + m_RotationAngle;
		float z = m_Radius * cos(angle);
		float y = m_Radius * sin(angle);
		FVector spawnPoint = GetActorLocation() + FVector(0, y, z);
		FTransform spawnTransform;
		spawnTransform.SetLocation(spawnPoint);
		auto bullet =  GetWorld()->SpawnActorDeferred<ABullet>(m_BPBullet,spawnTransform);
		
		if(bullet)
		{
			FVector direction = FVector(0, sin(angle), cos(angle));
			direction.Normalize();
			bullet->InitializeBullet(false, 200.0f, direction);
			bullet->FinishSpawning(spawnTransform);
			bullet->SetBulletMaterial();
		}
	}

	GetWorld()->GetTimerManager().SetTimer(m_BulletSpawnerTimer, this, &AEnemyBoss::ResetBulletSpawnTimer, m_SpawnDelay, false);
}

void AEnemyBoss::ResetBulletSpawnTimer()
{
	m_CanFire = true;
	GetWorld()->GetTimerManager().ClearTimer(m_BulletSpawnerTimer);
}

void AEnemyBoss::SimpleSeekBehavior(float deltaTime)
{
	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(player == nullptr)
		return;
	
	FVector playerLocation = player->GetActorLocation();
	FVector direction = playerLocation - GetActorLocation();
	direction.Normalize();
	FVector nextPos = GetActorLocation();
	nextPos += direction * m_MovementSpeed * deltaTime;
	SetActorLocation(nextPos);
}

void AEnemyBoss::KillEnemy()
{
	APlayerSpaceCraft* player = Cast<APlayerSpaceCraft>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if(player == nullptr)
		return;

	player->IncrementScore(m_ScoreOnKill);
	Destroy();
}
