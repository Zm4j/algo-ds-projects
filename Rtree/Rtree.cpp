#include "Rtree.h"
#include <iostream>
#include <queue>
#include <fstream>
#include <fstream>
#include <string>
#include <sstream>

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

Rtree::Rtree(int m, int M, int U, int L, int D, int R) : m(m), M(M), BoundL(L), BoundD(D), BoundU(U), BoundR(R) {}

void Rtree::printNode(Rtree* head, int mode){
	Rtree* temp = head;
	std::string tab = "";
	if(mode==0) while (temp->parent != nullptr) { tab+="\t"; temp = temp->parent; }
	
	if(head->children.size() > 0)
		std::cout << tab << "L, R, U, D: " << head->BoundL << ", " << head->BoundR << ", " << head->BoundU << ", " << head->BoundD << '\n' << tab + "------------CHILDREN-----------\n";
	else {
		if(mode==0) tab.pop_back();
		std::cout << tab << "X, Y: " << head->BoundL << ", " << head->BoundU << '\n';
	}

	for (auto c : head->children) {
		c->printNode(c);
	}
}

void Rtree::printTree(){
	Rtree *head = this;
	while (head->parent != nullptr) head = head->parent;
	Rtree::printNode(head);
}

void Rtree::RtreeAdd(Rtree* child) {
	// if there is space then we change this elemnts nodes
	if (children.size() < M) {
		children.push_back(child);
		this->BoundD = min(this->BoundD, child->BoundD);
		this->BoundL = min(this->BoundL, child->BoundL);
		this->BoundU = max(this->BoundU, child->BoundU);
		this->BoundR = max(this->BoundR, child->BoundR);
		Rtree* temp = this -> parent;
		while (temp) {
			temp->BoundD = min(temp->BoundD, this->BoundD);
			temp->BoundL = min(temp->BoundL, this->BoundL);
			temp->BoundU = max(temp->BoundU, this->BoundU);
			temp->BoundR = max(temp->BoundR, this->BoundR);
			temp = temp->parent;
		}
	}
	//if there is not space to add elemnt, we need to make 2 new nodes
	else {
		bool newparentflag = false;
		if (this->parent == nullptr) {
			Rtree* newHead = new Rtree(m, M);
			newHead->parent = nullptr;
			this->parent = newHead;
			newparentflag = true;
		}

		Rtree* newThis = new Rtree(m, M);
		newThis->parent = this->parent;

		this->BoundD = INT_MAX; this->BoundL = INT_MAX; this->BoundU = INT_MIN; this->BoundR = INT_MIN;
		children.push_back(child);

		std::vector< Rtree* > vector;
		for (int i = 0; i < this->children.size(); i++) {
			vector.push_back(this->children[i]);
		}
		children.clear();

// OVDE TREBA DA SE KUCA LOGIKA ZA SPLIT KADA SE RAZDVBIJA JEDAN CVOR NA 2 NOVA KAKO DA SE PODELE CVOROVI
// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

		//odredjivanje 2 elemnta koji su "suprotni" / daju najvecu povrsinu
		Rtree* c1 = vector[0];
		Rtree* c2 = vector[1];
		int Surface = 0;

		//std::cout << "povrsine: \n";

		for (int i = 0; i < vector.size();i++) {
			for (int j=i+1; j < vector.size(); j++)  {
				int newSurface = (max(vector[i]->BoundD, vector[j]->BoundD) - min(vector[i]->BoundU, vector[j]->BoundU)) *
					(max(vector[i]->BoundR, vector[j]->BoundR) - min(vector[i]->BoundL, vector[j]->BoundL));

				//std::cout << newSurface << '\n';

				if (newSurface > Surface) {
					Surface = newSurface;
					c1 = vector[i];
					c2 = vector[j];
				}
			}
		}

		this->RtreeAdd(c1);
		c2->parent = newThis;
		newThis->RtreeAdd(c2);

		int passed = 2;

		// sve ostale elemente uporedjujemo da vidimo gde treba da idu u koji skup
		for (int i = 0; i < vector.size(); i++) {
			//add chilndren that are popped to newThis or This
			if (vector[i] == c1 || vector[i] == c2) { passed--; continue; }
			
			int Surface1 = (max(vector[i]->BoundD, c1->BoundD) - min(vector[i]->BoundU, c1->BoundU))*
						   (max(vector[i]->BoundR, c1->BoundR) - min(vector[i]->BoundL, c1->BoundL));

			int Surface2 = (max(vector[i]->BoundD, c2->BoundD) - min(vector[i]->BoundU, c2->BoundU)) *
						   (max(vector[i]->BoundR, c2->BoundR) - min(vector[i]->BoundL, c2->BoundL));

			//ako je jedna sstrana popunjena a druga ce imati manje od m
			int xxx = vector.size() - passed - i;
			
			if (this->children.size() + xxx == this->m) {
				this->RtreeAdd(vector[i]);
				continue;
			}
			if (newThis->children.size() + xxx == this->m) {
				vector[i]->parent = newThis;
				newThis->RtreeAdd(vector[i]);
				continue;
			}
			


			if (Surface1>Surface2) {
				vector[i]->parent = newThis;
				newThis->RtreeAdd(vector[i]);
				
			}
			else this->RtreeAdd(vector[i]);
		}


////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if (newparentflag) 
			this->parent->RtreeAdd(this);
		else {
			this->parent->BoundD = min(this->parent->BoundD, this->BoundD);
			this->parent->BoundL = min(this->parent->BoundL, this->BoundL);
			this->parent->BoundU = max(this->parent->BoundU, this->BoundU);
			this->parent->BoundR = max(this->parent->BoundR, this->BoundR);
		}
		this->parent->RtreeAdd(newThis);
	}
}

