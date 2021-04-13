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

const std::string& RemoteModel::getLatexJson()
{
	return latexJson;
}

