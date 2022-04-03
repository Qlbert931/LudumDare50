// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"
#include "context.h"
#include "component.h"

enum SpriteName {
	None = 0,
    SpearGoblin = 1,
    BearBaby = 2,
    Golem = 3
};

 class Sprite : public Component {
public:
    Sprite(SpriteName spriteName, Color spriteColor);
    ~Sprite();

    int Width(Context& ctx) override;
    int Height(Context& ctx) override;
//    void Update(Context& ctx) override;

    SpriteName name;
    Color color;

 protected:
     void Draw(Context &ctx) override;
};

#endif //SPRITE_H
