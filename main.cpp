

// #include "ABDQ.hpp"
// #include "ABQ.hpp"
// #include "ABS.hpp"
// #include "Interfaces.hpp"
#include "LinkedList.hpp"
// #include "LLDQ.hpp"
// #include "LLQ.hpp"
// #include "LLS.hpp"
#include <iostream>
#include <utility>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    LinkedList<int> l;
    l.addHead(5);
    l.addHead(10);
    l.addHead(15);
    l.addTail(1);
    l.printForward();

    //Copy constructor
    LinkedList<int> b(l);
    b.addTail(0);
    b.printForward();

    //Copy assignment
    LinkedList<int> c = b;
    c.printForward();
    c.addHead(20);
    c.printForward();
    std::cout << std::endl;

    l.printForward();
    b.printForward();
    c.printForward();

    //Move constructor
    LinkedList<int> d(std::move(c));
    d.addTail(-5);
    d.printForward();

    //Move assignment
    LinkedList<int> f = std::move(d);
    d.printForward();
    return 0;
}


