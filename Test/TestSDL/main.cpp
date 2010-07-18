#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

GLuint gTexName;
//OpenGL初始化开始
void SceneInit(int  w,int  h)
{
  //glClearColor(0.0f , 0.0f , 0.0f , 0.0f );      // 黑色背景
  //glColor3f(1.0f , 1.0f , 1.0f );

  glViewport(0  ,0  , w, h);                      // Reset The Current Viewport

  //glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
  //glLoadIdentity();                                   // Reset The Projection Matrix

  //// Calculate The Aspect Ratio Of The Window
  //gluPerspective(45.0f  ,(GLfloat)w/(GLfloat)h,0.1f  ,100.0f  );

  //glMatrixMode(GL_MODELVIEW);                         // Select The Modelview Matrix
  //glLoadIdentity();                                   // Reset The Modelview Matrix

  //glClearColor(0.0f , 0.0f , 0.0f , 0.0f );      // 黑色背景
  //glColor3f(1.0f , 1.0f , 1.0f );

  glShadeModel(GL_FLAT);


  GLenum texture_format;
  GLint  nOfColors;

  SDL_Surface *surface = IMG_Load("dragon.png");
  //SDL_Surface *surface = SDL_LoadBMP("dragon.bmp");

  if (!surface)
  {
    printf("Load the picture failed.");
    exit(1);
  }
  // Check that the image's width is a power of 2
  if ( (surface->w & (surface->w - 1)) != 0 ) {
    printf("warning: image.bmp's width is not a power of 2\n");
  }

  // Also check if the height is a power of 2
  if ( (surface->h & (surface->h - 1)) != 0 ) {
    printf("warning: image.bmp's height is not a power of 2\n");
  }

  // get the number of channels in the SDL surface
  nOfColors = surface->format->BytesPerPixel;
  if (nOfColors == 4)     // contains an alpha channel
  {
    if (surface->format->Rmask == 0x000000ff)
      texture_format = GL_RGBA;
    else
      texture_format = GL_BGRA;
  } else if (nOfColors == 3)     // no alpha channel
  {
    if (surface->format->Rmask == 0x000000ff)
      texture_format = GL_RGB;
    else
      texture_format = GL_BGR;
  } else {
    printf("warning: the image is not truecolor..  this will probably break\n");
    // this error should not go unhandled
  }

  //glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
  glGenTextures(1  , &gTexName);
  glBindTexture(GL_TEXTURE_2D, gTexName);

  // Specify filtering and edge actions
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  //WINGDIAPI void APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);

  glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
    texture_format, GL_UNSIGNED_BYTE, surface->pixels );

  glEnable(GL_DEPTH_TEST);
  // Enable texturing
  glEnable( GL_TEXTURE_2D );
  
  //Free the loaded image
  SDL_FreeSurface( surface ); 
}

