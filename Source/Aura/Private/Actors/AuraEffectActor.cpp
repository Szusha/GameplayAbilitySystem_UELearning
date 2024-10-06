// Coryright Szusha


#include "Actors/AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	

}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply a gameplay effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAuraAttributeSet* AttributeSet = Cast<UAuraAttributeSet>(ASInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));

		UAuraAttributeSet* MutableAttributeSet = const_cast<UAuraAttributeSet*>(AttributeSet);
		MutableAttributeSet->SetHealth(AttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
	

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
	
}


