#include "../life_backend/Life.h"
#include "life_frontend.h"
#ifdef __APPLE__
#  include <mach-o/dyld.h>
#endif
#if defined(_WIN32)
#  include <windows.h>
#else
#include <unistd.h>
#endif
#include <filesystem>
#include "variables.h"


static bool quit = false;
static bool isPaused = false;
static bool isLeftButtonDown = false;
static bool isRightButtonDown = false;
static Uint32 speed = 61;
static int cellsize = 10;
static bool isDrawing = false;
static bool data;

void drawGame(SDL_Renderer* renderer, Life& life, int cellsize, SDLInterfaceLoader& sdlLoader) {
    sdlLoader.RenderClear(renderer);

    sdlLoader.SetRenderDrawColor(renderer, 15, 59, 9, 0);

    for (int i = 0; i <= life.getWidwght(); ++i) {
        sdlLoader.DrawLine(renderer, i * 10, 0, i * 10, life.getHeight() * 10);
    }

    for (int j = 0; j <= life.getHeight(); ++j) {
        sdlLoader.DrawLine(renderer, 0, j * 10, life.getWidwght() * 10, j * 10);
    }

    for (int i = 0; i < life.getWidwght(); ++i) {
        for (int j = 0; j < life.getHeight(); ++j) {
            if (life.getCellState(i, j)) {
                sdlLoader.SetRenderDrawColor(renderer, 191, 191, 191, 0);
                SDL_Rect rect = {i * cellsize, j * cellsize, cellsize, cellsize};
                if (sdlLoader.FillRect(renderer, &rect) != 0) {
                    std::cerr << "Error filling triangle" << sdlLoader.GetError() << std::endl;
                }
            }
        }
    }

    sdlLoader.SetRenderDrawColor(renderer, 0, 0, 0, 0);
    sdlLoader.RenderPresent(renderer);
}

void inputHandler(Life& life, SDLInterfaceLoader& sdlLoader, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Event e;
    bool isResizing = false;
    double resizeX = 1.0;
    double resizeY = 1.0;
    double scale = 1.0;
    int displayIndex = 0;

    std::string str;
    while (!quit) {
        while (sdlLoader.PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    int newWidth = e.window.data1;
                    int newHeight = e.window.data2;
                    newWidth -= newWidth % 10;
                    newHeight -= newHeight % 10;
                    life.changeSize(newWidth / cellsize, newHeight / cellsize);
                    scale = 1;
                    sdlLoader.SetLogicalSize(renderer, life.getWidwght() * cellsize * scale,
                                             life.getHeight() * cellsize * scale);
                    drawGame(renderer, life, 10, sdlLoader);
                }
                break;
            case SDL_MOUSEWHEEL:
                if (e.wheel.y > 0) {
                    scale / 1.1 >= 0.1 ? scale /= 1.1 : 0;
                }
                else if (e.wheel.y < 0) {
                    scale * 1.1 <= 1 ? scale *= 1.1 : 0;
                }

                sdlLoader.SetLogicalSize(renderer, life.getWidwght() * cellsize * scale,
                                         life.getHeight() * cellsize * scale);
                drawGame(renderer, life, cellsize, sdlLoader);
                break;
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    isLeftButtonDown = true;
                }
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    isRightButtonDown = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    if (e.button.x / cellsize < life.getWidwght() && e.button.y / cellsize < life.getHeight() && !
                        isDrawing) {
                        data = life.getCellState(e.button.x / cellsize, e.button.y / cellsize);
                        data
                            ? life.setDeadCell(e.button.x / cellsize, e.button.y / cellsize)
                            : life.setAliveCell(e.button.x / cellsize, e.button.y / cellsize);
                        drawGame(renderer, life, 10, sdlLoader);
                    }
                    isLeftButtonDown = false;
                }
                (e.button.button == SDL_BUTTON_RIGHT) ? isRightButtonDown = false : 1 + 1;
                isDrawing = false;
                break;
            case SDL_MOUSEMOTION:
                if (isLeftButtonDown && e.motion.x < life.getWidwght() * cellsize && e.motion.y < life.getHeight() *
                    cellsize) {
                    isDrawing = true;
                    life.setAliveCell(e.motion.x / cellsize, e.motion.y / cellsize);
                    drawGame(renderer, life, 10, sdlLoader);
                }
                if (isRightButtonDown && e.motion.x < life.getWidwght() * cellsize && e.motion.y < life.getHeight() *
                    cellsize) {
                    isDrawing = true;
                    life.setDeadCell(e.motion.x / cellsize, e.motion.y / cellsize);
                    drawGame(renderer, life, 10, sdlLoader);
                }
                if (scale < 1) {
                }
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                case SDLK_UP:
                    if (speed - 5 < 10) {
                        continue;
                    }
                    speed -= 10;
                    break;
                case SDLK_DOWN:
                    if (speed + 10 > 600) {
                        continue;
                    }
                    speed += 10;
                    break;
                case SDLK_SPACE:
                    isPaused = !isPaused;
                    break;

                case SDLK_r:
                    life.clear();
                    drawGame(renderer, life, 10, sdlLoader);
                    break;
                }
            }
        }
        if (isPaused) {
            continue;
        }
        sdlLoader.Delay(speed);

        life.update_game();
        drawGame(renderer, life, 10, sdlLoader);
    }
}

namespace {
    std::filesystem::path getExecutablePath() {
        char path[1024];
#if defined(_WIN32) || defined(_WIN64)
        GetModuleFileName(NULL, path, sizeof(path));
        return std::string(path);
#elif defined(__linux__)
        ssize_t len = ::readlink("/proc/self/exe", path, sizeof(path) - 1);
        if (len != -1)
        {
            path[len] = '\0';
            return std::string(path);
        }
#elif defined(__APPLE__)
        uint32_t size = sizeof(path);
        if (_NSGetExecutablePath(path, &size) == 0) {
            return std::filesystem::path(std::string(path));
        }
#endif

        return std::string();
    }
}

int main(int argc, char* argv[]) {
    Life life = Life(35, 50);
    life.fill();
    auto pathToExecutable = ::getExecutablePath();
    auto pathToDirWhereExecutable = std::filesystem::path(pathToExecutable.string()).parent_path().parent_path();
    std::string SDL_LIBRARY_NAME = MY_VARIABLE;
    auto pathToSdlLibrary = pathToDirWhereExecutable / "Frameworks" / MY_VARIABLE;
    SDLInterfaceLoader sdlLoader(pathToSdlLibrary.c_str());

    if (sdlLoader.Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << sdlLoader.GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = sdlLoader.CreateWindow(
        "Game of life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        life.getWidwght() * cellsize, life.getHeight() * cellsize, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Window creation failed: " << sdlLoader.GetError() << std::endl;
        return -1;
    }
    SDL_Renderer* renderer = sdlLoader.CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << sdlLoader.GetError() << std::endl;
        return -1;
    }
    inputHandler(life, sdlLoader, window, renderer);
    sdlLoader.DestroyRenderer(renderer);
    sdlLoader.DestroyWindow(window);
    sdlLoader.Quit();

    return 0;
}
