// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SPACEWAR_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetKillDelay(float delay) { m_KillDelay = delay; }
	void InitializeBullet(bool playerFired, float speed, const FVector& direction);
	
	UFUNCTION()
	void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void SetBulletMaterial();
private:
	//functions 
	void CheckPlayerHit(AActor* other);
	void CheckBulletHit(AActor* other);
	void CheckEnemyHit(AActor* other);
	
	//Bullet params
	UPROPERTY(EditAnywhere)
	float m_Speed{};
	UPROPERTY(EditAnywhere)
	UMaterialInstance* m_BulletMaterialPlayer;
	UPROPERTY(EditAnywhere)
	UMaterial* m_BulletMaterialEnemy;
	FVector m_Direction{};
	int m_DamageToPlayer = 25;
	bool m_FiredByPlayer;
	UPROPERTY()
	UStaticMeshComponent* m_Mesh;
	
	//Timer
	FTimerHandle m_KillTimer;
	void KillBullet();
	float m_KillDelay = 5.0f;
};
