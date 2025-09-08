// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterType.h"
#include "SlashCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class AItem;

UCLASS()
class SLASH_API ASlashCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<class UInputMappingContext> SlashContext;

	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> EquipAction;
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> AttackAction;

	/**
	 * Input Action Methods
	 */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Equip(const FInputActionValue& Value);
	virtual void Attack() override;

	/**
	 * Play Montage Methods
	 */
	virtual void PlayAttackMontage() override;
	virtual void AttackEnd() override;
	virtual bool CanAttack() override;
	void PlayEquipMontage(FName SectionName);
	bool CanDisarm();
	bool CanArm();

	UFUNCTION(BlueprintCallable)
	void Disarm();
	UFUNCTION(BlueprintCallable)
	void Arm();
	UFUNCTION(BlueprintCallable)
	void FinishEquipping();


private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> Camera;
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AItem> OverlappingItem;
	
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	TObjectPtr<UAnimMontage> EquipMontage;
	
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;
	
public:
	FORCEINLINE void SetOverlappingItem(TObjectPtr<AItem> Item) {OverlappingItem = Item;}
	FORCEINLINE TObjectPtr<AItem> GetOverlappingItem() {return OverlappingItem;}
	FORCEINLINE ECharacterState GetCharacterState() const {return CharacterState;}
};
