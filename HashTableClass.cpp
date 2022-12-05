#include<iostream>
#include<cmath>

template<class T>
class Node {
public:
    Node(T key);
    T getKey();
protected:
    T key_;
};

template<class T> Node<T>::Node(T key) :key_(key)
{}

template<class T> T Node<T>::getKey()
{
    return key_;
}

template<class T>
class LLNode : public Node<T> {
public:
    LLNode(T key);
    LLNode<T>* getNext();
    void setNext(LLNode<T>* next);
protected:
    LLNode<T>* next_;

};

template<class T> LLNode<T>::LLNode(T key) :Node<T>(key), next_(0)
{}

template<class T> LLNode<T>* LLNode<T>::getNext()
{
    return next_;
}

template<class T> void LLNode<T>::setNext(LLNode<T>* next)
{
    next_ = next;
}

template<class T>
class Stack {

public:
   
    Stack();
   
    virtual ~Stack();

   
    virtual void push(T data);
    virtual void pop();

   
    int getSize() const;

    int peek();

    
    void reversePrintList() const;
    void printList() const;

protected:
    LLNode<T>* createNode(T insertionKey);
    LLNode<T>* head_;
    int size_;

    void reversePrintWorker(LLNode<T>*) const;
    void printWorker(LLNode<T>*) const;
};

template<class T> Stack<T>::Stack() :head_(0), size_(0)
{}

template<class T> Stack<T>::~Stack()
{
    while (head_ != 0)
    {
        pop();
    }
}
template<class T> int Stack<T>::getSize() const
{
    return size_;
}

template<class T> int Stack<T>::peek()
{
    return head_->getKey();
}

template<class T> LLNode<T>* Stack<T>::createNode(T insertionKey)
{
    LLNode<T>* insertionPtr = new LLNode<T>(insertionKey);
    return insertionPtr;
}

template<class T> void Stack<T>::push(T data)
{
    
    LLNode<T>* newNode = createNode(data);

    if (head_ == 0)
    {
       
        head_ = newNode;
    }
    else
    {
        
        newNode->setNext(head_);
       
        head_ = newNode;
    }
    size_++;
}

template<class T> void Stack<T>::pop()
{
    if (head_ != 0)
    {
        LLNode<T>* tp = head_;
        head_ = head_->getNext();
        delete tp;
        size_--;
    }
}

template<class T> void Stack<T>::reversePrintWorker(LLNode<T>* currPtr) const
{
    if (currPtr != 0)
    {
        reversePrintWorker(currPtr->getNext());
        std::cout << currPtr->getKey() << " ";
    }
}

template<class T> void Stack<T>::printWorker(LLNode<T>* currPtr) const
{
    if (currPtr != 0)
    {
        std::cout << currPtr->getKey() << " ";
        printWorker(currPtr->getNext());
    }
}

template<class T> void Stack<T>::reversePrintList() const
{
    reversePrintWorker(head_);
}

template<class T> void Stack<T>::printList() const
{
   
    printWorker(head_);
}

template<class T>
class LinkedList : public Stack<T> {

public:
   
    void deleteNode(int i);

   
    int indexOfKey(T key);

    
    int getData(int i) const;

};

template<class T> void LinkedList<T>::deleteNode(int idx)
{
    if (idx == 0)
    {
        this->pop();
    }
    else
    {
        
        LLNode<T>* tp = this->head_;
       
        LLNode<T>* pp = 0;
        for (int i = 0; i < idx; i++)
        {
          
            pp = tp;
           
            tp = tp->getNext();
        }
        pp->setNext(tp->getNext());
        delete tp;
        (this->size_)--;
    }
}

template<class T> int LinkedList<T>::getData(int idx) const
{
  
    LLNode<T>* tp = this->head_;
   
    for (int i = 0; i < idx; i++) tp = tp->getNext();
   
    return tp->getKey();
}

template<class T> int LinkedList<T>::indexOfKey(T targetKey)
{
   
    LLNode<T>* tp = this->head_;
    for (int i = 0; i < this->size_; i++)
    {
       
        if (tp->getKey() == targetKey) return i;
       
        tp = tp->getNext();
    }
    return -1;
}

class HashTable {
public:
   
    HashTable(int tableSize,
        int (*prehash)(std::string key),
        int (*hashmap)(int prehashedKey, int tableSize));
   
    const bool search(std::string key) const;
    void insert(std::string key);
    void del(std::string key);
    void printTable() const;
private:
   
    int (*prehash_)(std::string key);
    int (*hashmap_)(int prehashedKey, int m);
    int tableSize_;
    LinkedList<int>* table_;
};

HashTable::HashTable(int tableSize,
    int (*prehash)(std::string key),
    int (*hashmap)(int prehashedKey, int m))
    :tableSize_(tableSize)
{
    table_ = new LinkedList<int>[tableSize];
    prehash_ = prehash;
    hashmap_ = hashmap;
}

const bool HashTable::search(std::string key) const
{
   
    int prehashedKey = (*prehash_)(key);
    int slot = (*hashmap_)(prehashedKey, tableSize_);
    
    int idx = table_[slot].indexOfKey(prehashedKey);
    bool isThere = false;
    if (idx != -1) isThere = true;
    return isThere;
}



void HashTable::insert(std::string key)
{
  
    int prehashedKey = (*prehash_)(key);
    int slot = (*hashmap_)(prehashedKey, tableSize_);
    
    int idx = table_[slot].indexOfKey(prehashedKey);
    if (idx == -1)
    {
      
        table_[slot].push(prehashedKey);
    }
    else
    {
        std::cout << "Hash table already contains target key.\n";
    }
}

void HashTable::del(std::string key)
{
    
    int prehashedKey = (*prehash_)(key);
    int slot = (*hashmap_)(prehashedKey, tableSize_);
   
    int idx = table_[slot].indexOfKey(prehashedKey);
    if (idx != -1)
    {
      
        table_[slot].deleteNode(prehashedKey);
    }
    else
    {
        std::cout << "Hash table does not contain target key.\n";
    }
}

void HashTable::printTable() const
{
    for (int i = 0; i < tableSize_; i++)
    {
        table_[i].printList();
        std::cout << std::endl;
    }
}

int prehash(std::string key)
{
    int len = key.length();
    int prehashedKey = 0;
    for (int i = 0; i < len; i++) prehashedKey += ((int)key[i] - 96) * pow(26, len - 1 - i);
    return prehashedKey;
}

int hashmap(int prehashedKey, int tableSize)
{
    return prehashedKey % tableSize;
}

int main()
{

    int NUMSLOTS = 21;
    int NUMNAMES = 20;
    std::string names[] =
    { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
         "k", "l", "m", "n", "o", "p", "q", "r", "s", "t" };

   
    HashTable myHashTable(NUMSLOTS, prehash, hashmap);
    for (int i = 0; i < NUMNAMES; i++) myHashTable.insert(names[i]);
   
    myHashTable.printTable();
}