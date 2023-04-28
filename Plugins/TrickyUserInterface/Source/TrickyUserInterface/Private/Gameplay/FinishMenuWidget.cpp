// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "Gameplay/FinishMenuWidget.h"

#include "ButtonWidget.h"
#include "TransitionScreenWidget.h"
#include "Kismet/GameplayStatics.h"

void UFinishMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto BindButtonEvent = [&](UButtonWidget* ButtonWidget)
	{
		ButtonWidget->OnButtonClicked.AddDynamic(this, &UFinishMenuWidget::OnButtonClicked);
	};

	BindButtonEvent(ToRawPtr(Button_Continue));
	BindButtonEvent(ToRawPtr(Button_Restart));
	BindButtonEvent(ToRawPtr(Button_Quit));
	Widget_TransitionScreen->OnHidden.AddDynamic(this, &UFinishMenuWidget::OnTransitionScreenShowed);
}

void UFinishMenuWidget::OnButtonClicked_Implementation(UButtonWidget* Button)
{
	ClickedButton = Button;
	Widget_TransitionScreen->Show();
}

void UFinishMenuWidget::Continue_Implementation()
{
	const FName CurrentLevelName = FName(UGameplayStatics::GetCurrentLevelName(this));
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

void UFinishMenuWidget::Restart_Implementation()
{
	const FName CurrentLevelName = FName(UGameplayStatics::GetCurrentLevelName(this));
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

void UFinishMenuWidget::Quit_Implementation()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UFinishMenuWidget::OnTransitionScreenShowed_Implementation()
{
	if (ClickedButton == Button_Continue)
	{
		Continue();
	}
	else if (ClickedButton == Button_Restart)
	{
		Restart();
	}
	else if (ClickedButton == Button_Quit)
	{
		Quit();
	}
}
