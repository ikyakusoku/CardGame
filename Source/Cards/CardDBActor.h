// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardDBActor.generated.h"


UENUM(BlueprintType)
enum class MonsterAttribute :uint8
{
	LEVEL UMETA(DisplayName="Level"),
	HP UMETA(DisplayName = "HP"),
	AD UMETA(DisplayName = "AD"),
	AP UMETA(DisplayName = "AP"),
	PR UMETA(DisplayName = "PR"),
	MR UMETA(DisplayName = "MR")
};


UENUM(BlueprintType)
enum class CardText :uint8
{
	CardName				UMETA(DisplayName = "CardName"),
	CardEffectText			UMETA(DisplayName = "CardEffectText"),
	CardSummonConditionText UMETA(DisplayName = "CardSummonConditionText")
};

UCLASS(BlueprintType)
class CARDS_API ACardDBActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardDBActor();
	//~ACardDBActor();
/*卡片数据库读取操作*/
	//创建连接。形参为Games文件夹下的路径例如："Content/DB/MonsterCard.db"
	UFUNCTION(BlueprintCallable, Category = "DBConnection,BlueprintFunc")
	bool OpenDB(const FString& path);
	//关闭连接
	UFUNCTION(BlueprintCallable, Category = "DBConnection,BlueprintFunc")
	void CloseDB();

//获取卡组中所有的卡片属性
	//获取CardID
	UFUNCTION(BlueprintCallable, Category = "DBConnection,BlueprintFunc")
	TArray<FString> GetCardsID();
	//获取CardName
	UFUNCTION(BlueprintCallable, Category = "DBConnection,BlueprintFunc")
	FText GetCardName(const FString& CardID);
	//获取效果文本
	UFUNCTION(BlueprintCallable, Category = "DBConnection,BlueprintFunc")
	FText GetCardEffectText(const FString& CardID);
	//获取文本
	UFUNCTION(BlueprintCallable, Category = "DBConnection,BlueprintFunc")
	FText GetCardText(const FString& CardID, CardText cText);
	//获取等级
	UFUNCTION(BlueprintCallable, Category = "DBConnection,BlueprintFunc")
	uint8 GetCardLevel(const FString& CardID);
	//获取属性值
	UFUNCTION(BlueprintCallable, Category = "DBConnection,BlueprintFunc")
	int GetCardValue(const FString& CardID,MonsterAttribute mAttri);

private:
	class FSQLiteDatabaseConnection* db;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};



