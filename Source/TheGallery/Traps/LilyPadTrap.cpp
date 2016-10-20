// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "LilyPadTrap.h"


// Sets default values
ALilyPadTrap::ALilyPadTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALilyPadTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALilyPadTrap::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

