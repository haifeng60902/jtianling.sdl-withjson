#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include "SDL.h"
#include "SDL_image.h"
int _tmain(int argc, _TCHAR* argv[])
{
  if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) 
  {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());

    exit(1);
  }
  if (IMG_Init(IMG_INIT_PNG) == 0 ) {
    printf("Unable to initialize SDL_image");

    exit(1);
  }
  atexit(SDL_Quit);

  //Load image 
  //SDL_Surface* picture = SDL_LoadBMP( "dragon.bmp" ); 
  SDL_Surface* picture = IMG_Load("dragon.png");

  SDL_Surface *screen = SDL_SetVideoMode(640, 480, 16, SDL_DOUBLEBUF);
  if ( screen == NULL ) 
  {
    printf("Unable to set video mode: %s\n", SDL_GetError());

    exit(1);
  }

  // because we use png with alpha now
  //Uint32 colorKey = SDL_MapRGB(picture->format, 0xFF, 0xFF, 0xFF);
  //SDL_SetColorKey(picture, SDL_SRCCOLORKEY, colorKey);

  //Apply image to screen 
  SDL_BlitSurface( picture, NULL, screen, NULL ); 

  SDL_Rect dest;
  dest.x = picture->w;
  dest.y = 0;

  //Apply image to screen again and move it to right
  SDL_BlitSurface( picture, NULL, screen, &dest ); 

  // main loop
  bool running = true;
  while (running) {
    //Update Screen 
    SDL_Flip( screen ); 

    // delay, 50 for simple
    SDL_Delay( 50 ); 

    //While there's an event to handle 
    SDL_Event event; 
    while( SDL_PollEvent( &event ) ) { 
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }
  }

  //Free the loaded image 
  SDL_FreeSurface( picture ); 

	return 1;
}
