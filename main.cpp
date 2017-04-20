#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <stdio.h>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


// Definition of reels
sf::Texture reel1[8];
sf::Texture reel2[8];
sf::Texture reel3[8];
// Definition of temporary array
sf::Texture tempArray[8];
// Sprite array
sf::Sprite sprites[9];
// Array for shuffuled reel
std::array<int,8> imgs {1,2,3,4,5,6,7,8};

bool roll = true;
bool anounceWinner = false;

// Functions
void loadReeels();
void setSpritesOrigin();
void setSpritesPositions();
void shift(int pos, sf::Texture *arr);
void checkWin();

int main(int argc, char const *argv[]) {
  sf::RenderWindow window(sf::VideoMode(900, 1000), "Test application");

  loadReeels();
  setSpritesOrigin();
  setSpritesPositions();

  int cont = 1;
  while (window.isOpen())
	{
		sf::Event event;
      // Wait for events generated by the window
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
      // Check if key is pressed
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::S)
        {
          roll = false;


        }
        if (event.key.code == sf::Keyboard::R)
        {
          roll = true;
          anounceWinner = false;

        }

      }
		}

    // Clean the previous frame
		window.clear(sf::Color::White);

    sprites[0].setTexture(reel1[3]);
    sprites[1].setTexture(reel1[4]);
    sprites[2].setTexture(reel1[5]);
    sprites[3].setTexture(reel2[3]);
    sprites[4].setTexture(reel2[4]);
    sprites[5].setTexture(reel2[5]);
    sprites[6].setTexture(reel3[3]);
    sprites[7].setTexture(reel3[4]);
    sprites[8].setTexture(reel3[5]);
    for (int i = 0; i < 9; i++)
    {
      window.draw(sprites[i]);
    }


    if(roll)
    {
      shift(1, reel1);
      shift(3, reel2);
      shift(5, reel3);
    }
    else
    {
      checkWin();
    }

		window.display();
	}

  return 0;
}

void loadReeels()
{
  char file[10];
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle (imgs.begin(), imgs.end(), std::default_random_engine(seed));

  for (int i = 1; i < 9; i++)
  {
    sprintf(file, "img-%d.png", i);
    reel1[i-1].loadFromFile(file);
    sprintf(file, "img-%d.png", 9-i);
    reel2[i-1].loadFromFile(file);
    sprintf(file, "img-%d.png", imgs[i-1]);
    std::cout << imgs[i-1] << std::endl;
    reel3[i-1].loadFromFile(file);
  }
}

void setSpritesOrigin()
{
  for(int i = 0; i < 9; i++)
  {
    sprites[i].setOrigin(0,0);
  }
}

void setSpritesPositions()
{
  sprites[0].setPosition(sf::Vector2f(0, 0));
  sprites[1].setPosition(sf::Vector2f(0, 250));
  sprites[2].setPosition(sf::Vector2f(0, 500));
  sprites[3].setPosition(sf::Vector2f(300, 0));
  sprites[4].setPosition(sf::Vector2f(300, 250));
  sprites[5].setPosition(sf::Vector2f(300, 500));
  sprites[6].setPosition(sf::Vector2f(600, 0));
  sprites[7].setPosition(sf::Vector2f(600, 250));
  sprites[8].setPosition(sf::Vector2f(600, 500));
}

void shift(int pos, sf::Texture *arr)
{
  int newpos;

  for (int j = 0; j < 8; j++)
  {
    tempArray[j] = arr[j];
  }

  // Iterate through the array and move it's conent to it's new position in the reel
  for (int i = 0; i < 8; i++)
  {
    newpos = i+pos;
    if(newpos < 8)
    {
      arr[i] = tempArray[newpos];
    }
    else if (newpos >= 8)
    {
      arr[i] = tempArray[newpos-8];
    }
  }

}

void checkWin()
{
  if(!anounceWinner)
  {
    // if (reel1pos2 == reel2pos2 && reel3pos2 == reel1pos2)
    // {
    //   std::cout << "You won" << std::endl;
    // }
    anounceWinner = true;
  }

}
