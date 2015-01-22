// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "HidingPlace.h"
#include "Rembrandt.generated.h"

UCLASS(config=Game)
class NORANEKO_API ARembrandt : public ACharacter
{
	GENERATED_BODY()

	bool bCanHide;
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Called for hiding*/
	void Hide();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	ARembrandt(const FObjectInitializer& ObjectInitializer);

	/** Event fired when the player collides with an enemy patroller. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Rembrandt")
	void EnterFight(AActor* OtherActor);

	/**Event fired when the player collides with a hiding place*/
	UFUNCTION(BlueprintNativeEvent, Category = HidingPlace)
		void OnFindHidingPlace(AActor* OtherActor);

	/** Event fired when the player exit the overlap of the hidden place*/
	UFUNCTION(BlueprintNativeEvent, Category = HidingPlace)
		void OnLeaveHidingPlace(AActor* OtherActor);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};
