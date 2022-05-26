#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

/*
 * Khai bao 1 phan tu stack hay 1 toán hang
 */
Element::Element(float value, int typeCode)
{
    this->value = value;
    this->typeCode = typeCode;
}
void Element::setTCode(const int &TCode)
{
    this->typeCode = TCode;
}
void Element::setValue(const float &value)
{
    this->value = value;
}
int Element::getTCode()
{
    return this->typeCode;
}
float Element::getValue()
{
    return this->value;
}
void Element::show()
{
    cout << "Value: " << value << endl;
}
bool Element::operator==(const Element &element)
{
    return (this->value == element.value && this->typeCode == element.typeCode);
}
bool Element::operator!=(const Element &element)
{
    return (this->value != element.value || this->typeCode != element.typeCode);
}
bool Element::operator<(const Element &element)
{
    return (this->value < element.value && this->typeCode == element.typeCode);
}
bool Element::operator>(const Element &element)
{
    return (this->value > element.value && this->typeCode == element.typeCode);
}
Element operator*(const Element &e1, const Element &e2)
{
    return Element(e1.value * e2.value, e1.typeCode);
}
Element operator+(const Element &e1, const Element &e2)
{
    return Element(e1.value + e2.value, e1.typeCode);
}
Element operator-(const Element &e1, const Element &e2)
{
    return Element(e1.value - e2.value, e1.typeCode);
}
Element operator/(const Element &e1, const Element &e2)
{
    if (e1.typeCode == 0)
        return Element((int)(e1.value / e2.value), 0);
    else
    {
        return Element(e1.value / e2.value, 1);
    }
}
Element operator%(const Element &e1, const Element &e2)
{
    return Element((int)e1.value % (int)e2.value, 0);
}
Element operator&(const Element &e1, const Element &e2)
{
    return Element((int)e1.value & (int)e2.value, 0);
}
Element operator|(const Element &e1, const Element &e2)
{
    return Element((int)e1.value | (int)e2.value, 0);
}

/*
 * Hien thuc cho Slinkedlist
 */
Node::Node()
{
    next = NULL;
}
Node::Node(Element data, Node *next = NULL)
{
    this->data = data;
    this->next = next;
}

/*
 * khai bao danh sach lien ket
 */
SlinkedList::SlinkedList()
{
    this->head = this->tail = NULL;
    this->count = 0;
}
void SlinkedList::add(Element item)
{
    Node *newNode = new Node(item);
    if (count == 0)
    {
        this->head = this->tail = newNode;
        count = 1;
    }
    else
    {
        this->tail->next = newNode;
        this->tail = newNode;
        count++;
    }
}
void SlinkedList::add(int index, const Element &item)
{
    if (index < 0 || index > this->count)
        throw out_of_range("Index is not valid");
    if (this->count == index)
    {
        return this->add(item);
    }
    if (index == 0)
    {
        Node *newNode = new Node(item, this->head);
        this->head = newNode;
        this->count++;
        return;
    }
    else
    {
        Node *newNode = new Node(item);
        Node *tmp = this->head;

        for (int i = 0; i < index - 1; i++)
        {
            tmp = tmp->next;
        }

        newNode->next = tmp->next;
        tmp->next = newNode;
        this->count++;
        return;
    }
}
Element SlinkedList::removeAt(const int &index)
{
    if (index < 0 || index >= this->count)
        throw out_of_range("Index is not valid");
    if (this->count == 1)
    {
        Element valueToReturn = this->head->data;
        delete this->head;
        this->head = this->tail = NULL;
        this->count = 0;
        return valueToReturn;
    }
    if (index == 0)
    {
        Element valueToReturn = this->head->data;
        Node *tmp = this->head;
        this->head = this->head->next;
        delete tmp;
        this->count--;
        return valueToReturn;
    }

    Node *tmp = this->head;
    for (int i = 0; i < index - 1; i++)
    {
        tmp = tmp->next;
    }

    if (index == (this->count - 1))
    {
        Element valueToReturn = this->tail->data;
        delete this->tail;
        tmp->next = NULL;
        this->tail = tmp;
        this->count--;
        return valueToReturn;
    }
    else
    {
        Element valueToReturn = tmp->next->data;
        Node *delNode = tmp->next;
        tmp->next = delNode->next;
        delete delNode;
        this->count--;
        return valueToReturn;
    }
}
int SlinkedList::indexOf(const Element &item)
{
    Node *tmp = this->head;
    for (int i = 0; i < this->count; i++)
    {
        if (tmp->data == item)
            return i;
        tmp = tmp->next;
    }
    return -1;
}
Element SlinkedList::get(const int &index)
{
    // Check index
    // if (index < 0 || index >= this->count)
    //     throw out_of_range("Index is not valid");

    Node *tmp = this->head;
    for (int i = 0; i < index; i++)
    {
        tmp = tmp->next;
    }
    return tmp->data;
}
bool SlinkedList::empty()
{
    return this->count == 0;
}
int SlinkedList::size()
{
    return this->count;
}
void SlinkedList::clear()
{
    while (this->head)
    {
        Node *tmp = this->head;
        this->head = this->head->next;
        delete tmp;
    }
    this->tail = NULL;
    this->count = 0;
}
SlinkedList::~SlinkedList()
{
    this->clear();
}

