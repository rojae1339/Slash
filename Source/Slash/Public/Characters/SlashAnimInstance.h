// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlashAnimInstance.generated.h"

enum class ECharacterState : uint8;

/**
 * 
 */
UCLASS()
class SLASH_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class ASlashCharacter> SlashCharacter;

	UPROPERTY(BlueprintReadOnly, Category=Movement)
	TObjectPtr<class UCharacterMovementComponent> SlashMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category=Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category=Movement)
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly, Category="Movement | CharacterState")
	ECharacterState CharacterState;
};
