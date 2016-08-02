// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandDataHolder.h"
#include "IslandPerson.h"
#include "IslandGameInstance.h"



// Sets default values
UIslandGameInstance::UIslandGameInstance(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	DATA_Items = nullptr;
	ReadTables();

}


/******************** ReadTables *************************/
void UIslandGameInstance::ReadTables()
{
	//~~ Items ~~//
	UDataTable* ItemTable = (UDataTable*)StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("DataTable'/Game/Island/Util/Structs/DATA_Items.DATA_Items'"));
	if (ItemTable)
	{
		DATA_Items = ItemTable;
	}

}


/******************** EnrichString *************************/
FString UIslandGameInstance::EnrichString(FString String, AIslandPerson* Person)
{
	if (Person)
	{
		String = String.Replace(TEXT("%FIRSTNAME%"), *Person->FirstName);
	}
	return String;
}


/******************** GetRoll *************************/
float UIslandGameInstance::GetRoll(AIslandPerson* Person, TArray<FST_Modifier> Modifiers)
{
	float Roll = 0.f;
	
	Roll = FMath::RandRange(0.f, 1.f);


	// Useless index

	// Traits + Modifiers matchup -> Outcomes

	return Roll;
}


/******************** GetOutcome *************************/
FST_Outcome UIslandGameInstance::GetOutcome(TArray<FST_Outcome> Outcomes, AIslandPerson* Person, TArray<FST_Modifier> Modifiers)
{
	FST_Outcome ResultOutcome;
	float Roll = GetRoll(Person, Modifiers);
	for (auto& Outcome : Outcomes)
	{
		if (Roll >= Outcome.ChanceRangeFrom && Roll <= Outcome.ChanceRangeTo)
		{
			ResultOutcome = Outcome;
			break;
		}
	}
	return ResultOutcome;
}


/******************** ParseAction *************************/
void UIslandGameInstance::ParseAction(ETarget TargetType, AIslandPerson* Person, EAction Action, float Amount, ECause Cause)
{
	// Or just a array of people? What else could be subject for target action?

	/*
	AIslandPerson* TargetPerson = Cast<AIslandPerson>(Target);
	if (TargetPerson)
	{}
	*/

	if (Person)
	{
		switch (Action)
		{
			case EAction::TakeDamage:
			{
				Person->TakeDamage(ECause::DoomEvent, Amount);
				break;
			}
			default:
				break;
		}
	}
}


/******************** ParseOutcome *************************/
void UIslandGameInstance::ParseOutcome(FST_Outcome Outcome, AIslandPerson* Person, ECause Cause, bool AddUpdate)
{
	// Some complex shit goes here..
	switch (Outcome.ActionType)
	{
		case EAction::GiveItem:
		{
			StoreItem(Outcome.ActionWildcard, Outcome.ActionAmount);
			break;
		}
		case EAction::TakeDamage:
		{
			if (Person) Person->TakeDamage(Cause, Outcome.ActionAmount);
			break;
		}
		case EAction::BreakStation:
		{
			if (Person)
			{
				// Find station though person and set brken state with ActionAmount
			}
			break;
		}
		default:
			break;
	}
	if (AddUpdate)
	{
		AddTaskDone(Outcome.Description, Person, EUsefulRating::Neutral, ETaskType::Work);
	}
}


/******************** AddTaskDone *************************/
void UIslandGameInstance::AddTaskDone(FString Description, AIslandPerson* By, EUsefulRating Rating, ETaskType TaskType)
{
	FST_TaskDone DoneTask = FST_TaskDone(EnrichString(Description, By), By, Rating, TaskType);
	TasksDoneThisTurn.Add(DoneTask);
	if (By)
	{
		By->TasksDoneThisTurn.Add(DoneTask);
	}
}


/******************** AddNotification *************************/
void UIslandGameInstance::AddNotification(FString Msg, AIslandPerson* Concerning, ENotificationType Type)
{
	Notifications.Add(FST_Notification(EnrichString(Msg, Concerning), Type));
}


/******************** GetRandItem *************************/
FST_Item UIslandGameInstance::GetRandItem() {
	FST_Item Item;
	if (DATA_Items)
	{
		TArray<FName> RowNames = DATA_Items->GetRowNames();
		int RandIndex = FMath::RandRange(0, RowNames.Num() - 1);
		FName RowId = RowNames[RandIndex];
		static const FString ContextString(TEXT("ItemLookup"));
		FST_Item* ItemData = DATA_Items->FindRow<FST_Item>(RowId, ContextString);
		Item = *ItemData; // Copy
	}
	return Item;
}


