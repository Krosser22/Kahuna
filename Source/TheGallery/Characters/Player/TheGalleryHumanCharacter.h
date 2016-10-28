// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheGalleryCharacter.h"
#include "TheGalleryAnimalCharacter.h"
#include "../../Projectiles/TheGallerySpell.h"
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

  void CastSpell(FSpellInfo SpellInfo);

  void CastIceSpell();
  void CastFireSpell();
  void CastEarthSpell();

  // Animal character template that is going to be spawned
	UPROPERTY(EditAnywhere, Category = "Transformation")
	TSubclassOf<ATheGalleryAnimalCharacter> AnimalTemplate;

  float SpinKickCooldown;

  UPROPERTY(EditAnywhere, Category = "Attacks")
	float SpinKickMaxCooldown;

	// Sphere Collision.
	UPROPERTY(Category = "Collision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComponent;

  UPROPERTY(EditAnywhere, Category = "Spells")
  FSpellInfo IceSpellData;

  UPROPERTY(EditAnywhere, Category = "Spells")
  FSpellInfo EarthSpellData;

  UPROPERTY(EditAnywhere, Category = "Spells")
  FSpellInfo FireSpellData;

  float IceSpellCooldown;
  float EarthSpellCooldown;
  float FireSpellCooldown;
};
