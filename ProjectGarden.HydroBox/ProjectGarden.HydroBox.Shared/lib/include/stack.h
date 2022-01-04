#ifndef PROJECT_GARDEN_HYDRO_BOX_SHARED_STACK_H
#define PROJECT_GARDEN_HYDRO_BOX_SHARED_STACK_H

#include <Arduino.h>
#include "iterator.h"

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Stack data structure.
     * @typedef T Data type to be stored in stack.
     */
    template <class T>
    class Stack : public Iterator<T>
    {
        public:
            /**
             * Initialize stack.
             */
            Stack()
            {
            }

            /**
             * Initialize stack with given elements.
             * @param elements Array of elements to initialize stack with.
             */
            Stack(T elements[])
            {
                byte elementCount = sizeof(*elements) / sizeof(elements[0]);

                for (byte i = 0; i < elementCount; i += 1)
                {
                    this->insert(elements[i]);
                }
            }

            /**
             * Add element to top of the stack.
             * @param element Element to be added.
             */
            void insert(T element)
            {
                IteratorNode<T>* newNode = new IteratorNode<T> { element, this->_begin };

                this->_begin = newNode;
            }

            /**
             * Add other stack elements to top of the stack.
             * @param other Other stack to pull elements from.
             */
            void insert(const Stack<T>& other)
            {
                for (T element : other)
                {
                    this->insert(element);
                }
            }
    };
}
}
}

#endif