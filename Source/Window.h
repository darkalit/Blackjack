#pragma once

#include <string>

struct SDL_Window;

class Window
{
public:
	enum WindowFlags : uint8_t
	{
		NONE = 0,
		FULLSCREEN,
		RESIZABLE,
	};

	Window(const std::string& title, int32_t width, int32_t height, WindowFlags flags = NONE);
	~Window();

	int32_t GetWidth() const;
	int32_t GetHeight() const;
	void ToggleFullscreen();

	int32_t GetMouseX() const;
	int32_t GetMouseY() const;

	SDL_Window* GetHandle() const;

private:
	SDL_Window* m_Window = nullptr;
	int32_t m_Width = 0, m_Height = 0;
	bool m_Fullscreen = false;
};