/*
 * Hien thuc Stack
 */
void Stack::push(const Element &e)
{
    list.add(0, e);
}
void Stack::pop()
{
    list.removeAt(0);
}
Element Stack::top()
{
    return list.get(0);
}
int Stack::size()
{
    return list.size();
}
bool Stack::empty()
{
    return list.size() == 0;
}

int NumberOfCommand(string s)
{
    int No = 0;
    if (s.find("add") != string::npos)
        No = 1;
    else if (s.find("sub") != string::npos)
        No = 3;
    else if (s.find("mul") != string::npos)
        No = 5;
    else if (s.find("div") != string::npos)
        No = 7;
    else if (s == "irem")
        No = 9;
    else if (s.find("neg") != string::npos)
        No = 10;
    else if (s == "iand")
        No = 12;
    else if (s == "ior")
        No = 13;
    else if (s == "ineq")
        No = 16;
    else if (s == "fneq")
        No = 17;
    else if (s.find("eq") != string::npos)
        No = 14;
    else if (s.find("lt") != string::npos)
        No = 18;
    else if (s == "igt")
        No = 20;
    else if (s == "fgt")
        No = 21;
    else if (s == "ibnot")
        No = 22;
    else if (s.find("iconst") != string::npos)
        No = 23;
    else if (s.find("fconst") != string::npos)
        No = 24;
    else if (s.find("iload") != string::npos)
        No = 25;
    else if (s.find("fload") != string::npos)
        No = 26;
    else if (s.find("istore") != string::npos)
        No = 27;
    else if (s.find("fstore") != string::npos)
        No = 28;
    else if (s == "i2f")
        No = 29;
    else if (s == "f2i")
        No = 30;
    else if (s == "top")
        No = 31;
    else if (s.find("val") != string::npos)
        No = 32;
    return No;
}
StackFrame::StackFrame()
{
    this->opStackMaxSize = OPERAND_STACK_MAX_SIZE;
    this->localVarArrSize = LOCAL_VARIABLE_ARRAY_SIZE;
    this->LVArr = new float[localVarArrSize];
    for (int i = 0; i < localVarArrSize; i++)
    {
        LVArr[i] = -1;
    }
    this->line = 0;
}

