// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "MovingPlatform.h"
#include <Components/BoxComponent.h>
#include <EngineUtils.h>

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!ensure(TriggerVolume != nullptr)) return;
	RootComponent = TriggerVolume;
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();	
	TriggerVolume->OnComponentBeginOverlap.AddUniqueDynamic(this, &APlatformTrigger::OnBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddUniqueDynamic(this, &APlatformTrigger::OnEndOverlap);
	GetAllPlatforms();
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformTrigger::GetAllPlatforms()
{
	const UWorld* world = GetWorld();
	for (TActorIterator<AActor> It(world, AMovingPlatform::StaticClass()); It; ++It)
	{
		AMovingPlatform* Platform = CastChecked<AMovingPlatform>(*It);
		if (IsValid(Platform))
		{
			PlatformsToTrigger.Add(Platform);
		}
	}
}

void APlatformTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Start"));
	for (TArray<AMovingPlatform*>::RangedForIteratorType platformIt = PlatformsToTrigger.begin(); platformIt != PlatformsToTrigger.end(); ++platformIt) {
		(*platformIt)->AddActiveTrigger();
	}
}

void APlatformTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("End"));
	for (TArray<AMovingPlatform*>::RangedForIteratorType platformIt = PlatformsToTrigger.begin(); platformIt != PlatformsToTrigger.end(); ++platformIt) {
		(*platformIt)->RemoveActiveTrigger();
	}
}