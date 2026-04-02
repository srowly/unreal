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

	int numberOfApples = 10;
	int numberOfOranges = 7;

	UE_LOG(LogTemp, Display, TEXT("Number of Apples: %d Oranges: %d"), numberOfApples, numberOfOranges);

	float pi = 3.14f;

	UE_LOG(LogTemp, Display, TEXT("Pi: %f"), pi);

	FString myName = "Sam";

	UE_LOG(LogTemp, Display, TEXT("My name is %s"), *myName);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

