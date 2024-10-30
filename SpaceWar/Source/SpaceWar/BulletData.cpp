// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceWar/BulletData.h"

// Sets default values
ABulletData::ABulletData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABulletData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

