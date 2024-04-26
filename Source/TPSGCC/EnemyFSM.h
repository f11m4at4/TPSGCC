// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"


UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	IDLE = 0 UMETA(DisplayName=BradIdle),
	MOVE,
	ATTACK,
	DAMAGE,
	DIE
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSGCC_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(BlueprintReadOnly)
	EEnemyState mState = EEnemyState::IDLE;

	// Idle �ʿ�Ӽ�
	// ����ð�
	float CurrentTime;
	// ���ð�
	UPROPERTY(EditAnywhere)
	float IdleDelayTime = 2;

	void IdleState();

// ---------- Move --------------
// �ʿ�Ӽ� : Ÿ��, �̵��ӵ�
	UPROPERTY()
	class ATP_ThirdPersonCharacter* Taret;

	// ���ڽ� ����
	UPROPERTY()
	class AEnemy* Me;

	UPROPERTY(EditAnywhere, Category="Settings")
	float Speed = 500;

	void MoveState();

// --------- attack ---------------
	// �ʿ�Ӽ� : ���ݹ���
	UPROPERTY(EditAnywhere, Category="Settings")
	float AttackRange = 200;
	// �ʿ�Ӽ� : ���ݴ��ð�
	UPROPERTY(EditAnywhere, Category="Settings")
	float AttackDelayTime = 2;

	void AttackState();

	// �ǰݴ��� �̺�Ʈ �ݹ� �Լ�
	void OnDamagePrcess();

	void DamageState();
	void DieState();
};
