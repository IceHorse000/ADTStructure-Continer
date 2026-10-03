#include "ADTComplex.h"

using namespace ADT::ADTComplex;

void ADT::ADTComplex::Creat(Complex& C, double x, double y)
{
	C.real = x;
	C.imag = y;
}

double ADT::ADTComplex::GetReal(Complex const& C)
{
	return C.real;
}

double ADT::ADTComplex::GetImag(Complex const& C)
{
	return C.imag;
}

Complex ADT::ADTComplex::Add(const Complex& C1, const Complex& C2)
{
	return Complex(C1.real + C2.real, C1.imag + C2.imag);
}

Complex ADT::ADTComplex::Sub(const Complex& C1, const Complex& C2)
{
	return Complex(C1.real - C2.real, C1.imag - C2.imag);
}

Complex ADT::ADTComplex::operator+(const Complex& C1, const Complex& C2)
{
	return Add(C1,C2);
}

Complex ADT::ADTComplex::operator-(const Complex& C1, const Complex& C2)
{
	return Sub(C1,C2);
}

std::ostream& ADT::ADTComplex::operator<<(std::ostream& os, const Complex& C)
{
	os << C.real << '+' << C.imag << 'i';
	return os;
}
