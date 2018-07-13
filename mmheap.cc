#include <iostream>
#include "mmheap.h"
#include <cstdint>
#include <vector>
#include <cstddef>
using namespace std;

namespace minmaxheap
{
  //Constructor
  mmheap::mmheap (uint32_t capacity)
  {
    _capacity = capacity;//set capacity to the given value
    _size = 0;//set size to zero
    _arr = new int32_t[capacity];//allocate an array of size capacity to _arr
  }

  //Destructor
  mmheap::~mmheap ()
  {
    delete [] _arr;
  }

  //find if you're at a min level
  bool mmheap::isAtMinLevel (uint32_t index) const
  {
    int32_t c = 0;//level counter
    int32_t i = index;//current index
    while(i > 0)// until indicator reaches 0
      {
	i = (i - 1) / 2;//go up to the current index's parent
	c++;//increase the counter
      }
    if(c % 2 == 0)//if the counter is even
      {
	return true;//the index was a min level
      }
    return false;//otherwise, it's a max level
  }

  //Drop element down according to pdf pseudocode
  void mmheap::percolateDown (uint32_t index)
  {
    //If the current level is a Min level
    if(isAtMinLevel(index))
      {
	percolateDownMin(index);
      }
    //If the current level is a Max level
    else
      {
	percolateDownMax(index);
      }
  }

  //helper-Percolate Down for Min according to pdf pseudocode
  void mmheap::percolateDownMin (uint32_t index)
  {
    //index of the smallest child or grandchild
    int32_t m = 0;
    //indexes of this node's children
    int32_t c1i = (index * 2) + 1;
    int32_t c2i = (index * 2) + 2;
    //indexes of this node's grandchildren
    int32_t g1i = (c1i * 2) + 1;
    int32_t g2i = (c1i * 2) + 2;
    int32_t g3i = (c2i * 2) + 1;
    int32_t g4i = (c2i * 2) + 2;
    //creating the pointers that will point to the descendents
    int32_t *c1 = NULL;
    int32_t *c2 = NULL;
    int32_t *g1 = NULL;
    int32_t *g2 = NULL;
    int32_t *g3 = NULL;
    int32_t *g4 = NULL;
    //pointing the pointers to the proper descendents, if out of bounds, set to NULL
    if(c1i < _size)
      {
	c1 = _arr + c1i;
	if(c2i < _size)
	  {
	    c2 = _arr + c2i;
	    if(g1i < _size)
	      {
		g1 = _arr + g1i;
		if(g2i < _size)
		  {
		    g2 = _arr + g2i;
		    if(g3i < _size)
		      {
			g3 = _arr + g3i;
			if(g4i < _size)
			  {
			    g4 = _arr + g4i;
			  }
		      }
		  }
	      }
	  }
      }
    
    //contianer to hold values for a swap
    int32_t temp;
    //value of smallest descendent's parent
    int32_t mPar = 0;

    //if the node has children/grandchildren, set m to the smallest one
    //and mPar to its parent
    if(c1 != NULL)
      {
	m = c1i;
	mPar = index;
      }
    if(c2 != NULL && *c2 < *(_arr + m))
      {
	m = c2i;
	mPar = index;
      }
    if(g1 != NULL && *g1 < *(_arr + m))
      {
	m = g1i;
	mPar = c1i;
      }
    if(g2 != NULL && *g2 < *(_arr + m))
      {
	m = g2i;
	mPar = c1i;
      }
    if(g3 != NULL && *g3 < *(_arr + m))
      {
	m = g3i;
	mPar = c2i;
      }
    if(g4 != NULL && *g4 < *(_arr + m))
      {
	m = g4i;
	mPar = c2i;
      }
    //if m is the grandchild of the index
    if(m == g1i || m == g2i || m == g3i || m == g4i)
      {
	if(*(_arr + m) < *(_arr + index))
	  {
	    //swap their values
	    temp = *(_arr + m);
	    *(_arr + m) = *(_arr + index);
	    *(_arr + index) = temp;

	    //if the value at m now is larger than its new parent
	    if(*(_arr + m) > *(_arr + mPar))
	      {
		//swap their values;
		temp = *(_arr + m);
		*(_arr + m) = *(_arr + mPar);
		*(_arr + mPar) = temp;
	      }//close if(*(_arr + m) > *(_arr + mPar))

	    //percolate down the new value at m
	    percolateDownMin(m);
	  }// close if(*(_arr + m) < *(_arr + index))
      }//close if if(m == g1i || m == g2i || m == g3i || m == g4i)
    else if(m == c1i || m == c2i)
      {
	//if the value at m is less than its parent
	if(*(_arr + m) < *(_arr + index))
	  {
	    //swap their values
	    temp = *(_arr + m);
	    *(_arr + m ) = *(_arr + index);
	    *(_arr + index) = temp;
	  }//close if(*(_arr + m) < *(_arr + index))
      }//close else if(m == c1i || m == c2i)
    
    
    //remove dangling pointers
    c1, c2, g1, g2, g3, g4 = NULL;
  }

  //Helper-Percolate Down for Max accoding to pdf pseudocode
  void mmheap::percolateDownMax (uint32_t index)
  {
    //index of the smallest child or grandchild
    int32_t m;
    //indexes of this node's children
    int32_t c1i = (index * 2) + 1;
    int32_t c2i = (index * 2) + 2;
    //indexes of this node's grandchildren
    int32_t g1i = (c1i * 2) + 1;
    int32_t g2i = (c1i * 2) + 2;
    int32_t g3i = (c2i * 2) + 1;
    int32_t g4i = (c2i * 2) + 2;
    //creating the pointers that will point to the descendents
    int32_t *c1 = NULL;
    int32_t *c2 = NULL;
    int32_t *g1 = NULL;
    int32_t *g2 = NULL;
    int32_t *g3 = NULL;
    int32_t *g4 = NULL;
    //pointing the pointers to the proper descendents
    if(c1i < _size)
      {
	c1 = _arr + c1i;
	if(c2i < _size)
	  {
	    c2 = _arr + c2i;
	    if(g1i < _size)
	      {
		g1 = _arr + g1i;
		if(g2i < _size)
		  {
		    g2 = _arr + g2i;
		    if(g3i < _size)
		      {
			g3 = _arr + g3i;
			if(g4i < _size)
			  {
			    g4 = _arr + g4i;
			  }
		      }
		  }
	      }
	  }
      }
    
    //contianer to hold values for a swap
    int32_t temp;
    //value of smallest descendent's parent
    int32_t mPar;

    //if the node has children/grandchildren, set m to the largest one
    //and mPar to its parent
    if(c1 != NULL)
      {
	m = c1i;
	mPar = index;
      }
    if(c2 != NULL && *c2 > *(_arr + m))
      {
	m = c2i;
	mPar = index;
      }
    if(g1 != NULL && *g1 > *(_arr + m))
      {
	m = g1i;
	mPar = c1i;
      }
    if(g2 != NULL && *g2 > *(_arr + m))
      {
	m = g2i;
	mPar = c1i;
      }
    if(g3 != NULL && *g3 > *(_arr + m))
      {
	m = g3i;
	mPar = c2i;
      }
    if(g4 != NULL && *g4 > *(_arr + m))
      {
	m = g4i;
	mPar = c2i;
      }
    //if m is the grandchild of the index
    if(m == g1i || m == g2i || m == g3i || m == g4i)
      {
	if(*(_arr + m) > *(_arr + index))
	  {
	    //swap their values
	    temp = *(_arr + m);
	    *(_arr + m) = *(_arr + index);
	    *(_arr + index) = temp;

	    //if the value at m now is smaller than its new parent
	    if(*(_arr + m) < *(_arr + mPar))
	      {
		//swap their values;
		temp = *(_arr + m);
		*(_arr + m) = *(_arr + mPar);
		*(_arr + mPar) = temp;
	      }//close if(*(_arr + m) < *(_arr + mPar))

	    //percolate down the new value at m
	    percolateDownMax(m);
	  }// close if(*(_arr + m) > *(_arr + index))
      }//close if if(m == g1i || m == g2i || m == g3i || m == g4i)
    else if(m == c1i || m == c2i)
      {
	//if the value at m is greater than its parent
	if(*(_arr + m) > *(_arr + index))
	  {
	    //swap their values
	    temp = *(_arr + m);
	    *(_arr + m ) = *(_arr + index);
	    *(_arr + index) = temp;
	  }//close if(*(_arr + m) > *(_arr + index))
      }//close else if(m == c1i || m == c2i)
    
    //remove dangling pointers
    c1, c2, g1, g2, g3, g4 = NULL;
  }

  //Percolate Up function according to pdf pseudocode
  void mmheap::percolateUp (uint32_t index)//Causes Segault when parent is accessed
  {
    uint32_t parentI = (index - 1) / 2;
    //if this is a Min Level
    if(isAtMinLevel(index))
      {
	//if there is a parent(at a Max Level)
	if(index != 0)
	  {
	    //if the current value is greater than its parent(in the Max Level)
	    if(*(_arr + index) > *(_arr + parentI))
	      {
		//swap the values of the two
		int32_t temp = *(_arr + index);
		*(_arr + index) = *(_arr + parentI);
		*(_arr + parentI) = temp;
		//Send up the parent
		percolateUpMax(parentI);
	      }//closes if statement for parent comparison
	    else
	      {
		percolateUpMin(index);
	      }//closes else statement for parent comparison
	  }//closes the if a parent exists statement
      }//closes Min Level if statement

    //if on Max Level
    else
      {
	//if a parent exists(in the min level)
	if(index != 0)
	  {
	    //if the value at the index is less than its parent
	    if(*(_arr + index) < *(_arr + parentI))
	      {
		//swap values
		int32_t temp = *(_arr + index);
		*(_arr + index) = *(_arr + parentI);
		*(_arr + parentI) = temp;
		percolateUpMin(parentI);
	      }
	    //if the value is greater than its parent
	    else
	      {
		percolateUpMax(index);
	      }
	  }
      }
  }

  //Percolate Up Min function according to pdf pseudocode
  void mmheap::percolateUpMin (uint32_t index)//segfault related?
  {
    uint32_t parentI = (index - 1) / 2;
    uint32_t grandparentI = (parentI - 1) / 2;
    
    //if there is a grandparent
    if(parentI != 0 && index != 0)
      {
	//if that grandparent is larger than the current index
	if(*(_arr + index) < *(_arr + grandparentI))
	  {
	    //swap their values
	    int32_t temp = *(_arr + index);
	    *(_arr + index) = *(_arr + grandparentI);
	    *(_arr + grandparentI) = temp;
	  }
      }
  }

  //Percolate Up Max function according to pdf pseudocode
  void mmheap::percolateUpMax (uint32_t index)//segfault related?
  {
    uint32_t parentI = (index - 1) / 2;
    uint32_t grandparentI = (parentI - 1) / 2;
    
    //if there is a grandparent
    if(parentI != 0 && index != 0)
      {
	//if that grandparent is smaller than the current index
	if(*(_arr + index) > *(_arr + grandparentI))
	  {
	    //swap their values
	    int32_t temp = *(_arr + index);
	    *(_arr + index) = *(_arr + grandparentI);
	    *(_arr + grandparentI) = temp;
	  }
      }
  }

  //insert function
  void mmheap::insert(int32_t val)//segfault related?
  {
    //set the value of the last leaf to the inserted value
    *(_arr + _size) = val;
    //restore order
    percolateUp(_size);
    //increase size
    _size += 1;
  }
  
  //buildHeap function
  void mmheap::buildHeap (const vector<int32_t> &vals)//causes segfault
  {
    //clear the heap
    _size = 0;
    //take each value in the vector
    for(int i = 0; i < vals.size(); i++)
      {
	//insert it into the heap
	insert(vals.at(i));
      }
  }

  //getMin function
  int32_t mmheap::getMin () const
  {
    //return min value (first value in heap)
    return *_arr;
  }

  //getMax function
  int32_t mmheap::getMax () const
  {
    //if heap is size 1 or 0
    if(_size == 1)
      {
	return *_arr;
      }
    //if max value is first child
    else if(*(_arr + 1) > *(_arr + 2))
      {
	//return max value
	return *(_arr + 1);
      }
    //if max value is second child
    else
      {
	//return max value
	return *(_arr + 2);
      }
  }

  //deleteMin function
  void mmheap::deleteMin ()
  {
    uint32_t lastIndex = _size - 1;
    //set min value to last leaf in heap
    *_arr = *(_arr + lastIndex);
    *(_arr + lastIndex) = 0;
    //reduce size
    _size -= 1;
    //restore order
    percolateDown(0);

    //if _size = 0;
    if(_size == 0)
      {
	for(int i = 0; i < _capacity; ++i)
	  {
	    *(_arr + i) = 0;
	  }
      }
  }

  //deleteMax function
  void mmheap::deleteMax ()
  {
    uint32_t lastIndex = _size - 1;
    if(_size == 1)
      {
	*_arr = 0;
	_size -= 1;
	for(int i = 0; i < _capacity; ++i)
	  {
	    *(_arr + i) = 0;
	  }
      }
    //if max value is first child
    else if(*(_arr + 1) > *(_arr + 2))
      {
	//set max value to last leaf in heap
	*(_arr + 1) = *(_arr + lastIndex);
	*(_arr + lastIndex) = 0;
	//reduce size
	_size -= 1;
	//restore order
	percolateDown(1);
      }
    //if max value is second child
    else
      {
	//set max value to last leaf in heap
	*(_arr + 2) = *(_arr + lastIndex);
	*(_arr + lastIndex) = 0;
	//reduce size
	_size -= 1;
	//restore order
	percolateDown(2);
      }
  }
}
