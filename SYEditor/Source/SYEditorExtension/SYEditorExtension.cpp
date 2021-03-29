// Fill out your copyright notice in the Description page of Project Settings.

#include "SYEditorExtension.h"
#include "SYExtensionCommands.h"

#include "LevelEditor.h"

IMPLEMENT_MODULE( FSYEditorExtension, SYEditorExtension );

#define LOCTEXT_NAMESPACE "SYEditor"

struct SYToolbarHandler
{
	static void CreateToolbar(FToolBarBuilder& ToolbarBuilder)
	{
		ToolbarBuilder.BeginSection("SY");
		ToolbarBuilder.AddToolBarButton(FSYExtensionCommands::Get().Command);
		ToolbarBuilder.EndSection();
	}
};

struct SYMenuHandler
{
	struct SYSubMenuHandler
	{
		static void CreateSubMenu(FMenuBuilder& SubMenuBuilder)
		{
			SubMenuBuilder.AddMenuEntry(FSYExtensionCommands::Get().Command);
		}
	};

	static void CreateMenu(FMenuBuilder& MenuBuilder)
	{
		MenuBuilder.BeginSection("Section1", LOCTEXT("SYMenu", "SY Menu Section1"));
		MenuBuilder.AddMenuEntry(FSYExtensionCommands::Get().Command);
		MenuBuilder.AddSubMenu(LOCTEXT("SYMenu", "SYSubMenu"), LOCTEXT("SYMenu", "SYSubMenu Tooltip"), FNewMenuDelegate::CreateStatic(&SYSubMenuHandler::CreateSubMenu), false, FSlateIcon());
		MenuBuilder.EndSection();
	}
};


void FSYEditorExtension::StartupModule()
{
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
}

#undef LOCTEXT_NAMESPACE