// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#include "Player_Normal_Projectile.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundWave.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "DMGGameInstance.h"
#include "UserConstant.h"

// Sets default values
APlayer_Normal_Projectile::APlayer_Normal_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMeshComponent->SetRelativeScale3D(FVector(10.f, 10.f, 10.f));
	ProjectileMeshComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	ProjectileParticle->SetVisibility(false);

	ProjectileMovementComponent->InitialSpeed = 20000.0f;
	ProjectileMovementComponent->MaxSpeed = 20000.0f;

	PlayerProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PLAYERPROJECTILEPARTICLE"));
	PlayerProjectileParticle->SetupAttachment(CollisionComponent);
	PlayerProjectileParticle->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PT_BODY(TEXT("StaticMesh'/Game/SciFiWeapDark/Weapons/Darkness_Pistol_Ammo.Darkness_Pistol_Ammo'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/SciFiWeapDark/FX/Particles/P_AssaultRifle_Tracer_Dark.P_AssaultRifle_Tracer_Dark'"));

	if (PT_BODY.Succeeded())
	{
		ProjectileMeshComponent->SetStaticMesh(PT_BODY.Object);
	}

	if (ParticleAsset.Succeeded())
	{
		PlayerProjectileParticle->SetTemplate(ParticleAsset.Object);
	}

	LifeTime_Counter = 0;
	Damage = 200;

	// Sound
	static ConstructorHelpers::FObjectFinder<USoundWave> PlayerBulletCollisionSoundWave(TEXT("SoundWave'/Game/Sound/PlayerBulletCollision.PlayerBulletCollision'"));
	PlayerBulletCollisionSound = PlayerBulletCollisionSoundWave.Object;
}

// Called when the game starts or when spawned
void APlayer_Normal_Projectile::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Player Projectile BeginPlay"));

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayer_Normal_Projectile::OnOverlapBegin);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATP_VirtualRealityPawn_Motion::StaticClass(), FoundActors);

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		Player = Cast<ATP_VirtualRealityPawn_Motion>(FoundActors[i]);
	}

	UE_LOG(LogTemp, Warning, TEXT("gameinstance %s"), *GetWorld()->GetGameInstance()->GetName());
	
}

// Called every frame
void APlayer_Normal_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Check_Destroy();
}

void APlayer_Normal_Projectile::Check_Destroy()
{
	LifeTime_Counter++;
	if (LifeTime_Counter > PLAYER_PROJECTILE_LIFETIME)
		Destroy();
}

void APlayer_Normal_Projectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->GetClass()->GetName().Equals(TEXT("Boss"))))
	{
		Cast<ABoss>(OtherActor)->SetBossCurrentHP(Cast<ABoss>(OtherActor)->GetBossCurrentHP() - Damage);
		//UE_LOG(LogClass, Warning, TEXT("Boss HP : %d"), Cast<ABoss>(OtherActor)->GetBossCurrentHP());
		
		Player->SetScore(Player->GetScore() + (Damage * GUN_SCORE_RATE));
		//UE_LOG(LogClass, Warning, TEXT("score : %d"), Player->GetScore());

		UGameplayStatics::PlaySound2D(this, PlayerBulletCollisionSound, 0.3f * Cast<UDMGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetSoundVolumeRate());

		Destroy();
		
	}
}
