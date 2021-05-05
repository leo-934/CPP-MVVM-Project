#pragma once

#ifdef HTTPMANAGER_EXPORTS
#define HTTPMANAGER_API __declspec(dllexport)
#else
#define HTTPMANAGER_API __declspec(dllimport)
#endif

#include <string>
class HTTPMANAGER_API HttpManager {
private:
	const static std::string request_url;
	const static std::string access_token;
	static std::string formula_result;

	const static std::string codecogs_url;
	static std::string svg_result;

	static size_t baiduOcrRequestCallback(void* ptr, size_t size, size_t nmemb, void* stream) {
		// 获取到的body存放在ptr中，先将其转换为string格式
		formula_result = std::string((char*)ptr, size * nmemb);
		return size * nmemb;
	}
	static size_t codecogsRenderRequestCallback(void* ptr, size_t size, size_t nmemb, void* stream) {
		// 获取到的body存放在ptr中，先将其转换为string格式
		svg_result = std::string((char*)ptr, size * nmemb);
		return size * nmemb;
	}

public:
	
	static std::string baiduOcrRequest(std::string img_base64);
	static std::string codecogsRenderRequest(std::string latex_string);
};