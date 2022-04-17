/* 
This file is the test cases I ran throughout my time developing this program.
I used google test suites to ensure that the code works correctly.
This file served as a way for me to know what to debug, as well as edge cases.
*/
#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include "maze.h"
#include "grid.h"
#include "EscapeTheLabyrinth.h"


TEST(grid, defaultConstructor){
    Grid<int>() maker;
    maker(0,0) = 1;
    ASSERT_EQ(maker(0,0), 1));
    ASSERT_EQ(maker.numrows(),4);
    ASSERT_EQ(maker.numcols(0),4);
    ASSERT_EQ(maker.size(), 16);
    ASSERT_EQ(maker(5,5), "Out Of Bounds");
}

TEST(grid, parameterizedConstructor){
	Grid<int>() maker(5,5);
	maker(0,0) = 1;
	ASSERT_EQ(maker(0,0), 1));
    ASSERT_EQ(maker.numrows(),5);
    ASSERT_EQ(maker.numcols(0),5);
    ASSERT_EQ(maker.size(), 25);
    ASSERT_EQ(maker(6,6), "Out Of Bounds");
    for(int i = 7; i < 107; i++){
    	  ASSERT_EQ(maker(i,i), "Out Of Bounds");
    }

TEST(grid, copyConstructor){
	Grid<int>() maker(5,5);
	Grid maker2 = maker;
	maker2(0,0) = 1;
	ASSERT_EQ(maker2(0,0), 1));
    ASSERT_EQ(maker2.numrows(),5);
    ASSERT_EQ(maker2.numcols(0),5);
    ASSERT_EQ(maker2.size(), 25);
    ASSERT_EQ(maker2(6,6), "Out Of Bounds");
	  for(int i = 7; i < 107; i++){
    	  ASSERT_EQ(maker2(i,i), "Out Of Bounds");
    }
}

TEST(maze, basic) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);

    MazeCell* start = m.getStart(2, 2);

    /* These paths are the ones in the handout. They all work. */
    cout<<"hi "<<endl;
    EXPECT_TRUE(isPathToFreedom(start, "ESNWWNNEWSSESWWN"));
    EXPECT_TRUE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES"));
    EXPECT_TRUE(isPathToFreedom(start, "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT_FALSE(isPathToFreedom(start, "ESNW"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWN"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNE"));

    // /* These paths don't work, since they aren't legal paths. */
    EXPECT_FALSE(isPathToFreedom(start, "WW"));
    EXPECT_FALSE(isPathToFreedom(start, "NN"));
    EXPECT_FALSE(isPathToFreedom(start, "EE"));
    EXPECT_FALSE(isPathToFreedom(start, "SS"));
}

TEST(maze, basic2) {
    vector<string> textMaze;

    textMaze.push_back("* *-S *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("P *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* W");

    Maze m(textMaze);

    MazeCell* start = m.getStart(3, 1);

    /* These paths are the ones in the handout. They all work. */
    EXPECT_TRUE(isPathToFreedom(start, "ESSWNNEWNWWESSWN"));
    EXPECT_TRUE(isPathToFreedom(start, "SEEEESEWSSNWWNWNNS"));
    EXPECT_TRUE(isPathToFreedom(start, "WSEENWNEWSNSEWNSES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT_FALSE(isPathToFreedom(start, "ENNS"));
    EXPECT_FALSE(isPathToFreedom(start, "SEWN"));
    EXPECT_FALSE(isPathToFreedom(start, "WSNE"));

    // /* These paths don't work, since they aren't legal paths. */
    EXPECT_FALSE(isPathToFreedom(start, "EW"));
    EXPECT_FALSE(isPathToFreedom(start, "NE"));
    EXPECT_FALSE(isPathToFreedom(start, "NE"));
    EXPECT_FALSE(isPathToFreedom(start, "SS"));
}

TEST(maze, tryingToGoThroughWalls) {
    vector<string> textMaze;

    textMaze.push_back("* S *");
    textMaze.push_back("     ");
    textMaze.push_back("W * P");
    textMaze.push_back( "     ");
    textMaze.push_back( "* * *");

    Maze m(textMaze);

    MazeCell* start = m.getStart(1, 1);

    EXPECT_FALSE(isPathToFreedom(start, "WNEES"));
    EXPECT_FALSE(isPathToFreedom(start, "NWSEE"));
    EXPECT_FALSE(isPathToFreedom(start, "ENWWS"));
    EXPECT_FALSE(isPathToFreedom(start, "SWNNEES"));
}

TEST(maze, startOnItem) {
    vector<string> textMaze;

    textMaze.push_back("P-S-W");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    EXPECT_TRUE(isPathToFreedom(start, "EE"));
    start = m.getStart(0, 1);
    EXPECT_TRUE(isPathToFreedom(start, "WEE"));
    start = m.getStart(0, 2);
    EXPECT_TRUE(isPathToFreedom(start, "WW"));

}

TEST(maze, invalidChar) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    /* These paths contain characters that aren't even close to permissible. */
    EXPECT_FALSE(isPathToFreedom(start, "Q"));
    EXPECT_FALSE(isPathToFreedom(start, "X"));
    EXPECT_FALSE(isPathToFreedom(start, "!"));
    EXPECT_FALSE(isPathToFreedom(start, "?"));

    EXPECT_FALSE(isPathToFreedom(start, "n"));
    EXPECT_FALSE(isPathToFreedom(start, "s"));
    EXPECT_FALSE(isPathToFreedom(start, "e"));
    EXPECT_FALSE(isPathToFreedom(start, "w"));

    ///* These are tricky - they're legal paths that happen to have an unexpected
    // * character at the end.
    start = m.getStart(2, 2);
    EXPECT_FALSE(isPathToFreedom(start, "ESNWWNNEWSSESWWNQ"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES!!!"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNEWSSESWWNSEENES??"));

}

TEST(maze, escapeRegularMaze) {
    Maze m(4, 4);
    MazeCell* start = m.mazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfRegularMaze));
}

TEST(maze, escapeTwistyMaze) {
    Maze m(4, 4);
    MazeCell* start = m.twistyMazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfTwistyMaze));
}

