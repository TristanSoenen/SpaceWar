// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceWar/Bullet.h"

#include "EnemyBoss.h"
#include "SpaceWar/PlayerSpaceCraft.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(m_KillTimer, this, &ABullet::KillBullet, m_KillDelay, false);
	m_Mesh = FindComponentByClass<UStaticMeshComponent>();
	if(m_Mesh)
		m_Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapStart);
}

void ABullet::InitializeBullet(bool playerFired, float speed, const FVector &direction)
{
	m_FiredByPlayer = playerFired;
	m_Direction = direction;
	m_Speed = speed;
}

void ABullet::SetBulletMaterial()
{
	if(m_Mesh == nullptr)
		return;
	
	if(m_FiredByPlayer == true)
		m_Mesh->SetMaterial(0, m_BulletMaterialPlayer);
	else
		m_Mesh->SetMaterial(0, m_BulletMaterialEnemy);
}


// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector nextPosition = GetActorLocation();
	nextPosition += m_Direction * m_Speed * DeltaTime;
	SetActorLocation(nextPosition);
}

void ABullet::KillBullet()
{
	Destroy();
}

void ABullet::OnOverlapStart(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	//check if player is hit
	CheckPlayerHit(OtherActor);

	//Enemy Hit
	CheckEnemyHit(OtherActor);

	//Check Collision Between Bullets
	CheckBulletHit(OtherActor);
}


void ABullet::CheckPlayerHit(AActor* other)
{
	//Returns if the player is null or the bullet is fired by the player
	APlayerSpaceCraft* player = Cast<APlayerSpaceCraft>(other);
	if (player == nullptr || m_FiredByPlayer == true)
		return;
	
	player->ReduceHealth(m_DamageToPlayer);
	KillBullet();
}

void ABullet::CheckBulletHit(AActor *other)
{
	//Destroy both bullets if they hit each other
	ABullet* otherBullet = Cast<ABullet>(other);
	if (otherBullet == nullptr)
		return;
	
	otherBullet->KillBullet();
	KillBullet();
}

void ABullet::CheckEnemyHit(AActor *other)
{
	//Returns if the player is null or the bullet is fired by the player
	AEnemyBoss* enemy = Cast<AEnemyBoss>(other);
	if (enemy == nullptr || m_FiredByPlayer == false)
		return;

	enemy->KillEnemy();
	KillBullet();
}
