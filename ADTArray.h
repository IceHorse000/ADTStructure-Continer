#pragma once
#include<memory>
#include<utility>
#include<concepts>
#include"ADTHelper.h"
ADTBEGIN
ADTSUBBEGIN(Array)

//Possible Version But Not Recommend:
#ifdef _EXPERIMENT
template<typename ElemType,size_t N>
struct ArrayBase
{
	ADTARRATTYPE _data;
	size_t length;
	ArrayBase()
	{
		_data = std::make_unique<ElemType[]>(N);
		length = N;
	}
	ElemType Value(size_t index)const 
	{
		if (index >= length)return ElemType{};
		return _data[index];
	}
	bool Assign(size_t index,ElemType value)
	{
		if (index >= length)return false;
		_data[index] = std::move(value);
		return true;
	}
	ElemType& operator[](size_t index)
	{
		if (index >= length)throw std::invalid_argument("Out_of_range");
		return _data[index];
	}
	const ElemType& operator[](size_t index)const
	{
		if (index >= length)throw std::invalid_argument("Out_of_range");
		return _data[index];
	}
	~ArrayBase()
	{
		_data.reset();
		length = 0;
	}
};

/*impl*/
template<typename T, size_t ...NN>struct ArrayT;

template<typename T,size_t N1,size_t ...NN>
struct ArrayT<T,N1,NN...>:public ArrayT<T,NN...>
{
	using type = ArrayBase<typename ArrayT<T, NN...>::type, N1>;
};

template<typename T,size_t N>
struct ArrayT<T, N>
{
	using type = ArrayBase<T, N>;
};

template<typename T,size_t ...NN>
struct Array
{
	ArrayT<T, NN...>::type _data;
	template<size_t I,size_t ...Rest,typename Arr>
	T& get_impl(const Arr& arr)
	{
		if constexpr (sizeof ...(Rest) == 0)
			return arr._data[I];
		else
			return get_impl<Rest...>(arr._data[I]);
	}
	template<size_t I,size_t ...Rest>
	T Value()
	{
		if (I >= _data.length)return T{};
		return get_impl<I, Rest...>(_data);
	}
	template<size_t I,size_t ...Rest>
	bool Assign(T value)
	{
		if (I >= _data.length)return false;
		auto& elem = get_impl<I, Rest...>(_data);
		elem = std::move(value);
		return true;
	}
};

template<typename T>
struct VectorBase
{
	std::unique_ptr<T[]> _data;
	size_t length;
	using element_type = T;
	VectorBase(size_t n = 0)
	{
		_data = std::make_unique<T[]>(n == 0 ? ADTMAXSIZE : 1.2 * n);
		length = n;
	}
	T& operator[](size_t index)
	{
		if (index >= length)throw std::invalid_argument("Out_of_range");
		return _data[index];
	}
	const T& operator[](size_t index)const
	{
		if (index >= length)throw std::invalid_argument("Out_of_range");
		return _data[index];
	}
};

template<typename T, typename ...I>
requires (std::is_integral_v<I>&&...)
struct VectorT;

template<typename T,typename Dim1,typename ...DimN>
requires std::is_integral_v<Dim1>&&(...&&std::is_integral_v<DimN>)
struct VectorT<T, Dim1, DimN...> :public VectorT<T, DimN...>
{
	using type = VectorBase<typename VectorT<T, DimN...>::type>;
};

template<typename T>
struct VectorT<T>
{
	using type = VectorBase<T>;
};

template<typename T, typename ...DimN>
requires (std::is_integral_v<DimN>&&...)
struct Vector;

template<typename T,typename Dim1,typename ...DimN>
struct Vector<T, Dim1, DimN...>
{
	VectorT<T, Dim1, DimN...>::type _data;
	template<typename Inner,typename First,typename ...Rest>
	static void Init_recurive(Inner&obj,First first,Rest...rest)
	{
		obj = Inner(static_cast<size_t>(first));
		if constexpr (sizeof...(Rest) > 0)
		{
			for (size_t i = 0; i < obj.length; ++i)
				Init_recurive(obj._data[i], rest...);
		}

	}
	Vector(Dim1 dim1, DimN...dimN):_data(static_cast<size_t>(dim1))
	{
		if constexpr (sizeof ...(DimN) > 0)
		{
			using Inner = VectorT<T, DimN...>::type;
			for (auto i = 0; i < _data.length; i++)
			{
				Inner temp;
				Init_recurive(temp, dimN...);
				_data[i] = std::move(temp);
			}
		}
	};
};


