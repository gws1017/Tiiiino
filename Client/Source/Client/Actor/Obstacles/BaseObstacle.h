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

	const int GetObjectID() const { return mObjectID; }
	void SetObjectID(const int id) { mObjectID = id; }
	void SetIsObjectSync(const bool sync) { bIsSyncObject = sync; }

	// 10/08 ������
	// ��Ʈ��ũ ����ȭ�� ���� ������ �����ϱ� ���� �Լ��� �߰��Ͽ����ϴ�.
	// �Ʒ� �Լ����� ȣ���Ͽ� ����ϸ� �� ������ ���Դϴ�.
	inline const bool IsMoveStart() const { return bIsStartMove; }
	void EnableMoveStart(const bool value) { bIsStartMove = value; }

	//��ֹ��� ����� ������ �Լ�, ����ؼ� ���α�� ����
	virtual void ActionObject() {};

protected:

	//1006 �̼��� �� mObjectID�� �μ����� ���ǹ� �μ����� ���� ��ȹ�� �ѹ����� ���־����. "������"
	//1010 �̼��� ��ȹ�� �̰� �ѹ��� �ϴٰ� �Ǽ� �Ҽ��������� �ڵ������� �ڵ�ȭ ��Ŵ.
	//-> �ٽû����غ��� �ε�Ÿ�̹��� ��Ÿ���̶� ��������� ����,,, �ڵ�ȭ �Ұ�.
	UPROPERTY(EditAnywhere, Category = "Network")
	int mObjectID;
	// 10.09 �̼��� ����ȭ�� �ʿ��� obstacle�� �ƴ� obstacle ex)LinearBelt�� �������� ����.
	//����ȭ�� �ʿ���ٸ� false. �⺻�� false ��ȹ�� �ǹ���ġ�ϰ� ����ȭ�� �ʿ��ϴٸ�
	// (�����̴� Ÿ�̹� ��) üũ�����ֵ����Ѵ�.
	UPROPERTY(EditAnywhere, Category = "Network")
	bool bIsSyncObject = false ;
		// 10/06 ������
		// �� �κ��� ��Ʈ��ũ ����ȭ�� ���� �����Դϴ�.
		// Ÿ�̹��� ����� �ϴ� ��ֹ����� �� ������ true�� �Ǵ� ���� �����̵��� �����ؾ� �մϴ�. 
	UPROPERTY(EditAnywhere, Category = "Network")
		bool bIsStartMove = false;
};
