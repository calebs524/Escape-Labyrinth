#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change this constant to contain your full first and last name (middle is ok too).
 *
 * WARNING: Once you've set set this constant and started exploring your maze,
 * do NOT edit the value of kYourName. Changing kYourName will change which
 * maze you get back, which might invalidate all your hard work!
 */
const string kYourName = "Caleb Satvedi";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "EWSSSEENNNSEN";
const string kPathOutOfTwistyMaze = "SENSWNSNWNNE";
//Function takes in string, and 3 booleans(as ref. parameters)
//bools correlate to if items have been found
//string is whatever is at the cell
void checker (string present, bool& spellBook, bool& wand, bool& potion){
if(present != "" ){
			if(present == "Potion"){
				potion = true;
			}
			 if(present == "Spellbook"){
				spellBook = true;
			}
			 if(present == "Wand"){
				wand = true;
			}
		}	
} 
//Takes in moves as a string and a mazecell as a pointer
//tells us if the moves gives us the 3 items or not
bool isPathToFreedom(MazeCell *start, const string& moves) {
	//set the bools all to false for the items
	bool spellBook = false;
	bool wand = false;
	bool potion = false;
	//no moves, meaning you don't go anywhere
	if(moves.size() == 0){
		return false;	}
	string present = "";
	//curr pointer as the start
	MazeCell * curr = start;
	//for loop to go through each move
	for(int i = 0; i < moves.size(); i++){
		//check what item is there
		 present = curr-> whatsHere;
		 //call checker function to change item 
		 //status if needed
		 checker(present, spellBook, wand, potion);
		 //if invalid move, then return false
		if((moves[i] != 'N')&&(moves[i] != 'S')&&(moves[i] != 'E')&&(moves[i] != 'W')){
			return false;		}
			//if you go somewhere you shouldn't, then return false
		if(moves[i] == 'N'){
			if(curr-> north == nullptr){
				return false;			}
			curr = curr -> north;		}
				else if(moves[i] == 'S'){
			if(curr -> south == nullptr){
				return false;			}
			 curr = curr -> south;		}
				else if(moves[i] == 'E'){
			if(curr -> east == nullptr){
				return false;			}
			curr = curr -> east;		}
				else if(moves[i] == 'W'){
			if(curr-> west == nullptr){
				return false;			}
			curr = curr -> west;		}	}
			//check very last node after last move
		 present = curr-> whatsHere;
		 checker(present, spellBook, wand, potion);
		 //return if all 3 items were found
	return (spellBook && wand&&potion);
}
