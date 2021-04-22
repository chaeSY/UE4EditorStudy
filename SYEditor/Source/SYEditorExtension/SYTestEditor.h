// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"


class IDetailsView;
class SSYViewport;
class USYTestAsset;
class FSYTestEditor : public FAssetEditorToolkit, public FGCObject
{
public:
	~FSYTestEditor();

	void Init(class USYTestAsset* Asset);

	//
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	virtual FName GetToolkitFName() const override;				
	virtual FText GetBaseToolkitName() const override;			
	virtual FString GetWorldCentricTabPrefix() const override;	
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	TSharedRef<class SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<class SDockTab> SpawnTab_Detail(const FSpawnTabArgs& Args);

	// FGCObject override
	// FReferenceCollector에 등록한 UObject는 가비지컬렉션에서 RootSet으로 취급한다.
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

private:
	static const FName TestEditorIdentifier;
	static const FName ViewportTabID;
	static const FName DetailTabID;

	void InitDetailView();
	void InitViewport();
	void InitLayout();

	TSharedPtr<IDetailsView>	DetailsView;
	TSharedPtr<SSYViewport>		Viewport;
	USYTestAsset*				TestAsset; 

};