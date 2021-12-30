#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <map>

/**
 * @brief Implements a LFUCache for integer keys (tag value)
 * 
 */
class LFUCache{
    public:
        /**
         * @brief Typedefs for lists.  Lists are used to ensure iterator validity
         * persists after random delete
         * 
         */
        using ListEntry = std::pair<int, int>; //{key, usage count}
        using List      = std::list<ListEntry>;
        using ListIter  = std::list<ListEntry>::iterator;

        /**
         * @brief Construct a new LFUCache object
         * 
         * @param capacity Maximum number of entries the cache can hold
         */
        LFUCache(int capacity) : capacity_(capacity){};
        LFUCache() : LFUCache(0){};
        ~LFUCache() = default;

        /**
         * @brief Returns the cached value for input key
         * 
         * @param key Tag value
         * @return int The cached value if one exists.  -1 otherwise.
         */
        int get(int key);

        /**
         * @brief Inserts a new {key: value} into the cache
         * 
         * @param key 
         * @param value 
         */
        void put(int key, int value);
    private:
        /**
         * @brief Increases usage count of key.
         * 
         * @param key 
         */
        void IncrementUsageCount(int key);

        /**
         * @brief Maximum number of entries the cache can hold.
         * 
         */
        int capacity_;
        
        /**
         * @brief {key: {value, iterator}}
         * 
         */
        std::unordered_map<int, std::pair<int, ListIter> > map_;

        /**
         * @brief {usage count : List}
         * 
         */
        std::map<int, List> lists_;
};

#endif /* LFUCACHE_H */