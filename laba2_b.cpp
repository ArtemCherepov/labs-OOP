/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- *
    В проекте «Классическое приложение Windows» в функции WndProc вставить обработчик события case WM_CREATE: {    break;} В нем создать две фигуры типа окружности и
прямоугольника и положить их в общее глобальное хранилище, применяя контейнер vector. (Использовать следует конструктор с необходимыми параметрами для каждого типа)
Далее в функции WndProc, в обработке события WM_PAINT, между строками hdc = BeginPaint(hWnd, &ps); и EndPaint(hWnd, &ps); последовательно проходя по хранимым в контейнере
vector данными, осуществить рисование окружности и прямоугольника.
* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <cmath>


// Процедура window
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

#define MAX_LOADSTRING 100

int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd, int mode)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass{};
    wndclass.hInstance = This;
    wndclass.lpszClassName = WinName;
    wndclass.lpfnWndProc = WndProc;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszMenuName = NULL;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wndclass))
    {
        return 0;
    }

    hwnd = CreateWindow(WinName, _T("Каркас Windows-приложения"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, NULL, This, NULL);

    ShowWindow(hwnd, mode);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// Иерархия классов
class Shape
{
public:
    Shape() {};
    virtual void Draw(HDC hdc) = 0;
    virtual ~Shape() {};
};

class Circle : public Shape
{
public:
    // Конструктор из условия
    Circle(int center, int radius) : startCoord_{ center - radius }, endCoord_{ center + radius }
    {}
    void Draw(HDC hdc)
    {
        Ellipse(hdc, startCoord_, 0, endCoord_, endCoord_);
    }

private:
    const int startCoord_; const int endCoord_;
};

class Rect : public Shape
{
public:
    // Конструктор из условия
    Rect(int start, int width, int height) :
        startCoord_{ start }, rightCoord_{ startCoord_ + width }, bottomCoord_{ height }
    {}

    void Draw(HDC hdc)
    {
        Rectangle(hdc, startCoord_, 0, rightCoord_, bottomCoord_);
    }

private:
    const int startCoord_; const int rightCoord_;
    const int bottomCoord_;
};

// Глобальное хранилище
std::vector<Shape*> figuresStorage;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc; int x{}, y{}; static int startx, starty, step, lenght, sx, sy;

    switch (message)
    {
    case WM_CREATE:
        figuresStorage.push_back(new Circle(230, 230));
        figuresStorage.push_back(new Rect(600, 300, 450));
        break;

    case WM_SIZE:
        sx = LOWORD(wParam);
        sy = LOWORD(lParam);
        break;

    case WM_PAINT:
        // Рисоваине окружности  и прямоугольника
        hdc = BeginPaint(hWnd, &ps);
        for (std::vector <Shape*>::iterator iter = figuresStorage.begin(); iter != figuresStorage.end(); ++iter)
        {
            (*iter)->Draw(hdc);
        }
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        for (std::vector <Shape*>::iterator iter = figuresStorage.begin(); iter != figuresStorage.end(); ++iter)
        {
            delete (*iter);
        }
        figuresStorage.clear();
        PostQuitMessage(0);
        break;

    default:return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}