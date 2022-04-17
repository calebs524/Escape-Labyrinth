/*
Project 4- Labyrinth Escape
File- grid.h
Caleb Satvedi
CS 251 SP 2022
Description: This project is an attempt to make a "maze", where the user inputs
commands N, S, E, W to move through the maze. This grid class contains code for
how the maze is made. Basically, each cell is linked to the next cell
in a linked list form. This file is the design of the grid and her layout.
*/

#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Grid {
 private:
  struct CELL {
    CELL* Next;
    T Val;
    size_t NumCols;  // total # of columns (0..NumCols-1)
    CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
      Next = _Next;
      Val = _Val;
      NumCols = _NumCols;
    }
  };

  size_t NumRows;  // total # of rows (0..NumRows-1)
  CELL** Rows;     // C array of linked lists
 public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 Grid.  All
  // elements are initialized to the default value of T.
  //
  Grid() {
    // initialize 4 rows
    Rows = new CELL*[4];
    NumRows = 4;

    // allocate the first cell of the linked list with default value:
    for (size_t r = 0; r < NumRows; ++r) {
      Rows[r] = new CELL(nullptr, T(), 4);
      CELL* cur = Rows[r];

      // create the linked list for this row.
      for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
        cur->Next = new CELL(nullptr, T());
        cur = cur->Next;
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a Grid with R rows,
  // where each row has C columns. All elements are initialized to
  // the default value of T.
  //
  //Similar structure to the default constructor
  Grid(size_t R, size_t C) {
    Rows = new CELL*[R];
    NumRows = R;
    for (size_t i = 0; i < NumRows; i++) {
      Rows[i] = new CELL(nullptr, T(), C);
      CELL* curr = Rows[i];
      for (size_t j = 1; j < Rows[i]->NumCols; j++) {
        curr->Next = new CELL(nullptr, T());
        curr = curr->Next;
      }
    }
  }

  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated by the vector.
  //
  virtual ~Grid() {
    // nested loop to delete each cell
    //for loop goes through each row
    for (size_t i = 0; i < NumRows; i++) {
      CELL* curr = Rows[i];
      //while loop goes through each cell in said row
      while (curr != nullptr) {
        CELL* prev = curr;
        curr = curr->Next;
        delete prev;
      }
    }
    delete[] Rows;  // delete at the end of it all
  }

  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a Grid that contains a
  // copy of an existing Grid.  Example: this occurs when passing
  // Grid as a parameter by value
  //
  //   void somefunction(Grid<int> G2)  <--- G2 is a copy:
  //   { ... }
  //
  Grid(const Grid<T>& other) {
    // copy number of rows
    NumRows = other.NumRows;
    // create new array with the number of rows
    this->Rows = new CELL*[other.NumRows];
    // use for loop for the NumRows
    for (size_t i = 0; i < NumRows; i++) {
      // Use above constructor to set the row up
      Rows[i] = new CELL(nullptr, other.Rows[i]->Val, other.Rows[i]->NumCols);
      CELL* curr = Rows[i];
      CELL* OtherCurr = other.Rows[i];
      // use while loop to get each cell in the row set up
      while (OtherCurr->Next != nullptr) {
        // the node has been copied here
        curr->Next = new CELL(nullptr, OtherCurr->Next->Val, OtherCurr->Next->NumCols);
        curr = curr->Next;
        OtherCurr = OtherCurr->Next;
      }
    }
  }
	//called by copy operator, used to clear the grid object
	//very similar structure to destrctor
  void _clear() {
    for (size_t i = 0; i < NumRows; i++) {
      CELL* curr = Rows[i];
      while (curr != nullptr) {
        CELL* prev = curr;
        curr = curr->Next;
        delete prev;
      }
    }
    delete[] Rows;  
  }

  //
  // copy operator=
  //
  // Called when you assign one vector into another, i.e. this = other;
  //
  Grid& operator=(const Grid& other) {
  //check if they are equal
    if (this == &other) {
      return *this;
    }
    //clear current grid
    _clear();
    //set values equal to each other
    this->Rows = new CELL*[other.NumRows];
    NumRows = other.NumRows;
    //use for loop to get each row set up
    for (size_t i = 0; i < NumRows; i++) {
    	//Use constructor from above
      Rows[i] = new CELL(nullptr, other.Rows[i]->Val, other.Rows[i]->NumCols);
      CELL* curr = Rows[i];
      CELL* OtherCurr = other.Rows[i];
      //use while loop to get each cell in the row set up
      while (OtherCurr->Next != nullptr) {
      	//use constructor from above
        curr->Next = new CELL(nullptr, OtherCurr->Next->Val, OtherCurr->Next->NumCols);
        curr = curr->Next;
        OtherCurr = OtherCurr->Next;
      }
    }
    return *this; 
  }

  //
  // numrows
  //
  // Returns the # of rows in the Grid.  The indices for these rows
  // are 0..numrows-1.
  //
  size_t numrows() const {
    // just return the rows
    return NumRows;
  }

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  For now, each row will have the same number of columns.
  //
  size_t numcols(size_t r) const { return Rows[r]->NumCols; }

  //
  // size
  //
  // Returns the total # of elements in the grid.
  //
  size_t size() const {
    return NumRows * Rows[0]->NumCols;
  }

  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    grid(r, c) = ...
  //    cout << grid(r, c) << endl;
  //
  T& operator()(size_t r, size_t c) {
	//Contingency checks if r or c is out of Rows 
    if (r < 0 || r >= NumRows) {
      throw string("ROWS OUT OF BOUNDS!");
    }
    if (c < 0 || c >= Rows[r]->NumCols) {
      throw string("COLUMNS OUT OF BOUNDS!");
    }
    //Get to the right row
    CELL* curr = Rows[r];
    //Loop to the right Cell value 
    for (size_t j = 0; j < c; j++) {
      curr = curr->Next;
    }
    return curr->Val;  // just return the value here
  }

  //
  // _output
  //
  // Outputs the contents of the grid; for debugging purposes.  This is not
  // tested.
  //
  void _output() {
    for (size_t r = 0; r < NumRows; r++) {
      // pointer to the head of the linked list
      CELL* cur = Rows[r];
      for (size_t c = 0; c < Rows[r]->NumCols; c++) {
        cout << cur->Val;
        cout << " ";
        cur = cur->Next;
      }
      cout << endl;
    }
  }
};
