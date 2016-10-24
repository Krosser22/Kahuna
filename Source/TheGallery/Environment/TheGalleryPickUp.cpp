// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryPickUp.h"
#include "Characters/TheGalleryCharacter.h"
#include "Game/TheGalleryGameInstance.h"

// Sets default values
ATheGalleryPickUp::ATheGalleryPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize
	RotationSpeed = 0.0f;
	Points = 0;
	CollisionRadius = 100.0f;

	// Create Collision
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(CollisionRadius);
	CollisionComponent->SetupAttachment(RootComponent);

	// Add Events
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATheGalleryPickUp::OnBeginOverlap);

	// Create Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CollisionComponent);
	Mesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	// Spawn
	/*
	_CoconutSpawnPosition = FVector(0.0f,0.0f,0.0f);
	_CoconutSpawnRotation = FRotator(0.0f,0.0f,0.0f);
	_NumberOfSpawningCoconuts = 0;
	*/
}


void ATheGalleryPickUp::BeginPlay()
{
	Super::BeginPlay();
	// Initialize Sphere Collision Radius.
	CollisionComponent->SetSphereRadius(CollisionRadius);
	
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
		//SpawnCoconuts();*/
		AddPoints();
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

/* 
ATheGalleryPickUp::SpawnCoconuts() {
	for (int i = 0; i < _NumberOfSpawningCoconuts; i++) {
		_CoconutSpawnPosition = FVector(GetActorLocation().X + RandomXPosition(), GetActorLocation().Y, GetActorLocation().Z);
		ATheGalleryPickUp* Spawn = GetWorld()->SpawnActorDeferred<ATheGalleryPickUp>(_CoconutSpawn, _CoconutSpawnPosition, _CoconutSpawnRotation);
		if (Spawn)
		{
			Spawn->_Points = _Points;
			Spawn->_CoconutVelocityRotation = _CoconutVelocityRotation;
			Spawn->_CoconutCollisionRadius = _CoconutCollisionRadius;
			Spawn->_NumberOfSpawningCoconuts = _NumberOfSpawningCoconuts;
			UGameplayStatics::FinishSpawningActor(Spawn, FTransform(_CoconutSpawnRotation, _CoconutSpawnPosition));
		} 
	}
}

float ATheGalleryPickUp::RandomXPosition() {
	float Position = 0.0f;
	Position = FMath::RandRange(-500.0f, 500.0f);
	return Position;
}
*/







