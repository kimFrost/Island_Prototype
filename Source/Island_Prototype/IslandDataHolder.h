// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IslandDataHolder.generated.h"



//~~~~~ Forward Declarations ~~~~~//
class AIslandPerson;


//~~~~~ ENUMS ~~~~~//

UENUM(BlueprintType)
enum class EUsefulRating : uint8
{
	UtterlyUseless UMETA(DisplayName = "Utterly useless"),
	Useless UMETA(DisplayName = "Useless"),
	Neutral UMETA(DisplayName = "Nothing special"),
	Useful UMETA(DisplayName = "Useful"),
	VeryUseful UMETA(DisplayName = "Very useful")
};


UENUM(BlueprintType)
enum class ETaskType : uint8
{
	Consume UMETA(DisplayName = "Consume"),
	Work UMETA(DisplayName = "Work")
};


UENUM(BlueprintType)
enum class ENotificationType : uint8
{
	Warning UMETA(DisplayName = "Warning")
};


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

// Maybe use levels instead? Hungry lv 1-3 -> Starving lv 1-3

UENUM(BlueprintType)
enum class ECause : uint8
{
	Stavation UMETA(DisplayName = "Stavation"),
	Work UMETA(DisplayName = "Work"),
	DoomEvent UMETA(DisplayName = "DoomEvent")
};

UENUM(BlueprintType)
enum class ERegenCause : uint8
{
	Satiated UMETA(DisplayName = "Satiated")
};

UENUM(BlueprintType)
enum class EPersonStat : uint8
{
	None UMETA(DisplayName = "None"),
	Confidence UMETA(DisplayName = "Confidence"),
	Endurance UMETA(DisplayName = "Endurance"),
	Cognitive UMETA(DisplayName = "Cognitive")
};

UENUM(BlueprintType)
enum class ETarget : uint8
{
	None UMETA(DisplayName = "None"),
	Camp UMETA(DisplayName = "Camp"),
	Group UMETA(DisplayName = "Group"),
	Person UMETA(DisplayName = "Person"),
	Station UMETA(DisplayName = "Station")
};

UENUM(BlueprintType)
enum class EAction : uint8
{
	None UMETA(DisplayName = "None"),
	TakeDamage UMETA(DisplayName = "Take damage"),
	BreakStation UMETA(DisplayName = "Break station"),
	GiveItem UMETA(DisplayName = "Give item"),
	Die UMETA(DisplayName = "Die"),
	Capture UMETA(DisplayName = "Capture")
};



//~~~~~ STRUCTS ~~~~~//

USTRUCT(BlueprintType)
struct FST_Notification
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Notification(FString Msg = "", ENotificationType Type = ENotificationType::Warning)
		: Msg(Msg)
		, Type(Type)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Notification")
	FString Msg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Notification")
	ENotificationType Type;
};


USTRUCT(BlueprintType)
struct FST_TaskDone
{
	GENERATED_USTRUCT_BODY()
public:
	FST_TaskDone(FString Description = "", AIslandPerson* By = nullptr, EUsefulRating Rating = EUsefulRating::Neutral, ETaskType TaskType = ETaskType::Work)
		: Description(Description)
		, By(By)
		, Rating(Rating)
		, TaskType(TaskType)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	AIslandPerson* By;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	EUsefulRating Rating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task")
	ETaskType TaskType;
};

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
struct FST_Stat
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

USTRUCT(BlueprintType)
struct FST_Outcome
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Outcome(FString Title = "", FString Description = "", float ChanceRangeFrom = 0.f, float ChanceRangeTo = 1.f, ETarget Target = ETarget::None, EAction ActionType = EAction::None, float ActionAmount = 0.f, FString ActionWildcard = "")
		: Title(Title)
		, Description(Description)
		, ChanceRangeFrom(ChanceRangeFrom)
		, ChanceRangeTo(ChanceRangeTo)
		, Target(Target)
		, ActionType(ActionType)
		, ActionAmount(ActionAmount)
		, ActionWildcard(ActionWildcard)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outcome")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outcome")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outcome")
	float ChanceRangeFrom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outcome")
	float ChanceRangeTo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outcome")
	ETarget Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outcome")
	EAction ActionType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outcome")
	float ActionAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outcome")
	FString ActionWildcard;
};

USTRUCT(BlueprintType)
struct FST_Influence
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Influence(FString Id = "", FString Title = "", float Alteration = 0.f)
		: Id(Id)
		, Title(Title)
		, Alteration(Alteration)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	float Alteration;
};


USTRUCT(BlueprintType)
struct FST_Modifier
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Modifier(FString Target = "", FString TargetId = "", TArray<FST_Outcome> Outcomes = TArray<FST_Outcome>())
		: Target(Target)
		, TargetId(TargetId)
		, Outcomes(Outcomes)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	FString Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	FString TargetId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	TArray<FST_Outcome> Outcomes;
};


//~~~~~ DATA IMPORT ~~~~~//

USTRUCT(BlueprintType)
struct FST_DoomEvent : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_DoomEvent(FString Id = "", FString Title = "", FString Description = "", TArray<FST_Outcome> Outcomes = TArray<FST_Outcome>(), TArray<FST_Influence> Influences = TArray<FST_Influence>())
		: Id(Id)
		, Title(Title)
		, Description(Description)
		, Outcomes(Outcomes)
		, Influences(Influences)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	TArray<FST_Outcome> Outcomes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	TArray<FST_Influence> Influences;
};


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


USTRUCT(BlueprintType)
struct FST_Station : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Station(FString Id = "", FString Title = "", FString Description = "", TArray<FST_Outcome> Outcomes = TArray<FST_Outcome>(), TArray<FST_Influence> Influences = TArray<FST_Influence>(), FString Group = "", TArray<FString> Tags = TArray<FString>())
		: Id(Id)
		, Title(Title)
		, Description(Description)
		, Outcomes(Outcomes)
		, Influences(Influences)
		, Tags(Tags)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	TArray<FST_Outcome> Outcomes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	TArray<FST_Influence> Influences; 
	
	// Influences vs traits specifics?  Might not modify result chance, but result in something specific, damage, certain result, damage stations, etc.

	// Modifiers

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station")
	TArray<FString> Tags;

	// Passive provides?

};


USTRUCT(BlueprintType)
struct FST_Location : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Location(FString Id = "", FString Title = "", FString Description = "", int32 Quantity = 0, FString Group = "", TArray<FString> Tags = TArray<FString>(), FST_Provider Provides = FST_Provider())
		: Id(Id)
		, Title(Title)
		, Description(Description)

		, Quantity(Quantity)
		, Group(Group)
		, Tags(Tags)
		, Provides()
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FString Description;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FString Group;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	TArray<FString> Tags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FST_Provider Provides;

	// Risk 

	// Dangers.

	// Rewards
	// Tiers reward?

	// Bonuses: Traits that fit.

	// Penalties. Traits that doesn't fit.

	// Or posisble items to find. 
	// Items hidden until found once. In any location.

	// Infinity items: Fish in stream. 

	// Rituals that alter the locations stats.

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