/******************** GetItem *************************/
FST_Item UIslandGameInstance::GetItem(FString Id, int32 Quantity) {
	FST_Item Item;
	if (DATA_Items)
	{
		static const FString ContextString(TEXT("ItemLookup"));
		FST_Item* ItemData = DATA_Items->FindRow<FST_Item>(FName(*Id), ContextString);
		if (ItemData)
		{
			Item = *ItemData; // Copy
			Item.Quantity = Quantity;
		}
	}
	return Item;
}


/******************** GetTotalResourceStored *************************/
float UIslandGameInstance::GetTotalResourceStored(FString Id)
{
	float Total = 0.f;
	for (auto& Item : StoredItems)
	{
		if (Item.Value.Provides.Id == Id)
		{
			Total += Item.Value.Provides.Quantity * Item.Value.Quantity;
		}
	}
	return Total;
}


/******************** HasItemsAvailable *************************/
bool UIslandGameInstance::HasItemsAvailable(TMap<FString, float>& Request, bool bTagSearch, bool bUseProvides)
{
	bool RequestMet = true;
	TMap<FString, FST_Item> Items = StoredItems; //~~ Copy items to prevent destruction of data ~~//


	return RequestMet;
}



/******************** HasResourcesAvailable *************************/
bool UIslandGameInstance::HasResourcesAvailable(TMap<FString, float>& Request)
{
	bool RequestMet = true;
	
	TMap<FString, FST_Item> Items = StoredItems; //~~ Copy items to prevent destruction of data ~~//

	for (auto& ResourceRequest : Request)
	{
		float RequestSize = ResourceRequest.Value;
		for (auto& Item : Items)
		{
			//if (Item.Value.Tags.Contains(ResourceRequest.Key)) // Item has request tag
			if (Item.Value.Provides.Id == ResourceRequest.Key) // Item has provides the requested resource
			{
				RequestSize -= Item.Value.Provides.Quantity * Item.Value.Quantity; // Provides * items in storage of type
				/*
				for (auto& Provide : Item.Value.Provides)
				{
					if (Provide.Id == ResourceRequest.Key)
					{
						RequestSize -= Provide.Quantity * Item.Value.Quantity; // Provides * items in storage of type
					}
				}
				*/
			}
		}
		if (RequestSize > 0)
		{
			RequestMet = false;
			break;
		}
	}

	return RequestMet;
}



