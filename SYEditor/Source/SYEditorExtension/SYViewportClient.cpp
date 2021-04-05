// Fill out your copyright notice in the Description page of Project Settings.

#include "SYViewportClient.h"
#include "SYTestEditor.h"
#include "SYViewport.h"
#include "AdvancedPreviewScene.h"


/* FEditorViewportClient
 *	FEditorModeTools* InModeTools, 
 *	FPreviewScene* InPreviewScene = nullptr, 
 *	const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr
 */

FSYViewportClient::FSYViewportClient(const TWeakPtr<FSYEditor> InEditor, const TSharedRef<FAdvancedPreviewScene> InPreviewScene, const TSharedRef<SSYViewport> InViewport, USYTestAsset* InTestAsset)
	:FEditorViewportClient(nullptr, &InPreviewScene.Get(), InViewport)
	//, Editor(InEditor)
	//, SYViewport(InViewport)
	//, AdvancedPreviewScene(InPreviewScene.Get())
	//, TestAsset(InTestAsset)
{

}

FSYViewportClient::~FSYViewportClient()
{

}