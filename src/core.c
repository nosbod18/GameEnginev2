#include "core.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <stdlib.h> // malloc, free
#include <string.h> // memcpy
#include <stdio.h>

#ifndef FILENAME
    #include <string.h>
    #define FILENAME (strrchr("/" __FILE__, '/') + 1)
#endif // FILENAME

//-----------------------------
// ~Window

static void windowOnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
static void windowOnButton(GLFWwindow* window, int button, int action, int mods);
static void windowOnMouseMove(GLFWwindow* window, double x, double y);
static void windowOnMouseScroll(GLFWwindow* window, double x, double y);

Window* windowCreate(const char* title, int w, int h, uint flags)
{
    if (!glfwInit())
        return NULL;

    Window* window = malloc(sizeof *window);

    if (!window)
        return NULL;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

    GLFWwindow* native = glfwCreateWindow(w, h, title, NULL, NULL);

    if (!native)
        return NULL;

    glfwSetWindowUserPointer(native, window);
    glfwSetKeyCallback(native, windowOnKey);
    glfwSetMouseButtonCallback(native, windowOnButton);
    glfwSetCursorPosCallback(native, windowOnMouseMove);
    glfwSetScrollCallback(native, windowOnMouseScroll);

    int x0, y0;
    glfwGetWindowPos(native, &x0, &y0);

    Window tmp = {native, title, x0, y0, w, h, x0, y0, w, h, flags, {0}, {0}};
    memcpy(window, &tmp, sizeof *window);

    glfwMakeContextCurrent(native);
    gladLoadGL();

    return window;
}

void windowDestroy(Window* window)
{
    glfwDestroyWindow((GLFWwindow*)window->native);

    free(window);
    window = NULL;

    // Only supports one window for now
    glfwTerminate();
}

void windowSwapBuffers(const Window* window)
{
    glfwSwapBuffers((GLFWwindow*)window->native);
}

int windowWidth(const Window* window)
{
    return window ? window->w : 0;
}

int windowHeight(const Window* window)
{
    return window ? window->h : 0;
}

bool windowIsOpen(const Window* window)
{
    return window ? !glfwWindowShouldClose((GLFWwindow*)window->native) : 0;
}

bool windowIsVsync(const Window* window)
{
    return window ? (window->flags >> WINDOW_VSYNC) & 1 : 0;
}

bool windowIsMinimized(const Window* window)
{
    return window ? (window->flags >> WINDOW_MINIMIZED) & 1 : 0;
}

bool windowIsMaximized(const Window* window)
{
    return window ? (window->flags >> WINDOW_MAXIMIZED) & 1 : 0;
}

void windowSetSize(Window* window, int w, int h)
{
    if (!window)
        return;

    window->w = w;
    window->h = h;

    glfwSetWindowSize((GLFWwindow*)window->native, w, h);
}

void windowSetPos(Window* window, int x, int y)
{
    if (!window)
        return;

    window->x = x;
    window->y = y;

    glfwSetWindowPos((GLFWwindow*)window->native, x, y);
}

void windowRestore(Window* window)
{
    if (!window)
        return;

    window->x = window->x0;
    window->y = window->y0;
    window->w = window->w0;
    window->h = window->h0;

    glfwSetWindowPos((GLFWwindow*)window->native, window->x, window->y);
    glfwSetWindowSize((GLFWwindow*)window->native, window->w, window->h);
}

//-----------------------------
// ~Input

static void windowRefreshInput(Window* window);

static InputButton windowGetKey(const Window* window, KeyCode key);
static InputButton windowGetButton(const Window* window, MouseCode button);

void windowPollEvents(Window* window)
{
    windowRefreshInput(window);
    glfwPollEvents();
}

bool windowIsKeyDown(const Window* window, KeyCode key)
{
    return windowGetKey(window, key).down;
}

bool windowIsKeyPressed(const Window* window, KeyCode key)
{
    return windowGetKey(window, key).pressed;
}

bool windowIsKeyReleased(const Window* window, KeyCode key)
{
    return windowGetKey(window, key).released;
}

bool windowIsButtonDown(const Window* window, MouseCode button)
{
    return windowGetButton(window, button).down;
}

bool windowIsButtonPressed(const Window* window, MouseCode button)
{
    return windowGetButton(window, button).pressed;
}

bool windowIsButtonReleased(const Window* window, MouseCode button)
{
    return windowGetButton(window, button).released;
}

float windowMouseXPos(const Window* window)
{
    return window ? window->mouse.x : 0.0f;
}

float windowMouseYPos(const Window* window)
{
    return window ? window->mouse.y : 0.0f;
}

