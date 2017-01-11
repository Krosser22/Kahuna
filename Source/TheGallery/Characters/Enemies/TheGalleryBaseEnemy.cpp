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

// Called when the game starts or when spawned
void ATheGalleryBaseEnemy::BeginPlay()
{
  Super::BeginPlay();

  HomeLocation = GetActorLocation();
}

void ATheGalleryBaseEnemy::CharacterDeath()
{
  DebugLog("Enemy killed");
  AddPoints();
  Destroy();
}

bool ATheGalleryBaseEnemy::GetIsFreezed()
{
  return IsFreezed;
}

bool ATheGalleryBaseEnemy::GetIsKnockedBack()
{
  return IsKnockedBack;
}

bool ATheGalleryBaseEnemy::GetIsDead()
{
  return IsDead;
}

bool ATheGalleryBaseEnemy::GetIsAttackOnCD()
{
  return IsAttackOnCD;
}

void ATheGalleryBaseEnemy::Attack()
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

bool ATheGalleryBaseEnemy::GetIsSpitPoisonOnCD()
{
  return IsSpitPoisonOnCD;
}

void ATheGalleryBaseEnemy::SpitPoison()
{
  DebugLog("Shooooooooooooooot spit poison");
  IsSpitPoisonOnCD = true;
  if (Type == EEnemyType::EEnemyType_Elite)
  {
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

void ATheGalleryBaseEnemy::GetPatrolPoint(FVector &position, float &delay)
{
  if (PatrolPoints.Num() > 0)
  {
    position = PatrolPoints[PatrolPointID]->GetActorLocation();
    delay = PatrolPoints[PatrolPointID]->DelayTime;

    PatrolPointID++;

    if (PatrolPointID > PatrolPoints.Num() - 1)
    {
      PatrolPointID = 0;
    }
  }
  else
  {
    position = FVector::ZeroVector;
    delay = 0.0f;
  }
}

bool ATheGalleryBaseEnemy::HasPatrolPoints()
{
  return (PatrolPoints.Num() > 0);
}

bool ATheGalleryBaseEnemy::IsActiveStatus()
{
  return Active;
}

void ATheGalleryBaseEnemy::SetActiveStatus(bool active)
{
  Active = active;
}

void ATheGalleryBaseEnemy::Reset()
{
  SetActorLocation(HomeLocation);
  Active = false;
  IsSpitPoisonOnCD = false;
  IsAttackOnCD = false;
}

void ATheGalleryBaseEnemy::FinishCDAttack()
{
  IsAttackOnCD = false;
}

void ATheGalleryBaseEnemy::FinishCDSpitPoison()
{
  IsSpitPoisonOnCD = false;
}