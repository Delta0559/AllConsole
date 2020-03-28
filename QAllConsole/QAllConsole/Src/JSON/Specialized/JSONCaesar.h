#pragma once

#include "../JSONManager.h"

class JSONCaesar : public JSONManager
{
public:
	enum class CaesarBool {
		KeepSpecialChar, KeepSpaces
	};

	void Caesar_ReplaceBoolValue(bool ok, CaesarBool type);
	void Caesar_GetBoolValue(bool& ok, CaesarBool type);
};
