// Copyright © 2022 Daylon Wilkins & Maxwell Chow
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef LABEL_H
#define LABEL_H
#include "context.h"
#include "component.h"
#include "string"

class Label : public Component {
public:
	Label(Context& ctx, std::string text, const Component::Options& options);
	~Label() override;
	int Width(Context& ctx) override;
	int Height(Context& ctx) override;

protected:
	void Draw(Context& ctx) override;

private:
	std::string text;
	float textLengthAt10;
};

#endif //LABEL_H
