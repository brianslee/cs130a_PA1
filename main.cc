#include <iostream>

#include "gtest/gtest.h"

#include "mmheap.h"

using namespace std;

TEST (MinMaxHeap, Test1) {
  vector<int32_t> vals = {7, 11, 9, 55, 22, 13, 29, 31, 3, -34, -5, 100, 103, 200, 205};
  minmaxheap::mmheap hp (50);
  
  hp.buildHeap (vals);
  ASSERT_EQ (hp.getMin (), -34);
  ASSERT_EQ (hp.getMax (), 205);
  
  hp.deleteMin ();
  ASSERT_EQ (hp.getMin (), -5);
  ASSERT_EQ (hp.getMax (), 205);

  hp.deleteMax ();
  ASSERT_EQ (hp.getMin (), -5);
  ASSERT_EQ (hp.getMax (), 200);
  
  hp.insert (300);
  ASSERT_EQ (hp.getMin (), -5);
  ASSERT_EQ (hp.getMax (), 300);

  hp.insert (-100);
  ASSERT_EQ (hp.getMin (), -100);
  ASSERT_EQ (hp.getMax (), 300);
}

TEST (MinMaxHeap, Test2) {
  vector<int32_t> vals = {7, 11, 9, 55, 22, 13, 29, 31, 3, -34, -5, 100, 103, 200, 205};
  vector<int32_t> vals2 = {99, 1, 32, 44, 12, 14, 25, 34, 343, -3, -5, 10, 133, 202, 250};
  minmaxheap::mmheap hp (50);

  hp.buildHeap (vals);
  ASSERT_EQ (hp.getMin (), -34);
  ASSERT_EQ (hp.getMax (), 205);

  hp.deleteMin ();
  ASSERT_EQ (hp.getMin (), -5);
  ASSERT_EQ (hp.getMax (), 205);

  //rebuild a min-max heap
  hp.buildHeap (vals2);
  ASSERT_EQ (hp.getMin (), -5);
  ASSERT_EQ (hp.getMax (), 343);

  hp.insert (300);
  ASSERT_EQ (hp.getMin (), -5);
  ASSERT_EQ (hp.getMax (), 343);

  hp.deleteMin ();
  ASSERT_EQ (hp.getMin (), -3);
  ASSERT_EQ (hp.getMax (), 343);

  hp.deleteMax ();
  ASSERT_EQ (hp.getMin (), -3);
  ASSERT_EQ (hp.getMax (), 300);
}

TEST (MinMaxHeap, Test3) {
  vector<int32_t> vals = {6};
  minmaxheap::mmheap hp (50);

  hp.buildHeap (vals);
  ASSERT_EQ (hp.getMin (), 6);
  ASSERT_EQ (hp.getMax (), 6);

  hp.deleteMin ();
  ASSERT_EQ (hp.getMin (), 0);
  ASSERT_EQ (hp.getMax (), 0);

  hp.insert (300);
  ASSERT_EQ (hp.getMin (), 300);
  ASSERT_EQ (hp.getMax (), 300);

  hp.deleteMax ();
  ASSERT_EQ (hp.getMin (), 0);
  ASSERT_EQ (hp.getMax (), 0);

  hp.insert (1);
  hp.insert (3);
  ASSERT_EQ (hp.getMin (), 1);
  ASSERT_EQ (hp.getMax (), 3);

  hp.deleteMax ();
  ASSERT_EQ (hp.getMin (), 1);
  ASSERT_EQ (hp.getMax (), 1);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}

