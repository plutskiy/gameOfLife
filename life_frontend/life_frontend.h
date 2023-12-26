#pragma once

#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
   #include "Windows.h"
#else
#include <dlfcn.h>

#endif
#include <SDL.h>

typedef int (*SDL_InitFunc)(Uint32 flags);
typedef SDL_Window* (*SDL_CreateWindowFunc)(const char* title, int x, int y, int w, int h, Uint32 flags);
typedef SDL_Renderer* (*SDL_CreateRendererFunc)(SDL_Window* window, int index, Uint32 flags);
typedef int (*SDL_SetRenderDrawColorFunc)(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
typedef int (*SDL_RenderClearFunc)(SDL_Renderer* renderer);
typedef void (*SDL_RenderPresentFunc)(SDL_Renderer* renderer);
typedef int (*SDL_PollEventFunc)(SDL_Event* event);
typedef void (*SDL_DestroyRendererFunc)(SDL_Renderer* renderer);
typedef void (*SDL_DestroyWindowFunc)(SDL_Window* window);
typedef void (*SDL_QuitFunc)();
typedef int (*SDL_FillRectFunc)(SDL_Renderer* renderer, const SDL_Rect* rect);
typedef const char* (*SDL_GetErrorFunc)();
typedef void (*SDL_DelayFunc)(Uint32 ms);
typedef int (*SDL_RenderDrawLineFunc)(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);
typedef int (*SDL_RenderSetLogicalSizeFunc)(SDL_Renderer* renderer, int w, int h);

class SDLInterface {
public:
    virtual int Init(Uint32 flags) = 0;
    virtual SDL_Window* CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags) = 0;
    virtual SDL_Renderer* CreateRenderer(SDL_Window* window, int index, Uint32 flags) = 0;
    virtual int SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;
    virtual int RenderClear(SDL_Renderer* renderer) = 0;
    virtual void RenderPresent(SDL_Renderer* renderer) = 0;
    virtual int PollEvent(SDL_Event* event) = 0;
    virtual void DestroyRenderer(SDL_Renderer* renderer) = 0;
    virtual void DestroyWindow(SDL_Window* window) = 0;
    virtual int FillRect(SDL_Renderer* renderer, const SDL_Rect* rect) = 0;
    virtual const char* GetError() = 0;
    virtual void Delay(Uint32 ms) = 0;
    virtual void Quit() = 0;
    virtual int DrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) = 0;
    virtual int SetLogicalSize(SDL_Renderer* renderer, int w, int h) = 0;

    virtual ~SDLInterface() = default;
};

class SDLInterfaceLoader : public SDLInterface {
private:
#if defined(_WIN32) || defined(_WIN64)
    HMODULE sdlLibrary;
#else
    void* sdlLibrary;
#endif

    template <typename T>
    T LoadFunction(const char* name) {
        T func;
#if defined(_WIN32) || defined(_WIN64)
        func = reinterpret_cast<T>(GetProcAddress((HMODULE)sdlLibrary, name));
#else
        func = reinterpret_cast<T>(dlsym(sdlLibrary, name));
#endif
        if (!func) {
#if defined(_WIN32) || defined(_WIN64)
            std::cerr << "Error loading SDL function '" << name << "': " << GetLastError() << std::endl;
#else
            std::cerr << "Error loading SDL function '" << name << "': " << dlerror() << std::endl;
#endif

            exit(EXIT_FAILURE);
        }
        return func;
    }

public:
    explicit SDLInterfaceLoader(const char* libraryPath) {
#if defined(_WIN32) || defined(_WIN64)
        sdlLibrary = LoadLibrary(libraryPath);
#else
        sdlLibrary = dlopen(libraryPath, RTLD_NOW);
#endif
        if (!sdlLibrary) {
#if defined(_WIN32) || defined(_WIN64)
            std::cerr << "Error loading SDL library " << ": " << GetLastError() << std::endl;
#else
            std::cerr << "Error loading SDL library " << ": " << dlerror() << std::endl;
#endif
        }
    }

    ~SDLInterfaceLoader() override {
#if defined(_WIN32) || defined(_WIN64)
        FreeLibrary((HMODULE)sdlLibrary);
#else
        dlclose(sdlLibrary);
#endif
    }

    int Init(Uint32 flags) override {
        auto func = LoadFunction<SDL_InitFunc>("SDL_Init");
        return func(flags);
    }

    SDL_Window* CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags) override {
        auto func = LoadFunction<SDL_CreateWindowFunc>("SDL_CreateWindow");
        return func(title, x, y, w, h, flags);
    }

    SDL_Renderer* CreateRenderer(SDL_Window* window, int index, Uint32 flags) override {
        auto func = LoadFunction<SDL_CreateRendererFunc>("SDL_CreateRenderer");
        return func(window, index, flags);
    }

    int SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) override {
        auto func = LoadFunction<SDL_SetRenderDrawColorFunc>("SDL_SetRenderDrawColor");
        return func(renderer, r, g, b, a);
    }

    int RenderClear(SDL_Renderer* renderer) override {
        auto func = LoadFunction<SDL_RenderClearFunc>("SDL_RenderClear");
        return func(renderer);
    }

    void RenderPresent(SDL_Renderer* renderer) override {
        auto func = LoadFunction<SDL_RenderPresentFunc>("SDL_RenderPresent");
        return func(renderer);
    }

    int PollEvent(SDL_Event* event) override {
        auto func = LoadFunction<SDL_PollEventFunc>("SDL_PollEvent");
        return func(event);
    }

    void DestroyRenderer(SDL_Renderer* renderer) override {
        auto func = LoadFunction<SDL_DestroyRendererFunc>("SDL_DestroyRenderer");
        return func(renderer);
    }

    void DestroyWindow(SDL_Window* window) override {
        auto func = LoadFunction<SDL_DestroyWindowFunc>("SDL_DestroyWindow");
        return func(window);
    }

    int FillRect(SDL_Renderer* renderer, const SDL_Rect* rect) override {
        auto func = LoadFunction<SDL_FillRectFunc>("SDL_RenderFillRect");
        return func(renderer, rect);
    }

    const char* GetError() override {
        auto func = LoadFunction<SDL_GetErrorFunc>("SDL_GetError");
        return func();
    }

    void Delay(Uint32 ms) override {
        auto func = LoadFunction<SDL_DelayFunc>("SDL_Delay");
        return func(ms);
    }

    int DrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) override {
        auto func = LoadFunction<SDL_RenderDrawLineFunc>("SDL_RenderDrawLine");
        return func(renderer, x1, y1, x2, y2);
    }

    int SetLogicalSize(SDL_Renderer* renderer, int w, int h) override {
        auto func = LoadFunction<SDL_RenderSetLogicalSizeFunc>("SDL_RenderSetLogicalSize");
        return func(renderer, w, h);
    }

    void Quit() override {
        auto func = LoadFunction<SDL_QuitFunc>("SDL_Quit");
        return func();
    }
};
