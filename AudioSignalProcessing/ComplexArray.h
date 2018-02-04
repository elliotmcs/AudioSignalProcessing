#pragma once
#include "stdafx.h"
ref class ComplexArray
{
public:
	Complex * c_array;
	int size = -1;
	ComplexArray(Complex *c_array, int size);
	int get_size();
	Complex get_at_index(int index);
};

