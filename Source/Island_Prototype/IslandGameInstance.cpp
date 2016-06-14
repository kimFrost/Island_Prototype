// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandDataHolder.h"
#include "IslandGameInstance.h"




/******************** RequestItem *************************/
FST_Item UIslandGameInstance::RequestItem(FString Id, int32 Quantity, TEnumAsByte<ERequestMetGateEnum>& Branches)
{
	FST_Item Resource = FST_Item();
	bool Met = true;

	if (Items.Contains(Id) && Items[Id].Quantity >= Quantity)
	{
		Items[Id].Quantity -= Quantity;
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

}


/******************** GetStoredItems *************************/
void UIslandGameInstance::GetStoredItems() {

}