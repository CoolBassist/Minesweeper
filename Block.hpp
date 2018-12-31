//
//  Block.hpp
//  MineSweeper
//
//  Created by Joe Errey on 31/12/2018.
//  Copyright © 2018 Joe Errey. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

class Block
{
public:
	void setMine();
	void setMarked();
	void setRevealed();
	
	bool getMine();
	bool getMarked();
	bool getRevealed();
	
private:
	bool isMine = false;
	bool isMarked = false;
	bool isRevealed = false;
	bool isHidden = true;
};

#endif /* Block_hpp */
