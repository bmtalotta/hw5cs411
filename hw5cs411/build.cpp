//build.cpp
//Ben Talotta
//11/16/2020
//for use in cs411 hw 5
#include "build.hpp"
using std::vector;
using std::max;
//based on RobotCoinCollection from textbook pg.289 Introduction to the Designand Analysis of Algorithms
//Applies dynamic programming to compute the largest number of  
//coins a robot can collect on an n × m board by starting at (1, 1)  
//and moving right and down from upper left to down right corner  
//Input: Matrix C[1..n, 1..m] whose elements are equal to 1 and 0  
//for cells with and without a coin, respectively 
//Output: Largest number of coins the robot can bring to cell (n, m) 
int build(int w, int e, const std::vector<Bridge>& bridges)
{
	vector<vector<int>> organizeBridges(w, vector<int>(e,0));
	vector<vector<int>> recVals(w,vector<int>(e));
	for (auto bridge : bridges) {
		organizeBridges[bridge[0]][bridge[1]] = max(organizeBridges[bridge[0]][bridge[1]], bridge[2]);
	}
	
	for (int col = 0; col < w; ++col) {
		for (int row = 0; row < e; ++row) {
			if (col == 0 && row == 0) {
				recVals[0][0] = organizeBridges[0][0];
			}
			else {
				if (col != 0 && row != 0) {
					recVals[col][row] = max(max(recVals[col - 1][row], recVals[col-1][row-1] + organizeBridges[col][row]), max(recVals[col][row - 1], organizeBridges[col][row]));
				}
				else if (col != 0) {
					recVals[col][row] = max(recVals[col - 1][row], organizeBridges[col][row]);
				}
				else if (row != 0) {
					recVals[col][row] = max(recVals[col][row - 1], organizeBridges[col][row]);
				}
			}
		}
	}

	return recVals[w-1][e-1];
}
