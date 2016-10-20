// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGallery.h"
#include "OwnGameInstance.h"



int32 UOwnGameInstance::GetTotalPointsCoconuts()
{
	return _TotalPointsCoconuts;
}

void UOwnGameInstance::SetTotalPointsCoconuts(int32 points)
{
	_TotalPointsCoconuts = points;
}

void UOwnGameInstance::IncreaseTotalPointsCoconuts(int32 points)
{
	_TotalPointsCoconuts += points;
}

