#include "stdafx.h"
#include "ComplexArray.h"
#include <stdexcept>

ComplexArray::ComplexArray(Complex *c_array, int size)
{
	this->c_array = c_array;
	this->size = size;
}

int ComplexArray::get_size() {
	if (this->size != -1) {
		return this->size;
	}
	else {
		int size = 0;
		for (; ; size++) {
				this->c_array[size];
		}
		return size;
	}
	return -1;
}

Complex ComplexArray::get_at_index(int index) {
	if (index >= this->size) {
		throw std::out_of_range("Index out of range");
	}
	for (int i = 0; i < size; i++) {
		if (i == index) {
			return this->c_array[i];
		}
	}
}