#include <iostream>
#include "Rtree.h"
#include <chrono>
#include <thread>

int main()
{
    Rtree r = Rtree(3, 5);
    
    //r.readfile("C:/Users/jovan/Desktop/txt.txt");
    std::cout << "asdasdasdasd\n\n\n";
    for (int i = 0; i < 30; i++) {
        int x = rand() % 100;
        int y = rand() % 100;
        r.add(x,y);
        //std::cout << x << ", " << y << '\n' << '\n';
        
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        //std::cout << "\033[2J\033[1;1H";
    }

    r.printTree();

    r.search(70, 30, 30, 70);
    
    std::cout << "-----------------------------------------------------\n";

    r.printTreeLevel(0);
    r.printTreeLevel(1);

    /*
    r.add(1, 1, 1, 1);
    r.printTree();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "\033[2J\033[1;1H";
    r.add(2, 2, 2, 2);
    r.printTree();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "\033[2J\033[1;1H";
    r.add(50, 50, 50, 50);
    r.printTree();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "\033[2J\033[1;1H";
    r.add(20, 20, 20, 20);
    r.printTree();
    std::this_thread::sleep_for(std::chrono::seconds(10));

    r.add(15, 15, 15, 15);
    r.printTree();
    std::this_thread::sleep_for(std::chrono::seconds(10));

    r.add(50, 50, 50, 50);
    r.printTree();
    std::this_thread::sleep_for(std::chrono::seconds(10));


    r.RtreeSearch(25, 0, 0, 25);
    */
}
