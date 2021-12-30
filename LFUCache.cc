#include "LFUCache.h"

void LFUCache::IncrementUsageCount(int key){
    //Increment usage count
    auto new_count = ++(map_[key].second->second);

    //Remove ListEntry from 'old_count' List and insert at the front of 'new_count' List
    lists_[new_count].splice(lists_[new_count].begin(), lists_[new_count-1], map_[key].second);

    //If 'old_count' List is empty, remove it from the ordered map
    //This enables lists_.begin() to always find a non-empty List
    if(lists_[new_count-1].empty())
        lists_.erase(new_count-1);
}

int LFUCache::get(int key) {
    if(map_.count(key) == 0)
        return -1;

    IncrementUsageCount(key);
    
    return map_[key].first;
}

void LFUCache::put(int key, int value) {
    if(capacity_ == 0)
        return;
    
    if(map_.count(key) == 1){
        map_[key].first = value;
        IncrementUsageCount(key);
    } else {
        if(map_.size() == capacity_){
            //Erase the oldest of the smallest count
            map_.erase(lists_.begin()->second.back().first);
            lists_.begin()->second.pop_back();
            if(lists_.begin()->second.empty())
                lists_.erase(lists_.begin());

        }

        //Insert at front of lists_[1]
        lists_[1].push_front({key, 1});
        map_[key] = {value, lists_[1].begin()};
    }
}