// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CardPawn.generated.h"

UENUM(BlueprintType)
enum class AreaType :uint8 {
	DrawPile=0,
	HandArea=1,
	Battlefield=1<<1,
	DiscardPile=1<<2
};

/*
* ��Ϸ�еĿ���ʵ�����ͣ���Ҫ�ڹؿ�����ʾ�����ſ���UI��WidgetComponet��
* 
* 1.���ֿ��е�ʱ������ƶ���ȥ����ʾ�������ֿ��ϲ㣬��������Ļ�Ϸ�λ�ơ�
* 2.���ֿ������н׶��ܹ��������ʾ��Ե������������߲����������ʾ����Ч�����飻��������ٻ��Ĺ��޿�����
* �����ֿ��з����Ŀ���Ӧ��ͬʱ�ڿ�Ƭ���Ϸ���ʾ�ٻ����߷�����ť������Ч���ж��������£�������ť
* ���������ٵ��ѡ��Ҫ������Ч��
* 3.λ�ڳ������н׶εĹ��޿��Զ���ʾ����ħ��������ֵ����������Ե������ͬʱ����Ƭ�Ϸ���ʾ�ܷ�����Ч����
* Ч��ѡ����ͬ�ϣ�������Ļ������ʾ����Ч����
* 4.λ���ڳ��ϵļ��ܿ����Ե���󱻱�Ե������
* 
* Ŀǰֻ�г鿨�׶Σ���Ϸ�׶Σ��غϽ����׶��������׶Ρ�
*/
UCLASS()
class CARDS_API ACardPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACardPawn();
	//ACardPawn(const ACardPawn& _cardPawnInstance);
	//ACardPawn(ACardPawn&& _cardPawnInstance);
	//
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//����������
	virtual void NotifyActorBeginCursorOver() override;
	//����Ƴ�����
	virtual void NotifyActorEndCursorOver() override;


//Event
public:

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



public:
	//UStaticMeshComponent* cardMeshComponent;
	//��Ƭ������ʾ��UIͼ�����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWidgetComponent* cardFrontWidgetComponent;

	//UStaticMeshComponent* cardMeshComponent;
	//��Ƭ������ʾ��UIͼ�����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWidgetComponent* cardBackWidgetComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UUserWidget* cardDetailsUI;

protected:
	//�ƺ�����Ҫ��ôһ����̬������
	////��Ƭģ��(һ��Plane Mesh)���
	//UPROPERTY(EditAnywhere,BlueprintReadAndWrite)


	//�����ͣ����Ƭ�Ϻ󣬿�Ƭx�����λ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int displacementX=20;

	//�����ͣ����Ƭ�Ϻ󣬿�Ƭz�����λ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int displacementZ = 10;

	//�������ͣ�0Ϊ���޿���1Ϊ���ܿ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool cardType = 0;

	//��ǰ������������TEST��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AreaType currentArea=AreaType::HandArea;
};
