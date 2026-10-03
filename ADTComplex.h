#pragma once
#include<iostream>
namespace ADT
{
	namespace ADTComplex 
	{
		typedef struct Complex
		{
			double real;
			double imag;
		}Complex;
		
		void Creat(Complex&, double = 0.0, double = 0.0);
		double GetReal(const Complex&);
		double GetImag(const Complex&);
		Complex Add(const Complex&, const Complex&);
		Complex Sub(const Complex&, const Complex&);
		Complex operator+(const Complex&, const Complex&);
		Complex operator-(const Complex&, const Complex&);
		std::ostream& operator<<(std::ostream&, const Complex&);
	}
}
