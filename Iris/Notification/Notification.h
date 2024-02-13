#pragma once
#include "NotificationBase.h"

class Notification {
public:
	static void renderNotifications() {
		static NotificationBase noti;
		auto& notifications = noti.getList();
		float yOffset = Game::Core::ClientInstance->getGuiData()->WindowResolution2.y - 30;
		const float textSize = 1.2f;

		for (auto& notif : notifications) {
			float elapsedTime = notif->getElapsedTime();
			float duration = notif->duration;
			Vector2<float> textPos;
			const float firstPos = Game::Core::ClientInstance->getGuiData()->WindowResolution2.x - ImRenderUtil::getTextWidth(&notif->message, textSize) - 8.f;
			const float lastPos = Game::Core::ClientInstance->getGuiData()->WindowResolution2.x + 8.f;
			const float speed = 1.f;
			static float fade = 0;

			EasingUtil easing;
			easing.percentage = (elapsedTime > duration) ? 1.0f - ((elapsedTime - duration) / speed) : elapsedTime / speed;
			textPos.x = (easing.percentage < 1) ? Math::lerp(lastPos, firstPos, (elapsedTime > duration) ? easing.easeInExpo() : easing.easeOutExpo()) : ((elapsedTime > duration) ? lastPos : firstPos);
			textPos.y = (easing.percentage < 1) ? Math::lerp(Game::Core::ClientInstance->getGuiData()->WindowResolution2.y + 10, yOffset, (elapsedTime > duration) ? easing.easeInExpo() : easing.easeOutExpo()) : ((elapsedTime > duration) ? Game::Core::ClientInstance->getGuiData()->WindowResolution2.y + 10 : yOffset);
			fade = (easing.percentage < 1) ? Math::lerp(0, 1.f, (elapsedTime > duration) ? easing.easeInExpo() : easing.easeOutExpo()) : 1.f;

			if (elapsedTime > duration && easing.percentage <= 0) notif->isOpen = false;

			float notifWidth = textPos.x + ImRenderUtil::getTextWidth(&notif->message, textSize);
			Vector4<float> test = Vector4<float>(textPos.x, textPos.y, textPos.x + ((notifWidth - textPos.x) * elapsedTime / duration), textPos.y + 10.5);

			if (!notif->message.find("Injected")) {
				ImRenderUtil::drawGradientString(Vector2<float>(textPos.x, yOffset), &notif->message, textSize, fade, true, 5, 1, 1, 50);
			}
			else {
				ImRenderUtil::drawText(Vector2<float>(textPos.x, yOffset), &notif->message, ColorUtil::getClientColor(5, 1, 1, yOffset * 5), textSize, fade, true);
			}

			yOffset = Math::lerp(yOffset, yOffset - 20 * textSize, (elapsedTime > duration) ? easing.easeInExpo() : easing.easeOutExpo());
		}
	}
};

