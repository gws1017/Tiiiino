// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObstacle.generated.h"

UCLASS()
class CLIENT_API ABaseObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	const int GetObjectType() const { return ObjectType; }
	void SetObjectType(const int Type) { ObjectType = Type; }

	const int GetObjectID() const { return mObjectID; }
	void SetObjectID(const int id) { mObjectID = id; }

	// 10/08 김혁동
	// 네트워크 동기화를 위한 변수를 제어하기 위한 함수를 추가하였습니다.
	// 아래 함수들을 호출하여 사용하면 될 것으로 보입니다.
	inline const bool IsMoveStart() const { return bIsStartMove; }
	void EnableMoveStart(const bool value) { bIsStartMove = value; }


protected:

	UPROPERTY(EditAnywhere, Category = "Network")
		int ObjectType;

	//1006 이수민 이 mObjectID에 부서지는 발판및 부서지는 문은 기획이 넘버링을 해주어야함. "무조건"
	UPROPERTY(EditAnywhere, Category = "Network")
	int mObjectID;

		// 10/06 김혁동
		// 이 부분은 네트워크 동기화를 위한 변수입니다.
		// 타이밍을 맞춰야 하는 장애물들은 이 변수가 true가 되는 순간 움직이도록 설정해야 합니다. 
	UPROPERTY(EditAnywhere, Category = "Network")
		bool bIsStartMove = false;
};
