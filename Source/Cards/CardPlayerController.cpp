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

	//ĿǰcardDetailsUI������ʱ����󴴽����������ݿ��޸�����
	//�޸ķ���1(����)���ؿ��д洢һ�������õ�ȫ�ֵ�UUserWidget,��Ӧ�����ֿ�Ƭ���ͣ�ÿ�ε�������󣬶��������ֺ�ͼƬ�����޸ģ�����ʾ�������3����ʡ��createWidget��ʱ�䣩
	//�޸ķ���2:����cardPawn��ʱ�򼴴���һ��UUserWidget.����ʡ������ʱ�䣬��Ҫ��Ƭ������UUserWidget���ڴ档
	//�޸ķ���3������������ÿ�ε������ʱ����һ����ÿ����ʧ�����١�
	auto cardDetailClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/UI/UI_CardDetailsWidget.UI_CardDetailsWidget_C'"));
	//cardDetailsUI = LoadObject<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/UI/UI_CardDetailsWidget.UI_CardDetailsWidget'"));

	//�ж��Ƿ�Ϊ�գ�Ϊ���򴴽�������������
	if (currentCard->cardDetailsUI == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("pointer null,create one cardDetailsUI."));
		currentCard->cardDetailsUI = CreateWidget<UUserWidget>(GetWorld(), cardDetailClass);
	}
	else {
		//����������Ӧ�ò���Ҫ���õģ����Ҳ���ȷ�����������ڴ��г������ڣ����UI�᲻�ϵĴ���������������ȷʵ�ǳ����Եģ�
		//�ҵ��Ļ����ڴ��Ͽ����ܴ���������
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
* ����������cardPawn���ж��Ƿ�����һ�ε���Ķ������򲻴������Ǿ�ȡ����һ�ε����Ч����Ȼ��������һ�εĵ��Ч����������ε���Ŀ��ƶ����¼
* �������Ĳ���cardPawn��ȡ����һ�ε����Ч������һ�β���¼���ƶ���
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
			//����д��...->IsA(ACardPawn::StaticClass)
			
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
	//	UE_LOG(LogTemp, Warning, TEXT("��ȡ��cardPawn"));
	//	posse
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("�޷���ȡ��cardPawn"));
	//}

	//
	//TArray<AActor*> cardPawns;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACardPawn::StaticClass(), cardPawns);

	//for()
}
