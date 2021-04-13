#pragma once

#include <memory>
#include <functional>
#include <any>

//using callbackFunction = std::function <void()>;
/*
using workFunction = std::function <std::any(std::any)>;
using workFunctionNoRet = std::function <void(std::any)>;
using workFunctionNoArg = std::function <std::any()>;
using workFunctionNoAll = std::function <void()>;
*/

template <typename T> using ptr = std::shared_ptr<T>;

#define BIND_TEMPLATE(EVENTID) \
void bind##EVENTID##(callbackFunction function) \
{\
	EVENTID = EventManager::registerEvent(function); \
} \