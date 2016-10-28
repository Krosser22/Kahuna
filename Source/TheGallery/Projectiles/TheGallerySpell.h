// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TheGalleryProjectile.h"
#include "TheGallerySpell.generated.h"

class ATheGallerySpell;

UENUM(BlueprintType)
enum class ESpellEffect : uint8
{
  SE_Freeze    UMETA(DisplayName = "Freeze"),
  SE_AoEDamage UMETA(DisplayName = "AoE Damage"),
  SE_None      UMETA(DisplayName = "Basic Damage")
};

USTRUCT(BlueprintType)
struct FSpellInfo
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, Category = "Spells")
  float Damage;

  UPROPERTY(EditAnywhere, Category = "Spells")
  float Cooldown;

  UPROPERTY(EditAnywhere, Category = "Spells")
  float ProjectileSpeed;

  UPROPERTY(EditAnywhere, Category = "Spells")
  float ProjectileLifeTime;

  UPROPERTY(EditAnywhere, Category = "Spells")
  float EffectTime;

  UPROPERTY(EditAnywhere, Category = "Spells")
  ESpellEffect Effect;

  // Blueprint template that is going to be spawned
  UPROPERTY(EditAnywhere, Category = "Spells")
  TSubclassOf<ATheGallerySpell> Template;
};

UCLASS()
class THEGALLERY_API ATheGallerySpell : public ATheGalleryProjectile
{
	GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ATheGallerySpell();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Called every frame
  virtual void Tick(float DeltaSeconds) override;

  virtual void SetInitialValues(FSpellInfo SpellInfo);

private:
  UFUNCTION()
  virtual void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

  void Freeze(ATheGalleryBaseCharacter* Target);
  void RadialDamage(ATheGalleryBaseCharacter* Target);
  void ApplyDamage(ATheGalleryBaseCharacter* Target);

  FSpellInfo Data;

  //To-Do: Particle System
};
