// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IslandDataHolder.generated.h"



//~~~~~ Forward Declarations ~~~~~//
//class APOTLStructure;


//~~~~~ ENUMS ~~~~~//


UENUM(BlueprintType)
enum class ETileActions : uint8
{
	Explore UMETA(DisplayName = "Explore"),
	Event UMETA(DisplayName = "Event"),
	GiveItem UMETA(DisplayName = "Give item"),
	DoNothing UMETA(DisplayName = "Do nothing")
};


//~~~~~ DATA IMPORT ~~~~~//

/*
USTRUCT(BlueprintType)
struct FST_Stat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Stat(EPersonStat Stat = EPersonStat::None, int32 Level = 0)
		: Stat(Stat)
		, Level(Level)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EPersonStat Stat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Level;
};
*/


//~~~~~ STRUCTS ~~~~~//

/*
USTRUCT(BlueprintType)
struct FST_Modifier
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Modifier()
		: Id(TEXT(""))
		, Description(TEXT(""))
		, Amount(0)
		, TurnsLeft(-1)
		//, Stats(TArray<FST_Stat>())
	{}
	TMap<FString, int32> Needs;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	int32 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	int32 TurnsLeft;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	//TArray<FST_Stat> Stats;
};
*/





UCLASS()
class ISLAND_PROTOTYPE_API UIslandDataHolder : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UIslandDataHolder(const FObjectInitializer& ObjectInitializer);

};

