#ifndef _1_SAFEQUEUE_SAFEQUEUE_HPP
#define _1_SAFEQUEUE_SAFEQUEUE_HPP

#include <mutex>
#include <queue>

template <class T>
class SafeQueue {
public:
    SafeQueue() = default;

    T Pop() {
        std::lock_guard<std::mutex> lock(_mutex);
        if (!_queue.empty()) {
            T deleteItem;
            deleteItem = _queue.front();
            _queue.pop();
            return deleteItem;
        } else {
            throw std::out_of_range("queue is empty");
        }
    }

    void Push(const T& value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(value);
    }

    bool TryPop(T& value) {
        std::unique_lock<std::mutex> lock(_mutex, std::try_to_lock);
        if(!lock.owns_lock() && _queue.front() == value && !_queue.empty()){
            _queue.pop();
            return true;
        } else {
            return false;
        }
    }

private:
    std::mutex _mutex;
    std::queue<T> _queue;
};