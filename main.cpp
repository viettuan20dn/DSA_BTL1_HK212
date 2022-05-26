#include <iostream>
#include "StackFrame.cpp"
#include "errors.h"
using namespace std;

/*
Run the testcase written in `filename`
@param filename name of the file
*/
void test(string filename) {
    StackFrame *sf = new StackFrame();
    try {
        sf->run(filename);
    }
    catch (exception& e) {
        cout << e.what();
    }
    delete sf;
}

/*
Main function
*/
int main() {
    test("test000.txt");
    /*
    * problem1: Toi uu code recode de tranh trung lap
    * problem2: Tu viet mot so test case
    * problem3: check dau bang de tranh tinh trang so sanh thanh ghep!
    */
    return 0;
}