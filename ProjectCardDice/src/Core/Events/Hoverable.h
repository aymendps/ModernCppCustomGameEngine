#pragma once
class Hoverable
{
public:
	/// <summary>
	/// Returns true if the mouse is hovering over the element, otherwise returns false.
	/// </summary>
	/// <param name="rect">The rect of the element to check</param>
	static bool IsHovered(struct SDL_Rect& rect);
};

