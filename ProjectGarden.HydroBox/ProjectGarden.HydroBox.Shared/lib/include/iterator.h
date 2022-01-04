#ifndef PROJECT_GARDEN_HYDRO_BOX_SHARED_ITERATOR_H
#define PROJECT_GARDEN_HYDRO_BOX_SHARED_ITERATOR_H

namespace ProjectGarden
{
namespace HydroBox
{
namespace Shared
{
    /**
     * Iterator node for storing an element in a sequence.
     * @class T Element data type.
     */
    template <class T>
    struct IteratorNode
    {
        /**
         * Data.
         */
        T data;

        /**
         * Pointer to next node in sequence.
         */
        IteratorNode* nextNode;
    };

    /**
     * Iterator for managing iterating over a sequence.
     * @class T Sequence element data type.
     */
    template <class T>
    class Iterator
    {
        public:
            /**
             * Deconstruct iterator.
             */
            virtual ~Iterator()
            {
                IteratorNode<T>* deleteMe;

                while (this->_begin != nullptr)
                {
                    deleteMe = this->_begin;
                    this->_begin = this->_begin->nextNode;

                    delete deleteMe;
                }
            }

            /**
             * Check if iterator is empty.
             * @return True if iterator is empty, otherwise false.
             */
            bool isEmpty() const
            {
                return this->_begin->nextNode == nullptr;
            }

            /**
             * Reset iterator and get first element.
             * @return Pointer to first element in sequence.
             */
            T* begin() const
            {
                this->_current = nullptr;

                return &this->_begin->data;
            }

            /**
             * Get last element.
             * @return Pointer to last element in sequence.
             */
            T* end() const
            {
                return &_end->data;
            }

            /**
             * Advance iterator and get current element.
             * @return Pointer to current element in sequence.
             */
            T* next() const
            {
                if (this->_current == nullptr)
                {
                    this->_current = this->_begin;
                }
                else
                {
                    this->_current = this->_current->nextNode;
                }

                return &this->_current->data;
            }

        protected:
            /**
             * Pointer to first iterator node.
             */
            mutable IteratorNode<T>* _begin = nullptr;

            /**
             * Pointer to last iterator node.
             */
            mutable IteratorNode<T>* _end = nullptr;

            /**
             * Pointer to current iterator node.
             */
            mutable IteratorNode<T>* _current = nullptr;
    };
}
}
}

#endif