//这里进行所有的绘图工作
void  SceneShow(GLvoid) {
  //static  float  xrot = 0.0f ,yrot = 0.0f ,zrot = 0.0f ;
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glLoadIdentity();                                   // Reset The View
  //glTranslatef(0.0f  ,0.0f  ,-5.0f  );

  //glRotatef(xrot,1.0f  ,0.0f  ,0.0f  );
  //glRotatef(yrot,0.0f  ,1.0f  ,0.0f  );
  //glRotatef(zrot,0.0f  ,0.0f  ,1.0f  );

  //glBindTexture(GL_TEXTURE_2D, gTexName);

  //glBegin(GL_QUADS);
  //// Front Face
  //glTexCoord2f(0.0f  , 0.0f  ); glVertex3f(-1.0f  , -1.0f  ,  1.0f  );
  //glTexCoord2f(1.0f  , 0.0f  ); glVertex3f( 1.0f  , -1.0f  ,  1.0f  );
  //glTexCoord2f(1.0f  , 1.0f  ); glVertex3f( 1.0f  ,  1.0f  ,  1.0f  );
  //glTexCoord2f(0.0f  , 1.0f  ); glVertex3f(-1.0f  ,  1.0f  ,  1.0f  );
  //// Back Face
  //glTexCoord2f(1.0f  , 0.0f  ); glVertex3f(-1.0f  , -1.0f  , -1.0f  );
  //glTexCoord2f(1.0f  , 1.0f  ); glVertex3f(-1.0f  ,  1.0f  , -1.0f  );
  //glTexCoord2f(0.0f  , 1.0f  ); glVertex3f( 1.0f  ,  1.0f  , -1.0f  );
  //glTexCoord2f(0.0f  , 0.0f  ); glVertex3f( 1.0f  , -1.0f  , -1.0f  );
  //// Top Face
  //glTexCoord2f(0.0f  , 1.0f  ); glVertex3f(-1.0f  ,  1.0f  , -1.0f  );
  //glTexCoord2f(0.0f  , 0.0f  ); glVertex3f(-1.0f  ,  1.0f  ,  1.0f  );
  //glTexCoord2f(1.0f  , 0.0f  ); glVertex3f( 1.0f  ,  1.0f  ,  1.0f  );
  //glTexCoord2f(1.0f  , 1.0f  ); glVertex3f( 1.0f  ,  1.0f  , -1.0f  );
  //// Bottom Face
  //glTexCoord2f(1.0f  , 1.0f  ); glVertex3f(-1.0f  , -1.0f  , -1.0f  );
  //glTexCoord2f(0.0f  , 1.0f  ); glVertex3f( 1.0f  , -1.0f  , -1.0f  );
  //glTexCoord2f(0.0f  , 0.0f  ); glVertex3f( 1.0f  , -1.0f  ,  1.0f  );
  //glTexCoord2f(1.0f  , 0.0f  ); glVertex3f(-1.0f  , -1.0f  ,  1.0f  );
  //// Right face
  //glTexCoord2f(1.0f  , 0.0f  ); glVertex3f( 1.0f  , -1.0f  , -1.0f  );
  //glTexCoord2f(1.0f  , 1.0f  ); glVertex3f( 1.0f  ,  1.0f  , -1.0f  );
  //glTexCoord2f(0.0f  , 1.0f  ); glVertex3f( 1.0f  ,  1.0f  ,  1.0f  );
  //glTexCoord2f(0.0f  , 0.0f  ); glVertex3f( 1.0f  , -1.0f  ,  1.0f  );
  //// Left Face
  //glTexCoord2f(0.0f  , 0.0f  ); glVertex3f(-1.0f  , -1.0f  , -1.0f  );
  //glTexCoord2f(1.0f  , 0.0f  ); glVertex3f(-1.0f  , -1.0f  ,  1.0f  );
  //glTexCoord2f(1.0f  , 1.0f  ); glVertex3f(-1.0f  ,  1.0f  ,  1.0f  );
  //glTexCoord2f(0.0f  , 1.0f  ); glVertex3f(-1.0f  ,  1.0f  , -1.0f  );
  //glEnd();

  //xrot+=0.3f  ;
  //yrot+=0.2f  ;
  //zrot+=0.4f  ;

  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindTexture(GL_TEXTURE_2D, gTexName);

  glBegin(GL_QUADS);
  glTexCoord2f(0.0 , 0.0 ); glVertex3f(-1.0 , -1.0 , 0.0 );
  glTexCoord2f(1.0 , 0.0 ); glVertex3f(1.0 , -1.0 , 0.0 );
  glTexCoord2f(1.0 , 1.0 ); glVertex3f(1.0 , 1.0 , 0.0 );
  glTexCoord2f(0.0 , 1.0 ); glVertex3f(-1.0 , 1.0 , 0.0 );
  glEnd();

}  

int _tmain(int argc, _TCHAR* argv[])
{
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
  {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());

    exit(1);
  }
  atexit(SDL_Quit);

  if  (IMG_Init(IMG_INIT_PNG) == 0  ) {
    printf("Unable to initialize SDL_image" );

    exit(1);
  }

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
