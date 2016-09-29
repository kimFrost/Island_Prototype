// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandDataHolder.h"
#include "Task.h"

UTask::UTask()
{
	Progress = 0.f;
	Timeleft = 0.f;

}

UTask::~UTask()
{

}

void UTask::ResetTask()
{
	Progress = 0.f;
	Timeleft = 0.f;
	PeopleWorkedOnTask = TArray<AIslandPerson*>();
}

float UTask::WorkTask(AIslandPerson* Person, float AmountTime)
{
	if (!PeopleWorkedOnTask.Contains(Person))
	{
		PeopleWorkedOnTask.Add(Person);
	}

	Progress += AmountTime / Data.WorkTime;
	if (Progress >= 1)
	{
		CompleteTask();
	}
	return Progress;
}

void UTask::CompleteTask()
{

}