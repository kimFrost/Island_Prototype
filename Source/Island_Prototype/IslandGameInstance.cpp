// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandDataHolder.h"
#include "IslandGameInstance.h"




/******************** HasItemsAvailable *************************/
bool UIslandGameInstance::HasItemsAvailable(TMap<FString, int32>& Request, bool TagSearch)
{
	bool RequestMet = true;
	TMap<FString, FST_Item> Items = StoredItems; //~~ Copy items to prevent destruction of data ~~//

	// Produce search? Mango gives 0.5 food..

	if (TagSearch)
	{
		for (auto& ResourceRequest : Request)
		{
			int32 RequestSize = ResourceRequest.Value;
			// Re-copy items ? No!
			for (auto& Item : Items)
			{
				if (Item.Value.Tags.Contains(ResourceRequest.Key)) // Item has request tag
				{

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


	/*
	for (auto& ResourceRequest : Request)
	{
		if (ResourceAvailable.Contains(ResourceRequest.Key))
		{
			int32 Remaining = ResourceRequest.Value;
			if (Remaining > ResourceAvailable[ResourceRequest.Key]) //~~ If request is larger than the resource pool ~~//
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
	*/
	return RequestMet;
}


/******************** RequestItem *************************/
FST_Item UIslandGameInstance::RequestItem(FString Id, int32 Quantity, bool TagSearch, TEnumAsByte<ERequestMetGateEnum>& Branches)
{
	FST_Item Resource = FST_Item();
	bool Met = true;

	if (TagSearch)
	{

	}

	if (StoredItems.Contains(Id) && StoredItems[Id].Quantity >= Quantity)
	{
		StoredItems[Id].Quantity -= Quantity;
	}
	else {
		Met = false;
	}

	if (Met)
	{
		Branches = ERequestMetGateEnum::Met;
		Resource.Id = Id;
		Resource.Title = Id;
		Resource.Quantity = Quantity;
	}
	else
	{
		Branches = ERequestMetGateEnum::NotMet;
	}
	return Resource;
}


/******************** StoreItem *************************/
void UIslandGameInstance::StoreItem() {
	// Get data from data table and create new item for storage


}


/******************** GetStoredItems *************************/
TArray<FST_Item> UIslandGameInstance::GetStoredItems() {
	TArray<FST_Item> Items;

	return Items;
}