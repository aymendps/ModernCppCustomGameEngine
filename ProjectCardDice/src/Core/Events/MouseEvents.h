#pragma once

struct SDL_Rect;
union SDL_Event;
class Vector2D;

class MouseEvents
{
public:
	/// <summary>
	/// Checks whether the mouse is hovering over the element.
	/// </summary>
	/// <param name="rect">The rect of the element to check, representing its position and size</param>
	/// <returns>True if the mouse is hovering over the element, otherwise false</returns>
	static bool IsHovered(const SDL_Rect& rect);

	/// <summary>
	/// Checks whether the element was clicked using the left button of the mouse. Only fires on the first frame of the click.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	/// <param name="rect">The rect of the element to check, representing its position and size</param>
	/// <returns>True if the element was clicked using the left button of the mouse, otherwise false</returns>
	static bool IsLeftClicked(const SDL_Event& event, const SDL_Rect& rect);

	/// <summary>
	/// Checks whether the element was clicked using the right button of the mouse. Only fires on the first frame of the click.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	/// <param name="rect">The rect of the element to check, representing its position and size</param>
	/// <returns>True if the element was clicked using the right button of the mouse, otherwise false</returns>
	static bool IsRightClicked(const SDL_Event& event, const SDL_Rect& rect);

	/// <summary>
	/// Checks whether the element was double clicked using the left button of the mouse. Only fires on the first frame of the second click.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	/// <param name="rect">The rect of the element to check, representing its position and size</param>
	/// <returns>True if the element was double clicked using the left button of the mouse, otherwise false</returns>
	static bool IsLeftDoubleClicked(const SDL_Event& event, const SDL_Rect& rect);

	/// <summary>
	/// Checks whether the element was double clicked using the right button of the mouse. Only fires on the first frame of the second click.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	/// <param name="rect">The rect of the element to check, representing its position and size</param>
	/// <returns>True if the element was double clicked using the right button of the mouse, otherwise false</returns>
	static bool IsRightDoubleClicked(const SDL_Event& event, const SDL_Rect& rect);

	/// <summary>
	/// Checks whether the element is being pressed using the left button of the mouse. Fires every frame the left button is pressed.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	/// <param name="rect">The rect of the element to check, representing its position and size</param>
	/// <param name="outMousePosition">The position of the mouse when the left button is pressed</param>
	/// <returns>True if the element is being pressed using the left button of the mouse, otherwise false</returns>
	static bool IsLeftPressed(const SDL_Event& event, const SDL_Rect& rect, Vector2D& outMousePosition);

	/// <summary>
	/// Checks whether the element is being pressed using the right button of the mouse. Fires every frame the right button is pressed.
	/// </summary>
	/// <param name="event">Polled event from SDL to handle</param>
	/// <param name="rect">The rect of the element to check, representing its position and size</param>
	/// <param name="outMousePosition">The position of the mouse when the right button is pressed</param>
	/// <returns>True if the element is being pressed using the right button of the mouse, otherwise false</returns>
	static bool IsRightPressed(const SDL_Event& event, const SDL_Rect& rect, Vector2D& outMousePosition);
};

