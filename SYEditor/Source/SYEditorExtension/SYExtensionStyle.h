// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Styling/SlateStyle.h"

class FSYExtensionStyle
{
public:
	static const ISlateStyle& Get();
	static FName GetStyleSetName();

	static void Init();
	static void Shutdown();
	static void ReloadTexture();

private:
	static TSharedRef<FSlateStyleSet> Create();
	static TSharedPtr<FSlateStyleSet> Instance;

};