// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class FSYExtensionCommands : public TCommands<FSYExtensionCommands>
{
public:
	FSYExtensionCommands()
		:TCommands< FSYExtensionCommands>(TEXT("SYEditor"), NSLOCTEXT("SYEditor", "SYEditor", "SYEditor"), NAME_None, TEXT("Default"))
	{
	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr<class FUICommandInfo> Command;
	TSharedPtr<class FUICommandInfo> OpenTestEditorCommand;
};

class FSYExtensionActions
{
public:
	static void Action();
	static void ActionOpenTestEditor();
};