void Rtree::RtreeAdd(int Up, int Left, int Down, int Right) {
	Rtree* child = new Rtree(m, M, Up, Left, Down, Right);
	child->parent = this;

	Rtree::RtreeAdd(child);
}

//ovo ne valja treba sva deca da se pitaju pa da se propagira update na gore
//dodavanjem vektora, node = vector, onda bi mozda moglo da se resi jer je problem ako je za vise MBR-a isti deltaSurface
void Rtree::add(int Up, int Left, int Down, int Right) {

	if (Down == INT_MIN) Down = Up;
	if (Right == INT_MIN) Right = Left;

	Rtree* head = this;
	while (head->parent) head = head->parent;

	std::queue< Rtree* > node;
	node.push(head);

	int minSurface = INT_MAX;



	while (node.size() > 0) {

		Rtree* temp = node.front();
		node.pop();

		//ako nije 'list' onda stavljamo dalje elemente u niz
		if (temp->children.size() > 0){ // && temp->children[0]->children.size()==0) {
			for (auto a : temp->children) {
				node.push(a);
			}
		}
		
		//ako jeste onda gledamo povrsinu
		else {
			//temp predstavlja MBR gde gledamo dal je dobro da se ubaci ili ne	
			int newBoundD = min(Down, temp->BoundD);
			int newBoundR = max(Right, temp->BoundR);
			int newBoundU = max(Up, temp->BoundU);
			int newBoundL = min(Left, temp->BoundL);

			int deltaSurface = (newBoundU - newBoundD) * (newBoundR - newBoundL);

			if (deltaSurface < minSurface) {
				minSurface = deltaSurface;
				head = temp;
			}
			
		}
	}
	
	if (head->parent) head = head->parent;
	head->RtreeAdd(Up, Left, Down, Right);

}

void Rtree::readfile(std::string myText){

	std::ifstream MyReadFile(myText);

	while (std::getline(MyReadFile, myText)) {
		
		std::string input = myText;

		std::istringstream iss(input);
		int firstInt, secondInt;
		char delimiter;

		if (iss >> firstInt >> delimiter >> secondInt && delimiter == ',') {
			// Both integers were successfully extracted
			this->add(firstInt, secondInt);
		}
		else {
			// Extraction failed
			std::cout << "Invalid input format!" << std::endl;
		}
	}

	MyReadFile.close();
}

void Rtree::printTreeLevel(int lvl){

	std::vector <Rtree*> vector;

	Rtree* head = this;
	while (head->parent) head = head->parent;

	std::queue< Rtree* > node;
	node.push(head);

	while (node.size() > 0) {

		Rtree* temp = node.front();
		node.pop();

		//1 if treba al je preglednije sa 2, provera dal su se seku pravougaonici
		if (temp->children.size() > 0) {
			for (auto a : temp->children) {
				node.push(a);
			}
		}

		Rtree* temp1 = temp;
		int templvl = 0;
		while (temp1->parent != nullptr) {
			templvl++;
			temp1 = temp1->parent;
		}

		if (templvl == lvl) {
			vector.push_back(temp);
		}
	}

	for (auto a : vector) {
		std::cout << "L, R, U, D: " << a->BoundL << ", " << a->BoundR << ", " << a->BoundU << ", " << a->BoundD << '\n';
	}

}

void Rtree::search(int Up, int Left, int Down, int Right){

	std::vector <Rtree*> vector;

	Rtree* head = this;
	while (head->parent) head = head->parent;

	std::queue< Rtree* > node;
	node.push(head);

	while (node.size() > 0) {

		Rtree* temp = node.front();
		node.pop();

		//1 if treba al je preglednije sa 2, provera dal su se seku pravougaonici
		if ((temp->BoundD >= Down && temp->BoundD <= Up) || (temp->BoundU >= Down && temp->BoundU <= Up) || 
			(Down >= temp->BoundD && Down <= temp->BoundU) || (Up >= temp->BoundD && Up <= temp->BoundU)) {
			
			if ((temp->BoundL >= Left && temp->BoundL <= Right) || (temp->BoundR >= Left && temp->BoundR <= Right) ||
				(Left >= temp->BoundL && Left <= temp->BoundR) || (Right >= temp->BoundL && Right <= temp->BoundR)) {
				
				if (temp->children.size() > 0) {
					for (auto a : temp->children) {
						node.push(a);
					}
				}

				else {
					vector.push_back(temp);
				}
			}
		}
	}

	for (auto a : vector) {
		a->printNode(a,1);
	}

}