template<typename T>
struct Vector<T>
{
	VectorT<T>::type _data;
	template<typename Dim>
	requires std::is_integral_v<Dim>
	Vector(Dim dim)
		: _data(static_cast<size_t>(dim))
	{
	}
};
#else

ADTCLASSBEGIN(Array)
{
	ADTARRATTYPE _data;
	size_t dim_count = 1;
	std::unique_ptr<size_t[]> dims_length;
	std::unique_ptr<size_t[]> dims_ranges;
}ADTCLASSEND;

template<typename Dim1,typename ...DimN>
requires std::is_integral_v<Dim1>&&(std::is_integral_v<DimN>&&...)
size_t CalculateDimLength(std::unique_ptr<size_t[]>&p, size_t idx, Dim1 d1, DimN ...dn)
{
	p[idx] = static_cast<size_t>(d1);
	if constexpr (sizeof...(dn) > 0)
		return d1*CalculateDimLength(p, idx + 1, dn...);
	else
		return d1;
}

template<typename Dim>
requires std::is_integral_v<Dim>
size_t CalculateDimLength(std::unique_ptr<size_t[]>& p, size_t idx, Dim d)
{
	p[idx] = static_cast<size_t>(d);
	return d;
}

template<typename Dim1,typename ...DimN>
void CalculateDimRange(std::unique_ptr<size_t[]>& p, size_t total, size_t curr_dim, Dim1 d1, DimN ...dn)
{
	p[curr_dim] = total / d1;
	if constexpr (sizeof...(DimN) > 0)
		CalculateDimRange(p, total / d1, curr_dim + 1, dn...);
}


template<typename ElemType, typename ...DimN>
requires (std::is_integral_v<DimN>&&...) && (sizeof...(DimN) > 0)
void InitArray(ADTINOUT(Array)A,DimN ...dn) 
{
	A.dim_count = sizeof...(dn);
	A.dims_length = std::make_unique<size_t[]>(A.dim_count);
	A.dims_ranges = std::make_unique<size_t[]>(A.dim_count);
	auto total = CalculateDimLength(A.dims_length, 0, dn...);
	CalculateDimRange(A.dims_ranges, total, 0, dn...);
	A._data = std::make_unique<ARGTYPE[]>(total);
};
ADTFUNCBEGIN
ASSIGNDESTORY(Array, A)
{
	A._data.reset();
	A.dims_length.reset();
	A.dim_count = 1;
}ADTFUNCEND;

template<typename T,typename Dim1,typename ...DimN>
T& get_elem(Array<T>const& A, size_t curr_dim,size_t base,Dim1 d1, DimN ...dn)
{
	if (d1 >= A.dims_length[curr_dim])throw std::out_of_range("Index_out_of_range");
	base += d1 * A.dims_ranges[curr_dim];
	if constexpr (sizeof ...(dn) > 0)
	{
		return get_elem(A, curr_dim + 1, base, dn...);
	}
	else
		return A._data[base];
}

template<typename T, typename ...DimN>
	requires (std::is_integral_v<DimN>&&...) && (sizeof...(DimN) > 0)
T Value(Array<T>& A, DimN ...dn)
{
	try
	{
		T res = get_elem(A,0,0, dn...);
		return res;
	}
	catch (const std::exception&)
	{
		return T{};
	}
}
template<typename T,typename ...DimN>
	requires (std::is_integral_v<DimN>&&...) && (sizeof...(DimN) > 0)
bool Assign(Array<T>& A, T value,DimN ...dn)
{
	try
	{
		get_elem(A, 0, 0, dn...) = std::move(value);
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

#endif


ADTSUBEND;
ADTEND;