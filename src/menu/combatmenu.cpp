// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include "state.h"
#include "rune.h"
#include "enemy.h"
#include "statuseffect.h"

int tempProgressBar = 190;
int tempProgressBarCurrent = 100;

Component* Menu::CreateCombatMenu(Context& ctx) {
	auto panel = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	auto timeRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .05});
	auto enemyRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .39});
	auto healthBar = new ProgressBar(ctx, {.WidthScale = .995, .HeightScale = .033, .DefaultColor = ctx.Colors.HealthBar}, &tempProgressBar, &tempProgressBarCurrent);
	auto experienceBar = new ProgressBar(ctx, {.WidthScale = .995, .HeightScale = .033, .DefaultColor = ctx.Colors.ExperienceBar}, &tempProgressBar, &tempProgressBarCurrent);
	auto runeRow = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .49});
	*panel += timeRow;
	*panel += enemyRow;
	*panel += healthBar;
	*panel += new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .004});;
	*panel += experienceBar;
	*panel += runeRow;

	// Time Row
	*timeRow += new Label(ctx, "Progress: 10m 45.32s", {.WidthScale = .2, .HeightScale = .98, .DefaultColor = WHITE});
	*timeRow += new HorizontalPanel(ctx, {.WidthScale = .55, .HeightScale = 1});
	*timeRow += new Label(ctx, "Current: 11m 17.43s", {.WidthScale = .2, .HeightScale = .98, .DefaultColor = WHITE});

	// Enemy Row
	auto enemy = new Enemy(ctx, 10, false);
	//TODO: insert spaces if there are only one/two/three enemies
	*enemyRow += new VerticalPanel(ctx, {.WidthScale = .3, .HeightScale = 1});
	*enemyRow += enemy->GenerateComponent(ctx, {.WidthScale = .3, .HeightScale = .9, .DefaultColor = ctx.Colors.EnemyBackground});
	*enemyRow += new VerticalPanel(ctx, {.WidthScale = .3, .HeightScale = 1});
	auto statusEffectsColumn = new VerticalPanel(ctx, {.WidthScale = .05, .HeightScale = 1});
	*enemyRow += statusEffectsColumn;
	auto statusEffectOption = Component::Options{.WidthScale = 1, .HeightScale = .15};
	for (StatusEffectInstance* statusEffect : ctx.GameState->CurrentBattle.StatusEffects) {
		if (statusEffect->IsCaster(ctx, ctx.GameState->CurrentRun.PlayerCharacter) && statusEffect->IsBuff(ctx)) {
			*statusEffectsColumn += statusEffect->StatusEffect.GetSprite(ctx, statusEffectOption);
		} else if (statusEffect->IsTarget(ctx, ctx.GameState->CurrentRun.PlayerCharacter) && !statusEffect->IsBuff(ctx)) {
			*statusEffectsColumn += statusEffect->StatusEffect.GetSprite(ctx, statusEffectOption);
		}
	}

	// Experience Bar
	auto innerHealthBar = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	*healthBar += innerHealthBar;
	*innerHealthBar += new Label(ctx, "Health 22/70", {.WidthScale = .1, .HeightScale = .95, .DefaultColor = WHITE});
	*innerHealthBar += new HorizontalPanel(ctx, {.WidthScale = .85, .HeightScale = 1});

	// Experience Bar
	auto innerEXPBar = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	*experienceBar += innerEXPBar;
	*innerEXPBar += new Label(ctx, "Level 22", {.WidthScale = .1, .HeightScale = .95, .DefaultColor = WHITE});
	*innerEXPBar += new HorizontalPanel(ctx, {.WidthScale = .85, .HeightScale = 1});

	// Rune Row
	auto runeCol1 = new VerticalPanel(ctx, {.WidthScale = .33, .HeightScale = 1});
	auto runeCol2 = new VerticalPanel(ctx, {.WidthScale = .33, .HeightScale = 1});
	auto runeCol3 = new VerticalPanel(ctx, {.WidthScale = .33, .HeightScale = 1});
	*runeRow += runeCol1;
	*runeRow += runeCol2;
	*runeRow += runeCol3;
	auto runeOptions = Component::Options{
		.WidthScale = 1,
		.HeightScale = .48,
		.DefaultColor = ctx.Colors.Button,
		.HoverColor = ctx.Colors.ButtonHover};
	*runeCol1 += Rune(ctx, true).GenerateComponent(ctx, runeOptions);
	*runeCol1 += Rune(ctx, true).GenerateComponent(ctx, runeOptions);
	*runeCol2 += Rune(ctx, true).GenerateComponent(ctx, runeOptions);
	*runeCol2 += Rune(ctx, true).GenerateComponent(ctx, runeOptions);
	*runeCol3 += Rune(ctx, true).GenerateComponent(ctx, runeOptions);
	*runeCol3 += Rune(ctx, true).GenerateComponent(ctx, runeOptions);

	return panel;
}
