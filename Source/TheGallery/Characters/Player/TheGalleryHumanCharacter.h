// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheGalleryCharacter.h"
#include "TheGalleryAnimalCharacter.h"
#include "../../Projectiles/TheGalleryIceSpell.h"
#include "TheGalleryHumanCharacter.generated.h"

UCLASS()
class THEGALLERY_API ATheGalleryHumanCharacter : public ATheGalleryCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ATheGalleryHumanCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

  // Transform to animal form
	UFUNCTION(BlueprintCallable, Category = "Transformation")
	void TransformToAnimal();

	void StartSpinKickCD();
	void UpdateCooldowns(float DeltaTime);
	void SpinKickDamage();

private:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

  void CastIceSpell();

  // Animal character template that is going to be spawned
	UPROPERTY(EditAnywhere, Category = "Transformation")
	TSubclassOf<ATheGalleryAnimalCharacter> AnimalTemplate;

  // Blueprint template that is going to be spawned
  UPROPERTY(EditAnywhere, Category = "Transformation")
  TSubclassOf<ATheGalleryIceSpell> IceSpellTemplate;

	bool bIsSpinKickUsed;
	float SpinKickCDTimer;
	float SpinKickCheckCDTimer;

	// Sphere Collision.
	UPROPERTY(Category = "Collision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;
};
