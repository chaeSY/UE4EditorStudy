// Fill out your copyright notice in the Description page of Project Settings.

#include "SYViewport.h"
#include "SYViewportClient.h"
#include "SYTestEditor.h"
#include "AdvancedPreviewScene.h"
#include "../SYEditor/SYTestAsset.h"

SSYViewport::SSYViewport()
{

}

SSYViewport::~SSYViewport()
{

}
void SSYViewport::Construct(const FArguments& InArgs)
{
	Editor = InArgs._Editor;
	TestAsset = InArgs._TestAsset;
	SEditorViewport::Construct(SEditorViewport::FArguments());
}


void SSYViewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	//이건 무엇인지
	//Collector
}

TSharedRef<FEditorViewportClient> SSYViewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable(new FSYViewportClient(Editor, PreviewScene.ToSharedRef(), SharedThis(this), TestAsset));
	return ViewportClient.ToSharedRef();
}