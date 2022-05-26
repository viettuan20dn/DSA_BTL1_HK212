#include "Stack.cpp"
#include <constants.h>
class JA_Stack
{
private:
    Stack<Element> st;
    int *LVArr = new int[LOCAL_VARIABLE_ARRAY_SIZE];
    int sizeOfLVAarr;

public:
    JA_Stack()
    {
        sizeOfLVAarr = 0;
    }
}