// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Rembrandt.generated.h"

UCLASS(config=Game)
class NORANEKO_API ARembrandt : public ACharacter
{
	GENERATED_BODY()

public:
	ARembrandt(const FObjectInitializer& ObjectInitializer);

	/** Event fired when the player collides with an enemy patroller. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Rembrandt")
	void FightStarted(APatroller* Patroller);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

private:

	/** Called after the Actor is spawned and its components are initialized. */
	void PostActorCreated();

	/** Called whenever an Actor begins overlaping with Rembrandt. */
	UFUNCTION()
	void HandleBeginOverlap(AActor* Other);

	/** Called whenever an Actor ends overlaping with Rembrandt. */
	UFUNCTION()
	void HandleEndOverlap(AActor* Other);

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};
