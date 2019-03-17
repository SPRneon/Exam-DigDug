#pragma once
#include "Helpers/Singleton.h"

namespace dae{
class TextRenderer final : public Singleton<TextRenderer>
{
public:
	TextRenderer();
	~TextRenderer();
};
}
