// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CardPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARDS_API ACardPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

protected:
	//TEST
	UPROPERTY(VisibleAnywhere)
	class ACardPawn* currentCard;

public:
	//���õ�ǰ���ʵĿ���
	void SetCurrentCard(ACardPawn* _currentCard);


/*
* ��������ƺ��Ƶķ�Ӧ���Լ�ȡ���÷�ӦЧ��
*/
	//currentCardӦ�ô�������Ӧ�¼�
	void CallOnCardClickedDisplayEffect();
	//currentCardӦ��ȡ�����¼�(��CallOnCardClickedDisplayEffectһһ��Ӧ)
	void CallOffCardClickedDisplayEffect();


	void LeftMouseClickedEvent();

	void RightMouseClickedEvent();
};
