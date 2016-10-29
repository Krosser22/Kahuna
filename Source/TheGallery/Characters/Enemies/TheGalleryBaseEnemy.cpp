// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryBaseEnemy.h"

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
  DebugLog("Attack");
  IsAttackOnCD = true;
  GetWorldTimerManager().SetTimer(attackCDTimerHandle, this, &ATheGalleryBaseEnemy::FinishCDAttack, attackCD, false);
}

void ATheGalleryBaseEnemy::FinishCDAttack()
{
  IsAttackOnCD = false;
}