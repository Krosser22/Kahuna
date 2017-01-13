// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryPickUp.h"
#include "Characters/Player/TheGalleryCharacter.h"
#include "Game/TheGalleryGameInstance.h"

// Sets default values
ATheGalleryPickUp::ATheGalleryPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize
	RotationSpeed = 0.0f;
	Points = 0;

	// Create Collision
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(60.0f);
	CollisionComponent->SetupAttachment(RootComponent);

	// Add Events
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryPickUp::OnBeginOverlap);

	// Create Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CollisionComponent);
	Mesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}


void ATheGalleryPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATheGalleryPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Rotate every Frame.
	RotatePickup(DeltaTime);
}

void ATheGalleryPickUp::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Call to Character
	ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);

	if (Character)
	{
    Character->CoconutsLocation.Push(CollisionComponent->GetRelativeTransform().GetLocation());
    Character->CoconutsPoints.Push(Points);
		AddPoints();
		PlaySound();
		// Destroy Actor.
		Destroy();
	}
}

int32 ATheGalleryPickUp::GetPoints()
{
	return Points;
}

void ATheGalleryPickUp::RotatePickup(float DeltaTime)
{
	// Rotate Actor.
	FRotator Rotation = FRotator(0.0f, RotationSpeed, 0.0f);
	Mesh->AddRelativeRotation(Rotation * DeltaTime, false);
}

void ATheGalleryPickUp::AddPoints()
{
	// Call To GameInstance.
	UTheGalleryGameInstance* GameInstance = Cast<UTheGalleryGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		// Increase Points.
		int32 TotalPoints = GameInstance->GetPickUpPoints();
		TotalPoints += Points;
		GameInstance->SetPickUpPoints(TotalPoints);
	}
}

void ATheGalleryPickUp::PlaySound_Implementation()
{

}
