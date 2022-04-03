// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "gui/system.h"
#include "gui/menus.h"
#include "iostream"

VerticalPanel* Menu::CreateMainMenu(Context& ctx) {
	auto mainMenu = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 1});
	auto titlePanel = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 0.4});
	auto buttonPanel = new VerticalPanel(ctx, {.WidthScale = 1, .HeightScale = 0.6});
	*mainMenu += titlePanel;
	*mainMenu += buttonPanel;

	auto menuButtonLabelOptions = Component::Options{
		.WidthScale = 0.7,
		.HeightScale = 0.7,
		.DefaultColor = Color{200, 200, 200, 255}};
	*titlePanel += new Label(ctx, "The Fastest RPG",{.WidthScale = 0.7, .HeightScale = 0.5, .DefaultColor = RAYWHITE});

	auto menuButtonOptions = Component::Options{
		.WidthScale = 0.4,
		.HeightScale = 0.15,
		.DefaultColor = Color{130, 130, 130, 255},
		.HoverColor = Color{150, 150, 150, 255}};
	auto playClickFunc = [](Context& ctx) { std::cout << "[PLAY] Clicked!" << std::endl; };
	auto leaderboardClickFunc = [](Context& ctx) { std::cout << "[LEADERBOARDS] Clicked!" << std::endl; };
	auto playerClickFunc = [](Context& ctx) { std::cout << "[PLAYER] Clicked!" << std::endl; };

	*buttonPanel += new Button(ctx, menuButtonOptions.WithOnClick(playClickFunc), new Label(ctx, "PLAY", menuButtonLabelOptions));
	*buttonPanel += new Button(ctx, menuButtonOptions.WithOnClick(leaderboardClickFunc), new Label(ctx, "LEADERBOARDS", menuButtonLabelOptions));
	*buttonPanel += new Button(ctx, menuButtonOptions.WithOnClick(playerClickFunc), new Label(ctx, "PLAYER", menuButtonLabelOptions));
	*buttonPanel += new Button(ctx, menuButtonOptions, new Label(ctx, "VOL PLACEHOLDER", menuButtonLabelOptions));
	return mainMenu;
}
