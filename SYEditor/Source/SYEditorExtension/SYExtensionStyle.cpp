// Fill out your copyright notice in the Description page of Project Settings.

#include "SYExtensionStyle.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FSYExtensionStyle::Instance = nullptr;

const ISlateStyle& FSYExtensionStyle::Get()
{
	return *Instance;
}

FName FSYExtensionStyle::GetStyleSetName()
{	
	static FName StyleSetName(TEXT("SYEditorExtension"));
	return StyleSetName;
}

void FSYExtensionStyle::Init()
{
	if (!Instance.IsValid())
	{
		Instance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*Instance);
	}
}

void FSYExtensionStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*Instance);
	ensure(Instance.IsUnique()); // ensure 무엇인지 확인해볼 것
	Instance.Reset();
}

void FSYExtensionStyle::ReloadTexture()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

TSharedRef<FSlateStyleSet> FSYExtensionStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->SetContentRoot(FPaths::ProjectContentDir() / TEXT("Editor/Icons"));

	// StyleSet에 Property와 Icon을 등록
	FName PropertyName = TEXT("SYExtensions.CommandIcon40");
	FSlateImageBrush* Brush = new FSlateImageBrush(StyleSet->RootToContentDir("Icon40", TEXT(".png")), FVector2D(40, 40));
	StyleSet->Set(PropertyName, Brush);

	StyleSet->Set(TEXT("SYExtensions.CommandIcon20"), new FSlateImageBrush(StyleSet->RootToContentDir("Icon20", TEXT(".png")), FVector2D(20, 20)));
	StyleSet->Set(TEXT("SYExtensions.CommandIcon16"), new FSlateImageBrush(StyleSet->RootToContentDir("Icon16", TEXT(".png")), FVector2D(16, 16)));


	return StyleSet;
}
