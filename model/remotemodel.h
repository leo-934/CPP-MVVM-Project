#pragma once
#include <string>
#include "def.h"
#include "event.h"
class RemoteModel {
private:

	const static std::string baiduOcrUrl;
	const static std::string accessToken;


	std::string latexJson;
	std::string svg;

	eventId getLatexJsonSuccess;
	eventId getLatexJsonFail;
	eventId getSvgFromLatexStringSuccess;
	eventId getSvgFromLatexStringFail;

	unsigned char decToHex(unsigned char x);
	std::string urlEncode(const std::string& bytes_to_encode);
	

public:
	void getLatexJsonFromBase64(std::string imgBase64);
	void getSvgFromLatexString(std::string latexString);

	const std::string& getLatexJson();
	const std::string& getSvg();

	BIND_TEMPLATE(getLatexJsonSuccess)
	BIND_TEMPLATE(getLatexJsonFail)
	BIND_TEMPLATE(getSvgFromLatexStringSuccess)
	BIND_TEMPLATE(getSvgFromLatexStringFail)
};