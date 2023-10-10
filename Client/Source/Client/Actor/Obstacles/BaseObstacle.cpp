// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/Obstacles/BaseObstacle.h"
#include "Network/Network.h"

// Sets default values
ABaseObstacle::ABaseObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABaseObstacle::BeginPlay()
{
	Super::BeginPlay();
	if (bIsSyncObject)
	{
		Network::GetNetwork()->RegisterObjectNetwork(this);
	}

	// 10/08 ������
	// �׳� �θ𿡼� �����ϸ� �Ǵ� �� ������ �ڽĿ��� �ϰ� �־����Ƿ�
	// �θ𿡼� �����ϴ� ������ �����Ͽ���.
	bIsStartMove = true;
	
}

// Called every frame
void ABaseObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

