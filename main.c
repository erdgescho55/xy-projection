#include <SDL3/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60

struct Vec2
{
  float x;
  float y;
};

struct Vec3
{
  float x;
  float y;
  float z;
};

void loop(SDL_Renderer *r);
void drawPoint(SDL_Renderer *r, struct Vec2 point);
struct Vec2 convertToScreenCoordinates(struct Vec2 point);
struct Vec2 projectToScreen(struct Vec3 point);

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
  float dt = 1. / FPS;
  float dz = 0;

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

    dz += 1 * dt;

    SDL_SetRenderDrawColor(r, 24, 24, 24, 255);
    SDL_RenderClear(r);

    drawPoint(r, convertToScreenCoordinates(
                     projectToScreen((struct Vec3){0.5, 0.5, 1 + dz})));
    drawPoint(r, convertToScreenCoordinates(
                     projectToScreen((struct Vec3){-0.5, 0.5, 1 + dz})));
    drawPoint(r, convertToScreenCoordinates(
                     projectToScreen((struct Vec3){-0.5, -0.5, 1 + dz})));
    drawPoint(r, convertToScreenCoordinates(
                     projectToScreen((struct Vec3){0.5, -0.5, 1 + dz})));

    SDL_RenderPresent(r);
  }
}

void drawPoint(SDL_Renderer *r, struct Vec2 point)
{
  float size = 20;

  SDL_SetRenderDrawColor(r, 80, 255, 80, 255);
  SDL_RenderFillRect(
      r, &(SDL_FRect){point.x - size / 2, point.y - size / 2, size, size});
}

struct Vec2 convertToScreenCoordinates(struct Vec2 point)
{
  // -1..1 => 0..2 => 0..1 => 0..w/h

  return (struct Vec2){
      .x = (point.x + 1) / 2 * WINDOW_WIDTH,
      .y = (1 - (point.y + 1) / 2) * WINDOW_HEIGHT,
  };
}

struct Vec2 projectToScreen(struct Vec3 point)
{
  return (struct Vec2){
      .x = point.x / point.z,
      .y = point.y / point.z,
  };
}
