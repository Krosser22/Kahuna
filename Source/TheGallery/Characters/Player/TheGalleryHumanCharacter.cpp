// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "TheGalleryHumanCharacter.h"

// Sets default values
ATheGalleryHumanCharacter::ATheGalleryHumanCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Collision
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(100);
	CollisionComponent->SetupAttachment(RootComponent);

	// Initialize
  SpinKickMaxCooldown = 2.0f;
  IceSpellMaxCooldown = 2.0f;

  IceProjectileVelocity = 100.0f;
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
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Transform", IE_Pressed, this, &ATheGalleryHumanCharacter::TransformToAnimal);
	InputComponent->BindAction("SpinKick", IE_Pressed, this, &ATheGalleryHumanCharacter::StartSpinKickCD);
	
  InputComponent->BindAction("IceSpell", IE_Pressed, this, &ATheGalleryHumanCharacter::CastIceSpell);

	//InputComponent->BindAction("StaffHit", IE_Released, this, &ATheGalleryCharacter::Jump);

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

void ATheGalleryHumanCharacter::CastIceSpell()
{
  if (IceSpellCooldown <= 0.0f)
  {
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * 50.0f);

    ATheGalleryIceSpell *IceProjectile = GetWorld()->SpawnActor<ATheGalleryIceSpell>(IceSpellTemplate, NewLocation, GetActorRotation(), SpawnParams);
    if (IceProjectile)
    {
      FVector Direction = GetActorForwardVector();
      Direction.Normalize();
      IceProjectile->GetMesh()->AddForce(Direction * IceProjectileVelocity * 1000.0f, NAME_None, true);

      IceSpellCooldown = IceSpellMaxCooldown;

      DebugLog("Casted Ice Spell");
    }
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
}

void ATheGalleryHumanCharacter::UpdateCooldowns(float DeltaTime) 
{
  if (SpinKickCooldown > 0.0f)
    SpinKickCooldown -= DeltaTime;

  if (IceSpellCooldown > 0.0f)
    IceSpellCooldown -= DeltaTime;

  if (EarthSpellCooldown > 0.0f)
    EarthSpellCooldown -= DeltaTime;

  if (FireSpellCooldown > 0.0f)
    FireSpellCooldown -= DeltaTime;
}

void ATheGalleryHumanCharacter::SpinKickDamage() 
{
	TArray<AActor*> Actors;
	CollisionComponent->GetOverlappingActors(Actors);

	for (int a = 0; a < Actors.Num(); a++) 
	{
		// Cast to Enemy
			// AEnemy *Enemy = Cast<AEnemy>(Actors[c]);
		// Check if its Overlapping with Enemy
			// if (CollisionComponent->IsOverlappingComponent(Enemy->CapsuleComponent)
		// Do Damage
			// Enemy->TakeDamage(50.0f,FDamageEvent(),EventInstigator,this);
		//
	}
}