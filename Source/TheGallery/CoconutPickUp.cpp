// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "CoconutPickUp.h"
#include "Engine.h"
#include "TheGalleryCharacter.h"


// Sets default values
ACoconutPickUp::ACoconutPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_CoconutCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CoconutCollision"));
	_CoconutCollision->SetCollisionProfileName(TEXT("SphereCollision"));
	RootComponent = _CoconutCollision;
	
	_CoconutMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoconutMesh"));
	_CoconutMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CoconutMeshAsset(TEXT("/Game/Meshes/SM_Sphere.SM_Sphere"));
	if (CoconutMeshAsset.Succeeded())
		_CoconutMesh->SetStaticMesh(CoconutMeshAsset.Object);

	_CoconutCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoconutPickUp::OnOverlapBegin);
	_CoconutCollision->OnComponentEndOverlap.AddDynamic(this, &ACoconutPickUp::OnOverlapEnd);
	
	_CoconutCollisionRadius = 100.0f;
	_CoconutCollision->InitSphereRadius(100.0f);
	_CoconutVelocityRotation = FVector(0.0f,0.0f,0.0f);
	_CoconutRotation = FRotator(0.0f, 0.0f, 0.0f);
	_Points = 0;
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
	ATheGalleryCharacter* character = Cast<ATheGalleryCharacter>(OtherActor);

	if (character){
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d Points"),_Points));
		Destroy();
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

int ACoconutPickUp::GetPoints()
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







