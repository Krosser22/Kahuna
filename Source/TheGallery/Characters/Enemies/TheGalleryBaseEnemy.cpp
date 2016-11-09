// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryBaseEnemy.h"
#include "Game/TheGalleryGameInstance.h"

// Sets default values
ATheGalleryBaseEnemy::ATheGalleryBaseEnemy()
{
  // Initialize
	Points = 0;


  // Create Collision
  AttackCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBoxCollision"));
  AttackCollisionComponent->InitBoxExtent(FVector(10, 10, 10));
  AttackCollisionComponent->SetupAttachment(RootComponent);
}

void ATheGalleryBaseEnemy::CharacterDeath()
{
  DebugLog("Enemy killed");
  AddPoints();
  Destroy();
}

bool ATheGalleryBaseEnemy::isFreezed()
{
  return IsFreezed;
}

bool ATheGalleryBaseEnemy::isKnockedBack()
{
  return IsKnockedBack;
}

bool ATheGalleryBaseEnemy::isDead()
{
  return IsDead;
}

bool ATheGalleryBaseEnemy::isAttackOnCD()
{
  return IsAttackOnCD;
}

void ATheGalleryBaseEnemy::attack()
{
  TArray<AActor*> baseCharacter;
  AttackCollisionComponent->GetOverlappingActors(baseCharacter);

  for (auto actor : baseCharacter)
  {
    ATheGalleryBaseCharacter *character = Cast<ATheGalleryBaseCharacter>(actor);

    if (character)
    {
      if (character != this)
      {
        actor->TakeDamage(Damage, FDamageEvent(), nullptr, nullptr);
      }
    }
  }

  IsAttackOnCD = true;
  GetWorldTimerManager().SetTimer(AttackCDTimerHandle, this, &ATheGalleryBaseEnemy::FinishCDAttack, AttackCD, false);
}

bool ATheGalleryBaseEnemy::isSpitPoisonOnCD()
{
  return IsSpitPoisonOnCD;
}

void ATheGalleryBaseEnemy::spitPoison()
{
  IsSpitPoisonOnCD = true;
  GetWorldTimerManager().SetTimer(SpitPoisonCDTimerHandle, this, &ATheGalleryBaseEnemy::FinishCDSpitPoison, SpitPoisonCD, false);

  FActorSpawnParameters SpawnParams;
  SpawnParams.Owner = this;
  SpawnParams.Instigator = Instigator;
  ATheGallerySpitPoison *spitPoison = GetWorld()->SpawnActor<ATheGallerySpitPoison>(SpitPoisonProjectileTemplate, GetActorLocation(), GetActorRotation(), SpawnParams);
  if (spitPoison)
  {
    spitPoison->SetLifeSpan(1.0f);
    spitPoison->AddImpulse(spitPoison->GetActorForwardVector() * SpitPoisonVelocity);
  }
}

void ATheGalleryBaseEnemy::FinishCDAttack()
{
  IsAttackOnCD = false;
}

void ATheGalleryBaseEnemy::FinishCDSpitPoison()
{
  IsSpitPoisonOnCD = false;
}

void ATheGalleryBaseEnemy::AddPoints()
{
	// Call To GameInstance.
	UTheGalleryGameInstance* GameInstance = Cast<UTheGalleryGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		// Increase Points.
		int32 TotalPoints = GameInstance->GetEnemiesPoints();
		TotalPoints += Points;
		GameInstance->SetEnemiesPoints(TotalPoints);
	}
}