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

    UFUNCTION(BlueprintNativeEvent, Category = "Animation")
    void MeleeAttackAnimation();

    void MeleeAttackAnimation_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = "Animation")
    void CastFireSpellAnimation();

    void CastFireSpellAnimation_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = "Animation")
        void CastIceSpellAnimation();

    void CastIceSpellAnimation_Implementation();

    UFUNCTION(BlueprintCallable, Category = "Spells")
    void CastSpell(FSpellInfo SpellInfo);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spells")
        FSpellInfo IceSpellData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spells")
        FSpellInfo EarthSpellData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spells")
        FSpellInfo FireSpellData;


     
private:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

    void CharacterJump();

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
	void SpinKickDoDamage();

	/**
	* Controls the moment when the player uses the Staff Hit button.
	*/
	void StartStaffHitCD();

	/**
	* Make the damage to the enemies in range.
	*/
	void StaffHitDoDamage();

  // Animal character template that is going to be spawned
  UPROPERTY(EditAnywhere, Category = "Transformation")
  TSubclassOf<ATheGalleryAnimalCharacter> AnimalTemplate;

  // Sphere Collision.
  UPROPERTY(Category = "Attacks", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
  USphereComponent* SpinKickCollisionComponent;

	// Damage from Spin Kick
	UPROPERTY(EditAnywhere, Category = "Attacks")
	float SpinKickDamage;

	// The cooldown of the Spin Kick ability.
	UPROPERTY(EditAnywhere, Category = "Attacks")
	float SpinKickMaxCooldown;

	// Time passed from the moment whe used the Spin Kick ability
	float SpinKickCooldown;

	// Box Collision.
	UPROPERTY(Category = "Attacks", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* StaffHitCollisionComponent;

	// Damage from Staff Hit.
	UPROPERTY(EditAnywhere, Category = "Attacks")
	float StaffHitDamage;

    // The cooldown of the Staff Hit ability.
    UPROPERTY(EditAnywhere, Category = "Attacks")
    float StaffHitMaxCooldown;

	// Knock Back Force.
	UPROPERTY(EditAnywhere, Category = "Attacks")
	float StaffHitKnockBackForce;

	// Total time the enemy is knocked.
	UPROPERTY(EditAnywhere, Category = "Attacks")
	float StaffHitKnockBackTime;

	// Elevation of the enemy when is knocked.
	UPROPERTY(EditAnywhere, Category = "Attacks")
	float StaffHitKnockBackZ;

	// Time passed from the moment whe used the Staff Hit ability.
	float StaffHitCooldown;

  float IceSpellCooldown;
  float EarthSpellCooldown;
  float FireSpellCooldown;
};
