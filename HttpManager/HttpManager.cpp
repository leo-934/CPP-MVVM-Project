#include "pch.h"
#include "httpmanager.h"
#include "curl.h"
#include <exception>
std::string HttpManager::formula_result;
const std::string HttpManager::request_url = "https://aip.baidubce.com/rest/2.0/ocr/v1/formula";
const std::string HttpManager::access_token = "24.69909779cc2b13da14231297bf7c6ac8.2592000.1618318584.282335-23773487";

std::string HttpManager::qwe()
{
	return std::string("dllfuck");
}
std::string HttpManager::baiduOcrRequest(std::string img_base64) 
{
    std::string url = request_url + "?access_token=" + access_token;
    CURL* curl = NULL;
    CURLcode result_code;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_httppost* post = NULL;
        curl_httppost* last = NULL;
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "image", CURLFORM_COPYCONTENTS, img_base64.c_str(), CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, baiduOcrRequestCallback);
        result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK) {
            throw std::exception("curl perform fail");
        }
        
        curl_easy_cleanup(curl);
        return formula_result;
    }
    else {
        throw std::exception("curl_easy_init() failed.");
        return std::string("");
    }
}