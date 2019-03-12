#include "SDL2/SDL.h"
#include <iostream>
#include <vector>

using namespace std;
//g++ -o line.exe line.cpp -lmingw32 -lSDL2main -lSDL2



//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = 800;
//const int GRID_SIZE = 10;
//const int ROWS = SCREEN_HEIGHT / GRID_SIZE;
//const int COLS = SCREEN_WIDTH / GRID_SIZE;

//int RECT_COUNT = (SCREEN_WIDTH * SCREEN_HEIGHT / GRID_SIZE);

void drawRect(int row, int col, SDL_Renderer* renderer, int GRID_SIZE);
void displayCells(vector<vector<int> > seed, SDL_Renderer* renderer, int GRID_SIZE);
void nextGeneration(vector<vector<int> > &seed);

int main(int argc, char* argv[])
{
  int SCREEN_WIDTH;
  int SCREEN_HEIGHT;
  int GRID_SIZE;
 
  cout << "SCREEN_WIDTH: ";
	  cin >> SCREEN_WIDTH;
  cout << "SCREEN_HEIGHT: ";
  cin >> SCREEN_HEIGHT;
  cout << "GRID_SIZE: ";
  cin >> GRID_SIZE;

  int ROWS = SCREEN_HEIGHT / GRID_SIZE;
  int COLS = SCREEN_WIDTH / GRID_SIZE;
  int RECT_COUNT = (SCREEN_WIDTH * SCREEN_HEIGHT / GRID_SIZE);
  bool click = false;
    
  int x,y;
  vector <vector<int> > seed(ROWS, vector<int>(COLS));

  
  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 50, 20, 200, 100);

		for (int i = 0; i < SCREEN_WIDTH; i += GRID_SIZE)
		  {
		    
		    SDL_RenderDrawLine(renderer, i,0,i,SCREEN_HEIGHT);		    
		  }
		for (int j = 0; j < SCREEN_HEIGHT; j += GRID_SIZE)
		  {
		    SDL_RenderDrawLine(renderer, 0,j,SCREEN_WIDTH,j);
		  }

			      
	        
                while (SDL_PollEvent(&event)) {
                    
		    switch (event.type){
		      case SDL_QUIT :
		        done = SDL_TRUE;
		        break;

		      case SDL_KEYDOWN:			
			//displayCells(seed, renderer);
			//SDL_RenderPresent(renderer);
			nextGeneration(seed);
		        break;

		      case SDL_MOUSEBUTTONDOWN:			
			SDL_GetMouseState(&x,&y);
			seed[y/GRID_SIZE][x/GRID_SIZE] = 1;
			click = true;
			//cout << x << ", " << y << endl;
			break;
		    case SDL_MOUSEMOTION:
		      
		      if (click == true)
			{
			  SDL_GetMouseState(&x,&y);
			  if (seed[y/GRID_SIZE][x/GRID_SIZE] == 0)
			    {
			      seed[y/GRID_SIZE][x/GRID_SIZE] = 1;
			    }
			  else
			    {
			      seed[y/GRID_SIZE][x/GRID_SIZE] = 0;
			    }
			  
			  //seed[y/GRID_SIZE][x/GRID_SIZE] = 1;
			}
		      break;

		    case SDL_MOUSEBUTTONUP:
		      click = false;
		      break;

		    default:
		        break;
                }
		}
		displayCells(seed,renderer, GRID_SIZE);
		SDL_RenderPresent(renderer);
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}

void drawRect(int row, int col, SDL_Renderer* renderer, int GRID_SIZE)
{
  SDL_Rect rect;
  rect.x = col * GRID_SIZE + (GRID_SIZE / 3);
  rect.y = row * GRID_SIZE + (GRID_SIZE / 3);
  rect.w = GRID_SIZE - (GRID_SIZE / 2);
  rect.h = GRID_SIZE - (GRID_SIZE / 2);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &rect);
}

void displayCells(vector<vector<int> > seed, SDL_Renderer* renderer, int GRID_SIZE)
{
  for (int i = 0; i < seed.size(); i++)
    {
      for (int j = 0; j < seed[0].size(); j++)
	{
	  if (seed[i][j] == 1)
	    {	      
	      drawRect(i,j,renderer, GRID_SIZE);
	    }
	}
    }
 
}

void nextGeneration(vector<vector<int> > &seed)
{
  
  vector<vector<int> > prevGen = seed;
  int neighborSum = 0;
  
  for (int i = 0; i < seed.size(); i++)
    {
      for (int j = 0; j < seed[0].size(); j++)
	{
	  
	  neighborSum = 0;
	  if (i > 0){
	  neighborSum += prevGen[i-1][j-1]; // above left
	  neighborSum += prevGen[i-1][j];   // above middle
	  neighborSum += prevGen[i-1][j+1]; // above right
	  }
	  neighborSum += prevGen[i][j-1];   // middle left
	  neighborSum += prevGen[i][j+1];   // middle right
	  if (i < seed.size()-1){
	  neighborSum += prevGen[i+1][j-1]; // below left
	  neighborSum += prevGen[i+1][j];   // below middle
	  neighborSum += prevGen[i+1][j+1]; // below right
	  }
	  
          
	  if (neighborSum < 2)
	    seed[i][j] = 0;
	  else if ((neighborSum == 2) && (prevGen[i][j] == 1))
	    seed[i][j] = 1;
	  else if (neighborSum == 3)
	    seed[i][j] = 1;
	  else if (neighborSum > 3)
	    seed[i][j] = 0;
	  
	}
    }
  
}
