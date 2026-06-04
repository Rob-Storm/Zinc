#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"

#include "ActorIOInterface.h"

#include "ItemChecker.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHasItemSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoesNotHaveItemSignature);

UCLASS()
class AItemChecker : public AActor, public IActorIOInterface
{
	GENERATED_BODY()

public:

	AItemChecker();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="ItemChecker")
	FOnHasItemSignature OnHasItem;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite, Category="ItemChecker")
	FOnDoesNotHaveItemSignature OnDoesNotHaveItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBillboardComponent> Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemChecker")
	TObjectPtr<class UItemData> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemChecker")
	bool RemoveItemOnCheck = false;

	UFUNCTION(BlueprintCallable, Category="ItemChecker")
	void CheckForItem();

	virtual void RegisterIOEvents(FActorIOEventList& EventRegistry) override;
	virtual void RegisterIOFunctions(FActorIOFunctionList& FunctionRegistry) override;

#if WITH_EDITOR

	virtual bool CanEditChange(const FProperty* InProperty) const override;

#endif
	
};
