// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "context.h"
#include "gui/menus.h"
#include "cmath"

Context::Context() {
	Screen.width = 1280;
	Screen.height = 720;
}

Context::~Context() {
	for (auto menu : Menu.menus) {
		delete(menu);
	}
}

void Context::Initialize() {
	this->Menu.initialize(*this);
}

void Context::Update() {
	// Screen
	Screen.prevWidth = Screen.width;
	Screen.prevHeight = Screen.height;
	Screen.width = GetScreenWidth();
	Screen.height = GetScreenHeight();

	// Mouse
	auto mousePos = GetMousePosition();
	int prevMouseX = Mouse.x;
	int prevMouseY = Mouse.y;
	Mouse.x = (int)mousePos.x;
	Mouse.y = (int)mousePos.y;
	bool prevMouseDown = Mouse.down;
	Mouse.down = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	if (prevMouseDown && !Mouse.down && (abs(Mouse.x - prevMouseX) + abs(Mouse.y - prevMouseY)) <= 4) {
		Mouse.clicked = true;
	} else {
		Mouse.clicked = false;
	}

	if (Menu.currentMenu >= 0) {
		Menu.menus.at(Menu.currentMenu)->Update(*this);
	}
}

void Context::Draw() {
	if (Menu.currentMenu >= 0) {
		Menu.menus.at(Menu.currentMenu)->DrawComponent(*this, 0, 0);
	}
}

void Context::Menus::initialize(Context& ctx) {
	// ENSURE that the menu order here matches the Menu::Index enumerated order
	menus.push_back(Menu::CreateMainMenu(ctx));
	menus.push_back(Menu::CreateRuneMenu(ctx));
	currentMenu = Menus::MainMenu;
}
