// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterType.h"
#include "Interfaces/HitInterface.h"
#include "Enemy.generated.h"

enum class EDeathPose : uint8;
enum class EEnemyState : uint8;

UCLASS()
class SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	virtual float TakeDamage(float Damage,
		const FDamageEvent& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
public:
	virtual void Destroyed() override;

protected:
	
	virtual void BeginPlay() override;
	
	void BeginPatrolling();

	virtual void Die() override;
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	virtual void Attack() override;
	virtual void PlayAttackMontage() override;
	virtual bool CanAttack() override;
	virtual void HandleDamage(float DamageAmount) override;

	
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose;
	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UHealthBarComponent> HealthBarWidget;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UPawnSensingComponent> PawnSensing;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class AActor> CombatTarget;

	UPROPERTY(EditAnywhere)
	double CombatRadius = 800.f;
	UPROPERTY(EditAnywhere)
	double AttackRadius = 160.f;
	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	/**
	 * Navigation
	 */
	UPROPERTY()
	TObjectPtr<class AAIController> EnemyController;
	
	//current patrol target
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	TObjectPtr<AActor> CurrentPatrolTarget;

	//current patrol target
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	TArray<TObjectPtr<AActor>> PatrolTargets;

	FTimerHandle PatrolTimer;
	void PatrolTimerFinished();
	void CheckCombatTarget();
	void CheckPatrolTarget();

	/**
	 * AI Behavior
	 */
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	void ClearPatrolTimer();
	

	/**
	 * Combat
	 */
	void StartAttackTimer();
	void ClearAttackTimer();
	
	FTimerHandle AttackTimer;
	
	UPROPERTY(EditAnywhere, Category=Combat)
	float AttackMin = 0.5f;
	UPROPERTY(EditAnywhere, Category=Combat)
	float AttackMax = 1.f;
	
	UPROPERTY(EditAnywhere, Category=Combaty)
	float PatrollingSpeed = 125.f;
	UPROPERTY(EditAnywhere, Category=Combaty)
	float ChasingSpeed = 300.f;

public:
	
};
