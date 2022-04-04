// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "state.h"

State::State(Context& ctx) : ctx(ctx) {}

State::~State() {
	for (auto enemy : CurrentBattle.Enemies) {
		delete(enemy);
	}
}

void State::Reset() {

}

void State::NextRoom() {

}

void State::NewEnemies() {
	
}

void State::GameOver() {

}
