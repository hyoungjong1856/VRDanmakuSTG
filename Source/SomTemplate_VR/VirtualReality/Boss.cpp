// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "Boss.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "ConstructorHelpers.h"
#include "TP_VirtualRealityPawn_Motion.h"
#include "Projectile.h"
#include "Math/UnrealMathUtility.h"
#include "UserConstant.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Body->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BossBodyAsset(TEXT
	("/Game/VirtualRealityBP/Boss/Corvette-F3.Corvette-F3"));
	

	Boss_Initial_Position = FVector(0.0f, 0.0f, 10000.0f);

	if (BossBodyAsset.Succeeded())
	{
		Body->SetStaticMesh(BossBodyAsset.Object);
		Body->SetRelativeLocation(Boss_Initial_Position);
		Body->SetWorldScale3D(FVector(5.f));
	}

	Boss_MaxHP = 10000;
	Boss_CurrentHP = 10000;

	Pattern_Timer = 0.0;

	Pattern_2_Windmill_Rotation = 10;

	Pattern_4_Windmill_Rotation = 10;

	// Boss Movement variable
	Boss_PreHP = Boss_CurrentHP;

	RandVector_Num = 0;
	Pre_RandVector_Num = 0;
	Movement_Speed = 0.0f;
	Movement_Timer = 0;
	Dash_Counter = 0;
	Is_Moving = false;

	Distance_P_To_B = 0.0f;

	Direction_Vector = FVector(0.0f, 0.0f, 0.0f);

	// Test Input
	//InputComponent->BindAction("Test", IE_Pressed, this, &ABoss::Test);
}

ABoss* ABoss::GetInstance()
{
	if (GEngine)
	{
		ABoss* Boss_Instance = NewObject<ABoss>();
			//Cast<ABoss>(GEngine->GameSingleton);
		return Boss_Instance;
	}
	return nullptr;
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Pattern_Timer += DeltaTime;

	if (Boss_CurrentHP <= 2000)
		CurrentPattern = static_cast<int>(Boss_Pattern::PATTERN4);
	else if (Boss_CurrentHP <= 5000)
		CurrentPattern = static_cast<int>(Boss_Pattern::PATTERN3);
	else if (Boss_CurrentHP <= 8000)
		CurrentPattern = static_cast<int>(Boss_Pattern::PATTERN2);
	else
		CurrentPattern = static_cast<int>(Boss_Pattern::PATTERN1);


	switch (CurrentPattern)
	{
	case 1:
	{
		if (Pattern_Timer > 1)
		{
			Pattern_1();
			Pattern_Timer = 0.0;
		}
		Pattern_1_Movement();
		break;
	}
	case 2:
		if (Pattern_Timer > 1)
		{
			Pattern_2();
			Pattern_Timer = 0.0;
		}
		Pattern_2_Movement();
		break;

	case 3:
		if (Pattern_Timer > 1)
		{
			Pattern_3();
			Pattern_Timer = 0.0;
		}
		Pattern_3_Movement();
		break;

	case 4:
		if (Pattern_Timer > 1)
		{
			Pattern_4();
			Pattern_Timer = 0.0;
		}
		Pattern_4_Movement();
		break;
	}


}

int ABoss::GetBossMaxHp()
{
	return Boss_MaxHP;
}

int ABoss::GetBossCurrentHp()
{
	return Boss_CurrentHP;
}

void ABoss::SetBossCurrentHp(int hp)
{
	Boss_CurrentHP = hp;
}

