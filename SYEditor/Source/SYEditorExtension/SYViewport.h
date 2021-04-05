// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateFwd.h"
#include "UObject/GCObject.h"
#include "SEditorViewport.h"


// Viewport
// 렌더링 관련 상태와 관련 컴포넌트를 관리

class FSYEditor;
class USYTestAsset;
class FAdvancedPreviewScene;
class FSYViewportClient;
class SSYViewport : public SEditorViewport, public FGCObject
{
public:
	SLATE_BEGIN_ARGS(SSYViewport){}
		SLATE_ARGUMENT(TWeakPtr <FSYEditor>, Editor)
		SLATE_ARGUMENT(USYTestAsset*, TestAsset)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	SSYViewport();
	~SSYViewport();

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

protected:
	virtual TSharedRef<class FEditorViewportClient> MakeEditorViewportClient() override;

private:
	TSharedPtr<FAdvancedPreviewScene>	PreviewScene;
	TSharedPtr<FSYViewportClient>		ViewportClient;
	TWeakPtr<FSYEditor> Editor;
	USYTestAsset*		TestAsset;
};