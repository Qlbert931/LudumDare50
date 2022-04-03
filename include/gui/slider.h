// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef SLIDER_H
#define SLIDER_H
#include "context.h"
#include "component.h"

class SliderTab;

class Slider : public Component {
public:
	Slider(Context& ctx, const Component::Options& options, Color trackColor, float* trackedValue);
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;
	void Update(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;

private:
	Color trackColor;
	float* trackedValue;
};

class SliderTab : public Component {
	friend class Slider;

public:
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;

private:
	SliderTab(Context& ctx, const Component::Options& options);
};

#endif //SLIDER_H
