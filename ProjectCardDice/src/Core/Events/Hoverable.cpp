#include "Hoverable.h"
#include <SDL.h>

bool Hoverable::IsHovered(SDL_Rect& rect)
{
	// Get the mouse position
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	
	// Check if the mouse is inside the rect. If it is, return true, otherwise return false.
	return mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h;
}
