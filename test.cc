#include <iostream>
#include "LFUCache.h"
#include "gtest/gtest.h"

TEST(LFUCache, tests) {
    //Capacity of 5
    LFUCache lfu_cache(5);

    //Empty cache shouldn't find anything
    ASSERT_EQ(lfu_cache.get(5), -1);

    //expected state after put():
    //1 usage: key=1
    lfu_cache.put(1, 2);

    //expected state after get():
    //2 usage: key=1
    ASSERT_EQ(lfu_cache.get(1), 2);

    //expected state after put():
    //2 usage: key=1
    //1 usage: key=2
    lfu_cache.put(2, 4);

    //expected state after put():
    //2 usage: key=1
    //1 usage: key=3 -> key=2
    lfu_cache.put(3, 6);

    //expected state after put():
    //2 usage: key=1
    //1 usage: key=4 -> key=3 -> key=2
    lfu_cache.put(4, 8);

    //expected state after get():
    //2 usage: key=4 -> key=1
    //1 usage: key=3 -> key=2
    ASSERT_EQ(lfu_cache.get(4), 8);

    //expected state after put():
    //2 usage: key=4 -> key=1
    //1 usage: key=5 -> key=3 -> key=2
    lfu_cache.put(5,10);

    //expected state after put():
    //2 usage: key=4 -> key=1
    //1 usage: key=6 -> key=5 -> key=3
    lfu_cache.put(6,12);

    //key=2 should be evicted as it was the oldest
    //in the set of 1 usage
    ASSERT_EQ(lfu_cache.get(2), -1);

    //expected state after put():
    //2 usage: key=4 -> key=1
    //1 usage: key=7 -> key=6 -> key=5
    lfu_cache.put(7,14);

    ASSERT_EQ(lfu_cache.get(3), -1);

    //expected state after gets():
    //3 usage: key = 5
    //2 usage: key = 6 -> key=7 -> key = 4 -> key = 1
    ASSERT_EQ(lfu_cache.get(7), 14);
    ASSERT_EQ(lfu_cache.get(6), 12);
    ASSERT_EQ(lfu_cache.get(5), 10);
    ASSERT_EQ(lfu_cache.get(5), 10);

    lfu_cache.put(8,16);
    lfu_cache.get(8);
    lfu_cache.get(8);
    ASSERT_EQ(lfu_cache.get(1), -1);

    lfu_cache.put(9,18);
    lfu_cache.get(9);
    lfu_cache.get(9);
    ASSERT_EQ(lfu_cache.get(4), -1);

    lfu_cache.put(10,20);
    lfu_cache.get(10);
    lfu_cache.get(10);
    ASSERT_EQ(lfu_cache.get(7), -1);

    lfu_cache.put(11,22);
    lfu_cache.get(11);
    lfu_cache.get(11);
    ASSERT_EQ(lfu_cache.get(6), -1);

    lfu_cache.put(12,24);
    ASSERT_EQ(lfu_cache.get(5), -1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}