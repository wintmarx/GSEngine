#define GSENGINE_EXPORT
#include "GUI/Window.h"

#include <algorithm>
#include <stdexcept>

#include "GL/glew.h"

Window::Window(const std::string& title, int width, int height) {
    if (!glfwInit()) {
        throw std::runtime_error("GLFW init error");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(0);

    glfwWindow = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (!glfwWindow) {
        glfwTerminate();
        throw std::runtime_error("glfwCreateWindow error");
    }

    glfwMakeContextCurrent(glfwWindow);

    glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetInputMode(glfwWindow, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);

    SubscribeToGLFWInputEvents();
}

void Window::SubscribeToGLFWInputEvents() {
    glfwSetWindowUserPointer(glfwWindow, this);

    glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* w, int btn, int action, int mods) {
        auto* wnd = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (!wnd) {
            return;
        }
        for (auto listener : wnd->inputEventsListeners) {
            listener->OnMouseButtonEvent(btn, action, mods);
        }
    });

    glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* w, double x, double y) {
        auto* wnd = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (!wnd) {
            return;
        }
        for (auto listener : wnd->inputEventsListeners) {
            listener->OnMouseCursorEvent(static_cast<float>(x), static_cast<float>(y));
        }
    });

    glfwSetScrollCallback(glfwWindow, [](GLFWwindow* w, double x, double y) {
        auto* wnd = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (!wnd) {
            return;
        }
        for (auto listener : wnd->inputEventsListeners) {
            listener->OnMouseScrollEvent(static_cast<float>(x), static_cast<float>(y));
        }
    });

    glfwSetKeyCallback(glfwWindow, [](GLFWwindow* w, int key, int scanCode, int action, int mods) {
        auto* wnd = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (!wnd) {
            return;
        }
        for (auto listener : wnd->inputEventsListeners) {
            listener->OnKeyboardEvent(key, scanCode, action, mods);
        }
    });
}

Window::~Window() {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

double Window::GetTime() { return glfwGetTime(); }

bool Window::IsWindowShouldClose() { return glfwWindowShouldClose(glfwWindow) == 0; }

void Window::SwapBuffers() { glfwSwapBuffers(glfwWindow); }

void Window::PollEvents() { glfwPollEvents(); }

void Window::AddInputEventsListener(InputEventsListener* listener) {
    if (!listener) {
        return;
    }

    inputEventsListeners.push_back(listener);
}

void Window::RemoveInputEventsListener(InputEventsListener* listener) {
    if (!listener) {
        return;
    }
    auto it = std::find(inputEventsListeners.begin(), inputEventsListeners.end(), listener);
    if (it == inputEventsListeners.end()) {
        return;
    }
    inputEventsListeners.erase(it);
}
