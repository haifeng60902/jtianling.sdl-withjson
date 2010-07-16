#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include "SDL.h"
#include "SDL_opengl.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
//OpenGL初始化开始
void SceneInit(int  w,int  h)
{
  glClearColor(0.0f , 0.0f , 0.0f , 0.0f );      // 黑色背景
  glColor3f(1.0f , 1.0f , 1.0f );

  glShadeModel(GL_FLAT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-50.0f , 50.0f , -50.0f , 50.0f , -1.0f , 1.0f );
}

//这里进行所有的绘图工作
void  SceneShow(GLvoid) {
  // 旋转角度

  static  float  fSpin = 0.0f ;

  fSpin += 2.0f ;

  if (fSpin > 360.0f ) {
    fSpin -= 360.0f ;
  }

  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();

  // 旋转矩形的主要函数
  glRotatef(fSpin, 0.0f , 0.0f , 1.0f );
  glRectf(-25.0 , -25.0 , 25.0 , 25.0 );
  glPopMatrix();
}  

int _tmain(int argc, _TCHAR* argv[])
{
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
  {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());

    exit(1);
  }
  atexit(SDL_Quit);

  // use these two lines instead of the commented one
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*
  SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_OPENGL); // *changed* 
  //SDL_Surface *screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_DOUBLEBUF);

  SceneInit(WINDOW_WIDTH, WINDOW_HEIGHT);

  // main loop
  bool running = true;
  while (running) {
    //While there's an event to handle 
    SDL_Event event; 
    while( SDL_PollEvent( &event ) ) { 
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    SceneShow();
    //Update Screen 
    // use this line instead of the commented one
    SDL_GL_SwapBuffers();
    //SDL_Flip( screen ); 

    // delay, 50 for simple
    SDL_Delay( 50 ); 

  }

	return 1;
}
