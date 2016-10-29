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

	/**
	* Update the cooldowns timers.
	* @param DeltaTime - The time in seconds it took to complete the last frame.
	*/
	void UpdateCooldowns(float DeltaTime);

private:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

    void CastSpell(FSpellInfo SpellInfo);

    void CastIceSpell();
    void CastFireSpell();
    void CastEarthSpell();

	/**
	* Controls the moment when the player uses the Spink Kick button.
	*/
	void StartSpinKickCD();

	/**
	* Make the damage to the enemies in range.
	*/
	void SpinKickDamage();

	/**
	* Controls the moment when the player uses the Staff Hit button.
	*/
	void StartStaffHitCD();

	/**
	* Make the damage to the enemies in range.
	*/
	void StaffHitDamage();

    // Animal character template that is going to be spawned
    UPROPERTY(EditAnywhere, Category = "Transformation")
    TSubclassOf<ATheGalleryAnimalCharacter> AnimalTemplate;

    // Time passed from the moment whe used the Spin Kick ability
    float SpinKickCooldown;

    // The cooldown of the Spin Kick ability.
    UPROPERTY(EditAnywhere, Category = "Attacks")
    float SpinKickMaxCooldown;

    // Sphere Collision.
    UPROPERTY(Category = "Collision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    USphereComponent* SpinKickCollisionComponent;

    // Radius Sphere Collision.
    UPROPERTY(EditAnywhere, Category = "Collision")
    float SpinKickCollisionRadius;

	// Time passed from the moment whe used the Staff Hit ability
    float StaffHitCooldown;

    // The cooldown of the Staff Hit ability.
    UPROPERTY(EditAnywhere, Category = "Attacks")
    float StaffHitMaxCooldown;

    // Box Collision.
    UPROPERTY(Category = "Collision", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* StaffHitCollisionComponent;

    // Radius Box Collision.
    UPROPERTY(EditAnywhere, Category = "Collision")
    float StaffHitCollisionRadius;

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
