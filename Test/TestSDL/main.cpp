#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "json/json.h"
#include <string>
#include <fstream>
#include <cassert>
#include <vector>

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300

using namespace std;
struct PictureInfo {
  string name;
  float rotation;
  float positionX;
  float positionY;
  float scaleX;
  float scaleY;

  // can't read from config,read from surface
  int width;
  int height;
  GLuint texName;
};

// didn't care about efficiency too much as a demo
vector<PictureInfo> gPictureInfoVec;

void ReadPictureInfo() {
  Json::Reader reader;
  ifstream file("picture.json");
  assert(file.is_open());
  Json::Value root;
  if (!reader.parse(file, root, false)) {
    printf("Parse error");
    exit(1);
  }

  assert(root.isArray());
  PictureInfo info;
  int size = root.size();
  for (int i = 0; i < size; ++i) {
    Json::Value &current = root[i];
    info.name = current["name"].asString();
    info.rotation = (float)current["rotation"].asDouble();
    info.positionX = (float)current["positionX"].asDouble();
    info.positionY = (float)current["positionY"].asDouble();
    info.scaleX = (float)current["scaleX"].asDouble();
    info.scaleY = (float)current["scaleY"].asDouble();
    gPictureInfoVec.push_back(info);
  }
}

void PictureInit() {
  ReadPictureInfo();
}

//OpenGL初始化开始
void SceneInit(int  w,int  h)
{
  glClearColor (0.0f , 0.0f , 0.0f , 0.0 );

  // make the world as 2D screen space
  glViewport(0, 0, w, h);
  //gluOrtho2D(0, w, h, 0);
  glShadeModel(GL_FLAT);

  for (vector<PictureInfo>::iterator it = gPictureInfoVec.begin();
    it != gPictureInfoVec.end();
    ++it) {
      PictureInfo& info = *it;
      SDL_Surface *surface = IMG_Load(info.name.c_str());

      if (!surface)
      {
        printf("Load the picture failed:%s",info.name.c_str());
        exit(1);
      }

      info.width = surface->w;
      info.height = surface->h;
      GLenum texture_format;

      // get the number of channels in the SDL surface
      GLint nOfColors = surface->format->BytesPerPixel;
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
        exit(1);
      }

      glGenTextures(1  , &info.texName);
      glBindTexture(GL_TEXTURE_2D, info.texName);

      glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
        texture_format, GL_UNSIGNED_BYTE, surface->pixels );

      // Specify filtering and edge actions
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

      //Free the loaded image
      SDL_FreeSurface( surface ); 
  }

  glEnable(GL_DEPTH_TEST);
  glEnable( GL_TEXTURE_2D );
}

// display
void  SceneShow(GLvoid) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (vector<PictureInfo>::const_iterator it = gPictureInfoVec.begin();
    it != gPictureInfoVec.end();
    ++it) {
      const PictureInfo& info = *it;
      glBindTexture(GL_TEXTURE_2D, info.texName);

      glPushMatrix();
      glMatrixMode(GL_MODELVIEW);
      glTranslatef(info.positionX, info.positionY, 0);
      glScalef(info.scaleX, info.scaleY, 0.0);
      glRotatef(info.rotation, 0, 0, 1.0);

      glBegin(GL_QUADS);
      glTexCoord2f(0.0 , 1.0 ); glVertex3f(-1.0 , -1.0 , 0.0 );
      glTexCoord2f(1.0 , 1.0 ); glVertex3f(1.0 , -1.0 , 0.0 );
      glTexCoord2f(1.0 , 0.0 ); glVertex3f(1.0 , 1.0 , 0.0 );
      glTexCoord2f(0.0 , 0.0 ); glVertex3f(-1.0 , 1.0 , 0.0 );
      glEnd();

      glPopMatrix();
  }

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

  PictureInit();
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
    SDL_GL_SwapBuffers();

    // delay, 50 for simple
    SDL_Delay( 50 ); 
  }

	return 1;
}
