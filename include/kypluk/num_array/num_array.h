#pragma once

template <class array_t, class num_t> 
class NumArray {
	private:
		array_t array;
	public:
		~NumArray() {
			// EMPTY
		}
		
		NumArray() {
			// EMPTY
		}
		
		NumArray(array_t value) : array(value) {
			// EMPTY
		}
		
		NumArray(const NumArray &other) : array(other.array) {
			// EMPTY
		}
		
		NumArray(NumArray &&other) : array(other.array) {
			// EMPTY
		}
		
		num_t sum() {
			num_t res = 0;
			for (auto i = 0; i < array.size(); i++) {
				res += array[i];
			}
			return res;
		}
		
		num_t min() {
			num_t min = array[0];
			for (auto i = 1; i < array.size(); i++) {
				if (array[i] < min)
					min = array[i];
			}
			return min;
		}
		
		num_t max() {
			num_t max = array[0];
			for (auto i = 1; i < array.size(); i++) {
				if (array[i] > max)
					max = array[i];
			}
			return max;
		}
		
		num_t mean() {
			return this->sum()/array.size();
		}
		
		NumArray& operator += (NumArray other) {
			for (auto i = 0; i < array.size(); i++) {
				this->array[i] += other.array[i]; 
			}
			
			return *this;
		} 
		
		NumArray& operator *= (NumArray other) {
			for (auto i = 0; i < array.size(); i++) {
				this->array[i] *= other.array[i];
			}
			
			return *this;
		}
		
		NumArray& operator -= (NumArray other) {
			for (auto i = 0; i < array.size(); i++) {
				this->array[i] -= other.array[i];
			}
			
			return *this;
		}
		
		NumArray& operator /= (NumArray other) {
			for (auto i = 0; i < array.size(); i++) {
				this->array[i] /= other.array[i];
			}
			
			return *this;
		}
		
		NumArray& operator += (num_t other) {
			for (auto i = 0; i < array.size(); i++) {
				this->array[i] += other; 
			}
			
			return *this;
		} 
		
		NumArray& operator *= (num_t other) {
			for (auto i = 0; i < array.size(); i++) {
				this->array[i] *= other;
			}
			
			return *this;
		}
		
		NumArray& operator -= (num_t other) {
			for (auto i = 0; i < array.size(); i++) {
				this->array[i] -= other;
			}
			
			return *this;
		}
		
		NumArray& operator /= (num_t other) {
			for (auto i = 0; i < array.size(); i++) {
				this->array[i] /= other;
			}
			
			return *this;
		}
		
		friend NumArray operator + (NumArray first, const NumArray& second) { return move(first += second); }
		friend NumArray operator - (NumArray first, const NumArray& second) { return move(first -= second); }
		friend NumArray operator * (NumArray first, const NumArray& second) { return move(first *= second); }
		friend NumArray operator / (NumArray first, const NumArray& second) { return move(first /= second); }
		
		friend NumArray operator + (NumArray first, num_t second) { return move(first += second); }
		friend NumArray operator - (NumArray first, num_t second) { return move(first -= second); }
		friend NumArray operator * (NumArray first, num_t second) { return move(first *= second); }
		friend NumArray operator / (NumArray first, num_t second) { return move(first /= second); }
		
		NumArray& operator = (const NumArray& other) {
			if (this != &other) {
				this->array = other.array;
			}
			return *this;
		}
		
		array_t& data() {
			return this->array;
		}
		
};
