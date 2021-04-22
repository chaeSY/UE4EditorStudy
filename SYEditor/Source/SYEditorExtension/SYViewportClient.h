// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

// ViewportClient
// ���� ������ ������ ����Ʈ ���� �����͸� ����
// ī�޶� ��ġ�� ����� �Է��� �ؼ��ϰ� ����Ʈ ������ ����

// SYEidtor(����� ���� ������)�� �ǿ� Viewport�� �����Ѵ�.
// Viewport�� ������ �� PreviewScene�� ViewportClient�� �����Ѵ�.
// �����, ViewportClient�� MakeEditorViewportClient �Լ����� �����Ѵ�.
// MakeEditorViewportClinet�� SEditorViewport���� ��ӹ޴� ���� �����Լ��̴�.

class FSYTestEditor;
class SSYViewport;
class USYTestAsset;
class FAdvancedPreviewScene;
class FSYViewportClient : public FEditorViewportClient, public TSharedFromThis<FSYViewportClient>
{
public:
	FSYViewportClient(const TWeakPtr<FSYTestEditor> InEditor, const TSharedRef<FAdvancedPreviewScene> InPreviewScene, const TSharedRef<SSYViewport> InViewport, USYTestAsset* InTestAsset);
	~FSYViewportClient();

private:
	TWeakPtr<FSYTestEditor>				Editor;
	TWeakPtr<SSYViewport>				SYViewport;
	TWeakPtr<FAdvancedPreviewScene>		AdvancedPreviewScene;
	USYTestAsset*						TestAsset; //dangling pointer�� �� ����.
};