// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include "rune.h"

int tempMinValue = 0;
int tempMaxValue = 50;
int tempHealth = 20;
int tempPhysicalArmor = 8;
int tempSpecialArmor = 10;
int tempPhysicalAttack = 35;
int tempSpecialAttack = 2;
int tempSpeed = 19;

Rune* tempRune1;
Rune* tempRune2;
Rune* tempRune3;
Rune* tempRune4;
Rune* tempRune5;
Rune* tempRune6;

Component* Menu::CreateLevelUpMenu(Context& ctx) {
	auto panel = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	auto timeRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .05});
	auto pointsRemainingRow = new Label(ctx, "Points Remaining: 2/5", {.WidthScale = .2, .HeightScale = .05, .DefaultColor = WHITE});
	auto statsRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .85});
	auto confirmRow = (new Button(ctx, {.WidthScale = .2, .HeightScale = .05, .DefaultColor = ctx.Colors.Button, .HoverColor = ctx.Colors.ButtonHover}))->
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

	auto statPanelOptions = Component::Options{.WidthScale = 1, .HeightScale = .08};
	auto statLabelOptions = Component::Options{.WidthScale = .4, .HeightScale = .6, .DefaultColor = WHITE};
	auto statSpriteOptions = Component::Options{.WidthScale = .2, .HeightScale = 1};
	auto statInputStepperOptions = Component::Options{.WidthScale = .25, .HeightScale = .7, .DefaultColor = ctx.Colors.InputStepper, .HoverColor = ctx.Colors.InputStepperHover};

	auto healthStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += healthStat;
	*healthStat += new Label(ctx, "Health", statLabelOptions);
	*healthStat += new Sprite(ctx, SpriteName::Health, statSpriteOptions);
	*healthStat += new InputStepper(ctx, statInputStepperOptions, &tempMinValue, &tempMaxValue, &tempHealth);
	auto physicalArmorStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += physicalArmorStat;
	*physicalArmorStat += new Label(ctx, "Physical Armor", statLabelOptions);
	*physicalArmorStat += new Sprite(ctx, SpriteName::PhysicalArmor, statSpriteOptions);
	*physicalArmorStat += new InputStepper(ctx, statInputStepperOptions, &tempMinValue, &tempMaxValue, &tempPhysicalArmor);
	auto specialArmorStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += specialArmorStat;
	*specialArmorStat += new Label(ctx, "Special Armor", statLabelOptions);
	*specialArmorStat += new Sprite(ctx, SpriteName::SpecialArmor, statSpriteOptions);
	*specialArmorStat += new InputStepper(ctx, statInputStepperOptions, &tempMinValue, &tempMaxValue, &tempSpecialArmor);
	auto physicalAttackStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += physicalAttackStat;
	*physicalAttackStat += new Label(ctx, "Physical Attack", statLabelOptions);
	*physicalAttackStat += new Sprite(ctx, SpriteName::PhysicalAttack, statSpriteOptions);
	*physicalAttackStat += new InputStepper(ctx, statInputStepperOptions, &tempMinValue, &tempMaxValue, &tempPhysicalAttack);
	auto specialAttackStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += specialAttackStat;
	*specialAttackStat += new Label(ctx, "Special Attack", statLabelOptions);
	*specialAttackStat += new Sprite(ctx, SpriteName::SpecialAttack, statSpriteOptions);
	*specialAttackStat += new InputStepper(ctx, statInputStepperOptions, &tempMinValue, &tempMaxValue, &tempSpecialAttack);
	auto speedStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += speedStat;
	*speedStat += new Label(ctx, "Speed", statLabelOptions);
	*speedStat += new Sprite(ctx, SpriteName::Speed, statSpriteOptions);
	*speedStat += new InputStepper(ctx, statInputStepperOptions, &tempMinValue, &tempMaxValue, &tempSpeed);
	auto fireResStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += fireResStat;
	*fireResStat += new Label(ctx, "Fire Resistance", statLabelOptions);
	*fireResStat += new Sprite(ctx, SpriteName::FireResistance, statSpriteOptions);
	*fireResStat += new Label(ctx, "0%", statInputStepperOptions);
	auto waterResStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += waterResStat;
	*waterResStat += new Label(ctx, "Water Resistance", statLabelOptions);
	*waterResStat += new Sprite(ctx, SpriteName::WaterResistance, statSpriteOptions);
	*waterResStat += new Label(ctx, "40%", statInputStepperOptions);
	auto electricResStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += electricResStat;
	*electricResStat += new Label(ctx, "Electric Resistance", statLabelOptions);
	*electricResStat += new Sprite(ctx, SpriteName::ElectricResistance, statSpriteOptions);
	*electricResStat += new Label(ctx, "-20%", statInputStepperOptions);
	auto windResStat = new HorizontalPanel(ctx, statPanelOptions);
	*statPanel += windResStat;
	*windResStat += new Label(ctx, "Wind Resistance", statLabelOptions);
	*windResStat += new Sprite(ctx, SpriteName::WindResistance, statSpriteOptions);
	*windResStat += new Label(ctx, "10%", statInputStepperOptions);

	// Runes Column
	tempRune1 = new Rune(ctx);
	tempRune2 = new Rune(ctx);
	tempRune3 = new Rune(ctx);
	tempRune4 = new Rune(ctx);
	tempRune5 = new Rune(ctx);
	tempRune6 = new Rune(ctx);
	auto runePanel = new VerticalPanel(ctx, {.WidthScale = .5, .HeightScale = 1});
	*statsRow += runePanel;

	auto runeRowOptions = Component::Options{.WidthScale = 1, .HeightScale = .15};
	auto runeSpriteOptions = Component::Options{.WidthScale = .1, .HeightScale = 1};
	auto runeLabelOptions = Component::Options{.WidthScale = .45, .HeightScale = 1};
	auto runeInputStepperOptions = Component::Options{.WidthScale = .35, .HeightScale = .5, .DefaultColor = ctx.Colors.InputStepper, .HoverColor = ctx.Colors.InputStepperHover};

	auto rune1Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune1Row;
	*rune1Row += tempRune1->GetSprite(ctx, runeSpriteOptions);
	*rune1Row += new Label(ctx, tempRune1->Name, runeLabelOptions.WithDefaultColor(tempRune1->GetRarityColor(ctx)));
	*rune1Row += new InputStepper(ctx, runeInputStepperOptions, &tempMinValue, &tempMaxValue, &tempRune1->AdditionalLevel);
	auto rune2Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune2Row;
	*rune2Row += tempRune2->GetSprite(ctx, runeSpriteOptions);
	*rune2Row += new Label(ctx, tempRune2->Name, runeLabelOptions.WithDefaultColor(tempRune2->GetRarityColor(ctx)));
	*rune2Row += new InputStepper(ctx, runeInputStepperOptions, &tempMinValue, &tempMaxValue, &tempRune2->AdditionalLevel);
	auto rune3Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune3Row;
	*rune3Row += tempRune3->GetSprite(ctx, runeSpriteOptions);
	*rune3Row += new Label(ctx, tempRune3->Name, runeLabelOptions.WithDefaultColor(tempRune3->GetRarityColor(ctx)));
	*rune3Row += new InputStepper(ctx, runeInputStepperOptions, &tempMinValue, &tempMaxValue, &tempRune3->AdditionalLevel);
	auto rune4Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune4Row;
	*rune4Row += tempRune4->GetSprite(ctx, runeSpriteOptions);
	*rune4Row += new Label(ctx, tempRune4->Name, runeLabelOptions.WithDefaultColor(tempRune4->GetRarityColor(ctx)));
	*rune4Row += new InputStepper(ctx, runeInputStepperOptions, &tempMinValue, &tempMaxValue, &tempRune4->AdditionalLevel);
	auto rune5Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune5Row;
	*rune5Row += tempRune5->GetSprite(ctx, runeSpriteOptions);
	*rune5Row += new Label(ctx, tempRune5->Name, runeLabelOptions.WithDefaultColor(tempRune5->GetRarityColor(ctx)));
	*rune5Row += new InputStepper(ctx, runeInputStepperOptions, &tempMinValue, &tempMaxValue, &tempRune5->AdditionalLevel);
	auto rune6Row = new HorizontalPanel(ctx, runeRowOptions);
	*runePanel += rune6Row;
	*rune6Row += tempRune6->GetSprite(ctx, runeSpriteOptions);
	*rune6Row += new Label(ctx, tempRune6->Name, runeLabelOptions.WithDefaultColor(tempRune6->GetRarityColor(ctx)));
	*rune6Row += new InputStepper(ctx, runeInputStepperOptions, &tempMinValue, &tempMaxValue, &tempRune6->AdditionalLevel);

	return panel;
}
