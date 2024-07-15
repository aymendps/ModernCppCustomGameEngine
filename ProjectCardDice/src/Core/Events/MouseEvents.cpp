#include "MouseEvents.h"
#include "../Math/Vector2D.h"
#include <SDL.h>

bool MouseEvents::IsHovered(const SDL_Rect& rect)
{
	// Get the mouse position
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	
	// Check if the mouse is inside the rect. If it is, return true, otherwise return false.
	return mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h;
}

bool MouseEvents::IsLeftClicked(const SDL_Event& event, const SDL_Rect& rect)
{
	return MouseEvents::IsHovered(rect) && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT;
}

bool MouseEvents::IsRightClicked(const SDL_Event& event, const SDL_Rect& rect)
{
	return MouseEvents::IsHovered(rect) && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT;
}

bool MouseEvents::IsLeftDoubleClicked(const SDL_Event& event, const SDL_Rect& rect)
{
	return MouseEvents::IsLeftClicked(event, rect) && event.button.clicks == 2;
}

bool MouseEvents::IsRightDoubleClicked(const SDL_Event& event, const SDL_Rect& rect)
{
	return MouseEvents::IsRightClicked(event, rect) && event.button.clicks == 2;
}

bool MouseEvents::IsLeftPressed(const SDL_Event& event, const SDL_Rect& rect, Vector2D& outMousePosition)
{
	int mouseX, mouseY;
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	outMousePosition.x = static_cast<float>(mouseX);
	outMousePosition.y = static_cast<float>(mouseY);
	return MouseEvents::IsHovered(rect) && mouseState & SDL_BUTTON_LMASK;
}

bool MouseEvents::IsRightPressed(const SDL_Event& event, const SDL_Rect& rect, Vector2D& outMousePosition)
{
	int mouseX, mouseY;
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	outMousePosition.x = static_cast<float>(mouseX);
	outMousePosition.y = static_cast<float>(mouseY);
	return MouseEvents::IsHovered(rect) && mouseState & SDL_BUTTON_RMASK;
}
