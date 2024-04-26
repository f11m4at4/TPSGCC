// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

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
	// Taret 을 찾아오자
	Taret = Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ATP_ThirdPersonCharacter::StaticClass()));
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 현재 상태 찍어보기
	FString stateStr = UEnum::GetValueAsString(mState);
	UE_LOG(LogTemp, Warning, TEXT("Current State : %s"), *stateStr);

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

//타겟 방향으로 이동하고 싶다.
// 필요속성 : 타겟, 이동속도
void UEnemyFSM::MoveState()
{
	// 1. 방향이 필요하다.
	FVector Direction = Taret->GetActorLocation() - Me->GetActorLocation();
	float Distance = Direction.Size();
	Direction.Normalize();
	// 2. 이동하고 싶다.
	FVector P = Me->GetActorLocation() + Direction * Speed * GetWorld()->DeltaTimeSeconds;
	Me->SetActorLocation(P);

	// 트렌지션 조건 설정
	// 공격범위안에 들어오면 상태를 공격으로 전환하고 싶다.
	// 1. 거리를 구해해야 한다.
	// 2. 공격범위안에 들어왔으니까
	if (Distance < AttackRange)
	{
		// 3. 상태를 공격으로 전환하고 싶다.
		mState = EEnemyState::ATTACK;
		CurrentTime = AttackDelayTime;
	}
}

// 일정시간에 한번씩 공격하고 싶다.
void UEnemyFSM::AttackState()
{
	// 1. 시간이 흘렀으니까
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	// 2. 일정시간이 됐으니까
	if (CurrentTime > AttackDelayTime)
	{
		// 3. 공격하고 싶다.
		//UE_LOG(LogTemp, Warning, TEXT("공격!!!"));
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, "Attack");
		CurrentTime = 0;
	}

	// 타겟이 도망가면 상태를 이동으로 전환하고 싶다.
	// ->타겟이 공격범위를 벗어나면
	// 만약 타겟과의 거리가 공격범위를 초과했다면
	float Distance = FVector::Dist(Taret->GetActorLocation(), Me->GetActorLocation());
	if (Distance > AttackRange)
	{
		mState = EEnemyState::MOVE; 
	}
}

void UEnemyFSM::OnDamagePrcess()
{
	Me->Destroy();
}

void UEnemyFSM::DamageState()
{

}

void UEnemyFSM::DieState()
{

}

