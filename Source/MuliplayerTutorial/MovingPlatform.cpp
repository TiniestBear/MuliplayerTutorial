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
        if(ActiveTriggers) {
            FVector Location = GetActorLocation();
            Location += MovementVectorNormalized * DeltaTime * Speed;
            const double movementMade = !invertMovement ? (Location - StartingLocation).SquaredLength() : (Location - TargetLocation).SquaredLength();
            if (movementMade > MovementVectorLength) {
                invertMovement = !invertMovement;
                MovementVectorNormalized *= -1;
            }
            SetActorLocation(Location);
        }
    }
    
}

void AMovingPlatform::AddActiveTrigger(){
    ++ActiveTriggers;
}
void AMovingPlatform::RemoveActiveTrigger(){
    if(ActiveTriggers) --ActiveTriggers;
}