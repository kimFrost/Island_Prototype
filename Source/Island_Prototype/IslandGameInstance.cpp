// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandDataHolder.h"
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



/******************** HasItemsAvailable *************************/
bool UIslandGameInstance::HasItemsAvailable(TMap<FString, float>& Request, bool bTagSearch, bool bUseProvides)
{
	bool RequestMet = true;
	TMap<FString, FST_Item> Items = StoredItems; //~~ Copy items to prevent destruction of data ~~//

	//!! Produce search? Mango gives 0.5 food.. !!//

	//?? I shouldn't combine bTagSearch and bUseProvides ??//

	//?? Just loop all and their providers ??//

	if (bTagSearch)
	{
		for (auto& ResourceRequest : Request)
		{
			float RequestSize = ResourceRequest.Value;
			// Re-copy items ? No!
			for (auto& Item : Items)
			{
				if (RequestSize <= 0) break; // Early exit
				if (Item.Value.Tags.Contains(ResourceRequest.Key)) // Item has request tag
				{
					if (bUseProvides)
					{
						for (auto& Provide : Item.Value.Provides)
						{
							if (Provide.Id == ResourceRequest.Key)
							{
								RequestSize -= Provide.Quanity * Item.Value.Quantity; // Provides * items in storage of type
							}
						}
					}
					else
					{
						RequestSize -= Item.Value.Quantity;
					}
				}
			}
			if (RequestSize > 0) 
			{
				RequestMet = false;
				break;
			}
		}
	}
	else
	{
		for (auto& ResourceRequest : Request)
		{
			if (Items.Contains(ResourceRequest.Key))
			{
				int32 RequestSize = ResourceRequest.Value;
				if (RequestSize > Items[ResourceRequest.Key].Quantity) //~~ If request is larger than the resource pool ~~//
				{
					RequestMet = false;
					break;
				}
			}
			else
			{
				RequestMet = false;
				break;
			}
		}
	}
	return RequestMet;
}


/******************** RequestItem *************************/
FST_Item UIslandGameInstance::RequestItem(FString Id, int32 Quantity, bool bTagSearch, bool bUseProvides, TEnumAsByte<ERequestMetGateEnum>& Branches)
{
	FST_Item Resource = FST_Item();
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
	return Resource;
}


/******************** StoreItem *************************/
FST_Item UIslandGameInstance::StoreItem(FString Id, int Quantity) {
	// Get data from data table and create new item for storage
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
			Item = *ItemData; // Copy
			Item.Quantity = Quantity;
			StoredItems.Add(Id, Item);
		}
		
		/*
		FST_Card Card;
		if (DATA_Cards)
		{
			TArray<FName> RowNames = DATA_Cards->GetRowNames();
			int RandIndex = FMath::RandRange(0, RowNames.Num() - 1);
			FName RowId = RowNames[RandIndex];
			static const FString ContextString(TEXT("CardLookup"));
			FST_Card* CardData = DATA_Cards->FindRow<FST_Card>(RowId, ContextString);
			if (CardData)
			{
				Card = *CardData;
			}
		}
		return Card;
		*/
	}
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