#include <SDL3/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void loop(SDL_Renderer *r);

int main()
{
  if (!SDL_Init(0))
  {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *w =
      SDL_CreateWindow("Demo x'=x/z", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!w)
  {
    SDL_Log("SDL_CreateWindow creation failed %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *r = SDL_CreateRenderer(w, NULL);
  if (!r)
  {
    SDL_Log("SDL_CreateRenderer failed %s", SDL_GetError());
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 1;
  }

  loop(r);

  SDL_DestroyRenderer(r);
  SDL_DestroyWindow(w);
  SDL_Quit();

  return 0;
}

void loop(SDL_Renderer *r)
{
  bool quit = false;

  SDL_Event event;

  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        quit = true;
      }
    }

    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);

    SDL_RenderClear(r);

    SDL_RenderPresent(r);
  }
}
