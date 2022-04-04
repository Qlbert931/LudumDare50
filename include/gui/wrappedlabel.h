// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef WRAPPEDLABEL_H
#define WRAPPEDLABEL_H
#include "context.h"
#include "component.h"
#include "string"

class WrappedLabel : public Component {
public:
	WrappedLabel(Context& ctx, std::string text, const Component::Options& options);
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;
	void SetText(Context& ctx, std::string text);

protected:
	void Draw(Context& ctx) override;

private:
	void calculateFontSize(Context& ctx);
	std::string text;
	int fontSize;
};

#endif //WRAPPEDLABEL_H
