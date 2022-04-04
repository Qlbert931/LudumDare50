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

VerticalPanel* Menu::CreateGameOverMenu(Context& ctx) {
	auto gameOverMenuButtonOptions = Component::Options{
		.WidthScale = 1.0,
		.HeightScale = 1.0,
		.DefaultColor = Color{130, 130, 130, 255},
		.HoverColor = Color{150, 150, 150, 255}
	};
	auto gameOverMenu = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});

	auto gameOverTitle = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = .35});
	*gameOverTitle += new Label(ctx, "Game Over", {.WidthScale = 1, .HeightScale = 1, .DefaultColor = RAYWHITE});
	*gameOverMenu += gameOverTitle;

	// Text time is a play holder for the variable time
	auto playerTime = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = .45});
	*playerTime += new Label(ctx, "time", {.WidthScale = 1, .HeightScale = 1, .DefaultColor = RAYWHITE});
	*gameOverMenu += playerTime;

	auto homeButtonArea = new HorizontalPanel(ctx, {.WidthScale = 1, .HeightScale = .2});
	auto homeButton = new Button(ctx, gameOverMenuButtonOptions.WithOnClick(claimedColor).WithWidthScale(.1));
	*homeButtonArea += homeButton->AddChild(new Sprite(ctx, SpriteName::HomeButton, {.WidthScale = 1, .HeightScale = 1}));

	return gameOverMenu;
}