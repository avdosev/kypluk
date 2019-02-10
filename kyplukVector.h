#ifndef _kypluk_Vector_
#define _kypluk_Vector_

#include <kyplukDefine.h>

template <class type>
class Vector {
	private:
    //vector <type> name;
        type *vector;
        size_t size=1;
        size_t realSize=1;
        class vectorIterator;
        friend class vectorIterator;


        void birn() {
            realSize= (realSize*3)/2 +1;
            type* mem=new type[realSize];
            memcpy(ret, vector, size*sizeof(type));
            /*
            ///
            ///
            */
        }
	public:
        using Iterator = vectorIterator;

        vector(size_t size=1) {
            vector=new type[size];
            this->size = realSize = size;
        }

        void pushBack(const type& val);
        void insert(int pos, type& value);
        void insert(Iterator pos, type& value);
        void resize(type count) {
        void popBack();
        void at(type pos);



};



    void Vector::pushBack(const type& val) {
        size+=1;
        vector[size] = val;
    }

    void Vector::insert(int pos, type& value) {
    }

    void Vector::insert(Iterator pos, type& value)
    {

    }

    void Vector::resize(type count) {
        if (this->size < count) {
        this->size=count;
        }
        else {
        //хм
        }
    }

    void Vector::popBack() {
        vector[this->size] = nullptr;
        this->size-=1;

    }

    type& Vector::operator[] (type const& pos)  {
        for (int it = 0; it<pos; ++it) {
            if
        }
    }
    const type& Vector::operator[](type const& pos ) const {

    }

    type& Vector::at(type pos) const {
        if (!(pos < this->size)) {
            throw "outOfRange";
        }
        else {
            return vector[pos];//элемент на поз
        }
    }

    type Vector::size() const {
        return this->size;
    }

    type Vector::front() const {
        return vector[0];
    }



















#endif
