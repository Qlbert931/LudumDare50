// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "state.h"
#include "statuseffect.h"
#include "gui/menus.h"

State::State(Context& ctx) : ctx(ctx) {}

State::~State() {
	GameOver();
}

void State::NewGame() {
	CurrentRun.ElapsedTime = 0;
	CurrentRun.ProgressTime = 0;
	ChanceProgress.NewRune = 0;
	ChanceProgress.FindBoss = 0;
	ChanceProgress.NextRuneCommon = 0;
	ChanceProgress.NextRuneUncommon = 0;
	ChanceProgress.NextRuneRare = 0;
	ChanceProgress.NextRuneEpic = 0;
	ChanceProgress.NextRuneLegendary = 0;
}

void State::NextRoom() {
	if (ctx.GameState->CurrentRun.PlayerCharacter.Experience == 10) {
		ctx.GameState->CurrentRun.PlayerCharacter.Experience = 0;
		ctx.Menu.Set(Context::Menus::LevelUpMenu);
		ctx.Menu.ReloadLevelUpMenu(ctx);
		((Menu::LevelUpMenuComponent*)ctx.Menu[ctx.Menu.Current()])->RoomLoad(ctx);
	}
	switch (ctx.Menu.Current()) {
		case Context::Menus::MainMenu:
			ctx.Menu.ReloadCombatMenu(ctx);
			ctx.Menu.Set(Context::Menus::CombatMenu);
			return;
		case Context::Menus::RuneMenu:
			return;
		case Context::Menus::GameOverMenu:
			ctx.Menu.Set(Context::Menus::MainMenu);
			return;
		case Context::Menus::NewRuneMenu:
			ctx.Menu.ReloadCombatMenu(ctx);
			ctx.Menu.Set(Context::Menus::CombatMenu);
			return;
		case Context::Menus::PauseMenu:
			return;
		case Context::Menus::LevelUpMenu:
		case Context::Menus::CombatMenu:
			double probability = ((double)GetRandomValue(0, 1000000000) / 1000000000.0);
			ChanceProgress.NewRune += Chances::Rune;
			if (probability <= ChanceProgress.NewRune) {
				ChanceProgress.NewRune = 0;
				this->CurrentRun.ReplacingIndex = -1;
				probability = ((double)GetRandomValue(0, 1000000000) / 1000000000.0);
				ChanceProgress.NextRuneLegendary += Chances::RarityLegendary;
				//TODO: will these panic if I delete the old rune?
				if (probability <= ChanceProgress.NextRuneLegendary) {
					ChanceProgress.NextRuneLegendary = 0;
					//TODO: add proper rune
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, true);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ChanceProgress.NextRuneEpic += Chances::RarityEpic;
				if (probability <= ChanceProgress.NextRuneEpic) {
					ChanceProgress.NextRuneEpic = 0;
					//TODO: add proper rune
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, true);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ChanceProgress.NextRuneRare += Chances::RarityRare;
				if (probability <= ChanceProgress.NextRuneRare) {
					ChanceProgress.NextRuneRare = 0;
					//TODO: add proper rune
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, true);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				ChanceProgress.NextRuneUncommon += Chances::RarityUncommon;
				if (probability <= ChanceProgress.NextRuneUncommon) {
					ChanceProgress.NextRuneUncommon = 0;
					//TODO: add proper rune
					ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, true);
					ctx.Menu.ReloadNewRuneMenu(ctx);
					ctx.Menu.Set(Context::Menus::NewRuneMenu);
					return;
				}
				//TODO: add proper rune
				ctx.GameState->CurrentRun.AddingRune = new Rune(ctx, true);
				ctx.Menu.ReloadNewRuneMenu(ctx);
				ctx.Menu.Set(Context::Menus::NewRuneMenu);
				return;
			}
			break;
	}
}

void State::Attack(int runeIndex) {

}

void State::GameOver() {
	for (auto enemy : CurrentBattle.Enemies) {
		delete(enemy);
	}
	CurrentBattle.Enemies.clear();
	for (auto statusEffect : CurrentBattle.StatusEffects) {
		delete(statusEffect);
	}
	CurrentBattle.StatusEffects.clear();
}
