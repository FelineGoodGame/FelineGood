// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Noraneko.h"
#include "Rembrandt.h"

ARembrandt::ARembrandt(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bCanHide(false)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->bGenerateOverlapEvents = true;

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);
	CameraBoom->bDoCollisionTest = false;

	// Create a camera and attach to boom
	SideViewCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Setup collisions with patrollers
	OnActorBeginOverlap.AddDynamic(this, &ARembrandt::EnterFight);
	OnActorBeginOverlap.AddDynamic(this, &ARembrandt::OnFindHidingPlace);
	OnActorEndOverlap.AddDynamic(this, &ARembrandt::OnLeaveHidingPlace);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARembrandt::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Hide", IE_Pressed, this, &ARembrandt::Hide);

	InputComponent->BindAxis("MoveRight", this, &ARembrandt::MoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &ARembrandt::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ARembrandt::TouchStopped);
}



void ARembrandt::OnFindHidingPlace_Implementation(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("you can hide here")));
	auto HiddingPlace = Cast<AHidingPlace>(OtherActor);
	if (HiddingPlace)
	{
		bCanHide = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("you can hide here")));
	}

}

void ARembrandt::OnLeaveHidingPlace_Implementation(AActor* OtherActor)
{
	auto HiddingPlace = Cast<AHidingPlace>(OtherActor);
	if (HiddingPlace)
	{
		bCanHide = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("left hiding place")));
	}
}

void ARembrandt::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-10.f,0.f), Value);
}

void ARembrandt::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ARembrandt::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ARembrandt::Hide()
{
	if (bCanHide)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("hidden")));
	}

}