/******************** RequestResource *************************/
TArray<FST_Item> UIslandGameInstance::RequestResource(FString Id, float Quantity, TEnumAsByte<ERequestMetGateEnum>& Branches)
{
	TArray<FST_Item> Items;
	bool Met = true;

	TMap<FString, float> Request;
	Request.Add(Id, Quantity);

	if (HasResourcesAvailable(Request))
	{
		for (auto& ResourceRequest : Request) // Loop request. //!! Only one id for now !!//
		{
			float RequestSize = ResourceRequest.Value;
			while (RequestSize > 0)
			{
				bool bAnyTaken = false;
				
				//~~ Shuffle list of keys ~~//
				TArray<FString> Keys;
				for (auto& Item : StoredItems)
				{
					Keys.Add(Item.Key);
				}
				Keys.Sort([this](const FString Item1, const FString Item2) {
					return FMath::FRand() < 0.5f;
				});

				for (FString Key : Keys)
				{
					FST_Item& Item = StoredItems[Key];

					// Best fit?  Closest. Need 1.4  Provide 1.5 , Provide 0.5. It would consume both else.

					// Calc waste for mimimum waste

					if (Item.Provides.Id == ResourceRequest.Key && Item.Quantity > 0)
					{
						if (Item.Provides.Quantity <= RequestSize)
						{
							RequestSize -= Item.Provides.Quantity;
							FST_Item ConsumedItem = Item;
							ConsumedItem.Quantity = 1;
							Items.Add(ConsumedItem);
							bAnyTaken = true;
							Item.Quantity--;
						}
					}
				}

				if (!bAnyTaken && RequestSize > 0)
				{
					// Take an item and produce waste
					for (auto& Item : StoredItems)
					{
						if (Item.Value.Provides.Id == ResourceRequest.Key && Item.Value.Quantity > 0)
						{
							if (Item.Value.Provides.Quantity >= RequestSize)
							{
								RequestSize = 0;
								FST_Item ConsumedItem = Item.Value;
								ConsumedItem.Quantity = 1;
								Items.Add(ConsumedItem);
								bAnyTaken = true;
								Item.Value.Quantity--;
							}
						}
					}
					if (RequestSize > 0)
					{
						// Logic is wrong then
						Met = false;
						break;
					}
				}
				else if (!bAnyTaken)
				{
					// Infinity loop safe handling
					Met = false;
					break;
				}
			}

			/*
			for (auto& Item : StoredItems)
			{
				if (Item.Value.Provides.Id == ResourceRequest.Key) // Item has provides the requested resource
				{
					float TotalItemProvide = Item.Value.Provides.Quantity * Item.Value.Quantity;
					if (TotalItemProvide >= RequestSize)
					{
						int AmountNeeded = RequestSize / Item.Value.Provides.Quantity;
						RequestSize = 0;
						FST_Item ConsumedItem = Item.Value;
						ConsumedItem.Quantity = AmountNeeded;
						Items.Add(ConsumedItem);
						Item.Value.Quantity -= AmountNeeded;
					}
					else 
					{
						RequestSize -= TotalItemProvide;
						FST_Item ConsumedItem = Item.Value;
						ConsumedItem.Quantity = Item.Value.Quantity; // maybe redudant
						Items.Add(ConsumedItem);
						Item.Value.Quantity = 0;
					}
					//RequestSize -= Item.Value.Provides.Quantity * Item.Value.Quantity; // Provides * items in storage of type
				}
			}
			*/
		}
	}
	else
	{
		Met = false;
	}

	//~~ Gate routes ~~//
	if (Met)
	{
		Branches = ERequestMetGateEnum::Met;
	}
	else
	{
		Branches = ERequestMetGateEnum::NotMet;
	}

	//~~ Combine items in return array ~~//
	TMap<FString, FST_Item> TempItems;
	for (auto& Item : Items)
	{
		if (TempItems.Contains(Item.Id))
		{
			TempItems[Item.Id].Quantity += Item.Quantity;
		}
		else
		{
			TempItems.Add(Item.Id, Item);
		}
	}
	Items.Empty();
	for (auto& Item : TempItems)
	{
		Items.Add(Item.Value);
	}

	OnIventoryUpdated.Broadcast();

	//GameInstance->OnPersonMoveEnded.Broadcast(this, TilePlacedOn);

	//~~ Return item ~~//
	return Items;
}


/******************** RequestItem *************************/
TArray<FST_Item> UIslandGameInstance::RequestItem(FString Id, int32 Quantity, bool bTagSearch, bool bUseProvides, TEnumAsByte<ERequestMetGateEnum>& Branches)
{
	TArray<FST_Item> Items;
	bool Met = true;

	TMap<FString, float> Request;
	Request.Add(Id, Quantity);

	if (HasItemsAvailable(Request, bTagSearch, bUseProvides))
	{
		// Remove item from storage

		// Set return item Resource
	}
	else
	{
		Met = false;
	}

	/*
	if (StoredItems.Contains(Id) && StoredItems[Id].Quantity >= Quantity)
	{
		StoredItems[Id].Quantity -= Quantity;
	}
	else {
		Met = false;
	}
	*/

	//~~ Gate routes ~~//
	if (Met)
	{
		Branches = ERequestMetGateEnum::Met;
	}
	else
	{
		Branches = ERequestMetGateEnum::NotMet;
	}
	//~~ Return item ~~//
	return Items;
}


/******************** StoreItem *************************/
FST_Item UIslandGameInstance::StoreItem(FString Id, int Quantity) {
	FST_Item Item;
	if (DATA_Items)
	{
		if (StoredItems.Contains(Id))
		{
			StoredItems[Id].Quantity += Quantity;
			Item = StoredItems[Id];
		}
		else
		{
			static const FString ContextString(TEXT("ItemLookup"));
			FST_Item* ItemData = DATA_Items->FindRow<FST_Item>(FName(*Id), ContextString);
			if (ItemData)
			{
				Item = *ItemData; // Copy
				Item.Quantity = Quantity;
				StoredItems.Add(Id, Item);
			}
		}
	}
	OnIventoryUpdated.Broadcast(); 
	return Item;
}


/******************** GetStoredItems *************************/
TArray<FST_Item> UIslandGameInstance::GetStoredItems() {
	TArray<FST_Item> Items;
	for (auto& Item : StoredItems)
	{
		Items.Add(Item.Value);
	}
	return Items;
}