#include "remotemodel.h"
#include "HttpManager.h"
#include <iostream>

void RemoteModel::getLatexJsonFromBase64(std::string img_base64)
{
	
	/*
	QFile file("log.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream text_stream(&file);
	text_stream << QString::fromStdString(HttpManager::baiduOcrRequest(img_base64)) << "\r\n";
	file.flush();
	file.close();
	*/
	try {
		latexJson = HttpManager::baiduOcrRequest(img_base64);
	}
	catch (std::exception a) {
		EventManager::raiseEvent(getLatexJsonFail);
		return;
	}
	EventManager::raiseEvent(getLatexJsonSuccess);
	return;
}

void RemoteModel::getSvgFromLatexString(std::string latexString)
{
	try {
		svg = HttpManager::codecogsRenderRequest(urlEncode(latexString));
	}
	catch (std::exception a) {
		EventManager::raiseEvent(getSvgFromLatexStringFail);
		return;
	}
	EventManager::raiseEvent(getSvgFromLatexStringSuccess);
	return;
}

unsigned char RemoteModel::decToHex(unsigned char x)
{
	return  x > 9 ? x + 55 : x + 48;
}
std::string RemoteModel::urlEncode(const std::string& bytes_to_encode)
{
	std::string strTemp = "";
	size_t length = bytes_to_encode.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)bytes_to_encode[i]) ||
			(bytes_to_encode[i] == '-') ||
			(bytes_to_encode[i] == '_') ||
			(bytes_to_encode[i] == '.') ||
			(bytes_to_encode[i] == '~'))
			strTemp += bytes_to_encode[i];
		else if (bytes_to_encode[i] == ' ')
		{
			//strTemp += "+";
			strTemp += "%20";
		}
		else
		{
			strTemp += '%';
			strTemp += decToHex((unsigned char)bytes_to_encode[i] >> 4);
			strTemp += decToHex((unsigned char)bytes_to_encode[i] % 16);
		}
	}
	return strTemp;
}

const std::string& RemoteModel::getLatexJson()
{
	return latexJson;
}

const std::string& RemoteModel::getSvg()
{
	return svg;
}

