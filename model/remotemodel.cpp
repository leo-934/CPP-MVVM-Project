#include "remotemodel.h"
#include "HttpManager.h"
#include <QDebug>
#include <iostream>
#include <QString>
#include <QFile>
void RemoteModel::getLatexFromBase64(std::string filePath)
{
	qDebug() << "getLatexFromImage function of RemoteModel";
	std::string img_base64;
	freopen("./a.txt", "r", stdin);
	std::cin >> img_base64;
	QFile file("log.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream text_stream(&file);
	text_stream << QString::fromStdString(HttpManager::baiduOcrRequest(img_base64)) << "\r\n";
	file.flush();
	file.close();
	//std::cout << HttpManager::baiduOcrRequest(img_base64);
	//qDebug() << QString::fromStdString(HttpManager::baiduOcrRequest(img_base64));
}
