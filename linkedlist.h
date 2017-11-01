#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <utility>
#include <ostream>

template<typename T>
struct Node
{
    T data;
    Node<T>* next;

    Node(T d, Node<T>* n = nullptr):data(d), next(n){}
    Node(T&& d, Node<T>* n = nullptr):data(d), next(n){}
};



template<typename T>
class LinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;

    std::size_t size;


public:
    LinkedList() noexcept;
    LinkedList(std::size_t initsize, T elem = T());
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& other);

    LinkedList& operator=(const LinkedList& other);
    LinkedList& operator=(LinkedList&& other);
    ~LinkedList();

    void addFront(const T& elem);
    void addFront(T&& elem);

    void addEnd(const T& elem);
    void addEnd(T&& elem);

    std::size_t Size() const noexcept;
    bool isEmpty() const noexcept;


    T& front();
    T& back();

    const T& front() const;
    const T& back() const;

    bool removeFront();
    bool removeEnd();

    void clear();
    void print(std::ostream& os) const;


};


template<typename T>
LinkedList<T>::LinkedList() noexcept
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
LinkedList<T>::LinkedList(std::size_t initsize, T elem)
{
    head = nullptr;
    tail = nullptr;
    size = 0;
    auto p = head;
    for(std::size_t i = 0; i < initsize; i++)
    {
        p = new Node<T>(elem);
        p = p->next;
        if(i + 1 == initsize)
            tail = p;
    }
    size = initsize;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList &other)
{
    head = tail = nullptr;
    size = 0;
    auto p = other.head;
    for(; p != nullptr; p = p->next)
        addEnd(p->data);

}

template<typename T>
LinkedList<T>::LinkedList(LinkedList &&other)
{
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = nullptr;
    other.tail = nullptr;

    other.size = 0;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator =(const LinkedList& other)
{
    if(this == &other)
        return *this;

    clear();
    auto p = other.head;
    for(; p != nullptr; p = p->next)
        addEnd(p->data);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator =(LinkedList<T>&& other)
{
    if(this == &other)
        return *this;

    clear();
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = nullptr;
    other.tail = nullptr;

    other.size = 0;
}

template<typename T>
void LinkedList<T>::clear()
{
    while(head)
    {
        auto next = head->next;
        delete head;
        head = next;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
void LinkedList<T>::addFront(const T &elem)
{
    if(!head)
    {
        head = new Node<T>(elem);
        tail = head;
    }
    else
    {
        Node<T>* newNode = new Node<T>(elem);
        newNode->next = head;
        head = newNode;
    }
    size++;
}

template<typename T>
void LinkedList<T>::addEnd(const T &elem)
{
    if(!tail)
    {
        addFront(elem);
        return;
    }
    else
    {
        Node<T>* newNode = new Node<T>(elem);
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}


template<typename T>
void LinkedList<T>::addEnd(T &&elem)
{
    if(!tail){
        addFront(elem);
        return;
    }
    else
    {
        Node<T>* newNode = new Node<T>(elem);
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template<typename T>
void LinkedList<T>::addFront(T &&elem)
{
    if(!head)
    {
        head = new Node<T>(elem);
        tail = head;
    }
    else
    {
        Node<T>* newNode = new Node<T>(elem);
        newNode->next = head;
        head = newNode;
    }
    size++;
}

template<typename T>
std::size_t LinkedList<T>::Size() const noexcept
{
    return size;
}

template<typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
    return !size;
}

template<typename T>
bool LinkedList<T>::removeFront()
{
    if(isEmpty())
        return false;

    Node<T>* tempNext = head->next;
    delete head;
    head = tempNext;
    size--;
    return true;
}

template<typename T>
bool LinkedList<T>::removeEnd()
{
    if(isEmpty())
        return false;

    auto beforeEnd = head;
    for(; beforeEnd->next != tail; beforeEnd = beforeEnd->next)  ;

    delete tail;
    tail = beforeEnd;
    size--;
    return true;
}

template<typename T>
T& LinkedList<T>::front()
{
    return head->data;
}

template<typename T>
T& LinkedList<T>::back()
{
    return tail->data;
}

template<typename T>
const T& LinkedList<T>::back() const
{
    return tail->data;
}

template<typename T>
const T& LinkedList<T>::front() const
{
    return  head->data;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template<typename T>
void LinkedList<T>::print(std::ostream &os) const
{
    for(auto p = head; p != nullptr; p = p->next)
        os << p->data << " ";
}

#endif // LINKEDLIST_H
