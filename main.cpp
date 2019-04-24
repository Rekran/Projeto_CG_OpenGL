// Include AssImp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include<cstdlib>

// Include GLEW
#include <GL/glew.h>

#include "display.h"
#include "object.h"
#include"objloader.h"

using namespace std;
using namespace glm;

int DISPLAY_WIDTH = 1080;
int DISPLAY_HEIGHT = 920;

	bool isRunning = true;
	float pos[]={ 0.0f ,0.0f, 5.0f};//posição da camera


double lastTime = 0;
int nbFrames = 0;
double currentTime = SDL_GetTicks();

int main(int argc, char** argv)
{

	object Yoda;
	Yoda.import("Yoda.obj");

    Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

 //define a luz
    float lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightPosition[]= {0.0f, 0.0f, 100.0f, 1.0f};

    float mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float mat_shininess[] = { 50.0f };

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0,GL_AMBIENT, lightAmbient);

    glLightfv(GL_LIGHT0,GL_DIFFUSE, lightDiffuse);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);




    glm::vec4 pos1 = glm::vec4(0.f, 0.f,1.f,0.f);

    // Yoda2.tras(rotate1);

    float x = 0.0f;


	while(isRunning){



	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//pega interação
	//processEvents(&Yoda);

	//limpando a tela
	display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0f,DISPLAY_WIDTH/DISPLAY_HEIGHT,1.1f,100.f);


	gluLookAt(  pos[0],pos[1],pos[2], //posição
				pos1[0],pos1[1],pos1[2], //olhando para
				0.0f,1.0f,0.0f); //up


	Yoda.drawObj();

SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type){
            case SDL_QUIT:
                std::exit(0);
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    std::exit(0);
                }
        }
    }

	display.SwapBuffers();


	// Measure speed
	currentTime = SDL_GetTicks();
	nbFrames++;

		if ( currentTime > lastTime + 1000 )
		{
		 // printf e reset
		    printf("%d fps\n",nbFrames);
		    nbFrames = 0;
		    lastTime = currentTime;
		}


	}


return 0;
}
