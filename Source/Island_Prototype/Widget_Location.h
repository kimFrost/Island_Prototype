// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Widget_Location.generated.h"




//~~~~~ STRUCTS ~~~~~//


USTRUCT(BlueprintType)
struct FST_LocationScene
{
	GENERATED_USTRUCT_BODY()
public:
	FST_LocationScene()
		: Title("")
		, Actions(TArray<UUserWidget*>())
		//: Id(TEXT(""))
		//, Amount(0)
	{}
	//TMap<FString, int32> Needs;
	//int32 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	TArray<UUserWidget*> Actions;
	// Actions
};


/**
 * 
 */
UCLASS()
class ISLAND_PROTOTYPE_API UWidget_Location : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My New User Widget")
	TArray<FST_LocationScene> Scenes;

	// Actions

	// Events / completed events


	UFUNCTION(BlueprintCallable, Category = "Location")
	void SwitchScene(FString SceneName);

	UFUNCTION(BlueprintCallable, Category = "Location")
	void Exit();

	UFUNCTION(BlueprintCallable, Category = "Location")
	void CreateAction();

	UFUNCTION(BlueprintCallable, Category = "Location")
	void CreateScene();


	/*
	"Runtime/UMG/Public/UMG.h"
	"Runtime/UMG/Public/UMGStyle.h"
	"Runtime/UMG/Public/Slate/SObjectWidget.h"
	"Runtime/UMG/Public/IUMGModule.h"
	"Runtime/UMG/Public/Blueprint/UserWidget.h"
	*/

};
