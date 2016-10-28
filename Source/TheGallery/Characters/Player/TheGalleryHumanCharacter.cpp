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
	bIsSpinKickUsed = false;
	SpinKickCDTimer = 2.0f;
	SpinKickCheckCDTimer = 0.0f;
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
}

void ATheGalleryHumanCharacter::StartSpinKickCD() {

	if (!bIsSpinKickUsed)
	{
		bIsSpinKickUsed = true;
		SpinKickDamage();
		DebugLog("Use Spin Kick");
	}
	else
		DebugLog("Spin Kick on CD");
}

void ATheGalleryHumanCharacter::UpdateCooldowns(float DeltaTime) {
	if (bIsSpinKickUsed)
	{
		if (SpinKickCheckCDTimer <= SpinKickCDTimer)
			SpinKickCheckCDTimer += DeltaTime;
		else
		{
			SpinKickCheckCDTimer = 0.0f;
			bIsSpinKickUsed = false;
			DebugLog("Spin Kick ready again");
		}
	}
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



