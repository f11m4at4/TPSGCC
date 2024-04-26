// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

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
	Me = Cast<AEnemy>(GetOwner());
	// Taret �� ã�ƿ���
	Taret = Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ATP_ThirdPersonCharacter::StaticClass()));
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ���� ���� ����
	//FString stateStr = UEnum::GetValueAsString<EEnemyState>(mState);
	//UE_LOG(LogTemp, Warning, TEXT("Current State : %s"), *stateStr);

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

// �����ð��� ������ ���¸� Move �� ��ȯ�ϰ� �ʹ�.
void UEnemyFSM::IdleState()
{
	// �����ð��� ������ ���¸� Move �� ��ȯ�ϰ� �ʹ�.
	// 1. �ð��� �귶���ϱ�
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	// 2. �����ð��� �������ϱ�
	if (CurrentTime > IdleDelayTime)
	{
		// 3. ���¸� Move �� ��ȯ�ϰ� �ʹ�.
		mState = EEnemyState::MOVE;
		CurrentTime = 0;
	}
}

//Ÿ�� �������� �̵��ϰ� �ʹ�.
// �ʿ�Ӽ� : Ÿ��, �̵��ӵ�
void UEnemyFSM::MoveState()
{
	// 1. ������ �ʿ��ϴ�.
	FVector Direction = Taret->GetActorLocation() - Me->GetActorLocation();
	Direction.Normalize();
	// 2. �̵��ϰ� �ʹ�.
	FVector P = Me->GetActorLocation() + Direction * Speed * GetWorld()->DeltaTimeSeconds;
	Me->SetActorLocation(P);
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

