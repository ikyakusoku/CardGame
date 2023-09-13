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
	//设置当前访问的卡牌
	void SetCurrentCard(ACardPawn* _currentCard);


/*
* 鼠标点击卡牌后卡牌的反应，以及取消该反应效果
*/
	//currentCard应该触发的响应事件
	void CallOnCardClickedDisplayEffect();
	//currentCard应该取消的事件(与CallOnCardClickedDisplayEffect一一对应)
	void CallOffCardClickedDisplayEffect();


	void LeftMouseClickedEvent();

	void RightMouseClickedEvent();
};
