// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef CONTEXT_H
#define CONTEXT_H
#include "raylib/raylib.h"
#include "vector"

class Context;
class Component;

struct Colors_ {
	Color Background = Color{30, 30, 30, 255};
	Color Slider = Color{0, 136, 182, 255};
	Color SliderHover = Color{0, 190, 253, 255};
	Color Button = Color{255, 255, 255, 50};
	Color ButtonHover = Color{255, 255, 255, 100};

	Color RarityCommon = Color{255, 255, 255, 255};
	Color RarityUncommon = Color{30, 255, 0, 255};
	Color RarityRare = Color{0, 112, 221, 255};
	Color RarityEpic = Color{163, 53, 238, 255};
	Color RarityLegendary = Color{255, 128, 0, 255};
};

struct Mouse_ {
	friend class Context;

public:
	int X() { return x; }
	int Y() { return y; }
	bool IsDown() { return down; }
	bool HasClicked() { return clicked; }

private:
	int x = -2147483648;
	int y = -2147483648;
	bool down = false;
	bool clicked = false;
};

struct Screen_ {
	friend class Context;

public:
	int Width() const { return width; };
	int Height() const { return height; };
	bool HasResized() const { return width != prevWidth || height != prevHeight; }

private:
	int width = 0;
	int height = 0;
	int prevWidth = 0;
	int prevHeight = 0;
};

class Context {
public:
	struct Menus {
		friend class Context;

	public:
		enum Index {
			None = -1,
			MainMenu = 0,
			RuneMenu = 1,
			GameOverMenu = 2,
			CombatMenu = 3,
			NewRuneMenu = 4,
			LevelUpMenu = 5,
			PauseMenu = 6
		};
		void Set(Index menuIndex) { currentMenu = menuIndex; }
		Index Current() { return currentMenu; }
		Component& operator [](Index idx) { return *(menus.at(idx)); }

	private:
		Index currentMenu = None;
		std::vector<Component*> menus;
		void initialize(Context& ctx);
	};

	Context();
	~Context();
	void Initialize();
	void Update();
	void Draw();
	const Colors_ Colors;
	Screen_ Screen;
	Mouse_ Mouse;
	Menus Menu;

	float Volume = 1;
};

#endif //CONTEXT_H
