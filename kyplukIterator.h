#ifndef _kypluk_iterator_
#define _kypluk_iterator_

/*unilateral*/
template <class type>
class Iterator {
	public:
		virtual Iterator & operator ++ ();//++i
		virtual const Iterator operator ++ (int);//i++
		virtual const Iterator & operator = (const Iterator&);
		virtual bool operator != (const Iterator&);
		virtual bool operator == (const Iterator&);
		virtual type & operator * ();
		virtual const type& operator * () const;
};

template <class type>
class BIterator : Iterator<type> {
	//tyda - syda (-- and ++)
	public:
		virtual const BIterator & operator -- ();
		virtual const BIterator & operator -- (int);
};

template <class type>
class RIterator : BIterator<type> {
	//tyda - syda += and -=
	public:
		virtual RIterator & operator += (const RIterator&);
		virtual RIterator & operator -= (const RIterator&);
		virtual type& operator [] (int);
		
		/*
		virtual bool operator <= (const Iterator&);
		virtual bool operator >= (const Iterator&);
		*/
};

#endif
