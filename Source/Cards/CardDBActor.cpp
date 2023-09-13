// Fill out your copyright notice in the Description page of Project Settings.


#include "CardDBActor.h"
#include "Engine/DataTable.h"
#include "SQLiteDataBaseConnection.h"

//#include"Database/SQLiteSupport/Source/SQLiteSupport"


// Sets default values
ACardDBActor::ACardDBActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

//ACardDBActor::~ACardDBActor()
//{
//	db.Close();
//
//}

bool ACardDBActor::OpenDB(const FString& path)
{
	FString dbPath =FPaths::ProjectUserDir() + path;
	UE_LOG(LogTemp, Warning, TEXT("Sqlite Connection Start"));

	db = new FSQLiteDatabaseConnection();
	if (!db)
	{
		UE_LOG(LogTemp, Warning, TEXT("FSQLiteDatabaseConnection creating failed"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Wrong"));
	if (!db->Open(*dbPath, nullptr, nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Sqlite Connection Failed"));
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Sqlite Connection Succeed"));
	return true;
}

void ACardDBActor::CloseDB()
{
	db->Close();
	delete db;
	db = nullptr;
}


TArray<FString> ACardDBActor::GetCardsID()
{
	FString query = FString::Printf(TEXT("SELECT CardID FROM CurrentDeck"));

	FDataBaseRecordSet* outRecords = nullptr;
	if (!db->Execute(*query, outRecords))
	{
		delete outRecords;
		UE_LOG(LogTemp, Warning, TEXT("Query Executing Failed"));
		return TArray<FString>();
	}

	int count = outRecords->GetRecordCount();
	UE_LOG(LogTemp, Warning, TEXT("CardNum:%i"), count);

	TArray<FString> CardsID;
	for (FDataBaseRecordSet::TIterator i(outRecords);i;++i)
	{
		CardsID.Push(i->GetString(*i->GetColumnNames()[0].ColumnName));
	}
	delete outRecords;
	return CardsID;
}

FText ACardDBActor::GetCardName(const FString& CardID)
{
	FString query = FString::Printf(TEXT("SELECT CardName FROM MonsterCard WHERE CardID='%s'"),*CardID);

	FDataBaseRecordSet* outRecords = nullptr;
	if (!db->Execute(*query, outRecords))
	{
		delete outRecords;
		UE_LOG(LogTemp, Warning, TEXT("Query Executing Failed"));
		return FText();
	}
	FString CardName = outRecords->GetString(*outRecords->GetColumnNames()[0].ColumnName);
	delete outRecords;
	return FText::FromString(CardName);
}

FText ACardDBActor::GetCardEffectText(const FString& CardID)
{
	FString query = FString::Printf(TEXT("SELECT CEText FROM MonsterCard WHERE CardID='%s'"), *CardID);

	FDataBaseRecordSet* outRecords = nullptr;
	if (!db->Execute(*query, outRecords))
	{
		delete outRecords;
		UE_LOG(LogTemp, Warning, TEXT("Query Executing Failed"));
		return FText();
	}
	FString CardEffectText = outRecords->GetString(*outRecords->GetColumnNames()[0].ColumnName);
	delete outRecords;
	return FText::FromString(CardEffectText);
}

uint8 ACardDBActor::GetCardLevel(const FString& CardID)
{

	//查询语句
	FString query = FString::Printf(TEXT("SELECT CardLevel FROM MonsterCard WHERE CardID='%s'"), *CardID);

	FDataBaseRecordSet* outRecords = nullptr;
	if (!db->Execute(*query, outRecords))
	{
		delete outRecords;
		UE_LOG(LogTemp, Warning, TEXT("Query Executing Failed"));
		return 0;
	}
	FString CardLevel = FDataBaseRecordSet::TIterator(outRecords)->GetColumnNames()[0].ColumnName;
	delete outRecords;
	return outRecords->GetInt(*CardLevel);
}

int ACardDBActor::GetCardValue(const FString& CardID, MonsterAttribute mAttri)
{
	//根据枚举选择对应的列名
	FString ColumnName;
	switch (mAttri)
	{
	case MonsterAttribute::LEVEL:
		ColumnName = "CardLevel";
		break;
	case MonsterAttribute::AD:
		ColumnName = "AD";
		break;
	case MonsterAttribute::AP:
		ColumnName = "AP";
		break;
	case MonsterAttribute::HP:
		ColumnName = "HP";
		break;
	case MonsterAttribute::MR:
		ColumnName = "MR";
		break;
	case MonsterAttribute::PR:
		ColumnName = "PR";
		break;
	}

	//查询语句
	FString query = FString::Printf(TEXT("SELECT %s FROM MonsterCard WHERE CardID='%s'"), *ColumnName, *CardID);

	FDataBaseRecordSet* outRecords = nullptr;
	if (!db->Execute(*query, outRecords))
	{
		delete outRecords;
		UE_LOG(LogTemp, Warning, TEXT("Query Executing Failed"));
		return 0;
	}

	FDataBaseRecordSet::TIterator recordIterator = FDataBaseRecordSet::TIterator(outRecords);
	FString CardVal = recordIterator->GetColumnNames()[0].ColumnName;
	int val = recordIterator->GetInt(*CardVal);

	delete outRecords;

	return val;
}

FText ACardDBActor::GetCardText(const FString& CardID, CardText cText)
{
	//根据枚举选择对应的列名
	FString ColumnName;
	switch (cText)
	{
	case CardText::CardName:
		ColumnName = "CardName";
		break;
	case CardText::CardEffectText:
		ColumnName = "CEText";
		break;
	case CardText::CardSummonConditionText:
		ColumnName = "SCText";
		break;
	}

	//查询语句
	FString query = FString::Printf(TEXT("SELECT %s FROM MonsterCard WHERE CardID='%s'"), *ColumnName, *CardID);

	FDataBaseRecordSet* outRecords = nullptr;

	if (!db->Execute(*query, outRecords))
	{
		delete outRecords;
		UE_LOG(LogTemp, Warning, TEXT("Query Executing Failed"));
		return FText();
	}

	FString CardText = FDataBaseRecordSet::TIterator(outRecords)->GetString(*outRecords->GetColumnNames()[0].ColumnName);

	UE_LOG(LogTemp, Warning, TEXT("OK"));
	UE_LOG(LogTemp, Warning, TEXT("result:%s"), *CardText);
	UE_LOG(LogTemp, Warning, TEXT("END"));
	delete outRecords;

	return FText::FromString(CardText);
}


// Called when the game starts or when spawned
void ACardDBActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACardDBActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

