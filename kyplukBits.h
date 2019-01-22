#ifndef _kyplukBits_H_
#define _kyplukBits_H_

#include <kyplukTypedef.h>

class Bits {
	private:
		Size_t byte;
		static const Size_t _size = sizeof(Size_t) * 8;

		class Bit {
			private:
				int index;
				Bits * parent;
			public:
				Bit(int i, Bits * p) { //стандартный конструктор копирования здесь прекрасно подходит так что можно и без него
					index = i;
					parent = p;
				}

				Bit& operator = (bool value) {
					parent->set(index, value);
					return *this;
				}

				Bit& operator = (const Bit& copy) {
					parent->set(index, copy); //здесь происходит преобразование bit to bool
					return *this;
				}

				operator bool () const {
					return parent->at(index);
				}

		};
	public:
		Bits (Size_t bits) {
			byte = bits;
		}

		//_size-1 - убрать если нужно представление как в компудахтере
		bool at (Size_t i) const {
			if (i > _size) throw 0;
			int index = 1 << i; //побитовое умножение на два
			return (byte & index) != 0;
		}
		//#
		void flip(Size_t i) {
			if (i >= _size) throw 0;

			byte ^= 1 << i;
		}
		//#
		void set(Size_t i, bool value) {
			if (i >= _size) throw 0;
			int index = 1 << i; //побитовое умножение на два
			int val = value ? (~0) : 0; //по идее это должно заполнить 1 все, но пока это под вопросом
			byte = (index & val) | (byte & ~index);
		}

		void flip() {
			byte = ~byte ;
		}

		Size_t size() const {
			return _size;
		}

		Bit operator [] (int index) {
			return Bit(index, this);
		}
};

#endif
