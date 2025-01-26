// Copyright Szusha


#include "AbilitySystem/Data/AbilityInfo.h"
#include "Aura/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound)
{
	for (const FAuraAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
		
		if (bLogNotFound)
		{
			UE_LOG(LogAura, Error, TEXT("Can't find Info for AbilityTag [%s] on AbilityInformation [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
		}
	}
	
	return FAuraAbilityInfo();
}
