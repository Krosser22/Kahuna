// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryBaseEnemy.h"

void ATheGalleryBaseEnemy::CharacterDeath()
{
  IsDead = true;
}

bool ATheGalleryBaseEnemy::isFreezed()
{
  return IsFreezed;
}

bool ATheGalleryBaseEnemy::isKnockedBack()
{
  return IsKnockedBack;
}