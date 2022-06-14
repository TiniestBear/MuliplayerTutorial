// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer) {
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformGameInstance::CTOR"));
}

void UPuzzlePlatformGameInstance::Init() {
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformGameInstance::INIT"));
}

void UPuzzlePlatformGameInstance::Host() {
    if (!ensure(GEngine != nullptr)) return;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UPuzzlePlatformGameInstance::HOST"));
    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;
    World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString& Address) {
    FString callAddress = FString("UPuzzlePlatformGameInstance::JOIN ") + Address;
    if (!ensure(GEngine != nullptr)) return;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, callAddress);
    
    APlayerController* playerController = GetFirstLocalPlayerController();
    if (!ensure(playerController != nullptr)) return;
    playerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}