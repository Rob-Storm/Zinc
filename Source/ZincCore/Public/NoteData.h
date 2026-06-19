#pragma once

#include "CoreMinimal.h"
#include "ReadableData.h"

#include "NoteData.generated.h"

UENUM(BlueprintType)
enum ENoteStyle
{
	Handwritten,
	Cursive,
	Computer,
	Typewriter
};

UCLASS(Blueprintable, BlueprintType)
class UNoteData : public UReadableData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NoteData")
	TEnumAsByte<ENoteStyle> NoteStyle;

	/** The text that will be shown in game */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NoteData", meta = (MultiLine="true"))
	FText Contents;

	/** Overrides the default texture used in the Note UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NoteData")
	TObjectPtr<UTexture2D> TextureOverride;
	
};
