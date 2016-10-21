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

	/// Events from Unreal.
	virtual void OnConstruction(const FTransform& Transform) override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {};

	/// Get Collision.
	UFUNCTION()
	USphereComponent* GetCoconutCollision();
	/// Get Mesh.
	UFUNCTION()
	UStaticMeshComponent* GetCoconutMesh();
	/// Get Rotation Velocity.
	UFUNCTION()
	FVector GetCoconutVelocityRotation();
	/// Get Rotation Itself.
	UFUNCTION()
	FRotator GetCoconutRotation();
	/// Get Collision Radius.
	UFUNCTION()
	float GetCoconutCollisionRadius();
	/// Get Points.
	UFUNCTION(BlueprintCallable, Category = CoconutPickUp)
	int32 GetPoints();

	/// Others
	UFUNCTION()
	void RotateCoconut();

	/// Spawning 
	/*UFUNCTION()
	void SpawnCoconuts();
	UFUNCTION()
	float RandomXPosition();*/

private:
	/// Sphere Collision.
	UPROPERTY()
	USphereComponent* _CoconutCollision;
	/// Mesh.
	UPROPERTY(EditAnywhere, Category = CoconutPickUp)
	UStaticMeshComponent* _CoconutMesh;
	/// Rotation Velocity.
	UPROPERTY(EditAnywhere, Category = CoconutPickUp)
	FVector _CoconutVelocityRotation;
	/// Rotation itself.
	UPROPERTY()
	FRotator _CoconutRotation;
	/// Radius Sphere Collision.
	UPROPERTY(EditAnywhere, Category = CoconutPickUp)
	float _CoconutCollisionRadius;
	/// Number of points.
	UPROPERTY(EditAnywhere, Category = CoconutPickUp)
	int32 _Points;

	/// Spawning
	/*UPROPERTY(EditAnywhere, Category = CoconutSpawn)
	TSubclassOf<class ATheGalleryPickUp> _CoconutSpawn;
	UPROPERTY(EditAnywhere, Category = CoconutSpawn)
	int _NumberOfSpawningCoconuts;
	UPROPERTY()
	FVector _CoconutSpawnPosition;
	UPROPERTY()
	FRotator _CoconutSpawnRotation;*/
	
};
