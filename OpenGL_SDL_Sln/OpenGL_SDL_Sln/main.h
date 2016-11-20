#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <windows.h>

#include <GL/glew.h>

#include <SDL.h>

#include "SceneNodeData.h"

#include "RenderEngine.h"

using namespace TotalGlobal;

#define PROGRAM_NAME "Tutorial1"

/* A simple function that prints a message, the error code returned by SDL,
* and quits the application */
void sdldie(const char *msg);

void checkSDLError(int line = -1);

// http://stackoverflow.com/questions/4845410/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
int _stdcall
WinMain(struct HINSTANCE__ *hInstance,
struct HINSTANCE__ *hPrevInstance,
	char               *lpszCmdLine,
	int                 nCmdShow);

/* Our program's entry point */
int main(int argc, char *argv[]);

std::vector<SceneNodeData *> SetupScene();

bool RenderLoop(RenderingEngine *pRenderEngine, SDL_Window *window);
