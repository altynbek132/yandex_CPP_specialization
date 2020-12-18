using namespace std;
#include <cstdlib>

template<typename T>
class LinkedList {
 public:
  struct Node {
    T value;
    Node *next = nullptr;
  };
  
  ~LinkedList();
  
  void PushFront(const T &value);
  void InsertAfter(Node *node, const T &value);
  void RemoveAfter(Node *node);
  void PopFront();
  
  Node *GetHead() { return head; }
  
  const Node *GetHead() const { return head; }
 
 private:
  Node *head = nullptr;
};

template<typename T>
void LinkedList<T>::PushFront(const T &value) {
    auto node = new Node{value, head};
    head = node;
}

template<typename T>
void LinkedList<T>::InsertAfter(LinkedList::Node *node, const T &value) {
    if (node == nullptr) {
        PushFront(value);
        return;
    }
    
    auto new_node = new Node{value, node->next};
    node->next = new_node;
}

template<typename T>
void LinkedList<T>::RemoveAfter(LinkedList::Node *node) {
    if (node == nullptr) {
        PopFront();
        return;
    }
    
    auto toRemove = node->next;
    node->next = node->next == nullptr ? nullptr : node->next->next;
    delete toRemove;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        PopFront();
    }
}

template<typename T>
void LinkedList<T>::PopFront() {
    if (head == nullptr) { return; }
    auto next = head->next;
    delete head;
    head = next;
}
