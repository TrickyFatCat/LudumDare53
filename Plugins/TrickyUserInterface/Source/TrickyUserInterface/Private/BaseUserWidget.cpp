// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "BaseUserWidget.h"

#include "Animation/WidgetAnimation.h"

void UBaseUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBaseUserWidget::Show()
{
	const float StartTime = CalculateStartTime(HideAnimation, ShowAnimation);
	PlayAnimation(ShowAnimation, StartTime);
}

void UBaseUserWidget::Hide()
{
	const float StartTime = CalculateStartTime(ShowAnimation, HideAnimation);
	PlayAnimation(HideAnimation, StartTime);
}

FString UBaseUserWidget::ConvertTimeSeconds(const float TimeSeconds, const ETimeFormat TimeFormat)
{
	const FTimespan Timespan = UKismetMathLibrary::FromSeconds(TimeSeconds);

	FString Result = "";

	const int32 TotalMinutes = static_cast<int32>(Timespan.GetTotalMinutes());
	const int32 Seconds = FMath::CeilToInt(Timespan.GetSeconds());
	const int32 TotalSeconds = (FMath::CeilToInt(Timespan.GetTotalSeconds()));
	const int32 Milliseconds = Timespan.GetFractionMilli();

	auto ConvertMilliseconds = [&Milliseconds](const float Fraction) -> int32
	{
		return static_cast<int32>(Milliseconds * Fraction);
	};

	switch (TimeFormat)
	{
	case ETimeFormat::MM_SS_MsMs:
		Result = FString::Printf(TEXT("%02d:%02d.%02d"),
		                         TotalMinutes,
		                         Seconds,
		                         ConvertMilliseconds(0.1f));
		break;

	case ETimeFormat::MM_SS_Ms:
		Result = FString::Printf(TEXT("%02d:%02d.%d"),
		                         TotalMinutes,
		                         Seconds,
		                         ConvertMilliseconds(0.01f));
		break;

	case ETimeFormat::MM_SS:
		Result = FString::Printf(TEXT("%02d:%02d"), TotalMinutes, Seconds);
		break;

	case ETimeFormat::SS_MsMs:
		Result = FString::Printf(TEXT("%02d.%02d"), TotalSeconds, ConvertMilliseconds(0.1f));
		break;

	case ETimeFormat::SS_Ms:
		Result = FString::Printf(TEXT("%02d.%d"), TotalSeconds, ConvertMilliseconds(0.01f));
		break;

	case ETimeFormat::SS:
		Result = FString::Printf(TEXT("%02d"), TotalSeconds);
		break;
	}

	return Result;
}

void UBaseUserWidget::OnAnimationStarted_Implementation(const UWidgetAnimation* Animation)
{
	SetVisibility(ESlateVisibility::Visible);
}

void UBaseUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation == ShowAnimation)
	{
		SetVisibility(ESlateVisibility::Visible); // In case, of rapid change of the state.
		OnShowed.Broadcast();
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
		OnHidden.Broadcast();
	}
}

float UBaseUserWidget::CalculateStartTime(const UWidgetAnimation* CurrentAnimation,
                                          const UWidgetAnimation* NewAnimation) const
{
	if (!CurrentAnimation || !NewAnimation)
	{
		return -1.f;
	}

	const float AnimationEndTime = CurrentAnimation->GetEndTime();
	const float TargetTime = ((AnimationEndTime - GetAnimationCurrentTime(CurrentAnimation)) / AnimationEndTime) *
		NewAnimation->GetEndTime();
	return TargetTime * static_cast<float>(IsAnimationPlaying(CurrentAnimation));
}
