// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (mState)
	{
	case EEnemyState::IDLE:
		IdleState();
		break;
	case EEnemyState::MOVE:
		MoveState();
		break;
	case EEnemyState::ATTACK:
		AttackState();
		break;
	case EEnemyState::DAMAGE:
		DamageState();
		break;
	case EEnemyState::DIE:
		DieState();
		break;
	}
}

// 일정시간이 지나면 상태를 Move 로 전환하고 싶다.
void UEnemyFSM::IdleState()
{
	// 일정시간이 지나면 상태를 Move 로 전환하고 싶다.
	// 1. 시간이 흘렀으니까
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	// 2. 일정시간이 지났으니까
	if (CurrentTime > IdleDelayTime)
	{
		// 3. 상태를 Move 로 전환하고 싶다.
		mState = EEnemyState::MOVE;
		CurrentTime = 0;
	}
}

void UEnemyFSM::MoveState()
{

}

void UEnemyFSM::AttackState()
{

}

void UEnemyFSM::DamageState()
{

}

void UEnemyFSM::DieState()
{

}