void StackFrame::run(string filename)
{
    ifstream ifs(filename);
    /*
     * kiem tra file da mo thanh cong hay chua?
     */
    if (!ifs)
    {
        cerr << "Error: file not opened." << endl;
        return;
    }
    /*
     *gia dinh rang cac lenh la hoan toan dung cu phap
     */
    string commandLine;

    while (getline(ifs, commandLine))
    {
        this->line++;
        int No = NumberOfCommand(commandLine);
        switch (No)
        {
        case 1: // add OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            if (commandLine[0] == 'i') // iadd
            {
                // Kiem tra kieu du lieu cua toan hang
                if (e1.getTCode() || e2.getTCode())
                {
                    throw TypeMisMatch(line);
                }
            }
            else // fadd
            {
                // Thuc hien ep kieu int->float(neu co)
                if (e1.getTCode() == 0)
                {
                    e1.setTCode(1);
                    e1.setValue((float)e1.getValue());
                }
                if (e2.getTCode() == 0)
                {
                    e2.setTCode(1);
                    e2.setValue((float)e2.getValue());
                }
            }

            // thuc hien phep cong
            st.push(e1 + e2);

            break;
        }
        case 3: // sub OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            if (commandLine[0] == 'i') // isub
            {
                // Kiem tra kieu du lieu cua toan hang
                if (e1.getTCode() || e2.getTCode())
                {
                    throw TypeMisMatch(line);
                }
            }
            else // fsub
            {
                // Thuc hien ep kieu int->float(neu co)
                if (e1.getTCode() == 0)
                {
                    e1.setTCode(1);
                    e1.setValue((float)e1.getValue());
                }
                if (e2.getTCode() == 0)
                {
                    e2.setTCode(1);
                    e2.setValue((float)e2.getValue());
                }
            }

            // Thuc hien phep tru
            st.push(e2 - e1);

            break;
        }
        case 5: // mul OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            if (commandLine[0] == 'i') // imul
            {
                // Kiem tra kieu du lieu cua toan hang
                if (e1.getTCode() || e2.getTCode())
                {
                    throw TypeMisMatch(line);
                }
            }
            else // fmul
            {
                // Thuc hien ep kieu int->float(neu co)
                if (e1.getTCode() == 0)
                {
                    e1.setTCode(1);
                    e1.setValue((float)e1.getValue());
                }
                if (e2.getTCode() == 0)
                {
                    e2.setTCode(1);
                    e2.setValue((float)e2.getValue());
                }
            }

            // thuc hien phep nhan
            st.push(e1 * e2);

            break;
        }
        case 7: // div OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            if (commandLine[0] == 'i') // idiv
            {
                // Kiem tra kieu du lieu cua toan hang
                if (e1.getTCode() || e2.getTCode())
                {
                    throw TypeMisMatch(line);
                }
            }
            else // fdiv
            {
                // Thuc hien ep kieu int->float(neu co)
                if (e1.getTCode() == 0)
                {
                    e1.setTCode(1);
                    e1.setValue((float)e1.getValue());
                }
                if (e2.getTCode() == 0)
                {
                    e2.setTCode(1);
                    e2.setValue((float)e2.getValue());
                }
            }

            if (e1.getValue() == 0)
                throw DivideByZero(line);
            st.push(e2 / e1);

            break;
        }
        case 9: // irem OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            // Kiem tra kieu du lieu cua toan hang
            if (e1.getTCode() || e2.getTCode())
            {
                throw TypeMisMatch(line);
            }
            else
            {
                if (e1.getValue() == 0)
                    throw DivideByZero(line);
                st.push(e2 % e1);
            }
            break;
        }
        case 10: // neg OK
        {
            // kiem tra stack
            if (st.empty())
                throw StackEmpty(line);

            // Lay phan tu dau ra
            Element e = st.top();
            st.pop();

            // kiem tra kieu du lieu
            if (commandLine[0] == 'i' && e.getTCode() == 1)
                throw TypeMisMatch(line);
            if (commandLine[0] == 'f' && e.getTCode() == 0)
            {
                e.setTCode(1);
                e.setValue((float)e.getValue());
            }

            // thuc hien dao dau
            e.setValue((-1) * e.getValue());
            st.push(e);
            break;
        }
        case 12: // iand OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            // Kiem tra kieu du lieu cua toan hang
            if (e1.getTCode() || e2.getTCode())
            {
                throw TypeMisMatch(line);
            }
            else
                st.push(e1 & e2);

            break;
        }
        case 13: // ior OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            // Kiem tra kieu du lieu cua toan hang
            if (e1.getTCode() || e2.getTCode())
            {
                throw TypeMisMatch(line);
            }
            else
                st.push(e1 | e2);

            break;
        }
        case 14: // eq OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            if (commandLine[0] == 'i') // ieq
            {
                // Kiem tra kieu du lieu cua toan hang
                if (e1.getTCode() || e2.getTCode())
                {
                    throw TypeMisMatch(line);
                }
            }
            else // feq
            {
                // Thuc hien ep kieu int->float(neu co)
                if (e1.getTCode() == 0)
                {
                    e1.setTCode(1);
                    e1.setValue((float)e1.getValue());
                }
                if (e2.getTCode() == 0)
                {
                    e2.setTCode(1);
                    e2.setValue((float)e2.getValue());
                }
            }

            // Thuc hien so sanh va day ket qua vao ngan xep
            Element e;
            e.setTCode(0);
            if (e2 == e1)
                e.setValue(1);
            else
                e.setValue(0);
            st.push(e);

            break;
        }
        case 16: // neq OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            if (commandLine[0] == 'i') // ineq
            {
                // Kiem tra kieu du lieu cua toan hang
                if (e1.getTCode() || e2.getTCode())
                {
                    throw TypeMisMatch(line);
                }
            }
            else // fneq
            {
                // Thuc hien ep kieu int->float(neu co)
                if (e1.getTCode() == 0)
                {
                    e1.setTCode(1);
                    e1.setValue((float)e1.getValue());
                }
                if (e2.getTCode() == 0)
                {
                    e2.setTCode(1);
                    e2.setValue((float)e2.getValue());
                }
            }

            // Thuc hien so sanh va day ket qua vao ngan xep
            Element e;
            e.setTCode(0);
            if (e2 != e1)
                e.setValue(1);
            else
                e.setValue(0);
            st.push(e);

            break;
        }
        case 18: // ilt OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            // Kiem tra kieu du lieu cua toan hang
            if (commandLine[0] == 'i') // ilt
            {
                // Kiem tra kieu du lieu cua toan hang
                if (e1.getTCode() || e2.getTCode())
                {
                    throw TypeMisMatch(line);
                }
            }
            else // flt
            {
                // Thuc hien ep kieu int->float(neu co)
                if (e1.getTCode() == 0)
                {
                    e1.setTCode(1);
                    e1.setValue((float)e1.getValue());
                }
                if (e2.getTCode() == 0)
                {
                    e2.setTCode(1);
                    e2.setValue((float)e2.getValue());
                }
            }
            
                // Thuc hien so sanh va day ket qua vao ngan xep
                Element e;
                e.setTCode(0);
                if (e2 < e1)
                    e.setValue(1);
                else
                    e.setValue(0);
                st.push(e);
            
            break;
        }
        case 20: // igt OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            // Kiem tra kieu du lieu cua toan hang
            if (e1.getTCode() || e2.getTCode())
            {
                throw TypeMisMatch(line);
            }
            else
            {
                // Thuc hien so sanh va day ket qua vao ngan xep
                Element e;
                e.setTCode(0);
                if (e2 > e1)
                    e.setValue(1);
                else
                    e.setValue(0);
                st.push(e);
            }

            break;
        }
        case 21: // fgt OK
        {
            // Lay lan luot 2 phan tu dau cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e1 = st.top();
            st.pop();
            if (st.empty())
                throw StackEmpty(line);
            Element e2 = st.top();
            st.pop();

            // Thuc hien ep kieu int->float(neu co)
            if (e1.getTCode() == 0)
            {
                e1.setTCode(1);
                e1.setValue((float)e1.getValue());
            }
            if (e2.getTCode() == 0)
            {
                e2.setTCode(1);
                e2.setValue((float)e2.getValue());
            }

            // Thuc hien so sanh va day ket qua vao ngan xep
            Element e;
            e.setTCode(0);
            if (e2 > e1)
                e.setValue(1);
            else
                e.setValue(0);
            st.push(e);

            break;
        }
        case 22: // ibnot OK
        {
            // kiem tra stack
            if (st.empty())
                throw StackEmpty(line);

            // Lay phan tu dau ra
            Element e = st.top();
            st.pop();

            // kiem tra kieu du lieu
            if (e.getTCode() == 1)
                throw TypeMisMatch(line);

            // thuc hien so sanh
            if (e.getValue() == 0)
                st.push(Element(1, 0));
            else
                st.push(Element(0, 0));
            break;
        }
        case 23: // iconst OK
        {
            // Kiem tra stack da full chua
            if (st.size() == opStackMaxSize)
                throw StackFull(line);

            // lay tham so cua ham
            unsigned int iSpace = commandLine.find(" ");
            int thamSo = stoi(commandLine.substr(iSpace + 1));

            // mac dinh la tham so dung(tuc testcase dua dung kieu)
            Element e(thamSo, 0);
            st.push(e);
            break;
        }
        case 24: // fconst OK
        {
            // Kiem tra stack da full chua
            if (st.size() == opStackMaxSize)
                throw StackFull(line);

            // lay tham so cua ham
            unsigned int iSpace = commandLine.find(" ");
            float thamSo = stof(commandLine.substr(iSpace + 1));

            // mac dinh la tham so dung(tuc testcase dua dung kieu)
            Element e(thamSo, 1);
            st.push(e);
            break;
        }
        case 25: // iload OK
        {
            // Lay tham so cua ham(tuc lay gia tri index)
            unsigned int iSpace = commandLine.find(" ");
            int ind = stoi(commandLine.substr(iSpace + 1));

            // Kiem tra loi voi index
            if (ind >= localVarArrSize)
                throw ArrayOutOfRange(line);
            if (LVArr[ind] == -1)
                throw UndefinedVariable(line);

            // Day gia tri vao ngan xep neu dung kieu
            if (LVArr[ind] == 0)
            {
                if (st.size() == opStackMaxSize)
                    throw StackFull(line);
                st.push(Element(LVArr[ind + 1], 0));
            }
            else
                throw TypeMisMatch(line);

            break;
        }
        case 26: // fload OK
        {
            // Lay tham so cua ham(tuc lay gia tri index)
            unsigned int iSpace = commandLine.find(" ");
            int ind = stoi(commandLine.substr(iSpace + 1));

            // Kiem tra loi voi index
            if (ind >= localVarArrSize)
                throw ArrayOutOfRange(line);
            if (LVArr[ind] == -1)
                throw UndefinedVariable(line);

            // Day gia tri vao ngan xep neu dung kieu
            if (LVArr[ind] == 1)
            {
                if (st.size() == opStackMaxSize)
                    throw StackFull(line);
                st.push(Element(LVArr[ind + 1], 1));
            }
            else
                throw TypeMisMatch(line);

            break;
        }
        case 27: // istore OK
        {
            // lay tham so ham(tuc gia tri ind)
            unsigned int iSpace = commandLine.find(" ");
            int ind = stoi(commandLine.substr(iSpace + 1));

            // kiem tra stack co rong khong-> Neu khong lay ra phan tu dau tien cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e = st.top();
            st.pop();

            // Kiem tra kieu du lieu cua toan hang va gia tri ind
            if (e.getTCode() == 1)
                throw TypeMisMatch(line);
            if (ind >= this->localVarArrSize)
                throw ArrayOutOfRange(line);

            // Thuc hien luu vao mang bien cuc bo
            this->LVArr[ind] = e.getTCode();
            this->LVArr[ind + 1] = e.getValue();
            break;
        }
        case 28: // fstore OK
        {
            // lay tham so ham(tuc gia tri ind)
            unsigned int iSpace = commandLine.find(" ");
            int ind = stoi(commandLine.substr(iSpace + 1));

            // kiem tra stack co rong khong-> Neu khong lay ra phan tu dau tien cua ngan xep
            if (st.empty())
                throw StackEmpty(line);
            Element e = st.top();
            st.pop();

            // Kiem tra kieu du lieu cua toan hang va gia tri ind
            if (e.getTCode() == 0)
                throw TypeMisMatch(line);
            if (ind >= this->localVarArrSize)
                throw ArrayOutOfRange(line);

            // Thuc hien luu vao mang bien cuc bo
            this->LVArr[ind] = e.getTCode();
            this->LVArr[ind + 1] = e.getValue();
            break;
        }
        case 29: // i2f OK
        {
            // Kiem tra stack
            if (st.empty())
                throw StackEmpty(line);

            // lay ra phan tu dau tien
            Element e = st.top();
            st.pop();

            // kiem tra kieu du lieu
            if (e.getTCode() == 1)
                throw TypeMisMatch(line);

            // Thuc hien convert int -> float
            e.setTCode(1);
            e.setValue((float)e.getValue());
            st.push(e);

            break;
        }
        case 30: // f2i OK
        {
            // Kiem tra stack
            if (st.empty())
                throw StackEmpty(line);

            // lay ra phan tu dau tien
            Element e = st.top();
            st.pop();

            // kiem tra kieu du lieu
            if (e.getTCode() == 0)
                throw TypeMisMatch(line);

            // Thuc hien convert float -> int
            e.setTCode(0);
            e.setValue((int)e.getValue());
            st.push(e);

            break;
        }
        case 31: // top OK
            if (st.empty())
                throw StackEmpty(line);
            cout << st.top().getValue() << endl;
            break;
        case 32: // val OK
        {
            // lay tham so cua ham( tuc lay gia tri ind)
            unsigned int iSpace = commandLine.find(" ");
            int ind = stoi(commandLine.substr(iSpace + 1));

            // Kiem tra cac loi co the doi voi ind
            if (ind >= localVarArrSize)
                throw ArrayOutOfRange(line);
            if (LVArr[ind] == -1)
                throw UndefinedVariable(line);

            // In ra gia tri cua phan tu thu ind(thuc ra la ind+1) trong mang cuc bo
            cout << LVArr[ind + 1] << endl;
            break;
        }
        default:
            break;
        }
    }

    ifs.close();
}
StackFrame::~StackFrame() {}