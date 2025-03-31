#pragma once

#include "InventoryStructs.generated.h"

USTRUCT(BlueprintType)
struct FInventoryStruct
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Size", meta=(ClampMin="1"))
	int Size = 1;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Size", meta=(ClampMin="1"))
	int Length = 1;;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Size", meta=(ClampMin="1"))
	int Height = 1;;
	
};
