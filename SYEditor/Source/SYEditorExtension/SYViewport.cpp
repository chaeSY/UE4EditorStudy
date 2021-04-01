// Fill out your copyright notice in the Description page of Project Settings.

#include "SYViewport.h"
#include "SYViewportClient.h"

SSYViewport::SSYViewport()
{

}

SSYViewport::~SSYViewport()
{

}

void SSYViewport::AddReferencedObjects(FReferenceCollector& Collector)
{

}

//!!!!! tsharedptr tsharedref 정리필요.
TSharedRef<FEditorViewportClient> SSYViewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable(new FSYViewportClient(Editor.ToSharedRef(), PreviewScene, this, TestAsset));
	return ViewportClient.ToSharedRef();
}