// Fill out your copyright notice in the Description page of Project Settings.

#include "SYEditorExtension.h"
#include "SYExtensionCommands.h"
#include "SYExtensionStyle.h"
#include "LevelEditor.h"

IMPLEMENT_MODULE( FSYEditorExtension, SYEditorExtension );

#define LOCTEXT_NAMESPACE "SYEditor"

struct SYToolbarHandler
{
	static void CreateToolbar(FToolBarBuilder& ToolbarBuilder)
	{
		ToolbarBuilder.BeginSection("SY");

		//FSlateIcon::FSlateIcon
		// const FName& InStyleSetName, 
		// const FName& InStyleName );

		//get ui command
		const TSharedPtr< const FUICommandInfo > UICommand(FSYExtensionCommands::Get().Command);
		
		// get slate icon
		FName StyleName = TEXT("SYExtensions.CommandIcon40");
		FSlateIcon SlateIcon(FSYExtensionStyle::GetStyleSetName(), StyleName);

		ToolbarBuilder.AddToolBarButton(
			UICommand,
			NAME_None,
			TAttribute<FText>(), // todo: TAttribute은 무엇인지?
			TAttribute<FText>(),
			SlateIcon);

		// AddToolBarButton
		// const TSharedPtr< const FUICommandInfo > InCommand, 
		// FName InExtensionHook, 
		// const TAttribute<FText>& InLabelOverride, 
		// const TAttribute<FText>& InToolTipOverride, 
		// const TAttribute<FSlateIcon>& InIconOverride, 
		// const EUserInterfaceActionType UserInterfaceActionType, 
		// FName InTutorialHighlightName);

		ToolbarBuilder.EndSection();
	}
};

struct SYMenuHandler
{
	struct SYSubMenuHandler
	{
		static void CreateSubMenu(FMenuBuilder& SubMenuBuilder)
		{
			SubMenuBuilder.AddMenuEntry(FSYExtensionCommands::Get().Command,
				NAME_None,
				TAttribute<FText>(),
				TAttribute<FText>(),
				FSlateIcon(FSYExtensionStyle::GetStyleSetName(), TEXT("SYExtensions.CommandIcon16")));
		}
	};

	static void CreateMenu(FMenuBuilder& MenuBuilder)
	{
		MenuBuilder.BeginSection("Section1", LOCTEXT("SYMenu", "SY Menu Section1"));

		//void AddMenuEntry(
		// const TSharedPtr< const FUICommandInfo > InCommand, 
		// FName InExtensionHook = NAME_None, 
		// const TAttribute<FText>& InLabelOverride = TAttribute<FText>(), 
		// const TAttribute<FText>& InToolTipOverride = TAttribute<FText>(), 
		// const FSlateIcon& InIconOverride = FSlateIcon(), 
		// FName InTutorialHighlightName = NAME_None)

		// add default menu
		MenuBuilder.AddMenuEntry(FSYExtensionCommands::Get().Command, 
			NAME_None, 
			TAttribute<FText>(), 
			TAttribute<FText>(), 
			FSlateIcon(FSYExtensionStyle::GetStyleSetName(), TEXT("SYExtensions.CommandIcon20")));

		// add sub menu
		MenuBuilder.AddSubMenu(LOCTEXT("SYMenu", "SYSubMenu"), 
			LOCTEXT("SYMenu", "SYSubMenu Tooltip"), 
			FNewMenuDelegate::CreateStatic(&SYSubMenuHandler::CreateSubMenu), 
			false, 
			FSlateIcon(FSYExtensionStyle::GetStyleSetName(), TEXT("SYExtensions.CommandIcon20")));

		MenuBuilder.EndSection();
	}
};


void FSYEditorExtension::StartupModule()
{
	FSYExtensionStyle::Init();
	FSYExtensionStyle::ReloadTexture();

	FSYExtensionCommands::Register();

	CommandList = MakeShareable(new FUICommandList());
	CommandList->MapAction(FSYExtensionCommands::Get().Command, FExecuteAction::CreateStatic(&FSYExtensionActions::Action), FCanExecuteAction());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	// create menu extender
	TSharedPtr<FExtender> SYMenuExtender = MakeShareable(new FExtender());
	SYMenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, CommandList, FMenuExtensionDelegate::CreateStatic(&SYMenuHandler::CreateMenu));
	
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(SYMenuExtender);

	// create toolbar extender
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender());
	ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, CommandList, FToolBarExtensionDelegate::CreateStatic(&SYToolbarHandler::CreateToolbar));
	
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FSYEditorExtension::ShutdownModule()
{
	FSYExtensionCommands::Unregister();
	FSYExtensionStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE