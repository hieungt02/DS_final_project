#ifndef HEAPQUEUE_H
#define HEAPQUEUE_H

#include <vector>

template <typename E>
class VectorCompleteTree
{
private:
  // Vector to store elements of type E
  std::vector<E> V; 
public:
  // Position iterator in the vector
  typedef typename std::vector<E>::iterator Position;
protected:
  // Get the position of an element at index i
  Position pos(int i) 
  {
    return V.begin() + i;
  }

  // Get the index of a position
  int idx(const Position &p) const
  {
    return p - V.begin();
  }

public:
  VectorCompleteTree() : V(1) {} // Initializes the vector with size 1
  int size() const { return V.size() - 1; } // Return the size of the tree
  Position left(const Position &p) { return pos(2 * idx(p)); } // Get the left child of a position
  Position right(const Position &p) { return pos(2 * idx(p) + 1); }  // Get the right child of a position
  Position parent(const Position &p) { return pos(idx(p) / 2); } // Get the parent of a position
  bool hasLeft(const Position &p) const { return 2 * idx(p) <= size(); } // Check if a posiiton has left child
  bool hasRight(const Position &p) const { return 2 * idx(p) + 1 <= size(); } // Check if a position has right child
  bool isRoot(const Position &p) const { return idx(p) == 1; } // Check if a position is root node
  Position root() { return pos(1); } // Get the root position
  Position last() { return pos(size()); } // Get the last node of the tree
  void addLast(const E &e) { V.push_back(e); } // Add an element to the end of the tree
  void removeLast() { V.pop_back(); } // Remove the last element from the end of the tree
  void swap(const Position &p, const Position &q) // Swap elements 
  {
    E e = *q;
    *q = *p;
    *p = e;
  }
};

template <typename E, typename C>
class HeapQueue
{
public:
  int size() const; // Get the size of the priority queue
  bool empty() const; // Check if the priority queue is empty
  void insert(const E &e); // Insert an element into the priority queue
  const E &min(); // Get the minimum element in the priority queue
  void removeMin(); // Remove the minimum element from the priority queue

private:
  VectorCompleteTree<E> T;
  C isLess;

  typedef typename VectorCompleteTree<E>::Position Position;
};

// Implmentations of the methods for HeapQueue
template <typename E, typename C>
int HeapQueue<E, C>::size() const
{
  return T.size();
}

template <typename E, typename C>
bool HeapQueue<E, C>::empty() const
{
  return size() == 0;
}

template <typename E, typename C>
const E &HeapQueue<E, C>::min()
{
  return *(T.root());
}

template <typename E, typename C>
void HeapQueue<E, C>::removeMin()
{
  if (size() == 1)
  {
    T.removeLast();
  }
  else
  {
    Position u = T.root();
    T.swap(u, T.last());
    T.removeLast();

    while (T.hasLeft(u))
    {
      Position v = T.left(u);
      if (T.hasRight(u) && isLess(*(T.right(u)), *v))
      {
        v = T.right(u);
      }
      if (isLess(*v, *u))
      {
        T.swap(u, v);
        u = v;
      }
      else
      {
        break;
      }
    }
  }
}

template <typename E, typename C>
void HeapQueue<E, C>::insert(const E &e)
{
  T.addLast(e);
  Position v = T.last();
  while (!T.isRoot(v))
  {
    Position u = T.parent(v);
    if (!isLess(*v, *u))
      break;
    T.swap(v, u);
    v = u;
  }
}

#endif