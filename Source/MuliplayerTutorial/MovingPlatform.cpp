// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() {
    Super::BeginPlay();

    if (HasAuthority()){
        SetReplicates(true);
        SetReplicateMovement(true);
        StartingLocation = GetActorLocation();
        TargetLocation += StartingLocation;
        MovementVectorLength = (TargetLocation - StartingLocation).SquaredLength();
        MovementVectorNormalized = (TargetLocation - StartingLocation).GetUnsafeNormal();
    }
}

void AMovingPlatform::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    
    if(HasAuthority()){
        FVector Location = GetActorLocation();
        Location += MovementVectorNormalized * DeltaTime * Speed;

        if (!invertMovement) {
            if ((Location - StartingLocation).SquaredLength() > MovementVectorLength) {
                invertMovement = !invertMovement;
                MovementVectorNormalized *= -1;
                UE_LOG(LogTemp, Warning, TEXT("Invert 1"));
            }
        } else {
            if ((Location - TargetLocation).SquaredLength() > MovementVectorLength) {
                invertMovement = !invertMovement;
                MovementVectorNormalized *= -1;
                UE_LOG(LogTemp, Warning, TEXT("Invert 2"));
            }
        }
        SetActorLocation(Location);
    }
    
}