// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TheGalleryPickUp.generated.h"


UCLASS()
class THEGALLERY_API ATheGalleryPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheGalleryPickUp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Events from Unreal.
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Get Points.
	UFUNCTION(BlueprintCallable, Category = PickUp)
	int32 GetPoints();

	// Others
	UFUNCTION()
	void RotatePickup(float DeltaTime);

	/*
	// Spawning
	UFUNCTION()
	void SpawnCoconuts();
	UFUNCTION()
	float RandomXPosition();
	*/

private:
	// Sphere Collision.
	UPROPERTY(Category = "Collision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

	// Mesh.
	UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *Mesh;

	// Rotation Velocity.
	UPROPERTY(EditAnywhere, Category = PickUp)
	float RotationSpeed;

	// Radius Sphere Collision.
	UPROPERTY(EditAnywhere, Category = PickUp)
	float CollisionRadius;

	// Number of points.
	UPROPERTY(EditAnywhere, Category = PickUp)
	int32 Points;

	// Spawning (enemies)
	/*
	UPROPERTY(EditAnywhere, Category = CoconutSpawn)
	TSubclassOf<class ATheGalleryPickUp> _CoconutSpawn;
	UPROPERTY(EditAnywhere, Category = CoconutSpawn)
	int _NumberOfSpawningCoconuts;
	UPROPERTY()
	FVector _CoconutSpawnPosition;
	UPROPERTY()
	FRotator _CoconutSpawnRotation;
	*/
};
