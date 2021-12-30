# LFUCache

A LFU (least frequently used) cache is a cache with a two-tier eviction policy.  First, the cache considers the set of entries that have been accessed the least amount of times.  From this set, the oldest entry is evicted.

## Implementation

This is a C++ implementation for a LFUCache with a configurable maximum capacity that stores integer values using integer keys (tags).  The `LFUCache` is implemented in `LFUCache.h` and `LFUCache.cc`.  `test.cc` contains unit tests that use the [Google Test Framework](https://github.com/google/googletest).  Inspiration for this comes from https://leetcode.com/problems/lfu-cache/.

The provided Makefile assumes Google Test is installed on your machine.
