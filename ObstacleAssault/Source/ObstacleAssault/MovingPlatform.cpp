// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	/*
	UE_LOG(LogTemp, Display, TEXT("Member Vector Values: %f %f %f"), StartPosition.X, StartPosition.Y, StartPosition.Z);
	*/
}

/// <summary>
/// Moves the platform
/// </summary>
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector currentLocation = GetActorLocation();
	currentLocation += (Velocity * DeltaTime);
	SetActorLocation(currentLocation);
}

/// <summary>
/// Rotates the platform
/// </summary>
void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator currentRotation = GetActorRotation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

