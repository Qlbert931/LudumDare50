// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef INPUTSTEPPER_H
#define INPUTSTEPPER_H
#include "context.h"
#include "component.h"

class InputStepper : public Component {
public:
	InputStepper(Context& ctx, const Component::Options& options, int* minValue, int* maxValue, int* currentValue);
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;
	void OnClick(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;

private:
	int* min;
	int* max;
	int* current;
};

#endif //INPUTSTEPPER_H
