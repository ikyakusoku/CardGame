// Fill out your copyright notice in the Description page of Project Settings.


#include "CardPawn.h"
#include "Components/WidgetComponent.h"



// Sets default values
ACardPawn::ACardPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	////创建一个静态网格体为Plane的静态网格体组件，作为根组件
	//cardMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CardMeshComponent"));
	//SetRootComponent(cardMeshComponent);
	//
	//ConstructorHelpers::FObjectFinder<UStaticMesh> planeAsset(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	//if (planeAsset.Succeeded())
	//{
	//	cardMeshComponent->SetStaticMesh(planeAsset.Object);
	//	cardMeshComponent->SetRelativeScale3D(FVector(3.58,2.56,1));
	//}

	//创建显示卡片正面的UWidgetComponent组件
	cardFrontWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CardFrontWidgetComponent"));
	SetRootComponent(cardFrontWidgetComponent);

	//auto cardFrontWidegtClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/UI/BP_CardWidget.BP_CardWidget'"));
	ConstructorHelpers::FClassFinder<UUserWidget> cardFrontWidgetAsset(TEXT("WidgetBlueprint'/Game/UI/BP_CardWidget'"));
	cardFrontWidgetComponent->SetWidgetClass(cardFrontWidgetAsset.Class);

	//这里默认是world吗？可以去掉这一句吗？
	cardFrontWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	cardFrontWidgetComponent->SetDrawAtDesiredSize(true);
	cardFrontWidgetComponent->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));

	//创建显示卡片背面的UWidgetComponent组件
	cardBackWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CardBackWidgetComponent"));
	cardBackWidgetComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	//auto cardBackWidgetClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/UI/UI_CardBackWidget.UI_CardBackWidget'"));
	ConstructorHelpers::FClassFinder<UUserWidget> cardBackWidgetAsset(TEXT("WidgetBlueprint'/Game/UI/UI_CardBackWidget'"));
	cardBackWidgetComponent->SetWidgetClass(cardBackWidgetAsset.Class);
	cardBackWidgetComponent->SetDrawSize(FVector2D(256, 358));
	cardBackWidgetComponent->SetRelativeLocation(FVector(-0.1, 0, 0));

	
}

// Called when the game starts or when spawned
void ACardPawn::BeginPlay()
{
	Super::BeginPlay();
	Controller = GetWorld()->GetFirstPlayerController();
	//EnableInput(Cast<APlayerController>(Controller));

}

void ACardPawn::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();
	
	//TEST
	if (static_cast<uint8>(currentArea) & static_cast<uint8>(AreaType::HandArea))
	{
		SetActorLocation(GetActorLocation() + FVector(displacementX, 0, displacementZ));
	}

}

void ACardPawn::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();
	
	if (static_cast<uint8>(currentArea) & static_cast<uint8>(AreaType::HandArea))
	{
		SetActorLocation(GetActorLocation() - FVector(displacementX, 0, displacementZ));
	}
}


// Called every frame
void ACardPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACardPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



