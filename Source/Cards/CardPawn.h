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
* 游戏中的卡牌实体类型，需要在关卡中显示，附着卡牌UI的WidgetComponet。
* 
* 1.在手卡中的时候鼠标移动过去会显示在其他手卡上层，并且向屏幕上方位移。
* 2.在手卡中所有阶段能够点击后显示边缘高亮，并在左边侧面的区域显示卡牌效果详情；如果是能召唤的怪兽卡或者
* 能在手卡中发动的卡，应该同时在卡片正上方显示召唤或者发动按钮，发动效果有多个的情况下，发动按钮
* 点击后可以再点击选择要发动的效果
* 3.位于场上所有阶段的怪兽卡自动显示护甲魔抗和生命值，被点击后边缘高亮，同时，卡片上方显示能发动的效果，
* 效果选择功能同上，并且屏幕侧面显示卡牌效果。
* 4.位于于场上的技能卡可以点击后被边缘高亮。
* 
* 目前只有抽卡阶段，游戏阶段，回合结束阶段这三个阶段。
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

	//鼠标移入后发生
	virtual void NotifyActorBeginCursorOver() override;
	//鼠标移出后发生
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
	//卡片正面显示的UI图像组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWidgetComponent* cardFrontWidgetComponent;

	//UStaticMeshComponent* cardMeshComponent;
	//卡片背面显示的UI图像组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWidgetComponent* cardBackWidgetComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UUserWidget* cardDetailsUI;

protected:
	//似乎不需要这么一个静态网格体
	////卡片模型(一个Plane Mesh)组件
	//UPROPERTY(EditAnywhere,BlueprintReadAndWrite)


	//鼠标悬停到卡片上后，卡片x方向的位移量
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int displacementX=20;

	//鼠标悬停到卡片上后，卡片z方向的位移量
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int displacementZ = 10;

	//卡牌类型：0为怪兽卡，1为技能卡
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool cardType = 0;

	//当前卡牌所在区域（TEST）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AreaType currentArea=AreaType::HandArea;
};