void ABoss::Pattern_1()
{
	//UE_LOG(LogTemp, Warning, TEXT("Boss Pattern_1 start"));
	FActorSpawnParameters SpawnParams;


	if (Pattern_1_Projectile)
	{
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(Offset);

		UWorld* World = GetWorld();
		if (World)
		{
			AProjectile* Projectile[PATTERN_1_PROJECTILE_NUM * PATTERN_1_PROJECTILE_NUM];
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			for (int i = 0; i < PATTERN_1_PROJECTILE_NUM; i++)
			{
				for (int j = 0; j < PATTERN_1_PROJECTILE_NUM; j++)
				{
					if (!(i == 0 && (j == 0 || j == 7)))
					{
						Projectile[i * 8 + j] = World->SpawnActor<AProjectile>(
							Pattern_1_Projectile, 
							MuzzleLocation, 
							GetActorRotation() + FRotator(45.0f * i, 360.0f / PATTERN_1_PROJECTILE_NUM * j, 0.0f), 
							SpawnParams);
						if (Projectile[i * 8 + j])
						{
							FVector LaunchDirection = Projectile[i * PATTERN_1_PROJECTILE_NUM + j]->GetActorRotation().Vector();
							Projectile[i * PATTERN_1_PROJECTILE_NUM + j]->FireInDirection(LaunchDirection);
						}
					}
				}
			}
			
		} // if (World)
	}

	//UE_LOG(LogTemp, Warning, TEXT("Pawns location %f, %f, %f"), Player_Pawn->GetActorLocation().X, Player_Pawn->GetActorLocation().Y, Player_Pawn->GetActorLocation().Z);

}

void ABoss::Pattern_2()
{
	//UE_LOG(LogTemp, Warning, TEXT("Boss Pattern_2 start"));
	FActorSpawnParameters SpawnParams;


	// Rain Pattern
	if (Pattern_2_Rain_Projectile)
	{
		//FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(Offset);

		UWorld* World = GetWorld();
		if (World)
		{
			AProjectile* Rain_Projectile[PATTERN_2_RAIN_PROJECTILE_NUM];
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			

			for (int i = 0; i < PATTERN_2_RAIN_PROJECTILE_NUM; i++)
			{	
				int Rain_x = FMath::RandRange(-20000, 20000);
				int Rain_y = FMath::RandRange(-20000, 20000);
				Rain_Projectile[i] = World->SpawnActor<AProjectile>(
					Pattern_2_Rain_Projectile, 
					FVector(Rain_x, Rain_y, PATTERN_2_RAIN_SPAWN_HEIGHT),
					GetActorRotation() + FRotator(-90.0f, 0.0f, 0.0f), 
					SpawnParams);
				if (Rain_Projectile[i])
				{
					FVector LaunchDirection = Rain_Projectile[i]->GetActorRotation().Vector();
					Rain_Projectile[i]->FireInDirection(LaunchDirection);
				}
			}

		} // if (World)

		UE_LOG(LogTemp, Warning, TEXT("Boss Rain Projectile fire"));
	}

	
	// Windmill Pattern
	if (Pattern_2_Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boss Pattern_2 Windmill start"));
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(Offset);

		UWorld* World = GetWorld();
		if (World)
		{
			AProjectile* Projectile[PATTERN_2_WINDMILL_LAYER * PATTERN_2_WINDMILL_PROJECTILE_NUM];
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			for (int n = 0; n < PATTERN_2_WINDMILL_LAYER; n++)
			{
				for (int i = 0; i < PATTERN_2_WINDMILL_PROJECTILE_NUM; i++)
				{
					Projectile[i] = World->SpawnActor<AProjectile>
						(Pattern_2_Projectile,
							MuzzleLocation + FVector(0.0f, 0.0f, PATTERN_2_WINDMILL_FIRSTLAYER_HEIGHT - ((PATTERN_2_WINDMILL_FIRSTLAYER_HEIGHT / 3) * n)),
							GetActorRotation() + FRotator(
								0.0f,
								360.0f / PATTERN_2_WINDMILL_PROJECTILE_NUM * i + Pattern_2_Windmill_Rotation,
								0.0f),
							SpawnParams);
					if (Projectile[i])
					{
						FVector LaunchDirection = Projectile[i]->GetActorRotation().Vector();
						Projectile[i]->FireInDirection(LaunchDirection);
					}
				}
			}
			

		} // if (World)

		Pattern_2_Windmill_Rotation += 10;
	}
}

