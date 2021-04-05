// Fill out your copyright notice in the Description page of Project Settings.

#include "SYTestEditor.h"
#include "SYExtensionStyle.h"
#include "PropertyEditorModule.h"
#include "SYViewport.h"
#include "../SYEditor/SYTestAsset.h"

const FName FSYTestEditor::TestEditorIdentifier = FName("TestEditorID");
const FName FSYTestEditor::ViewportTabID = FName("ViewportTabID");
const FName FSYTestEditor::DetailTabID = FName("DetailTabID");

FSYTestEditor::~FSYTestEditor()
{
	DetailsView.Reset();
}

void FSYTestEditor::Init(USYTestAsset* Asset)
{
	TestAsset = Asset;

	InitDetailView();
	InitLayout();
}

void FSYTestEditor::InitLayout()
{
	EToolkitMode::Type Mode = EToolkitMode::Type::Standalone;
	TSharedPtr< class IToolkitHost > InitToolkitHost;

	const TSharedRef<FTabManager::FLayout> DefaultLayout = FTabManager::NewLayout("SYEidtorLayout1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f) // Coefficient: 계수
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)->SetHideTabWell(true)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->AddTab(ViewportTabID, ETabState::OpenedTab)->SetHideTabWell(true) // Tab을 보이고 숨기는 기능. 근데 Well의 뜻이 뭐지?
				)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(DetailTabID, ETabState::OpenedTab)
				)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, TestEditorIdentifier, DefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, TestAsset);
}

void FSYTestEditor::InitDetailView()
{
	// create detail view
	FPropertyEditorModule& PropertyEditor = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	const bool bIsUpdatable = false;
	const bool bAllowFavorites = true;
	const bool bAllowSearch = true;
	const bool bIsLockable = false;
	const FDetailsViewArgs DetailViewArgs(bIsUpdatable, bIsLockable, bAllowSearch, FDetailsViewArgs::ObjectsUseNameArea);

	DetailsView = PropertyEditor.CreateDetailView(DetailViewArgs);

	// set object
	if (DetailsView.IsValid())
	{
		DetailsView->SetObject(TestAsset);
	}
}

void FSYTestEditor::InitViewport()
{
	TSharedRef<FSYTestEditor> ref = SharedThis(this);

	Viewport = SNew(SSYViewport)
		//.Editor(SharedThis(this))
		.TestAsset(TestAsset);
}

FName FSYTestEditor::GetToolkitFName() const
{
	return FName(TEXT("ToolkitName"));
}

#define LOCTEXT_NAMESPACE "SYEditor"

FText FSYTestEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "BaseToolkitName");
}

FString FSYTestEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "WorldCentricTabPrefix2").ToString();
}

FLinearColor FSYTestEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(1.f, 0.f, 0.f, 1.f);
}

void FSYTestEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	// LOCTEXT(key, literal)
	// localization 공부 필요

	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_SYAssetEditor", "SY Asset Editor"));

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	/* RegisterTabSpawner
	 * const FName TabId, 
	 * const FOnSpawnTab& OnSpawnTab, 
	 * const FCanSpawnTab& CanSpawnTab
	 */

	// delegate 바인딩
	// CreateSP: 슬레이트 인스턴스 바인딩
	// BindUObject: uobject 타입 바인딩

	InTabManager->RegisterTabSpawner(ViewportTabID, FOnSpawnTab::CreateSP(this, &FSYTestEditor::SpawnTab_Viewport))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FSYExtensionStyle::GetStyleSetName(), "SYExtensions.CommandIcon16"));

	InTabManager->RegisterTabSpawner(DetailTabID, FOnSpawnTab::CreateSP(this, &FSYTestEditor::SpawnTab_Detail))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FSYExtensionStyle::GetStyleSetName(), "SYExtensions.CommandIcon20"));
}

void FSYTestEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(ViewportTabID);
	InTabManager->UnregisterTabSpawner(DetailTabID);
}

TSharedRef<SDockTab> FSYTestEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == ViewportTabID);
	return SNew(SDockTab)
		[
			Viewport.ToSharedRef()
		];
}

TSharedRef<SDockTab> FSYTestEditor::SpawnTab_Detail(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == DetailTabID);
	return SNew(SDockTab)
		[
			DetailsView.ToSharedRef()

		];
}


#undef LOCTEXT_NAMESPACE 