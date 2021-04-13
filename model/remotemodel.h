#pragma once
#include <string>
#include "def.h"
#include "event.h"
class RemoteModel {
private:
	std::string latexJson;

	eventId getLatexJsonSuccess;
	eventId getLatexJsonFail;

public:
	void getLatexJsonFromBase64(std::string img_base64);

	const std::string& getLatexJson();

	BIND_TEMPLATE(getLatexJsonSuccess)

	BIND_TEMPLATE(getLatexJsonFail)

};