void ABoss::Pattern_3()
{
	//UE_LOG(LogTemp, Warning, TEXT("Boss Pattern_3 start"));
	FActorSpawnParameters SpawnParams;

	
	if (Pattern_3_Projectile)
	{
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(Offset);

		UWorld* World = GetWorld();
		if (World)
		{
			AProjectile* Projectile[PATTERN_3_PROJECTILE_NUM];
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			for (int i = 0; i < PATTERN_3_PROJECTILE_NUM; i++)
			{
				float R_x = FMath::RandRange(0, 360);
				float R_y = FMath::RandRange(0, 360);
				float R_z = FMath::RandRange(0, 360);
				Projectile[i] = World->SpawnActor<AProjectile>(
					Pattern_3_Projectile,
					MuzzleLocation,
					GetActorRotation() + FRotator(R_x, R_y, R_z),
					SpawnParams);
				if (Projectile[i])
				{
					FVector LaunchDirection = Projectile[i]->GetActorRotation().Vector();
					Projectile[i]->FireInDirection(LaunchDirection);
				}
			}

		} // if (World)
	}
}

void ABoss::Pattern_4()
{
	//UE_LOG(LogTemp, Warning, TEXT("Boss Pattern_4 start"));
	FActorSpawnParameters SpawnParams;


	if (Pattern_4_First_Projectile)
	{
		FVector MuzzleLocation = GetActorLocation() + FTransform(GetActorRotation()).TransformVector(Offset);

		UWorld* World = GetWorld();
		if (World)
		{
			AProjectile* First_Projectile[PATTERN_4_PROJECTILE_NUM];
			AProjectile* Second_Projectile[PATTERN_4_PROJECTILE_NUM];
			AProjectile* Third_Projectile[PATTERN_4_PROJECTILE_NUM];
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			for (int i = 0; i < PATTERN_4_PROJECTILE_NUM; i++)
			{
				First_Projectile[i] = World->SpawnActor<AProjectile>(
					Pattern_4_First_Projectile,
					MuzzleLocation,
					GetActorRotation() + FRotator(0.0f, 360.0f / PATTERN_4_PROJECTILE_NUM * i + Pattern_4_Windmill_Rotation, 0.0f),
					SpawnParams);
				if (First_Projectile[i])
				{
					Pattern_4_First_Projectile_Vector.push_back(First_Projectile[i]);
					FVector LaunchDirection = First_Projectile[i]->GetActorRotation().Vector();
					First_Projectile[i]->FireInDirection(LaunchDirection);
				}
			}

			//** Second Projectile **//
			for (int j = 0; j < Pattern_4_First_Projectile_Vector.size() / PATTERN_4_PROJECTILE_NUM; j++)
			{
				for (int i = 0; i < PATTERN_4_PROJECTILE_NUM; i++)
				{
					Second_Projectile[i] = World->SpawnActor<AProjectile>(
					Pattern_4_Second_Projectile,
					Pattern_4_First_Projectile_Vector.at(j * 4 + i)->GetActorLocation(),
					GetActorRotation() + FRotator(0.0f, 360.0f / PATTERN_4_PROJECTILE_NUM * i - Pattern_4_Windmill_Rotation, 0.0f),
					SpawnParams);

					if (Second_Projectile[i])
					{
						Pattern_4_Second_Projectile_Vector.push_back(Second_Projectile[i]);
						FVector LaunchDirection = FVector(0.0f, 0.0f, 1.0f);
						if(i % 2)
							LaunchDirection = FVector(0.0f, 0.0f, -1.0f);
						Second_Projectile[i]->FireInDirection(LaunchDirection);
					}
				}
			}

			//** Third Projectile **//
			for (int j = 0; j < Pattern_4_Second_Projectile_Vector.size() / PATTERN_4_PROJECTILE_NUM; j++)
			{
				for (int i = 0; i < PATTERN_4_PROJECTILE_NUM; i++)
				{
					Third_Projectile[i] = World->SpawnActor<AProjectile>(
						Pattern_4_Third_Projectile,
						Pattern_4_Second_Projectile_Vector.at(j * 4 + i)->GetActorLocation(),
						GetActorRotation() + FRotator(0.0f, 360.0f / PATTERN_4_PROJECTILE_NUM * i - Pattern_4_Windmill_Rotation, 0.0f),
						SpawnParams);

					if (Third_Projectile[i])
					{
						Pattern_4_Third_Projectile_Vector.push_back(Third_Projectile[i]);
						FVector LaunchDirection = FVector(0.0f, 1.0f, 0.0f);
						if (i % 2)
							LaunchDirection = FVector(0.0f, -1.0f, 0.0f);
						Third_Projectile[i]->FireInDirection(LaunchDirection);
					}
				}
			}
		} // if (World)

		Pattern_4_Windmill_Rotation += 10;
	}
}

