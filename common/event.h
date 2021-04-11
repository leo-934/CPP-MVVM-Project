#pragma once

#include "def.h"
#include <vector>
#include <functional>
#include <exception>
//事件管理器
using callbackFunction = std::function<void()>;

class EventManager {
private:
	//私有定义类，使得事件管理器外部无法定义_eventid对象，只能定义eventid指针，这样可以保证每一个_eventid对象都在控制之中。
	class _eventId {
	private:
		bool registered;
		int id;
		bool isRegistered() { return registered; }
		void setRegistered(bool state) { registered = state; }
	public:
		_eventId(int _id) {
			if (_id <= 0) throw std::exception("_id must >0");
			id = _id;
			registered = true;
		}
		friend class EventManager;
	};

	static std::vector<callbackFunction> eventVector;
	static std::vector<int> unusedId;

	

public:
	using eventId = ptr<_eventId>;

	static eventId registerEvent(callbackFunction callback) {
		if (unusedId.empty()) {
			eventVector.push_back(callback);
			return std::make_shared<_eventId>(eventVector.size());
		}
		else {
			auto id = unusedId.back();
			eventVector[id-1] = callback;
			unusedId.pop_back();
			return std::make_shared<_eventId>(id);
		}
	}
	static void unregisterEvent(eventId tmp) {
		if (tmp->isRegistered() == true) {
			tmp->setRegistered(false);
			unusedId.push_back(tmp->id);
		}
	}
	static int raiseEvent(eventId tmp) {
		if ((*tmp).isRegistered()) {
			eventVector[(*tmp).id-1]();
			return 1;
		}
		else {
			throw std::exception("unregistered event");
			return 0;
		}
	}
};

using eventId = EventManager::eventId;
