// Copyright Szusha


#include "AbilitySystem/Abilities/AuraFirebolt.h"
#include "AuraGameplayTags.h"

FString UAuraFirebolt::GetDescription(int32 Level)
{

	const int32 Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
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
			Level, Manacost, Cooldown, Damage);
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
			Level, Manacost, Cooldown, FMath::Min(Level, NumProjectiles), Damage);
	}
}

FString UAuraFirebolt::GetNextLevelDescription(int32 NextLevel)
{
	const int32 Damage = GetDamageByDamageType(NextLevel, FAuraGameplayTags::Get().Damage_Fire);
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
		NextLevel, Manacost, Cooldown, FMath::Min(NextLevel, NumProjectiles), Damage);
	
}