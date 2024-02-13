#pragma once

struct NotificationData {
	std::string title;
	std::string message;
	float duration = 3;
	bool isOpen = true;

	std::chrono::time_point<std::chrono::steady_clock> startTime;

	NotificationData(std::string title, std::string message) : title(title), message(message)
	{
		startTime = std::chrono::steady_clock::now();
	}

	inline float getElapsedTime()
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
		return elapsedTime / 1000.0f;
	}
};

class NotificationBase {
public:
	inline static std::vector<std::shared_ptr<NotificationData>> notificationQueue;

	inline std::vector<std::shared_ptr<NotificationData>>& getList()
	{
		// Are we populated?
		while (!this->notificationQueue.empty())
		{
			auto& first = this->notificationQueue.front();
			if (!first->isOpen)
			{
				this->notificationQueue.erase(this->notificationQueue.begin());
				continue;
			}
			break;
		}
		return this->notificationQueue;
	}

	inline std::shared_ptr<NotificationData> addNotification(std::string title, std::string message, const float duration = 3.f)
	{
		auto notification = std::make_shared<NotificationData>(title, message);
		notification->duration = duration;
		this->notificationQueue.push_back(notification);
		return notification;
	}
};