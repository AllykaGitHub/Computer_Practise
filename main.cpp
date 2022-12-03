#include <iostream>
using namespace std;

struct Node {
    int number; //������
    Node* next; //��������� �� ��������� ����
    Node* prev; //��������� �� ����������
};

class doubleList {
    Node* head;
    Node* tail;
public:
    doubleList();
    void addFirst(int number);
    void addLast(int number);
    void delTail();
    void delHead();
    void sortingList();
    void swap(int& a, int& b);
    void showList() const;
};

doubleList::doubleList() {
    head = tail = NULL;
}

//���������� ���� � ������
void doubleList::addFirst(int number) {
    Node* buf = new Node;
    buf->number = number;
    if (!head) {
        buf->next = tail;
        tail = buf;
    }
    else {
        buf->next = head;
        head->prev = buf;
    }
    head = buf;
    head->prev = NULL;

}

//���������� ���� � ������
void doubleList::addLast(int number) {
    Node* buf = new Node;
    buf->number = number;
    if (!head) {
        buf->next = tail;
        head = buf;
        buf->prev = NULL;
    }
    else {
        buf->next = tail->next;
        buf->prev = tail;
        tail->next = buf;
    }
    tail = buf;
}

//������ �� ������ � ������� ��� ��������
void doubleList::showList() const {
    if (head) {
        Node* buf = head;
        while (buf) {
            cout << buf->number << " ";
            buf = buf->next;
        }
        cout << endl;
    }
    else cout << "List is empty " << endl;
}

//�������� ������
void doubleList::delHead() {
    if (head) {
        Node* buf = head;
        head = head->next;
        head->prev = NULL;
        delete buf;
    }
    else cout << "List is empty" << endl;
}

//�������� ������
void doubleList::delTail() {
    if (tail) {
        Node* buf = tail;
        tail = tail->prev;
        tail->next = NULL;
        delete buf;
    }
    else cout << "List is empty" << endl;
}

//����� ������ ������
void doubleList::swap(int& a, int& b) {
    int buf = a;
    a = b;
    b = buf;
}

//����������
void doubleList::sortingList() {
    Node* buf = head;
    for (Node* i = buf; i; i = i->next) {
        for (Node* j = i->next; j; j = j->next) {
            if (i->number < j->number) {
                swap(i->number, j->number);
            }
        }
    }

}


int main()
{
    doubleList ob;
    int a_i;
    cout << "Enter elements" << endl;
    while (1) {
        cin >> a_i;
        if (a_i) {
            ob.addFirst(a_i);
        }
        else break;
    }
    ob.sortingList();
    ob.showList();
    
    return 0;
}