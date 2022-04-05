// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include "rune.h"
#include "state.h"

int startHealth = 0;
int maxHealth = 0;
int startPArmor = 0;
int maxPArmor = 0;
int startSArmor = 0;
int maxSArmor = 0;
int startPAttack = 0;
int maxPAttack = 0;
int startSAttack = 0;
int maxSAttack = 0;
int startSpeed = 0;
int maxSpeed = 0;
int startEvasion = 0;
int maxEvasion = 0;

int remainingPoints = 5;
int rune0Min = 0;
int rune1Min = 0;
int rune2Min = 0;
int rune3Min = 0;
int rune4Min = 0;
int rune5Min = 0;
int rune0Max = 100;
int rune1Max = 100;
int rune2Max = 100;
int rune3Max = 100;
int rune4Max = 100;
int rune5Max = 100;

void Menu::LevelUpMenuComponent::RoomLoad(Context& ctx) {
	remainingPoints = 5;
	startHealth = ctx.GameState->CurrentRun.PlayerCharacter.Health;
	startPArmor = ctx.GameState->CurrentRun.PlayerCharacter.PhysicalArmor;
	startSArmor = ctx.GameState->CurrentRun.PlayerCharacter.SpecialArmor;
	startPAttack = ctx.GameState->CurrentRun.PlayerCharacter.PhysicalAttack;
	startSAttack = ctx.GameState->CurrentRun.PlayerCharacter.SpecialAttack;
	startSpeed = ctx.GameState->CurrentRun.PlayerCharacter.Speed;
	startEvasion = ctx.GameState->CurrentRun.PlayerCharacter.Evasion;
	rune0Min = ctx.GameState->CurrentRun.PlayerCharacter.Runes[0].AdditionalLevel;
	rune1Min = ctx.GameState->CurrentRun.PlayerCharacter.Runes[1].AdditionalLevel;
	rune2Min = ctx.GameState->CurrentRun.PlayerCharacter.Runes[2].AdditionalLevel;
	rune3Min = ctx.GameState->CurrentRun.PlayerCharacter.Runes[3].AdditionalLevel;
	rune4Min = ctx.GameState->CurrentRun.PlayerCharacter.Runes[4].AdditionalLevel;
	rune5Min = ctx.GameState->CurrentRun.PlayerCharacter.Runes[5].AdditionalLevel;
}

void Menu::LevelUpMenuComponent::Update(Context& ctx) {
	Component::Update(ctx);
	auto ProgressLabel = (Label*)(this->Child(0)->Child(0));
	auto ElapsedLabel = (Label*)(this->Child(0)->Child(2));
	auto PointsRemainingLabel = (Label*)(this->Child(1));
	ProgressLabel->SetText(ctx, TextFormat("Progress: %s", ctx.GameState->CurrentRun.ProgressTimeString().c_str()));
	ElapsedLabel->SetText(ctx, TextFormat("Current: %s", ctx.GameState->CurrentRun.ElapsedTimeString().c_str()));
	PointsRemainingLabel->SetText(ctx, TextFormat("Points Remaining: %i/5", remainingPoints));

	remainingPoints = 5;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.Health - startHealth;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.PhysicalArmor - startPArmor;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.SpecialArmor - startSArmor;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.PhysicalAttack - startPAttack;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.SpecialAttack - startSAttack;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.Speed - startSpeed;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.Evasion - startEvasion;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.Runes[0].AdditionalLevel - rune0Min;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.Runes[1].AdditionalLevel - rune1Min;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.Runes[2].AdditionalLevel - rune2Min;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.Runes[3].AdditionalLevel - rune3Min;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.Runes[4].AdditionalLevel - rune4Min;
	remainingPoints -= ctx.GameState->CurrentRun.PlayerCharacter.Runes[5].AdditionalLevel - rune5Min;

	maxHealth = ctx.GameState->CurrentRun.PlayerCharacter.Health + remainingPoints;
	maxPArmor = ctx.GameState->CurrentRun.PlayerCharacter.PhysicalArmor + remainingPoints;
	maxSArmor = ctx.GameState->CurrentRun.PlayerCharacter.SpecialArmor + remainingPoints;
	maxPAttack = ctx.GameState->CurrentRun.PlayerCharacter.PhysicalAttack + remainingPoints;
	maxSAttack = ctx.GameState->CurrentRun.PlayerCharacter.SpecialAttack + remainingPoints;
	maxSpeed = ctx.GameState->CurrentRun.PlayerCharacter.Speed + remainingPoints;
	maxEvasion = ctx.GameState->CurrentRun.PlayerCharacter.Evasion + remainingPoints;
	rune0Max = ctx.GameState->CurrentRun.PlayerCharacter.Runes[0].AdditionalLevel + remainingPoints;
	rune1Max = ctx.GameState->CurrentRun.PlayerCharacter.Runes[1].AdditionalLevel + remainingPoints;
	rune2Max = ctx.GameState->CurrentRun.PlayerCharacter.Runes[2].AdditionalLevel + remainingPoints;
	rune3Max = ctx.GameState->CurrentRun.PlayerCharacter.Runes[3].AdditionalLevel + remainingPoints;
	rune4Max = ctx.GameState->CurrentRun.PlayerCharacter.Runes[4].AdditionalLevel + remainingPoints;
	rune5Max = ctx.GameState->CurrentRun.PlayerCharacter.Runes[5].AdditionalLevel + remainingPoints;
}

