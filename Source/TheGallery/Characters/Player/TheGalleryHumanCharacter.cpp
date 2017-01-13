// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryHumanCharacter.h"

// Sets default values
ATheGalleryHumanCharacter::ATheGalleryHumanCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize
	SpinKickMaxCooldown = StaffHitMaxCooldown = 2.0f;
	StaffHitDamage = 5.0f;
	SpinKickDamage = 10.0f;
	StaffHitKnockBackForce = 800.0f;
	StaffHitKnockBackTime = 1.0f;
	StaffHitKnockBackZ = 30.0f;

	IceSpellData.Damage = FireSpellData.Damage = EarthSpellData.Damage = 1.0f;
	IceSpellData.Cooldown = FireSpellData.Cooldown = EarthSpellData.Cooldown = 2.0f;
	IceSpellData.ProjectileSpeed = FireSpellData.ProjectileSpeed = EarthSpellData.ProjectileSpeed = 10.0f;
	IceSpellData.ProjectileLifeTime = FireSpellData.ProjectileLifeTime = EarthSpellData.ProjectileLifeTime = 5.0f;

	// Create Collision
	SpinKickCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SpinKickCollisionComponent"));
	SpinKickCollisionComponent->InitSphereRadius(100.0f);
	SpinKickCollisionComponent->SetupAttachment(RootComponent);

	StaffHitCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("StaffHitCollisionComponent"));
	StaffHitCollisionComponent->SetRelativeLocation(FVector(60.0f, 0.0f, 0.0f));
	StaffHitCollisionComponent->SetupAttachment(RootComponent);

	CanUseFireSpell = false;
	CanUseIceSpell = false;
}

// Called when the game starts or when spawned
void ATheGalleryHumanCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATheGalleryHumanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCooldowns(DeltaTime);
}

// Called to bind functionality to input
void ATheGalleryHumanCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ATheGalleryHumanCharacter::CharacterJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Transform", IE_Pressed, this, &ATheGalleryHumanCharacter::TransformToAnimal);
	InputComponent->BindAction("SpinKick", IE_Pressed, this, &ATheGalleryHumanCharacter::StartSpinKickCD);
	InputComponent->BindAction("StaffHit", IE_Released, this, &ATheGalleryHumanCharacter::StartStaffHitCD);
	
    InputComponent->BindAction("IceSpell", IE_Pressed, this, &ATheGalleryHumanCharacter::CastIceSpell);
    InputComponent->BindAction("FireSpell", IE_Pressed, this, &ATheGalleryHumanCharacter::CastFireSpell);
    InputComponent->BindAction("EarthSpell", IE_Pressed, this, &ATheGalleryHumanCharacter::CastEarthSpell);

    InputComponent->BindAction("Pause", IE_Pressed, this, &ATheGalleryCharacter::ActivePauseMenu);

	// Use parent movement functions (camera movement also)
	InputComponent->BindAxis("MoveForward", this, &ATheGalleryHumanCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATheGalleryHumanCharacter::MoveRight);
}

void ATheGalleryHumanCharacter::TransformToAnimal()
{
	// Create a Animal Transformation actor if there is no one already
	if (!TransformationCharacter)
	{
		//Spawn
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ATheGalleryAnimalCharacter* AnimalForm = GetWorld()->SpawnActor<ATheGalleryAnimalCharacter>(AnimalTemplate, GetActorLocation(), GetActorRotation(), params);
		
		if (AnimalForm)
		{
			//Set altern transformed actor
			AnimalForm->SetTransformationCharacter(this);
			TransformationCharacter = AnimalForm;
			bPossessedNewCharacter = true;
		}
	}
	
	PossessCharacter(TransformationCharacter, this);
}

void ATheGalleryHumanCharacter::MeleeAttackAnimation_Implementation()
{
}

void ATheGalleryHumanCharacter::MoveForward(float Value)
{
    if(!IsDead)
	    ATheGalleryCharacter::MoveForward(Value);
}

void ATheGalleryHumanCharacter::MoveRight(float Value)
{
    if (!IsDead)
	    ATheGalleryCharacter::MoveRight(Value);
}

void ATheGalleryHumanCharacter::CharacterJump()
{
    if(!IsDead)
        ACharacter::Jump();
}

void ATheGalleryHumanCharacter::CastFireSpellAnimation_Implementation()
{
}

void ATheGalleryHumanCharacter::CastIceSpellAnimation_Implementation()
{
}

