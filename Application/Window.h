#pragma once

class Window
{
public:
	Window(HINSTANCE hInstance, LPCTSTR className);
	~Window();

	void create(LPCTSTR title);

	int width() const { return rect.right - rect.left; }
	int height() const { return rect.bottom - rect.top; }
	int posX() const { return rect.left; }
	int posY() const { return rect.top; }

	void size(int& width, int& height) const { width = this->width(); height = this->height(); }
	void pos(int& x, int& y) const { x = posX(); y = posY(); }

	void setPosX(int x) { rect.right += x - rect.left; rect.left = x; }
	void setPosY(int y) { rect.bottom += y - rect.top; rect.top = y; }
	void setWidth(int width) { rect.right = rect.left + width; }
	void setHeight(int height) { rect.bottom = rect.top + height; }

	void setSize(int width, int height) { setWidth(width); setHeight(height); }
	void setPos(int x, int y) { setPosX(x); setPosY(y); }

	HWND handle() const { return hWnd; }
private:
	// prevent copy
	Window(const Window&);
	Window& operator=(const Window&);

	/// Static WndProc that will propagate message to @link{handleMessage}.
	static LRESULT CALLBACK staticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	/**
	 * Member version of classic windows WndProc callback.
	 * @see http://msdn.microsoft.com/en-us/library/windows/desktop/ms633573(v=vs.85).aspx
	 */
	LRESULT handleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND hWnd;
	LPCTSTR className;
	HINSTANCE hInstance;

	struct Rect : public RECT 
	{
		Rect() { left = 0; right = 0; top = 0; bottom = 0;}
		Rect(long left, long top, long right, long bottom) { 
			this->left = left; this->top = top; 
			this->right = right; this->bottom = bottom;
		}
	};
	Rect rect;
};
