// Fill out your copyright notice in the Description page of Project Settings.


#include "CardPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include"CardPawn.h"
#include "Components/WidgetComponent.h"

void ACardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	bEnableMouseOverEvents = true;
	//bEnableClickEvents = true;	
}

void ACardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("LMouseClicked"), EInputEvent::IE_Pressed, this, &ACardPlayerController::LeftMouseClickedEvent);
	InputComponent->BindAction(TEXT("RMouseClicked"), EInputEvent::IE_Pressed, this, &ACardPlayerController::RightMouseClickedEvent);
}



void ACardPlayerController::SetCurrentCard(ACardPawn* _currentCard)
{
	currentCard = _currentCard;
}



void ACardPlayerController::CallOnCardClickedDisplayEffect()
{
	currentCard->cardFrontWidgetComponent->SetRenderCustomDepth(true);

	//目前cardDetailsUI是运行时点击后创建并访问数据库修改文字
	//修改方案1(优先)：关卡中存储一个创建好的全局的UUserWidget,对应于两种卡片类型，每次点击发生后，对它的文字和图片进行修改，并显示。（相比3，节省了createWidget的时间）
	//修改方案2:构造cardPawn的时候即创建一个UUserWidget.（节省了所有时间，需要卡片数量个UUserWidget的内存。
	//修改方案3：现在这样，每次点击运行时创建一个，每次消失就销毁。
	auto cardDetailClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/UI/UI_CardDetailsWidget.UI_CardDetailsWidget_C'"));
	//cardDetailsUI = LoadObject<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/UI/UI_CardDetailsWidget.UI_CardDetailsWidget'"));

	//判断是否为空，为空则创建，否则先销毁
	if (currentCard->cardDetailsUI == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("pointer null,create one cardDetailsUI."));
		currentCard->cardDetailsUI = CreateWidget<UUserWidget>(GetWorld(), cardDetailClass);
	}
	else {
		//有垃圾回收应该不需要调用的，但我不想确定的垃圾在内存中持续存在，这个UI会不断的创建，但垃圾回收确实非持续性的，
		//我担心会有内存上开销很大的情况发生
		UE_LOG(LogTemp, Warning, TEXT("GC hasn't destroy it."));
		//TEST
		currentCard->cardDetailsUI->MarkAsGarbage();
		currentCard->cardDetailsUI = CreateWidget<UUserWidget>(GetWorld(), cardDetailClass);
	}

	if (currentCard->cardDetailsUI == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("cardDtailsUI loading failed."));
	}
	else
	{
		currentCard->cardDetailsUI->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("cardDtailsUI loading success"));
	}
}

void ACardPlayerController::CallOffCardClickedDisplayEffect()
{
	if (currentCard != nullptr)
	{
		currentCard->cardFrontWidgetComponent->SetRenderCustomDepth(false);
		UE_LOG(LogTemp, Warning, TEXT("SetRenderCustomDepth:FALSE."));

		auto currentDetailsUI = currentCard->cardDetailsUI;
		if (currentDetailsUI != nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT("currentDetailsUI is not nullptr."));
			if (currentDetailsUI->IsInViewport())
			{
				currentDetailsUI->RemoveFromViewport();
				UE_LOG(LogTemp, Display, TEXT("removeUI."));
				
			}
			currentDetailsUI->MarkAsGarbage();
			UE_LOG(LogTemp, Warning, TEXT("GC is set in Controller"));
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("currentDetailsUI is nullptr."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("currentCard is nullptr when call off."));
	}
}


/*
* 如果点击的是cardPawn再判断是否是上一次点击的对象，是则不处理，不是就取消上一次点击的效果，然后启动这一次的点击效果，并把这次点击的卡牌对象记录
* 如果点击的不是cardPawn则取消上一次点击的效果，这一次不记录卡牌对象。
*/
void ACardPlayerController::LeftMouseClickedEvent()
{
	FHitResult cursorHit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, cursorHit))
	{
		UE_LOG(LogTemp, Display, TEXT("Get Hit."));
		if (cursorHit.bBlockingHit)
		{
			UE_LOG(LogTemp, Display, TEXT("Is a Blocking Hit."));
			//或者写成...->IsA(ACardPawn::StaticClass)
			
			if (auto hitActor = Cast<ACardPawn>(cursorHit.GetActor()))
			{
				UE_LOG(LogTemp, Display, TEXT("Hit a ACardPawn"));
				if (currentCard == nullptr)
				{
					currentCard = hitActor;
					CallOnCardClickedDisplayEffect();
				}
				else if (currentCard != nullptr&&currentCard!=hitActor)
				{
					UE_LOG(LogTemp, Display, TEXT("HitCard is not a same Card"));
					CallOffCardClickedDisplayEffect();
					currentCard = hitActor;
					CallOnCardClickedDisplayEffect();
				}
			}
			else {
				UE_LOG(LogTemp, Display, TEXT("Hit is not a Card"));
				if (currentCard != nullptr)
				{
					CallOffCardClickedDisplayEffect();
					currentCard = nullptr;
				}
			}
		}
	}
}

void ACardPlayerController::RightMouseClickedEvent()
{
	//FHitResult hit;

	//GetHitResultUnderCursor(ECC_Visibility, false, hit);
	//TSubclassOf<ACardPawn> cardClass = hit.GetActor()->StaticClass();
	//if (cardClass)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("获取到cardPawn"));
	//	posse
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("无法获取到cardPawn"));
	//}

	//
	//TArray<AActor*> cardPawns;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACardPawn::StaticClass(), cardPawns);

	//for()
}
