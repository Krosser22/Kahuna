// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TheGallery.h"


IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, TheGallery, "TheGallery" );

void DebugLog(FString msg)
{
  if (GEngine)
  {
    GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, msg);
  }
}

void DebugLog(FString msg, int msgInt)
{
  FString realMsg = msg;
  realMsg.AppendInt(msgInt);
  if (GEngine)
  {
    GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, realMsg);
  }
}