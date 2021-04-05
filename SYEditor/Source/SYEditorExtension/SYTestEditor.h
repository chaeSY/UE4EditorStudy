// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"


class FSYTestEditor : public FAssetEditorToolkit
{
public:
	~FSYTestEditor();

	void Init(class USYTestAsset* Asset);
	void InitLayout();
	void InitDetailView();
	void InitViewport();
	//
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	virtual FName GetToolkitFName() const override;				// Must implement in derived class!
	virtual FText GetBaseToolkitName() const override;			// Must implement in derived class!
	virtual FString GetWorldCentricTabPrefix() const override;	// Must implement in derived class!
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	TSharedRef<class SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<class SDockTab> SpawnTab_Detail(const FSpawnTabArgs& Args);


private:
	static const FName TestEditorIdentifier;
	static const FName ViewportTabID;
	static const FName DetailTabID;

	TSharedPtr< class IDetailsView > DetailsView;
	TSharedPtr< class SSYViewport > Viewport;
	class USYTestAsset* TestAsset; //UPROPERTY 안해도 되나?

};