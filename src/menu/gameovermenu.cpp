// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include <iostream>

// Temp variable to check for clicked
bool beenClicked = false;

void claimedColor (Context& ctx, Component& component) {
	std::cout << "Clicked!" << std::endl;
	if (!beenClicked) {
		component.GetOptions().DefaultColor = Color{150, 150, 150, 255};
		beenClicked = true;
		return;
	}
	component.GetOptions().DefaultColor = Color{130, 130, 130, 255};
	beenClicked = false;
}

Component* Menu::CreateGameOverMenu(Context& ctx) {
	auto gameOverMenuButtonOptions = Component::Options{
		.WidthScale = 1.0,
		.HeightScale = 1.0,
		.DefaultColor = Color{130, 130, 130, 255},
		.HoverColor = Color{150, 150, 150, 255}
	};
	auto gameOverMenu = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});

	auto gameOverTitle = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = .2});
	*gameOverTitle += new Label(ctx, "Game Over", {.WidthScale = .5, .HeightScale = 1, .DefaultColor = RAYWHITE});
	*gameOverMenu += gameOverTitle;

	// Text time is a play holder for the variable time
	auto playerTime = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = .3});
	*playerTime += new Label(ctx, "time", {.WidthScale = 1, .HeightScale = 1, .DefaultColor = RAYWHITE});
	*gameOverMenu += playerTime;

	// monsters killed
	// bosses defeated
	auto titleLevel = new HorizontalPanel (ctx, {.WidthScale = 1, .HeightScale =.15});

	auto monstersSlainTitle = new VerticalPanel(ctx, {.WidthScale = .3, .HeightScale = 1});
	*monstersSlainTitle += new Label(ctx, "Monsters Slain:", {.WidthScale = 1, .HeightScale = 1, .DefaultColor = RAYWHITE});
	auto bossesDefeatedTitle = new VerticalPanel(ctx, {.WidthScale = .3,.HeightScale = 1});
	*bossesDefeatedTitle += new Label(ctx, "Bosses Slain:", {.WidthScale = 1, .HeightScale = 1, .DefaultColor = RAYWHITE});
	*titleLevel += monstersSlainTitle;
	*titleLevel += bossesDefeatedTitle;

	*gameOverMenu += titleLevel;

	// Numbers are updated later
	auto numberLevel = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .15});

	auto monstersSlainNumber = new VerticalPanel(ctx, {.WidthScale = .3, .HeightScale = 1});
	*monstersSlainNumber += new Label(ctx, "5", {.WidthScale = 1, .HeightScale = 1,.DefaultColor = RAYWHITE});
	auto bossesDefeatedNumber = new VerticalPanel(ctx, {.WidthScale = .3,.HeightScale = 1});
	*bossesDefeatedNumber += new Label(ctx, "6", {.WidthScale = 1, .HeightScale = 1,.DefaultColor = RAYWHITE});
	*numberLevel += monstersSlainNumber;
	*numberLevel += bossesDefeatedNumber;

	*gameOverMenu += numberLevel;

	// Home Button
	// homeButtonArea -> entire button area across the bottom
	auto homeButtonArea = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .15});
	// button occupying the row
	auto homeButton = new Button(ctx, gameOverMenuButtonOptions.WithOnClick(claimedColor).WithWidthScale(.2));
	// icon inside the button
	auto homeIcon = new HorizontalPanel(ctx, {.WidthScale = .3, .HeightScale = 1});
	// add the sprite to the home icon spot and add back to the home button area
	*homeButton += new Sprite(ctx, SpriteName::Home, {.WidthScale = 1, .HeightScale = 1});

	// add text to the home area and text to the same home area
	auto homeName = (new HorizontalPanel(ctx, {.WidthScale = .3, .HeightScale = 1}))->
		AddChild(new Label(ctx, "HOME", {.WidthScale = 1, .HeightScale = 1, .DefaultColor = BLACK}));
	*homeButton += homeName;

	*homeButtonArea += homeButton;

	auto homeButtonFill = new HorizontalPanel(ctx, {.WidthScale = .8, .HeightScale = 1});
	*homeButtonArea += homeButtonFill;

	*gameOverMenu += homeButtonArea;




	// runes
	return gameOverMenu;
}