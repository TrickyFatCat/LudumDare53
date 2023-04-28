// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#include "StetingsMenu/SettingsMenuWidget.h"

#include "ButtonWidget.h"
#include "GameFramework/GameUserSettings.h"


void USettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Quality_Low->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyQuality);
	Button_Quality_Medium->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyQuality);
	Button_Quality_High->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyQuality);

	const UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	const int32 QualityIndex = UserSettings->GetOverallScalabilityLevel();

	switch (QualityIndex)
	{
	case 0:
		Button_Quality_Low->SetIsEnabled(false);
		CurrentQualityButton = Button_Quality_Low;
		break;

	case 1:
		Button_Quality_Medium->SetIsEnabled(false);
		CurrentQualityButton = Button_Quality_Medium;
		break;

	case 2:
		Button_Quality_High->SetIsEnabled(false);
		CurrentQualityButton = Button_Quality_High;
		break;

	default:
		Button_Quality_High->SetIsEnabled(false);
		CurrentQualityButton = Button_Quality_High;
		SetQualitySettings(2);
		break;
	}

	Button_ScreenMode_Window->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyScreenMode);
	Button_ScreenMode_Full->OnButtonClicked.AddDynamic(this, &USettingsMenuWidget::ApplyScreenMode);

	const EWindowMode::Type WindowMode = UserSettings->GetDefaultWindowMode();
	
	switch (WindowMode)
	{
	case EWindowMode::Fullscreen:
	case EWindowMode::WindowedFullscreen:
		Button_ScreenMode_Full->SetIsEnabled(false);
		CurrentScreenModeButton = Button_ScreenMode_Full;
		SetScreenMode(EWindowMode::Fullscreen);
		break;

	case EWindowMode::Windowed:
		Button_ScreenMode_Window->SetIsEnabled(false);
		CurrentScreenModeButton = Button_ScreenMode_Window;
		break;
	}
}

void USettingsMenuWidget::SetQualitySettings(const int32 QualityIndex)
{
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	UserSettings->SetShadowQuality(QualityIndex);
	UserSettings->SetAntiAliasingQuality(QualityIndex);
	UserSettings->SetViewDistanceQuality(QualityIndex);
	UserSettings->SetTextureQuality(QualityIndex);
	UserSettings->SetViewDistanceQuality(QualityIndex);
	UserSettings->SetShadingQuality(QualityIndex);
	UserSettings->SetFoliageQuality(QualityIndex);

	switch (QualityIndex)
	{
	case 0:
		UserSettings->SetResolutionScaleNormalized(0.5f);
		break;

	case 1:
		UserSettings->SetResolutionScaleNormalized(0.75f);
		break;

	case 2:
		UserSettings->SetResolutionScaleNormalized(1.0f);
		break;
	}

	UserSettings->ApplySettings(false);
}

void USettingsMenuWidget::SetScreenMode(EWindowMode::Type ScreenMode)
{
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	UserSettings->SetFullscreenMode(ScreenMode);
	
	FIntPoint DesktopResolution = UserSettings->GetDesktopResolution();

	if (ScreenMode == EWindowMode::Windowed)
	{
		DesktopResolution.X *= 0.75;
		DesktopResolution.Y *= 0.75;
	}
	
	UserSettings->SetScreenResolution(DesktopResolution);
	UserSettings->ApplySettings(false);
	UserSettings->ApplyResolutionSettings(false);
}

void USettingsMenuWidget::ApplyQuality(UButtonWidget* ButtonWidget)
{
	if (!ButtonWidget)
	{
		return;
	}

	int32 QualityIndex = 0;

	if (ButtonWidget == Button_Quality_Low)
	{
		QualityIndex = 0;
	}
	else if (ButtonWidget == Button_Quality_Medium)
	{
		QualityIndex = 1;
	}
	else if (ButtonWidget == Button_Quality_High)
	{
		QualityIndex = 2;
	}

	SetQualitySettings(QualityIndex);
	ButtonWidget->SetIsEnabled(false);
	CurrentQualityButton->SetIsEnabled(true);
	CurrentQualityButton = ButtonWidget;
}

void USettingsMenuWidget::ApplyScreenMode(UButtonWidget* ButtonWidget)
{
	if (!ButtonWidget)
	{
		return;
	}

	EWindowMode::Type WindowMode = EWindowMode::Fullscreen;

	if (ButtonWidget == Button_ScreenMode_Window)
	{
		WindowMode = EWindowMode::Windowed;
	}

	SetScreenMode(WindowMode);
	ButtonWidget->SetIsEnabled(false);
	CurrentScreenModeButton->SetIsEnabled(true);
	CurrentScreenModeButton = ButtonWidget;
}
