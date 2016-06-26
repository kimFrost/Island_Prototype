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


UENUM(BlueprintType)
enum class EPersonState : uint8
{
	Hungry UMETA(DisplayName = "Hungry"),
	Starving UMETA(DisplayName = "Starving"),
	Sad UMETA(DisplayName = "Sad"),
	Depressed UMETA(DisplayName = "Depressed"),
	Injured UMETA(DisplayName = "Injured"),
	Wounded UMETA(DisplayName = "Wounded"),
	Sick UMETA(DisplayName = "Sick"),
	Happy UMETA(DisplayName = "Happy"),
	Ecstatic UMETA(DisplayName = "Ecstatic"),
	Thirsty UMETA(DisplayName = "Thirsty"),
	Dehydrated UMETA(DisplayName = "Dehydrated")
};

UENUM(BlueprintType)
enum class EDeathCauses : uint8
{
	Stavation UMETA(DisplayName = "Stavation"),
	DoomEvent UMETA(DisplayName = "DoomEvent")
};

UENUM(BlueprintType)
enum class EPersonStat : uint8
{
	None UMETA(DisplayName = "None"),
	Confidence UMETA(DisplayName = "Confidence"),
	Endurance UMETA(DisplayName = "Endurance"),
	Cognitive UMETA(DisplayName = "Cognitive")
};


//~~~~~ STRUCTS ~~~~~//

USTRUCT(BlueprintType)
struct FST_Rating
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Rating(FString Title = "", int32 Rating = 0)
		: Title(Title)
		, Rating(Rating)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rating")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rating")
	int32 Rating;
};

USTRUCT(BlueprintType)
struct FST_Happening
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Happening(FString Title = "", int32 Rating = 0)
		: Title(Title)
		, Rating(Rating)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rating")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rating")
	int32 Rating;
};

USTRUCT(BlueprintType)
struct FST_Provider
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Provider(FString Id = "", float Quantity = 0.f)
		: Id(Id)
		, Quantity(Quantity)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float Quantity;
};

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


//~~~~~ DATA IMPORT ~~~~~//

USTRUCT(BlueprintType)
struct FST_Trait : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Trait(FString Id = "", FString Description = "", int32 Rating = 0)
		: Id(Id)
		, Description(Description)
		, Rating(Rating)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	int32 Rating;
};

//FST_Trait(FString Id = "", FString Description = "", FST_Rating Rating = FST_Rating())


USTRUCT(BlueprintType)
struct FST_Profession : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Profession(FString Id = "", FString Description = "")
		: Id(Id)
		, Description(Description)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession")
	FString Description;
};


USTRUCT(BlueprintType)
struct FST_Item : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Item(FString Id = "", FString Title = "", FString Description = "", int32 Quantity = 0, FString Group = "", TArray<FString> Tags = TArray<FString>(), FST_Provider Provides = FST_Provider())
		: Id(Id)
		, Title(Title)
		, Description(Description)
		, Quantity(Quantity)
		, Group(Group)
		, Tags(Tags)
		, Provides()
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Group;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<FString> Tags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FST_Provider Provides;
};

USTRUCT(BlueprintType)
struct FST_Event : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Event(FString Id = "", FString Title = "", FString Description = "")
		: Id(Id)
		, Title(Title)
		, Description(Description)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description;
};


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

USTRUCT(BlueprintType)
struct FST_Action : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Action()
		: Title(TEXT("No title"))
		, TileId(TEXT(""))
		, Type(ETileActions::DoNothing)
		, Conditions(TArray<FString>())
		, NotConditions(TArray<FString>())
		, ReqStats(TArray<FST_Stat>())
		, Events(TArray<FString>())
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FString TileId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	ETileActions Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FString> Conditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FString> NotConditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FST_Stat> ReqStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FString> Events;
};



USTRUCT(BlueprintType)
struct FST_Card : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Card()
		: Id(TEXT(""))
		, Title(TEXT("No title"))
		, TileScene(TEXT(""))
		, Items(TArray<FString>())
		, Actions(TArray<FST_Action>())
		, IdleActions(TArray<FST_Action>())
		, bBlockPath(false)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString TileScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<FString> Items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<FST_Action> Actions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<FST_Action> IdleActions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	bool bBlockPath;
};





UCLASS()
class ISLAND_PROTOTYPE_API UIslandDataHolder : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UIslandDataHolder(const FObjectInitializer& ObjectInitializer);

};