void ATheGalleryHumanCharacter::CastSpell(FSpellInfo SpellInfo)
{
  FActorSpawnParameters SpawnParams;
  SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

  FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * 50.0f);
  ATheGallerySpell *SpellProjectile = GetWorld()->SpawnActor<ATheGallerySpell>(SpellInfo.Template, NewLocation, GetActorRotation(), SpawnParams);
  if (SpellProjectile)
  {
    SpellProjectile->SetCharacterOwner(this);
    SpellProjectile->SetInitialValues(SpellInfo);

    FVector Direction = GetActorForwardVector();
    Direction.Normalize();
    SpellProjectile->AddImpulse(Direction * SpellInfo.ProjectileSpeed);
  }
}

void ATheGalleryHumanCharacter::CastIceSpell()
{
    if (!IsDead && CanUseIceSpell)
    {
        if (IceSpellCooldown <= 0.0f)
        {
            CastIceSpellAnimation();
            IceSpellCooldown = IceSpellData.Cooldown;
        }
    }
 
}

void ATheGalleryHumanCharacter::CastFireSpell()
{
    if (!IsDead && CanUseFireSpell)
    {
        if (FireSpellCooldown <= 0.0f)
        {
            CastFireSpellAnimation();
            FireSpellCooldown = FireSpellData.Cooldown;
        }
    }
}

void ATheGalleryHumanCharacter::CastEarthSpell()
{
    if (!IsDead) 
    {
        if (EarthSpellCooldown <= 0.0f)
            EarthSpellCooldown = EarthSpellData.Cooldown;
    }
}

void ATheGalleryHumanCharacter::UpdateCooldowns(float DeltaTime) 
{
  if (SpinKickCooldown > 0.0f)
    SpinKickCooldown -= DeltaTime;

  if (StaffHitCooldown > 0.0f)
	  StaffHitCooldown -= DeltaTime;

  if (IceSpellCooldown > 0.0f)
    IceSpellCooldown -= DeltaTime;

  if (EarthSpellCooldown > 0.0f)
    EarthSpellCooldown -= DeltaTime;

  if (FireSpellCooldown > 0.0f)
    FireSpellCooldown -= DeltaTime;
}

void ATheGalleryHumanCharacter::StartSpinKickCD()
{
	if (SpinKickCooldown <= 0.0f)
	{
		SpinKickDoDamage();
		SpinKickCooldown = SpinKickMaxCooldown;
	}
}

void ATheGalleryHumanCharacter::SpinKickDoDamage() 
{
	// Get all the actors overlapping with the collision component.
	TArray<AActor*> Actors;
	SpinKickCollisionComponent->GetOverlappingActors(Actors);

	for (int a = 0; a < Actors.Num(); a++)
	{
		// Check if the actor is not the proper Character.
		if (Actors[a] != this)
		{
			ATheGalleryBaseCharacter* Enemies = Cast<ATheGalleryBaseCharacter>(Actors[a]);
			// Check if the enemy capsule is overlapping with the characters collision component.
			if (Enemies && SpinKickCollisionComponent->IsOverlappingComponent(Enemies->GetCapsuleComponent()))
				Enemies->TakeDamage(SpinKickDamage, FDamageEvent(), Enemies->GetController(), this);
		}
	}
}

void ATheGalleryHumanCharacter::StartStaffHitCD()
{
    if (!IsDead)
    {
        if (StaffHitCooldown <= 0.0f)
        {
            MeleeAttackAnimation();
            StaffHitDoDamage();
            StaffHitCooldown = StaffHitMaxCooldown;
        }
    }
}

void ATheGalleryHumanCharacter::StaffHitDoDamage()
{
	// Get all the actors overlapping with the collision component.
	TArray<AActor*> Actors;
	StaffHitCollisionComponent->GetOverlappingActors(Actors);

	for (int a = 0; a < Actors.Num(); a++)
	{
		// Check if the actor is not the proper Character.
		if (Actors[a] != this)
		{
			ATheGalleryBaseCharacter* Enemies = Cast<ATheGalleryBaseCharacter>(Actors[a]);
			// Check if the enemy capsule is overlapping with the characters collision component.
			if (Enemies && SpinKickCollisionComponent->IsOverlappingComponent(Enemies->GetCapsuleComponent()))
			{
				// Direction 
				FVector Dir =  Enemies->GetActorLocation() - this->GetActorLocation();
				// Elevatation 
				Dir.Z += StaffHitKnockBackZ;
				// Normalize
				Dir.Normalize();
				// Force
				FVector Force = Dir * StaffHitKnockBackForce;
				// Launch
				Enemies->LaunchCharacter(Force, true, true); 
				Enemies->KnockBackCharacter(StaffHitKnockBackTime);
				Enemies->TakeDamage(StaffHitDamage, FDamageEvent(), Enemies->GetController(), this);
			}
		}
	}
}