void ABoss::Pattern_1_Movement()
{
	if (Boss_CurrentHP != Boss_PreHP)
	{
		PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		Direction_Vector = GetActorLocation() - PlayerLocation;

		Movement_Timer++;

		Body->AddWorldOffset(Direction_Vector * PATTERN_1_MOVEMENT_SPEED / Direction_Vector.Size());

		if (PATTERN_1_MOVEMENT_TIME < Movement_Timer)
		{
			Movement_Timer = 0;
			Boss_PreHP = Boss_CurrentHP;
		}
	}
}

void ABoss::Pattern_2_Movement()
{
	// 멈춰있는 시간
	if (Dash_Counter == 4)
	{
		Is_Moving = false;

		Movement_Timer++;
		if (Movement_Timer > PATTERN_2_MOVEMENT_BREAKTIME)
		{
			Movement_Timer = 0;
			Dash_Counter = 0;
		}
	}
	// 움직이는 시간
	else
	{
		Is_Moving = true;
		// 방향 설정
		if (Movement_Timer == 0)
		{
			while (Pre_RandVector_Num == RandVector_Num)
				RandVector_Num = FMath::RandRange(0, 26);
			Pre_RandVector_Num = RandVector_Num;
			Dash_Counter++;
			Movement_Timer = 1;
		}
		else
		{
			Movement_Timer++;
			Body->AddWorldOffset(Random_Vector(RandVector_Num) * PATTERN_2_MOVEMENT_SPEED);

			if (PATTERN_2_MOVEMENT_TIME < Movement_Timer)
			{
				Movement_Timer = 0;
			}
		}
	}
}

void ABoss::Pattern_3_Movement()
{
	// 멈춰있는 시간
	if (Movement_Timer < PATTERN_3_MOVEMENT_BREAKTIME)
	{
		if (Is_Moving == true)
		{
			Is_Moving = false;
			SetActorHiddenInGame(false);
			Direction_Vector = FVector(0.0f, 0.0f, 0.0f);
		}
		Movement_Timer++;
	}
	// 움직이는 시간
	else
	{
		if (Direction_Vector == FVector(0.0f, 0.0f, 0.0f))
		{
			SetActorHiddenInGame(true);
			PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

			Direction_Vector = PlayerLocation - GetActorLocation();
			Distance_P_To_B = (GetActorLocation() - PlayerLocation).Size();

			UE_LOG(LogTemp, Warning, TEXT("location %f %f %f"), PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z);
			UE_LOG(LogTemp, Warning, TEXT("distance %f"), Distance_P_To_B);
			UE_LOG(LogTemp, Warning, TEXT("vector %f %f %f"), Direction_Vector.X, Direction_Vector.Y, Direction_Vector.Z);
		}
		
		if (Distance_P_To_B > 3000)
		{
			Distance_P_To_B = (GetActorLocation() - PlayerLocation).Size();

			Body->AddWorldOffset(Direction_Vector * PATTERN_3_MOVEMENT_SPEED / Direction_Vector.Size());
			UE_LOG(LogTemp, Warning, TEXT("distance %f"), Distance_P_To_B);			
		}
		else
		{
			Movement_Timer = 0;
			Is_Moving = true;
		}

	}

}

