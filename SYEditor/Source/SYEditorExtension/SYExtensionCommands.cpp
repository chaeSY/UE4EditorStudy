// Fill out your copyright notice in the Description page of Project Settings.

#include "SYExtensionCommands.h"
#include "SYTestEditor.h"
#include "../SYEditor/SYTestAsset.h"

#define LOCTEXT_NAMESPACE "SYCommand"

void FSYExtensionCommands::RegisterCommands()
{
	// friendly name: 실제 에디터에서 보여질 이름
	
	UI_COMMAND(ShowMessageBoxCommand, "ShowMessageBox", "Desc: Command Tooltip", EUserInterfaceActionType::Button, FInputGesture());

	UI_COMMAND(OpenTestEditorCommand, "OpenTestEditor", "Open Test Editor", EUserInterfaceActionType::Button, FInputGesture());
}

void FSYExtensionActions::Action()
{
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("SYAction", "Action1 Message"));
}


void FSYExtensionActions::ActionOpenTestEditor()
{
	TSharedRef<FSYTestEditor> TestEditor(new FSYTestEditor());
	TestEditor->Init(NewObject<USYTestAsset>());

}


#undef LOCTEXT_NAMESPACE
