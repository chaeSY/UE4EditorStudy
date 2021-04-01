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

		
		// add messagebox command toolbar

		// get ui command
		const TSharedPtr< const FUICommandInfo > MessageBoxCommand(FSYExtensionCommands::Get().ShowMessageBoxCommand);
		
		// get slate icon
		FName PropertyName = TEXT("SYExtensions.CommandIcon40");
		FSlateIcon SlateIcon40(FSYExtensionStyle::GetStyleSetName(), PropertyName);
		
		// add toolbar button
		ToolbarBuilder.AddToolBarButton(
			MessageBoxCommand,
			NAME_None,
			TAttribute<FText>(), // todo: TAttribute은 무엇인지?
			TAttribute<FText>(),
			SlateIcon40);

		/* AddToolBarButton
		 * const TSharedPtr< const FUICommandInfo > InCommand, 
		 * FName InExtensionHook, 
		 * const TAttribute<FText>& InLabelOverride, 
		 * const TAttribute<FText>& InToolTipOverride, 
		 * const TAttribute<FSlateIcon>& InIconOverride, 
		 * const EUserInterfaceActionType UserInterfaceActionType, 
		 * FName InTutorialHighlightName);
		 */


		// add OpenTestEditor command toolbar
		ToolbarBuilder.AddToolBarButton(
			FSYExtensionCommands::Get().OpenTestEditorCommand,
			NAME_None,
			TAttribute<FText>(),
			TAttribute<FText>(),
			FSlateIcon(FSYExtensionStyle::GetStyleSetName(), TEXT("SYExtensions.CommandIcon40")));


		ToolbarBuilder.EndSection();
	}
};

struct SYMenuHandler
{
	struct SYSubMenuHandler
	{
		static void CreateSubMenu(FMenuBuilder& SubMenuBuilder)
		{
			SubMenuBuilder.AddMenuEntry(FSYExtensionCommands::Get().OpenTestEditorCommand,
				NAME_None,
				TAttribute<FText>(),
				TAttribute<FText>(),
				FSlateIcon(FSYExtensionStyle::GetStyleSetName(), TEXT("SYExtensions.CommandIcon16")));
		}
	};

	static void CreateMenu(FMenuBuilder& MenuBuilder)
	{
		MenuBuilder.BeginSection("Section1", LOCTEXT("SYMenu", "SY Menu Section1"));

		// add default menu
		MenuBuilder.AddMenuEntry(FSYExtensionCommands::Get().ShowMessageBoxCommand, 
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

	// binding action
	CommandList = MakeShareable(new FUICommandList());
	CommandList->MapAction(FSYExtensionCommands::Get().ShowMessageBoxCommand, FExecuteAction::CreateStatic(&FSYExtensionActions::Action), FCanExecuteAction());
	CommandList->MapAction(FSYExtensionCommands::Get().OpenTestEditorCommand, FExecuteAction::CreateStatic(&FSYExtensionActions::ActionOpenTestEditor), FCanExecuteAction());

	// add menu and toolbar to LevelEditor
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