#pragma once

#include "define.h"

namespace kypluk {

template <class type, class container_t>
class Stack {
    private:
        container_t container;
    public:
        Stack() = default;
        Stack(const Stack &other) = default;
        Stack(Stack&& other) = default;

        ~Stack() = default;


        type& top() {
            return container.back();
        }


        bool empty() {
            return container.empty();
        }


        auto size() {
            return container.size();
        }


        void push(const type& value) {
            container.push_back(value);
        }


        void pop() {
            container.pop_back();
        }


        void clear() {
            container.clear();
        }


        Stack& operator = (const Stack &copy) = default;
        Stack& operator = (Stack&& copy) = default;
		
};

}
