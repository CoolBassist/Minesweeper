//
//  main.cpp
//  MineSweeper
//
//  Created by Joe Errey on 31/12/2018.
//  Copyright © 2018 Joe Errey. All rights reserved.
//

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Block.hpp"

std::string getMinesAround(int x, int y, Block map[10][10]);

int main() {
	sf::RenderWindow window(sf::VideoMode (800, 800), "Mine Sweeper");
	sf::Font font;
	sf::RectangleShape visualmap[10][10];
	Block map[10][10];
	
	if (!font.loadFromFile("/Users/joeerrey/Desktop/font.ttf")) {
		return EXIT_FAILURE;
	}
	
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			visualmap[i][j].setSize(sf::Vector2f(80.f, 80.f));
			visualmap[i][j].setFillColor(sf::Color::Blue);
			visualmap[i][j].setPosition(i*80, j*80);
		}
	}
	
	int bombs_placed = 0;
	
	srand((unsigned)time(0));
	
	while(bombs_placed != 10)
	{
		
		int i = rand()%10;
		int j = rand()%10;
		
		if(!map[i][j].getMine())
		{
			map[i][j].setMine();
			bombs_placed++;
		}
	}
	
	
	
	while(window.isOpen())
	{
		sf::Event event;
		
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					sf::Vector2i localPosition = sf::Mouse::getPosition(window);
					switch(event.mouseButton.button)
					{
						case sf::Mouse::Left:
							if(map[localPosition.x/80][localPosition.y/80].getMine())
							{
								std::cout << "Game over!" << std::endl;
								return 0;
							}
							getMinesAround(localPosition.x/80, localPosition.y/80, map);
							break;
							
						case sf::Mouse::Right:
							map[localPosition.x/80][localPosition.y/80].setMarked();
							break;
					}
			}
		}
	
						
	window.clear();
						
	//draw objects below
	
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			window.draw(visualmap[i][j]);
			if(map[i][j].getRevealed())
			{
				visualmap[i][j].setFillColor(sf::Color::Green);
				if(getMinesAround(i,j,map) != "0")
				{
					sf::Text text(getMinesAround(i,j, map), font, 30);
					text.setPosition(i*80 + 40, j*80 + 40);
					text.setFillColor(sf::Color::White);
					window.draw(text);
				}
			}else if(map[i][j].getMarked())
			{
				visualmap[i][j].setFillColor(sf::Color::Yellow);
			}else
			{
				visualmap[i][j].setFillColor(sf::Color::Blue);
			}
		}
	}
	
	window.display();
	}
						
	return 0;
}

std::string getMinesAround(int x, int y, Block map[10][10])
{
	map[x][y].setRevealed();
	
	
	if((x > 9) || (x < 0) || (y > 9) || (y < 0))
	{
		return "";
	}
	
	int total = 0;
	
	if(x-1 >= 0)
	{
		if(y-1 >= 0)
			if(map[x-1][y-1].getMine())
				total++;
		if(map[x-1][y].getMine())
			total++;
		if(y+1 <= 9)
			if(map[x-1][y+1].getMine())
				total++;
	}
	
	if(y-1 >= 0)
		if(map[x][y-1].getMine())
			total++;
	if(y+1 <= 9)
		if(map[x][y+1].getMine())
			total++;
	
	
	if(x+1 <= 9)
	{
		if(y-1 >= 0)
			if(map[x+1][y-1].getMine())
				total++;
		if(map[x+1][y].getMine())
			total++;
		if(y+1 <= 9)
			if(map[x+1][y+1].getMine())
				total++;
	}
	
	if(total == 0)
	{
		if(y-1 >= 0)
			if(!map[x-1][y-1].getRevealed())
				getMinesAround(x-1, y-1, map);
		if(!map[x-1][y].getRevealed())
			getMinesAround(x-1, y, map);
		if(y+1 <= 9)
			if(!map[x-1][y+1].getRevealed())
				getMinesAround(x-1, y+1, map);
		
		
		if(y-1 >= 0)
			if(!map[x][y-1].getRevealed())
				getMinesAround(x, y-1, map);
		if(y+1 <= 9)
			if(!map[x][y+1].getRevealed())
				getMinesAround(x, y+1, map);
		
		
		if(x+1 <= 9)
		{
			if(y-1 >= 0)
				if(!map[x+1][y-1].getRevealed())
					getMinesAround(x+1, y-1, map);
			if(!map[x+1][y].getRevealed())
				getMinesAround(x+1, y, map);
			if(y+1 <= 9)
				if(!map[x+1][y+1].getRevealed())
					getMinesAround(x+1, y+1, map);
		}
	}

	
	return std::to_string(total);
}
