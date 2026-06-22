#include "SlateLibrary.h"
#include "Widgets/SWindow.h"

void USlateLibrary::ShowSlate()
{
	TSharedRef<SVerticalBox> MySlate = SNew(SVerticalBox)
	+ SVerticalBox::Slot()
	[
		SNew(SImage)
	]
	+ SVerticalBox::Slot()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Hello"))
		.ColorAndOpacity(FSlateColor(FLinearColor::Yellow))
	]
	+ SVerticalBox::Slot()
	[
		SNew(SButton)
		.OnClicked_Static(&USlateLibrary::OnMyButtonClick)
		[
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Button"))
			]
		]
	];

	TSharedRef<SWindow> Window = SNew(SWindow)
	.AutoCenter(EAutoCenter::None)
	.Title(FText::FromString(TEXT("Window")))
	.IsInitiallyMaximized(false)
	.SizingRule(ESizingRule::Autosized)
	.SupportsMaximize(false)
	.SupportsMinimize(true);

	Window->SetContent(MySlate);
	FSlateApplication::Get().AddWindow(Window);
}

FReply USlateLibrary::OnMyButtonClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Clicked"));
	return FReply::Handled();
}