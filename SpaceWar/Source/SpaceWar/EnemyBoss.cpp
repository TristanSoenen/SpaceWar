// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceWar/EnemyBoss.h"

#include "Bullet.h"

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
	if(m_RotationAngle > 360) m_RotationAngle -= 360;
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
		auto bullet =  GetWorld()->SpawnActor<ABullet>(m_BPBullet, spawnPoint, GetActorRotation());

		FVector direction = FVector(0, sin(angle), cos(angle));
		direction.Normalize();
		bullet->SetDirection(direction);
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
	FVector playerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector direction = playerLocation - GetActorLocation();
	direction.Normalize();
	FVector nextPos = GetActorLocation();
	nextPos += direction * m_MovementSpeed * deltaTime;
	SetActorLocation(nextPos);
}
