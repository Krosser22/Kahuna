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
	SpinKickCollisionRadius = 100.0f;

	IceSpellData.Damage = FireSpellData.Damage = EarthSpellData.Damage = 1.0f;
	IceSpellData.Cooldown = FireSpellData.Cooldown = EarthSpellData.Cooldown = 2.0f;
	IceSpellData.ProjectileSpeed = FireSpellData.ProjectileSpeed = EarthSpellData.ProjectileSpeed = 10.0f;
	IceSpellData.ProjectileLifeTime = FireSpellData.ProjectileLifeTime = EarthSpellData.ProjectileLifeTime = 5.0f;

	// Create Collision
	SpinKickCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SpinKickCollisionComponent"));
	SpinKickCollisionComponent->InitSphereRadius(SpinKickCollisionRadius);
	SpinKickCollisionComponent->SetupAttachment(RootComponent);

	StaffHitCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("StaffHitCollisionComponent"));
	StaffHitCollisionComponent->SetRelativeLocation(FVector(60.0f, 0.0f, 0.0f));
	StaffHitCollisionComponent->InitBoxExtent(FVector(30.0f, 30.0f, 50.0f));
	StaffHitCollisionComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATheGalleryHumanCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Initialize Sphere Collision Radius.
	SpinKickCollisionComponent->SetSphereRadius(SpinKickCollisionRadius);
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
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Transform", IE_Pressed, this, &ATheGalleryHumanCharacter::TransformToAnimal);
	InputComponent->BindAction("SpinKick", IE_Pressed, this, &ATheGalleryHumanCharacter::StartSpinKickCD);
	InputComponent->BindAction("StaffHit", IE_Released, this, &ATheGalleryHumanCharacter::StartStaffHitCD);
	
    InputComponent->BindAction("IceSpell", IE_Pressed, this, &ATheGalleryHumanCharacter::CastIceSpell);
    InputComponent->BindAction("FireSpell", IE_Pressed, this, &ATheGalleryHumanCharacter::CastFireSpell);
    InputComponent->BindAction("EarthSpell", IE_Pressed, this, &ATheGalleryHumanCharacter::CastEarthSpell);

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

void ATheGalleryHumanCharacter::MoveForward(float Value)
{
	ATheGalleryCharacter::MoveForward(Value);
}

void ATheGalleryHumanCharacter::MoveRight(float Value)
{
	ATheGalleryCharacter::MoveRight(Value);
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
  if (IceSpellCooldown <= 0.0f)
  {
    CastSpell(IceSpellData);

    IceSpellCooldown = IceSpellData.Cooldown;
    DebugLog("Casted Ice Spell");
  }
}

void ATheGalleryHumanCharacter::CastFireSpell()
{
  if (FireSpellCooldown <= 0.0f)
  {
    CastSpell(FireSpellData);

    FireSpellCooldown = FireSpellData.Cooldown;
    DebugLog("Casted Fire Spell");
  }
}

void ATheGalleryHumanCharacter::CastEarthSpell()
{
  if (EarthSpellCooldown <= 0.0f)
  {
    CastSpell(EarthSpellData);

    EarthSpellCooldown = EarthSpellData.Cooldown;
    DebugLog("Casted Earth Spell");
  }
}

void ATheGalleryHumanCharacter::StartSpinKickCD() 
{
	if (SpinKickCooldown <= 0.0f)
	{
		SpinKickDamage();
        SpinKickCooldown = SpinKickMaxCooldown;
		DebugLog("Use Spin Kick");
	}
	else
		DebugLog("Cooldown Spin Kick");
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

void ATheGalleryHumanCharacter::SpinKickDamage() 
{
	// Get all the actors overlapping with the collision component.
	TArray<AActor*> Actors;
	SpinKickCollisionComponent->GetOverlappingActors(Actors);

	for (int a = 0; a < Actors.Num(); a++)
	{
		// Check if the actor is not the proper Character.
		if (Actors[a] != this)
		{
			ACharacter* Enemies = Cast<ACharacter>(Actors[a]);
			// Check if the enemy capsule is overlapping with the characters collision component.
			if (Enemies && SpinKickCollisionComponent->IsOverlappingComponent(Enemies->GetCapsuleComponent()))
			{
				// Do Damage
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s affected by: Spin Kick"), *Enemies->GetName()));
			}
		}
	}
}

void ATheGalleryHumanCharacter::StartStaffHitCD()
{
	if (StaffHitCooldown <= 0.0f)
	{
		StaffHitDamage();
		StaffHitCooldown = StaffHitMaxCooldown;
		DebugLog("Use Staff Hit");
	}
	else
		DebugLog("Cooldown Staff Hit");
}

void ATheGalleryHumanCharacter::StaffHitDamage()
{
	// Get all the actors overlapping with the collision component.
	TArray<AActor*> Actors;
	StaffHitCollisionComponent->GetOverlappingActors(Actors);

	for (int a = 0; a < Actors.Num(); a++)
	{
		// Check if the actor is not the proper Character.
		if (Actors[a] != this)
		{
			ACharacter* Enemies = Cast<ACharacter>(Actors[a]);
			// Check if the enemy capsule is overlapping with the characters collision component.
			if (Enemies && SpinKickCollisionComponent->IsOverlappingComponent(Enemies->GetCapsuleComponent()))
			{
				// Direction 
				FVector Dir =  this->GetActorLocation() - Enemies->GetActorLocation();
				Dir.Normalize();
				// Backward
				FVector Force = Dir * -1000.0f;
				Enemies->LaunchCharacter(Force, true, true); 

				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s affected by: Staff Kick"), *Enemies->GetName()));
			}
		}
	}
}
