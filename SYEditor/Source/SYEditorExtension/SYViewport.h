// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateFwd.h"
#include "UObject/GCObject.h"
#include "SEditorViewport.h"


// Viewport
// 렌더링 관련 상태와 관련 컴포넌트를 관리

class FSYTestEditor;
class USYTestAsset;
class FAdvancedPreviewScene;
class FSYViewportClient;
class SSYViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SSYViewport){}
		SLATE_ARGUMENT(TWeakPtr <FSYTestEditor>, Editor)
		SLATE_ARGUMENT(USYTestAsset*, TestAsset)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	SSYViewport();
	~SSYViewport();

protected:
	// Create ViewportClient
	virtual TSharedRef<class FEditorViewportClient> MakeEditorViewportClient() override; 

private:
	TSharedPtr<FAdvancedPreviewScene>	PreviewScene;
	TSharedPtr<FSYViewportClient>		ViewportClient;
	TWeakPtr<FSYTestEditor>				Editor;
	TWeakObjectPtr<USYTestAsset>		TestAsset;
};