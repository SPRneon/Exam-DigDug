#pragma once
#include "Singleton.h"

namespace dae{
class TextRenderer final : public Singleton<TextRenderer>
{
public:
	TextRenderer();
	~TextRenderer();
};
}
