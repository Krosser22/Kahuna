// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TheGalleryPickUp.generated.h"


UCLASS()
class THEGALLERY_API ATheGalleryPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	/**
	* Sets default values for this actor's properties.
	*/
	ATheGalleryPickUp();

	/**
	* Called when the game starts or when spawned.
	*/
	virtual void BeginPlay() override;
	
	/**
	* Update
	* @param DeltaTime - The time in seconds it took to complete the last frame.
	*/
	virtual void Tick( float DeltaSeconds ) override;
	
	/**
	* Called when the object starts to overlap with a specific component.
	* @param HitComp - Pointer to the Component you are hitting with. 
	* @param OtherActor -  Pointer to the Actor you are overlapping with.
	* @param OtherComp -  Pointer to the Component you are overlapping with. 
	* @param OtherBodyIndex - Body index of the Component you are overlaping with.
	* @param bFromSweep -  Hitting with another collision unit.
	* @param SweepResult - Structure containing information about one hit of a trace, such as point of impact and surface normal at that point.
	*/
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/**
	* Get quantity of points from one pickup.
	*/
	UFUNCTION(BlueprintCallable, Category = PickUp)
	int32 GetPoints();

	/**
	* Rotate a pickup.
	* @param DeltaTime - The time in seconds it took to complete the last frame.
	*/
	UFUNCTION()
	void RotatePickup(float DeltaTime);

	/**
	* Incresase player pickup points
	*/
	UFUNCTION(BlueprintCallable, Category = PickUp)
	void AddPoints();

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

	// Number of points from one pickup.
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
