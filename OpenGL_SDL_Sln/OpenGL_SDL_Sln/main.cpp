#include "main.h"

#include "ModelNodeData.h"
#include "GUIDFinder.h"

/* A simple function that prints a message, the error code returned by SDL,
* and quits the application */
void sdldie(const char *msg)
{
	printf("%s: %s\n", msg, SDL_GetError());
	SDL_Quit();
	exit(1);
}


void checkSDLError(int line)
{
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
		if (line != -1)
			printf(" + line: %i\n", line);
		SDL_ClearError();
	}
#endif
}

// http://stackoverflow.com/questions/4845410/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
int _stdcall
WinMain(struct HINSTANCE__ *hInstance,
struct HINSTANCE__ *hPrevInstance,
	char               *lpszCmdLine,
	int                 nCmdShow)
{
	return main(__argc, __argv);
}

/* Our program's entry point */
int main(int argc, char *argv[])
{
	SDL_Window *mainwindow; /* Our window handle */
	SDL_GLContext maincontext; /* Our opengl context handle */

	if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
		sdldie("Unable to initialize SDL"); /* Or die on error */

	/* Request opengl 3.2 context.
	* SDL doesn't have the ability to choose which profile at this time of writing,
	* but it should default to the core profile */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	/* Turn on double buffering with a 24bit Z buffer.
	* You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/* Create our window centered at 512x512 resolution */
	mainwindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!mainwindow) /* Die if creation failed */
		sdldie("Unable to create window");

	checkSDLError(__LINE__);

	/* Create our opengl context and attach it to our window */
	maincontext = SDL_GL_CreateContext(mainwindow);
	checkSDLError(__LINE__);


	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	SDL_GL_SetSwapInterval(1);

	// ----------------------------------------------------------------

	// http://stackoverflow.com/questions/20766864/glew-opengl-access-violation-when-using-glgenvertexarrays
	// Initialize GLEW
    glewExperimental = true; // Needed for core profile
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

	// ===============================================================

	///* Clear our buffer with a red background */
	//glClearColor(1.0, 0.0, 0.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	///* Swap our back buffer to the front */
	//SDL_GL_SwapWindow(mainwindow);
	///* Wait 2 seconds */
	//SDL_Delay(2000);

	///* Same as above, but green */
	//glClearColor(0.0, 1.0, 0.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//SDL_GL_SwapWindow(mainwindow);
	//SDL_Delay(2000);

	///* Same as above, but blue */
	//glClearColor(0.0, 0.0, 1.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//SDL_GL_SwapWindow(mainwindow);
	//SDL_Delay(2000);

	// ===============================================================
	
	std::vector<SceneNodeData *> sceneNodeDataSet = SetupScene();

	RenderingEngine *pRenderEngine = new RenderingEngine();
	pRenderEngine->Init(sceneNodeDataSet);

	RenderLoop(pRenderEngine);

	// ==================================================================

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	return 0;
}

std::vector<SceneNodeData *> SetupScene()
{
	std::vector<SceneNodeData *> sceneNodeDataSet;

	// -------------------------------------------------------------------------------------------------------------------
	GUID modelId;
	HRESULT hCreateGuid = CoCreateGuid(&modelId);
	GUID parentNodeId = GUIDFinder::ZeroGuid;
	std::vector<GUID> childNodeIdSet;
	std::string objectFilename = "C:/OpenGL_SDL_Sln/OpenGL_SDL_Sln/Debug/data/obj/capsule/capsule.obj";
	std::string textureFilename = "C:/OpenGL_SDL_Sln/OpenGL_SDL_Sln/Debug/data/obj/capsule/capsule0.jpg";

	std::map<AttributeType, std::string> attributeTypeNameSet;

	attributeTypeNameSet.insert(std::pair<AttributeType, std::string>(AttributeType::CoordCart, "CoordCart"));
	attributeTypeNameSet.insert(std::pair<AttributeType, std::string>(AttributeType::CoordTex, "CoordTex"));
	attributeTypeNameSet.insert(std::pair<AttributeType, std::string>(AttributeType::NormCart, "NormCart"));


	ModelNodeData * pModelNode = new ModelNodeData(modelId, parentNodeId, childNodeIdSet, objectFilename, textureFilename, attributeTypeNameSet);
	// -------------------------------------------------------------------------------------------------------------------

	sceneNodeDataSet.push_back(pModelNode);

	return sceneNodeDataSet;
}


bool RenderLoop(RenderingEngine *pRenderEngine)
{
	// TODO: do the loop and SDL-Event Handling

	bool succ = true;
	while (true)
	{
		succ = pRenderEngine->Render();
	}

	return true;
}