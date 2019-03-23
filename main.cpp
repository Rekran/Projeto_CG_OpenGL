// Include AssImp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <SDL2/SDL.h>
#include "display.h"

// Include GLEW
#include <GL/glew.h>

#include "object.h"

#include"objloader.h"
using namespace std;
using namespace glm;

int DISPLAY_WIDTH = 1080;
int DISPLAY_HEIGHT = 920;

	bool isRunning = true;
	float pos[]={ 0.0f ,0.0f, 5.0f};//posição da camera





//Interação do usuario
void processEvents(object *o){
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0){
        switch (event.type){
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                //Eventod de tecla pressionada aqui
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    isRunning = false;
                }
                if(event.key.keysym.sym == SDLK_DOWN){
           			pos[2]-=0.1;
                }
                if(event.key.keysym.sym == SDLK_UP){
                 	pos[2]+=0.1;   
                }
                if(event.key.keysym.sym == SDLK_RIGHT){
                    pos[0]+=0.1;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    pos[0]-=0.1;
                }
                if(event.key.keysym.sym == SDLK_u){
                    pos[1]+=0.1;
                }
                if(event.key.keysym.sym == SDLK_d){
                    pos[1]-=0.1;
                }
                if(event.key.keysym.sym == SDLK_r){
                    pos[0]=0.0;
                    pos[1]=0.0;
                    pos[2]=5.0;
                }
                break;
            case SDL_KEYUP:
                //Eventod de tecla solta aqui
                break;
            case SDL_MOUSEBUTTONDOWN:
                //Eventos de botão do mouse pressionado aqui
                break;
            case SDL_MOUSEBUTTONUP:
                //Eventos de botão do mouse solto aqui
                break;
            case SDL_MOUSEMOTION:
                //Eventos de movimentação do mouse aqui            	
                break;
            case SDL_MOUSEWHEEL:
                //Eventos de movimentação da roldana do mouse aqui
                break;
            case SDL_WINDOWEVENT:
      			break;
        }
    }
}






int main(int argc, char** argv)
{	

	object Yoda;
	Yoda.import("Yoda.obj");
	

	float rot = 0.0f;

	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 5.0, 0.0, 2.0, 0.0 };

   



while(isRunning){	

//define a luz
glShadeModel (GL_SMOOTH);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);

glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_DEPTH_TEST);

//pega interação
processEvents(&Yoda);



//limpando a tela
display.Clear(1.0f, 1.0f, 1.0f, 1.0f);




glMatrixMode(GL_MODELVIEW);
glLoadIdentity();


glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(55.0f,DISPLAY_WIDTH/DISPLAY_HEIGHT,1.1f,100.f);


gluLookAt(  pos[0],pos[1],pos[2], //posição
			0.0f,0.0f,0.0f, //olhando para
			0.0f,1.0f,0.0f); //up

	
Yoda.drawObj();
	
display.SwapBuffers();

}


	return 0;
}
