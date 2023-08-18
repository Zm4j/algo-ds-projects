#include <vector>
#include <string>
#pragma once

class Rtree
{
private:
	int m, M; // min and max
	int BoundL, BoundR, BoundU, BoundD; // bounds of this MBR
	std::vector<Rtree*> children;
	Rtree* parent = nullptr;
	//Rtree* head = this;
	
	void printNode(Rtree* head, int=0);
	void RtreeAdd(int Up, int Left, int Down, int Right); //add element in tree with coordiantes
	void RtreeAdd(Rtree* x); //add element in tree with coordiantes

public:
	Rtree(int, int, int= INT_MIN, int= INT_MAX, int= INT_MAX, int= INT_MIN);
	void printTree();
	void add(int Up, int Left, int Down=INT_MIN, int Right=INT_MIN);
	void search(int Up, int Left, int Down, int Right); //search elemnt in tree with coordinates
	void readfile(std::string name);
	void printTreeLevel(int lvl);
};

