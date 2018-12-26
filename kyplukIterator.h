#ifndef _kypluk_iterator_
#define _kupluk_iterator_

/*unilateral*/
template <class type>
class Iterator {
	public:
		virtual const Iterator & operator ++ () = 0;//++i
		virtual const Iterator & operator = (const Iterator&) {};// = 0 хз но почему то это не прокатывало
		virtual bool operator != (const Iterator&) {};//+ считай что это костыль в идеале это нужно исправить
		virtual bool operator == (const Iterator&) {};
		virtual bool operator <= (const Iterator&) {};
		virtual bool operator >= (const Iterator&) {};
		virtual type & operator * () = 0;
		virtual const type& operator * () const = 0;
		const type& at() const { return *(*this); } ;
};

template <class type>
class BIterator : Iterator<type> {
	//tyda - syda (-- and ++)
	public:
		virtual const BIterator & operator -- () = 0;
};

template <class type>
class RIterator : BIterator<type> {
	//tyda - syda (no na += and -=)
	public:
		virtual RIterator & operator += (const RIterator&) {};
		virtual RIterator & operator -= (const RIterator&) {};
};

#endif
