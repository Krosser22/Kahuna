// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "GroundSpikeTrap.h"


// Sets default values
AGroundSpikeTrap::AGroundSpikeTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGroundSpikeTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGroundSpikeTrap::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
