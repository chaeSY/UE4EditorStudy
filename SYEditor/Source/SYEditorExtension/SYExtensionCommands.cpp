// Fill out your copyright notice in the Description page of Project Settings.

#include "SYExtensionCommands.h"

#define LOCTEXT_NAMESPACE "SYCommand"

void FSYExtensionCommands::RegisterCommands()
{
	// friendly name: 실제 에디터에서 보여질 이름
	
	UI_COMMAND(Command, "SYCommand", "Desc: Command Tooltip", EUserInterfaceActionType::Button, FInputGesture());
}

void FSYExtensionActions::Action()
{
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("SYAction", "Action1 Message"));
}


#undef LOCTEXT_NAMESPACE