void confirmClicked(Context& ctx, Component& component) {
	if (remainingPoints == 0) {
		ctx.GameState->NextRoom();
	}
}

Component* Menu::CreateLevelUpMenu(Context& ctx) {
	auto panel = new LevelUpMenuComponent(ctx, {.WidthScale = 1, .HeightScale = 1});
	auto timeRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .05});
	auto pointsRemainingRow = new Label(ctx, "Points Remaining: 2/5", {.WidthScale = .2, .HeightScale = .05, .DefaultColor = WHITE});
	auto statsRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .85});
	auto confirmRow = (new Button(ctx, {.WidthScale = .2, .HeightScale = .05, .DefaultColor = ctx.Colors.Button, .HoverColor = ctx.Colors.ButtonHover, .OnClick = confirmClicked}))->
		AddChild(new Label(ctx, "Confirm", {.WidthScale = 7, .HeightScale = .7, .DefaultColor = WHITE}));
	*panel += timeRow;
	*panel += pointsRemainingRow;
	*panel += statsRow;
	*panel += confirmRow;

	// Time Row
	*timeRow += new Label(ctx, "Progress: 10m 45.32s", {.WidthScale = .2, .HeightScale = .98, .DefaultColor = WHITE});
	*timeRow += new HorizontalPanel(ctx, {.WidthScale = .55, .HeightScale = 1});
	*timeRow += new Label(ctx, "Current: 11m 17.43s", {.WidthScale = .2, .HeightScale = .98, .DefaultColor = WHITE});

	// Stats Column
	auto statPanel = new VerticalPanel(ctx, {.WidthScale = .5, .HeightScale = 1});
	*statsRow += statPanel;

	auto statPanelOptions = Component::Options{.WidthScale = 1, .HeightScale = .0727};
	auto statLabelOptions = Component::Options{.WidthScale = .4, .HeightScale = .6, .DefaultColor = WHITE};
	auto statSpriteOptions = Component::Options{.WidthScale = .2, .HeightScale = 1};
	auto statInputStepperOptions = Component::Options{.WidthScale = .25, .HeightScale = .7, .DefaultColor = ctx.Colors.InputStepper, .HoverColor = ctx.Colors.InputStepperHover};

	auto healthStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += healthStat;
	*healthStat += new Label(ctx, "Health", statLabelOptions);
	*healthStat += new Sprite(ctx, SpriteName::Health, statSpriteOptions);
	*healthStat += new InputStepper(ctx, statInputStepperOptions, &startHealth, &maxHealth, &ctx.GameState->CurrentRun.PlayerCharacter.Health);
	auto physicalArmorStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += physicalArmorStat;
	*physicalArmorStat += new Label(ctx, "Physical Armor", statLabelOptions);
	*physicalArmorStat += new Sprite(ctx, SpriteName::PhysicalArmor, statSpriteOptions);
	*physicalArmorStat += new InputStepper(ctx, statInputStepperOptions, &startPArmor, &maxPArmor, &ctx.GameState->CurrentRun.PlayerCharacter.PhysicalArmor);
	auto specialArmorStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += specialArmorStat;
	*specialArmorStat += new Label(ctx, "Special Armor", statLabelOptions);
	*specialArmorStat += new Sprite(ctx, SpriteName::SpecialArmor, statSpriteOptions);
	*specialArmorStat += new InputStepper(ctx, statInputStepperOptions, &startSArmor, &maxSArmor, &ctx.GameState->CurrentRun.PlayerCharacter.SpecialArmor);
	auto physicalAttackStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += physicalAttackStat;
	*physicalAttackStat += new Label(ctx, "Physical Attack", statLabelOptions);
	*physicalAttackStat += new Sprite(ctx, SpriteName::PhysicalAttack, statSpriteOptions);
	*physicalAttackStat += new InputStepper(ctx, statInputStepperOptions, &startPAttack, &maxPAttack, &ctx.GameState->CurrentRun.PlayerCharacter.PhysicalAttack);
	auto specialAttackStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += specialAttackStat;
	*specialAttackStat += new Label(ctx, "Special Attack", statLabelOptions);
	*specialAttackStat += new Sprite(ctx, SpriteName::SpecialAttack, statSpriteOptions);
	*specialAttackStat += new InputStepper(ctx, statInputStepperOptions, &startSAttack, &maxSAttack, &ctx.GameState->CurrentRun.PlayerCharacter.SpecialAttack);
	auto speedStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += speedStat;
	*speedStat += new Label(ctx, "Speed", statLabelOptions);
	*speedStat += new Sprite(ctx, SpriteName::Speed, statSpriteOptions);
	*speedStat += new InputStepper(ctx, statInputStepperOptions, &startSpeed, &maxSpeed, &ctx.GameState->CurrentRun.PlayerCharacter.Speed);
	auto evasionStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += evasionStat;
	*evasionStat += new Label(ctx, "Evasion", statLabelOptions);
	*evasionStat += new Sprite(ctx, SpriteName::Evasion, statSpriteOptions);
	*evasionStat += new InputStepper(ctx, statInputStepperOptions, &startEvasion, &maxEvasion, &ctx.GameState->CurrentRun.PlayerCharacter.Evasion);
	auto fireResStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += fireResStat;
	*fireResStat += new Label(ctx, "Fire Resistance", statLabelOptions);
	*fireResStat += new Sprite(ctx, SpriteName::FireResistance, statSpriteOptions);
	*fireResStat += new Label(ctx, TextFormat("%i%%", (int)(ctx.GameState->CurrentRun.PlayerCharacter.FireResistance(ctx) * 100.0)), statInputStepperOptions.WithHoverColor(Color{}));
	auto waterResStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += waterResStat;
	*waterResStat += new Label(ctx, "Water Resistance", statLabelOptions);
	*waterResStat += new Sprite(ctx, SpriteName::WaterResistance, statSpriteOptions);
	*waterResStat += new Label(ctx, TextFormat("%i%%", (int)(ctx.GameState->CurrentRun.PlayerCharacter.WaterResistance(ctx) * 100.0)), statInputStepperOptions.WithHoverColor(Color{}));
	auto electricResStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += electricResStat;
	*electricResStat += new Label(ctx, "Electric Resistance", statLabelOptions);
	*electricResStat += new Sprite(ctx, SpriteName::ElectricResistance, statSpriteOptions);
	*electricResStat += new Label(ctx, TextFormat("%i%%", (int)(ctx.GameState->CurrentRun.PlayerCharacter.ElectricResistance(ctx) * 100.0)), statInputStepperOptions.WithHoverColor(Color{}));
	auto windResStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += windResStat;
	*windResStat += new Label(ctx, "Wind Resistance", statLabelOptions);
	*windResStat += new Sprite(ctx, SpriteName::WindResistance, statSpriteOptions);
	*windResStat += new Label(ctx, TextFormat("%i%%", (int)(ctx.GameState->CurrentRun.PlayerCharacter.WindResistance(ctx) * 100.0)), statInputStepperOptions.WithHoverColor(Color{}));

	auto runePanel = new VerticalPanel(ctx, {.WidthScale = .5, .HeightScale = 1});
	*statsRow += runePanel;

	auto runeRowOptions = Component::Options{.WidthScale = 1, .HeightScale = .15};
	auto runeSpriteOptions = Component::Options{.WidthScale = .1, .HeightScale = 1};
	auto runeLabelOptions = Component::Options{.WidthScale = .45, .HeightScale = 1};
	auto runeInputStepperOptions = Component::Options{.WidthScale = .35, .HeightScale = .5, .DefaultColor = ctx.Colors.InputStepper, .HoverColor = ctx.Colors.InputStepperHover};

	auto rune1Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune1Row;
	*rune1Row += ctx.GameState->CurrentRun.PlayerCharacter.Runes[0].GetSprite(ctx, runeSpriteOptions);
	*rune1Row += new Label(ctx, ctx.GameState->CurrentRun.PlayerCharacter.Runes[0].Name, runeLabelOptions.WithDefaultColor(ctx.GameState->CurrentRun.PlayerCharacter.Runes[0].GetRarityColor(ctx)));
	*rune1Row += new InputStepper(ctx, runeInputStepperOptions, &rune0Min, &rune0Max, &ctx.GameState->CurrentRun.PlayerCharacter.Runes[0].AdditionalLevel);
	auto rune2Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune2Row;
	*rune2Row += ctx.GameState->CurrentRun.PlayerCharacter.Runes[1].GetSprite(ctx, runeSpriteOptions);
	*rune2Row += new Label(ctx, ctx.GameState->CurrentRun.PlayerCharacter.Runes[1].Name, runeLabelOptions.WithDefaultColor(ctx.GameState->CurrentRun.PlayerCharacter.Runes[1].GetRarityColor(ctx)));
	*rune2Row += new InputStepper(ctx, runeInputStepperOptions, &rune1Min, &rune1Max, &ctx.GameState->CurrentRun.PlayerCharacter.Runes[1].AdditionalLevel);
	auto rune3Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune3Row;
	*rune3Row += ctx.GameState->CurrentRun.PlayerCharacter.Runes[2].GetSprite(ctx, runeSpriteOptions);
	*rune3Row += new Label(ctx, ctx.GameState->CurrentRun.PlayerCharacter.Runes[2].Name, runeLabelOptions.WithDefaultColor(ctx.GameState->CurrentRun.PlayerCharacter.Runes[2].GetRarityColor(ctx)));
	*rune3Row += new InputStepper(ctx, runeInputStepperOptions, &rune2Min, &rune2Max, &ctx.GameState->CurrentRun.PlayerCharacter.Runes[2].AdditionalLevel);
	auto rune4Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune4Row;
	*rune4Row += ctx.GameState->CurrentRun.PlayerCharacter.Runes[3].GetSprite(ctx, runeSpriteOptions);
	*rune4Row += new Label(ctx, ctx.GameState->CurrentRun.PlayerCharacter.Runes[3].Name, runeLabelOptions.WithDefaultColor(ctx.GameState->CurrentRun.PlayerCharacter.Runes[3].GetRarityColor(ctx)));
	*rune4Row += new InputStepper(ctx, runeInputStepperOptions, &rune3Min, &rune3Max, &ctx.GameState->CurrentRun.PlayerCharacter.Runes[3].AdditionalLevel);
	auto rune5Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune5Row;
	*rune5Row += ctx.GameState->CurrentRun.PlayerCharacter.Runes[4].GetSprite(ctx, runeSpriteOptions);
	*rune5Row += new Label(ctx, ctx.GameState->CurrentRun.PlayerCharacter.Runes[4].Name, runeLabelOptions.WithDefaultColor(ctx.GameState->CurrentRun.PlayerCharacter.Runes[4].GetRarityColor(ctx)));
	*rune5Row += new InputStepper(ctx, runeInputStepperOptions, &rune4Min, &rune4Max, &ctx.GameState->CurrentRun.PlayerCharacter.Runes[4].AdditionalLevel);
	auto rune6Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune6Row;
	*rune6Row += ctx.GameState->CurrentRun.PlayerCharacter.Runes[5].GetSprite(ctx, runeSpriteOptions);
	*rune6Row += new Label(ctx, ctx.GameState->CurrentRun.PlayerCharacter.Runes[5].Name, runeLabelOptions.WithDefaultColor(ctx.GameState->CurrentRun.PlayerCharacter.Runes[5].GetRarityColor(ctx)));
	*rune6Row += new InputStepper(ctx, runeInputStepperOptions, &rune5Min, &rune5Max, &ctx.GameState->CurrentRun.PlayerCharacter.Runes[5].AdditionalLevel);

	return panel;
}
