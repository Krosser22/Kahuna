// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "CoconutPickUp.h"
#include "TheGalleryCharacter.h"
#include "Engine.h"
#include "OwnGameInstance.h"


// Sets default values
ACoconutPickUp::ACoconutPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// Create Collision
	_CoconutCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CoconutCollision"));
	_CoconutCollision->SetCollisionProfileName(TEXT("SphereCollision"));
	RootComponent = _CoconutCollision;
	
	/// Create Mesh
	_CoconutMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoconutMesh"));
	_CoconutMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CoconutMeshAsset(TEXT("/Game/Meshes/SM_Sphere.SM_Sphere"));
	if (CoconutMeshAsset.Succeeded())
		_CoconutMesh->SetStaticMesh(CoconutMeshAsset.Object);	
		
	/// Add Events
	_CoconutCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoconutPickUp::OnOverlapBegin);
	_CoconutCollision->OnComponentEndOverlap.AddDynamic(this, &ACoconutPickUp::OnOverlapEnd);
	
	/// Initialize
	_CoconutCollisionRadius = 100.0f;
	_CoconutCollision->InitSphereRadius(100.0f);
	_CoconutVelocityRotation = FVector(0.0f,0.0f,0.0f);
	_CoconutRotation = FRotator(0.0f, 0.0f, 0.0f);
	_Points = 0;


	/// Spawn
	/*_CoconutSpawnPosition = FVector(0.0f,0.0f,0.0f);
	_CoconutSpawnRotation = FRotator(0.0f,0.0f,0.0f);
	_NumberOfSpawningCoconuts = 0;*/
}

// Called when the game starts or when spawned
void ACoconutPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoconutPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateCoconut();
}

void ACoconutPickUp::OnConstruction(const FTransform& Transform) {
	_CoconutCollision->SetSphereRadius(_CoconutCollisionRadius);
}

void ACoconutPickUp::OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ATheGalleryCharacter* Character = Cast<ATheGalleryCharacter>(OtherActor);

	if (Character){
		UOwnGameInstance* OGI = Cast<UOwnGameInstance>(GetGameInstance());

		if (OGI){
			OGI->IncreaseTotalPointsCoconuts(_Points);
			
			//SpawnCoconuts();
			Destroy();
		}
	}
}

USphereComponent* ACoconutPickUp::GetCoconutCollision()
{
	return _CoconutCollision;
}

UStaticMeshComponent* ACoconutPickUp::GetCoconutMesh()
{
	return _CoconutMesh;
}

FVector ACoconutPickUp::GetCoconutVelocityRotation()
{
	return _CoconutVelocityRotation;
}

FRotator ACoconutPickUp::GetCoconutRotation()
{
	return _CoconutRotation;
}

float ACoconutPickUp::GetCoconutCollisionRadius()
{
	return _CoconutCollisionRadius;
}

int32 ACoconutPickUp::GetPoints()
{
	return _Points;
}

void ACoconutPickUp::RotateCoconut()
{
	_CoconutRotation.Roll += _CoconutVelocityRotation.X;
	_CoconutRotation.Pitch += _CoconutVelocityRotation.Y;
	_CoconutRotation.Yaw += _CoconutVelocityRotation.Z;
	_CoconutMesh->SetRelativeRotation(_CoconutRotation);
}

/* ACoconutPickUp::SpawnCoconuts() {
	for (int i = 0; i < _NumberOfSpawningCoconuts; i++) {
		_CoconutSpawnPosition = FVector(GetActorLocation().X + RandomXPosition(), GetActorLocation().Y, GetActorLocation().Z);
		ACoconutPickUp* Spawn = GetWorld()->SpawnActorDeferred<ACoconutPickUp>(_CoconutSpawn, _CoconutSpawnPosition, _CoconutSpawnRotation);
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

float ACoconutPickUp::RandomXPosition() {
	float Position = 0.0f;
	Position = FMath::RandRange(-500.0f, 500.0f);
	return Position;
}*/







