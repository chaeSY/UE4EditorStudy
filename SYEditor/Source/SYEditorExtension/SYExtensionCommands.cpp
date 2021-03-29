// Fill out your copyright notice in the Description page of Project Settings.

#include "SYExtensionCommands.h"

#define LOCTEXT_NAMESPACE "SYCommand"

void FSYExtensionCommands::RegisterCommands()
{
	UI_COMMAND(Command, "SYCommand", "Command Tooltip", EUserInterfaceActionType::Button, FInputGesture());
}

void FSYExtensionActions::Action()
{
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("SYAction", "Action1 Message"));
}


#undef LOCTEXT_NAMESPACE
