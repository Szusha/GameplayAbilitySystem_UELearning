// Copyright Szusha


#include "AbilitySystem/Abilities/AuraFirebolt.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actors/AuraProjectile.h"

FString UAuraFirebolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float Manacost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Launches a bolt of fire, exploding on impact and dealing </>"
			"<Damage>%d</><Default> fire damage with a chance to burn</>"),

			// Values
			Level, Manacost, Cooldown, ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			//Description
			"<Default>Launches %d bolts of fire, exploding on impact and dealing </>"
			"<Damage>%d</><Default> fire damage with a chance to burn</>"),

			// Values
			Level, Manacost, Cooldown, FMath::Min(Level, NumProjectiles), ScaledDamage);
	}
}

FString UAuraFirebolt::GetNextLevelDescription(int32 NextLevel)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(NextLevel);
	const float Manacost = FMath::Abs(GetManaCost(NextLevel));
	const float Cooldown = GetCooldown(NextLevel);

	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL:</>\n\n"

		// Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		//Description
		"<Default>Launches %d bolts of fire, exploding on impact and dealing </>"
		"<Damage>%d</><Default> fire damage with a chance to burn</>"),

		// Values
		NextLevel, Manacost, Cooldown, FMath::Min(NextLevel, NumProjectiles), ScaledDamage);
	
}

void UAuraFirebolt::SpawnProjectiles(const FVector& TargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (TargetLocation - SocketLocation).Rotation();
	// TODO: Calculate Pitch based on distance
	if (bOverridePitch) Rotation.Pitch = PitchOverride;

	const FVector Forward = Rotation.Vector();

	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);

	for (const FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation + FVector(0,0,-50));
		SpawnTransform.SetRotation(Rot.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		Projectile->FinishSpawning(SpawnTransform);
	}


}
