//
//  Block.cpp
//  MineSweeper
//
//  Created by Joe Errey on 31/12/2018.
//  Copyright © 2018 Joe Errey. All rights reserved.
//

#include "Block.hpp"

void Block::setMine()
{
	isMine = true;
}

void Block::setMarked()
{
	isMarked = !isMarked;
}

void Block::setRevealed()
{
	isRevealed = true;
}

bool Block::getMine()
{
	return isMine;
}

bool Block::getMarked()
{
	return isMarked;
}

bool Block::getRevealed()
{
	return isRevealed;
}




