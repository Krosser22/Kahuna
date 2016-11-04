// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryBaseEnemy.h"

// Sets default values
ATheGalleryBaseEnemy::ATheGalleryBaseEnemy()
{
  // Create Collision
  attackCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBoxCollision"));
  attackCollisionComponent->InitBoxExtent(FVector(10, 10, 10));
  attackCollisionComponent->SetupAttachment(RootComponent);
}

void ATheGalleryBaseEnemy::CharacterDeath()
{
  DebugLog("Enemy killed");
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
  attackCollisionComponent->GetOverlappingActors(baseCharacter);

  for (auto actor : baseCharacter)
  {
    ATheGalleryBaseCharacter *character = Cast<ATheGalleryBaseCharacter>(actor);

    if (character)
    {
      if (character != this)
      {
        actor->TakeDamage(damage, FDamageEvent(), nullptr, nullptr);
      }
    }
  }

  IsAttackOnCD = true;
  GetWorldTimerManager().SetTimer(attackCDTimerHandle, this, &ATheGalleryBaseEnemy::FinishCDAttack, attackCD, false);
}

void ATheGalleryBaseEnemy::FinishCDAttack()
{
  IsAttackOnCD = false;
}