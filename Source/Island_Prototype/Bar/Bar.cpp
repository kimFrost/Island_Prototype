// Fill out your copyright notice in the Description page of Project Settings.

#include "Island_Prototype.h"
#include "IslandDataHolder.h"
#include "Bar.h"

UBar::UBar()
{
	Min = 0.f;
	Max = 10.f;
	Value = 0.f;
	Percent = 0.f;

}

UBar::~UBar()
{
}

// AddValue
void UBar::AddValue(float _Value)
{
	Value += _Value;
	FMath::Clamp(Value, Min, Max);
	UpdatePercent();
}



// UpdatePercent
void UBar::UpdatePercent()
{
	Percent = Value / 10;
	// Set state
	for(FST_BarSegment& Segment : Data.Segments)
	{
		if (Value >= Segment.Min && Value < Segment.Max)
		{
			SetState(Segment);
			break;
		}
		else if (Value == 10.f && Segment.Max == 10.f)
		{
			SetState(Segment);
			break;
		}
	}
}

void UBar::SetState(FST_BarSegment& Segment)
{
	CurrentState = Segment;
}

