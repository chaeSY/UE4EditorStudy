// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

// ViewportClient
// 각종 렌더링 설정과 뷰포트 관련 데이터를 관리
// 카메라 위치와 사용자 입력을 해석하고 뷰포트 설정을 관리

// SYEidtor(사용자 설정 에디터)는 탭에 Viewport를 생성한다.
// Viewport를 생성할 때 PreviewScene과 ViewportClient를 생성한다.
// 참고로, ViewportClient는 MakeEditorViewportClient 함수에서 생성한다.
// MakeEditorViewportClinet는 SEditorViewport에서 상속받는 순수 가상함수이다.

class FSYEditor;
class SSYViewport;
class USYTestAsset;
class FAdvancedPreviewScene;
class FSYViewportClient : public FEditorViewportClient, public TSharedFromThis<FSYViewportClient>
{
public:
	FSYViewportClient(const TWeakPtr<FSYEditor> InEditor, const TSharedRef<FAdvancedPreviewScene> InPreviewScene, const TSharedRef<SSYViewport> InViewport, USYTestAsset* InTestAsset);
	~FSYViewportClient();

private:
	TWeakPtr<FSYEditor>		Editor;
	TWeakPtr<SSYViewport>	SYViewport;
	FAdvancedPreviewScene*	AdvancedPreviewScene;
	USYTestAsset*			TestAsset;
};