void ABoss::Pattern_4_Movement()
{
	// 멈춰있는 시간
	if (Dash_Counter == 6)
	{
		Is_Moving = false;

		Movement_Timer++;
		if (Movement_Timer > PATTERN_4_MOVEMENT_BREAKTIME)
		{
			Movement_Timer = 0;
			Dash_Counter = 0;
		}
	}
	// 움직이는 시간
	else
	{
		Is_Moving = true;
		// 방향 설정
		if (Movement_Timer == 0)
		{
			while (Pre_RandVector_Num == RandVector_Num)
				RandVector_Num = FMath::RandRange(0, 26);
			Pre_RandVector_Num = RandVector_Num;
			Dash_Counter++;
			Movement_Timer = 1;
		}
		else
		{
			Movement_Timer++;
			Body->AddWorldOffset(Random_Vector(RandVector_Num) * PATTERN_4_MOVEMENT_SPEED);

			if (PATTERN_4_MOVEMENT_TIME < Movement_Timer)
			{
				Movement_Timer = 0;
			}
		}
	}
}

FVector ABoss::Random_Vector(int random_value)
{
	FVector result;

	switch (random_value)
	{
	case 0:
		result = FVector(-1.0f, 0.0f, 0.0f);
		break;
	case 1:
		result = FVector(1.0f, 0.0f, 0.0f);
		break;
	case 2:
		result = FVector(0.0f, -1.0f, 0.0f);
		break;
	case 3:
		result = FVector(0.0f, 1.0f, 0.0f);
		break;
	case 4:
		result = FVector(0.0f, 0.0f, -1.0f);
		break;
	case 5:
		result = FVector(0.0f, 0.0f, 1.0f);
		break;
	case 6:
		result = FVector(-1.0f, -1.0f, 0.0f);
		break;
	case 7:
		result = FVector(-1.0f, 1.0f, 0.0f);
		break;
	case 8:
		result = FVector(-1.0f, 0.0f, -1.0f);
		break;
	case 9:
		result = FVector(-1.0f, 0.0f, 1.0f);
		break;
	case 10:
		result = FVector(0.0f, -1.0f, -1.0f);
		break;
	case 11:
		result = FVector(0.0f, -1.0f, 1.0f);
		break;
	case 12:
		result = FVector(1.0f, -1.0f, 0.0f);
		break;
	case 13:
		result = FVector(1.0f, 1.0f, 0.0f);
		break;
	case 14:
		result = FVector(1.0f, 0.0f, -1.0f);
		break;
	case 15:
		result = FVector(1.0f, 0.0f, 1.0f);
		break;
	case 16:
		result = FVector(0.0f, 1.0f, -1.0f);
		break;
	case 17:
		result = FVector(0.0f, 1.0f, 1.0f);
		break;
	case 18:
		result = FVector(1.0f, 1.0f, 1.0f);
		break;
	case 19:
		result = FVector(-1.0f, 1.0f, 1.0f);
		break;
	case 20:
		result = FVector(1.0f, -1.0f, 1.0f);
		break;
	case 21:
		result = FVector(1.0f, 1.0f, -1.0f);
		break;
	case 22:
		result = FVector(-1.0f, -1.0f, 1.0f);
		break;
	case 23:
		result = FVector(1.0f, -1.0f, -1.0f);
		break;
	case 24:
		result = FVector(-1.0f, 1.0f, -1.0f);
		break;
	case 25:
		result = FVector(-1.0f, -1.0f, -1.0f);
		break;
	}

	return result;
}

void ABoss::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("Boss Current Hp: %d\n"), Boss_CurrentHP);
}