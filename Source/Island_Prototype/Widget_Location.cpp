// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "Widget_Location.h"




void UWidget_Location::SwitchScene(FString SceneName)
{
	for (int32 i = 0; i < Scenes.Num(); i++)
	{
		FST_LocationScene& Scene = Scenes[i];
		if (Scene.Title == SceneName)
		{
			for (int32 ii = 0; ii < Scene.Actions.Num(); ii++)
			{
				UUserWidget* Action = Scene.Actions[ii];
				Action->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else {
			for (int32 ii = 0; ii < Scene.Actions.Num(); ii++)
			{
				UUserWidget* Action = Scene.Actions[ii];
				Action->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UWidget_Location::Exit()
{

}

void UWidget_Location::CreateAction()
{

}

void UWidget_Location::CreateScene()
{
	FST_LocationScene Scene;


	Scenes.Add(Scene);
}