void windowMousePos(const Window* window, float* x, float* y)
{
    if (x) *x = windowMouseXPos(window);
    if (y) *y = windowMouseYPos(window);
}

float windowMouseXOffset(const Window* window)
{
    return window ? window->mouse.dx : 0.0f;
}

float windowMouseYOffset(const Window* window)
{
    return window ? window->mouse.dy : 0.0f;
}

void windowMouseOffset(const Window* window, float* x, float* y)
{
    if (x) *x = windowMouseXOffset(window);
    if (y) *y = windowMouseYOffset(window);
}

float windowMouseXScroll(const Window* window)
{
    return window ? window->mouse.scrollX : 0.0f;
}

float windowMouseYScroll(const Window* window)
{
    return window ? window->mouse.scrollY : 0.0f;
}

void windowMouseScroll(const Window* window, float* x, float* y)
{
    if (x) *x = windowMouseXScroll(window);
    if (y) *y = windowMouseYScroll(window);
}

void windowShowCursor(Window* window)
{
    if (!window)
        return;

    window->mouse.hidden = 0;
}

void windowHideCursor(Window* window)
{
    if (!window)
        return;

    window->mouse.hidden = 1;
}

bool windowIsCursorHidden(const Window* window)
{
    return window ? window->mouse.hidden : 0;
}

void windowEnableCursor(Window* window)
{
    if (!window)
        return;

    window->mouse.disabled = 0;
}

void windowDisableCursor(Window* window)
{
    if (!window)
        return;

    window->mouse.disabled = 1;
}

bool windowIsCursorDisabled(const Window* window)
{
    return window ? window->mouse.disabled : 0;
}

static void windowRefreshInput(Window* window)
{
    for (int i = 0; i < KEY_LAST; ++i)
    {
        window->keyboard.keys[i].pressed  = 0;
        window->keyboard.keys[i].released = 0;
    }

    for (int i = 0; i < MOUSE_BUTTON_LAST; ++i)
    {
        window->mouse.buttons[i].pressed = 0;
        window->mouse.buttons[i].released = 0;
    }

    window->mouse.dx = 0.0f;
    window->mouse.dy = 0.0f;
    window->mouse.scrollX = 0.0f;
    window->mouse.scrollY = 0.0f;
}

static InputButton windowGetKey(const Window* window, KeyCode key)
{
    if (!window || key < KEY_UNKNOWN || key > KEY_LAST)
        return (InputButton){0};

    return window->keyboard.keys[key];
}

static InputButton windowGetButton(const Window* window, MouseCode button)
{
    if (!window || button < 0 || button > MOUSE_BUTTON_LAST)
        return (InputButton){0};

    return window->mouse.buttons[button];
}

static void windowOnKey(GLFWwindow* native, int key, int scancode, int action, int mods)
{
    (void)scancode; (void)mods;

    Window* window = glfwGetWindowUserPointer(native);

    if (!window)
        return;

    // GLFW_KEY_UNKNOWN is -1, make it 0 to avoid a seg fault
    if (key == GLFW_KEY_UNKNOWN)
        key = KEY_UNKNOWN;

    switch (action)
    {
        case GLFW_PRESS: {
            window->keyboard.keys[key].pressed = !window->keyboard.keys[key].down;
            window->keyboard.keys[key].down = 1;
        } break;

        case GLFW_RELEASE: {
            window->keyboard.keys[key].released = 1;
            window->keyboard.keys[key].down = 0;
        } break;

        default: {
        } break;
    }
}

static void windowOnButton(GLFWwindow* native, int button, int action, int mods)
{
    (void)mods;

    Window* window = glfwGetWindowUserPointer(native);

    if (!window)
        return;

    switch (action)
    {
        case GLFW_PRESS: {
            window->mouse.buttons[button].pressed = !window->mouse.buttons[button].down;
            window->mouse.buttons[button].down = 1;
        } break;

        case GLFW_RELEASE: {
            window->mouse.buttons[button].released = 1;
            window->mouse.buttons[button].down = 0;
        } break;

        default: {
        } break;
    }
}

static void windowOnMouseMove(GLFWwindow* native, double x, double y)
{
    Window* window = glfwGetWindowUserPointer(native);

    if (!window)
        return;

    window->mouse.dx = x - window->mouse.x;
    window->mouse.dy = x - window->mouse.y;
    window->mouse.x  = x;
    window->mouse.y  = y;
}

static void windowOnMouseScroll(GLFWwindow* native, double x, double y)
{
    Window* window = glfwGetWindowUserPointer(native);

    if (!window)
        return;

    window->mouse.scrollX = x;
    window->mouse.scrollY = y;
}
