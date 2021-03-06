#include "main.h"

#include <glm/gtc/matrix_transform.hpp>

#include "ModelNodeData.h"
#include "ShaderNodeData.h"
#include "CameraNodeData.h"
#include "ViewPortNodeData.h"

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

	RenderLoop(pRenderEngine, mainwindow);

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

	GUID viewPortId;
	HRESULT hCreateGuid = CoCreateGuid(&viewPortId);
	GUID cameraId;
	hCreateGuid = CoCreateGuid(&cameraId);
	GUID shaderId;
	hCreateGuid = CoCreateGuid(&shaderId);
	GUID modelId;
	hCreateGuid = CoCreateGuid(&modelId);

	// -------------------------------------------------------------------------------------------------------------------

	GUID viewPortParentId = GUIDFinder::ZeroGuid;
	std::vector<GUID> viewPortChildIdSet;
	viewPortChildIdSet.push_back(cameraId);
	GLsizei width = 512; 
	GLsizei height = 512;

	ViewPortNodeData *pViewPortNode = new ViewPortNodeData(viewPortId, viewPortParentId, viewPortChildIdSet, width, height);

	// -------------------------------------------------------------------------------------------------------------------

	GUID cameraParentId = viewPortId;
	std::vector<GUID> cameraChildIdSet;
	cameraChildIdSet.push_back(shaderId);
	glm::mat4x4 viewTransform = glm::lookAt(glm::vec3(0, 0, -100), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	glm::mat4x4 projectionTransform = glm::perspective(35.0f, 1.0f, 0.1f, 100.0f);

	CameraNodeData *pCameraNode = new CameraNodeData(cameraId, cameraParentId, cameraChildIdSet, viewTransform, projectionTransform);

	// -------------------------------------------------------------------------------------------------------------------

	GUID shaderParentId = cameraId;
	std::vector<GUID> shaderChilIdSet;
	shaderChilIdSet.push_back(modelId);
	std::string vertexShaderName = "C:/OpenGL_SDL_Sln/OpenGL_SDL_Sln/OpenGL_SDL_Sln/Shader/TransformVertexShader.vertexshader";
	std::string fragmentShaderName = "C:/OpenGL_SDL_Sln/OpenGL_SDL_Sln/OpenGL_SDL_Sln/Shader/TextureFragmentShader.fragmentshader";
	std::vector<std::string> uniformNames;
	uniformNames.push_back("MVP");
	uniformNames.push_back("myTextureSampler");
	std::vector<std::string> attributeNames;
	attributeNames.push_back("vertexPosition_modelspace");
	attributeNames.push_back("vertexUV");

	ShaderNodeData * pShaderNode = new ShaderNodeData(shaderId, shaderParentId, shaderChilIdSet,
		vertexShaderName, fragmentShaderName, uniformNames, attributeNames);

	// -------------------------------------------------------------------------------------------------------------------
	GUID modelParentId = shaderId;
	std::vector<GUID> modelChildIdSet;
	std::string objectFilename = "C:/OpenGL_SDL_Sln/OpenGL_SDL_Sln/Debug/data/obj/capsule/capsule.obj";
	//std::string textureFilename = "C:/OpenGL_SDL_Sln/OpenGL_SDL_Sln/Debug/data/obj/capsule/capsule0.jpg";
	std::string textureFilename = "C:/OpenGL_SDL_Sln/OpenGL_SDL_Sln/Debug/data/obj/capsule/capsule0Square.jpg";

	std::map<UniformType, std::string> uniformTypeNameSet;
	uniformTypeNameSet.insert(std::pair<UniformType, std::string>(UniformType::ModelViewProjectionMatrix, "MVP"));
	uniformTypeNameSet.insert(std::pair<UniformType, std::string>(UniformType::Texture2D00, "myTextureSampler"));

	std::map<AttributeType, std::string> attributeTypeNameSet;
	attributeTypeNameSet.insert(std::pair<AttributeType, std::string>(AttributeType::CoordCart, "vertexPosition_modelspace"));
	attributeTypeNameSet.insert(std::pair<AttributeType, std::string>(AttributeType::CoordTex, "vertexUV"));
	attributeTypeNameSet.insert(std::pair<AttributeType, std::string>(AttributeType::NormCart, "NormCart"));

	ModelNodeData * pModelNode = new ModelNodeData(modelId, modelParentId, modelChildIdSet, objectFilename, textureFilename, uniformTypeNameSet, attributeTypeNameSet);
	// -------------------------------------------------------------------------------------------------------------------

	sceneNodeDataSet.push_back(pViewPortNode);
	sceneNodeDataSet.push_back(pCameraNode);

	sceneNodeDataSet.push_back(pShaderNode);
	sceneNodeDataSet.push_back(pModelNode);

	// -------------------------------------------------------------------------------------------------------------------

	return sceneNodeDataSet;
}


bool RenderLoop(RenderingEngine *pRenderEngine, SDL_Window *window)
{
	// TODO: do the loop and SDL-Event Handling

	bool succ = true;

	// ViewPort-Setup
	// TODO: move to own Node !!!

	// EXTREME HACK
	static const GLfloat gray[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const GLfloat ones[] = { 1.0f };
	glViewport(0, 0, 512, 512);

	glEnable(GL_DEPTH_TEST);

	//Event handler
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
			return true;

		glClearBufferfv(GL_COLOR, 0, gray);
		glClearBufferfv(GL_DEPTH, 0, ones);

		succ = pRenderEngine->Render();

		SDL_GL_SwapWindow(window);
		// TEST
		SDL_Delay(2000);

		/* Same as above, but blue */
		glClearColor(0.0, 0.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
		SDL_Delay(2000);
	}

	return true;
}