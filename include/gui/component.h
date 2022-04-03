// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef COMPONENT_H
#define COMPONENT_H
#include "context.h"
#include "functional"

class Component {
	friend class VerticalPanel;
	friend class HorizontalPanel;
	friend class Button;

public:
	virtual ~Component() {}
	virtual int Width(Context& ctx) = 0;
	virtual int Height(Context& ctx) = 0;
	virtual void Update(Context& ctx);
	void DrawComponent(Context& ctx, int x, int y);
	bool IsMouseOver(Context& ctx);
	bool IsMouseDown(Context& ctx);
	void OnClick(Context& ctx) const;
	int X() { return x; }
	int Y() { return y; }

	struct Options {
	public:
		float WidthScale = 0;
		float HeightScale = 0;
		Color DefaultColor = {};
		Color HoverColor = {};
		std::function<void(Context&)> OnClick = nullptr;

		Options WithWidthScale(float widthScale);
		Options WithHeightScale(float heightScale);
		Options WithDefaultColor(Color defaultColor);
		Options WithHoverColor(Color hoverColor);
		Options WithOnClick(std::function<void(Context&)> onClick);

	private:
		Options copy();
	};

protected:
	virtual void Draw(Context& ctx) = 0;
	Component* parent = nullptr;
	Options options;

private:
	int x = 0;
	int y = 0;
};

#endif //COMPONENT_H
