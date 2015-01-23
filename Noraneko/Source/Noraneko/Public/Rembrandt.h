// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "HidingPlace.h"
#include "Rembrandt.generated.h"

/**Enum State*/
UENUM(BlueprintType)		
enum class EState: uint8
{
	Idle = 0,
	Fighting = 1,
	Hidden = 2,
	CanHide = 3,
};

UCLASS(config=Game)
class NORANEKO_API ARembrandt : public ACharacter
{
	GENERATED_BODY()
public:
	ARembrandt(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EState State;
	/** Event fired when the player collides with an enemy patroller. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Rembrandt")
	void FightStarted(APatroller* Patroller);

	/**Event fired when the player collides with a hiding place*/
	UFUNCTION(BlueprintNativeEvent, Category = HidingPlace)
		void OnFindHidingPlace(AActor* OtherActor);

	/** Event fired when the player exit the overlap of the hidden place*/
	UFUNCTION(BlueprintNativeEvent, Category = HidingPlace)
		void OnLeaveHidingPlace(AActor* OtherActor);

	EState GetState();

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Called for hiding*/
	void Hide();

	/**Called for unhiding*/
	void Unhide();

	// APawn interface
	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

private:

	/** Called after the Actor is spawned and its components are initialized. */
	void PostActorCreated();

	/** Called whenever an Actor begins overlaping with Rembrandt. */
	UFUNCTION()
	void HandleBeginOverlap(AActor* Other);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Called whenever an Actor ends overlaping with Rembrandt. */
	UFUNCTION()
	void HandleEndOverlap(AActor* Other);

	/** Called whenever the player wants to hide*/
	UFUNCTION()
	void HandleHidingState();
	
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	
};
