// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoconutPickUp.generated.h"


UCLASS()
class THEGALLERY_API ACoconutPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoconutPickUp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/// Unreal
	virtual void OnConstruction(const FTransform& Transform) override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {};

	/// Getters
	UFUNCTION()
	USphereComponent* GetCoconutCollision();
	UFUNCTION()
	UStaticMeshComponent* GetCoconutMesh();
	UFUNCTION()
	FVector GetCoconutVelocityRotation();
	UFUNCTION()
	FRotator GetCoconutRotation();
	UFUNCTION()
	float GetCoconutCollisionRadius();
	UFUNCTION()
	int GetPoints();

	/// Others
	UFUNCTION()
	void RotateCoconut();

private:
	UPROPERTY()
	USphereComponent* _CoconutCollision;
	UPROPERTY()
	UStaticMeshComponent* _CoconutMesh;
	UPROPERTY(EditAnywhere, Category = CoconutPickUp)
	FVector _CoconutVelocityRotation;
	UPROPERTY()
	FRotator _CoconutRotation;
	UPROPERTY(EditAnywhere, Category = CoconutPickUp)
	float _CoconutCollisionRadius;
	UPROPERTY(EditAnywhere, Category = CoconutPickUp)
	int _Points;
};
