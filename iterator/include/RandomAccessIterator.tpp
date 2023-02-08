/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.tpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:22:18 by jrocha            #+#    #+#             */
/*   Updated: 2023/02/03 10:49:20 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RandomAccessIterator.hpp"

	// Empty constructor
	template < class T >
	ft::RandomAccessIterator<T>::RandomAccessIterator(): _ptr() {}
	
	// Constructor with pointer
	template < class T >
	ft::RandomAccessIterator<T>::RandomAccessIterator(pointer p)
	{
		this->_ptr = ft::is_const(p);
	}
	
	// Copy constructor
	template < class T >
	template < class U >
	ft::RandomAccessIterator<T>::RandomAccessIterator(RandomAccessIterator<U> const &obj)
	{
		this->_ptr = ft::is_const(obj.base());
	}
	
	// Assignment operator
	template < class T >
	ft::RandomAccessIterator<T>& ft::RandomAccessIterator<T>::operator=(ft::RandomAccessIterator<T> const &obj)
	{
		if (this == &obj)
			return *this;
		this->_ptr = obj.base();
		return *this;
	}

	// Base - pointer to the first block
	template < class T >
	typename ft::RandomAccessIterator<T>::pointer ft::RandomAccessIterator<T>::base() const
	{
		return this->_ptr;
	}
	
	// Increment
	template <class T>
	ft::RandomAccessIterator<T>& ft::RandomAccessIterator<T>::operator++()
	{
		this->_ptr++;
		return *this;
	}

	// Return Iterator and Increment
	template <class T>
	ft::RandomAccessIterator<T> ft::RandomAccessIterator<T>::operator++(int)
	{
		ft::RandomAccessIterator<T> temp(*this);
		this->_ptr++;
		return (temp);
	}

	// Decrement
	template <class T>
	ft::RandomAccessIterator<T>& ft::RandomAccessIterator<T>::operator--()
	{
		this->_ptr--;
		return *this;
	}
	
	// Return Iterator and Decrement
	template <class T>
	ft::RandomAccessIterator<T> ft::RandomAccessIterator<T>::operator--(int)
	{
		ft::RandomAccessIterator<T> temp;
		temp._ptr = this->_ptr;
		this->_ptr--;
		return (temp);
	}

	// Increment iterator by n difference
	template <class T>
	ft::RandomAccessIterator<T> ft::RandomAccessIterator<T>::operator+(difference_type const &n) const
	{
		return this->_ptr + n; 
	}
	
	// Increment and assign iterator by n difference
	template <class T>
	ft::RandomAccessIterator<T> ft::RandomAccessIterator<T>::operator+=(difference_type const &n)
	{
		this->_ptr += n;
		return *this;
	}
	
	// Decrement iterator by n difference
	template <class T>
	ft::RandomAccessIterator<T> ft::RandomAccessIterator<T>::operator-(difference_type const &n) const
	{
		return this->_ptr - n;
	}
	
	// Decrement and assign iterator by n difference
	template <class T>
	ft::RandomAccessIterator<T> ft::RandomAccessIterator<T>::operator-=(difference_type const& n)
	{
		this->_ptr -= n;
		return *this;
	}

	// Return reference to iterator
	template <class T>
	typename ft::RandomAccessIterator<T>::reference ft::RandomAccessIterator<T>::operator*() const
	{
		return *this->_ptr;
	}
	
	// Return iterator pointer
	template <class T>
	typename ft::RandomAccessIterator<T>::pointer ft::RandomAccessIterator<T>::operator->() const
	{
		return this->_ptr;
	}

	// Subscription
	template <class T>
	typename ft::RandomAccessIterator<T>::reference ft::RandomAccessIterator<T>::operator[](difference_type n)
	{
		return *(this->_ptr + n);
	}

	template <typename lvalue, typename rvalue>
	bool operator==(ft::RandomAccessIterator<lvalue> const &lval, ft::RandomAccessIterator<rvalue> const &rval)
	{
		return lval.base() == rval.base();
	}

	template <typename lvalue, typename rvalue>
	bool operator!=(ft::RandomAccessIterator<lvalue> const &lval, ft::RandomAccessIterator<rvalue> const &rval)
	{
		return lval.base() != rval.base();
	}
	
	// Greater / Smaller than operators
	template <typename lvalue, typename rvalue>
	bool operator>(ft::RandomAccessIterator<lvalue> const &lval, ft::RandomAccessIterator<rvalue> const &rval)
	{
		return lval.base() > rval.base();
	}

	template <typename lvalue, typename rvalue>
	bool operator<(ft::RandomAccessIterator<lvalue> const &lval, ft::RandomAccessIterator<rvalue> const &rval)
	{
		return lval.base() < rval.base();
	}

	template <typename lvalue, typename rvalue>
	bool operator>=(ft::RandomAccessIterator<lvalue> const &lval, ft::RandomAccessIterator<rvalue> const &rval)
	{
		return lval.base() >= rval.base();
	}

	template <typename lvalue, typename rvalue>
	bool operator<=(ft::RandomAccessIterator<lvalue> const &lval, ft::RandomAccessIterator<rvalue> const &rval)
	{
		return lval.base() <= rval.base();
	}

	template <class Iter>
	ft::RandomAccessIterator<Iter> operator+(typename ft::RandomAccessIterator<Iter>::difference_type const n,
			ft::RandomAccessIterator<Iter> const& rval)
	{
		return (RandomAccessIterator<Iter>(rval.base() + n));
	}

	template <typename lvalue, typename rvalue>
	typename ft::RandomAccessIterator<lvalue>::difference_type operator-(ft::RandomAccessIterator<lvalue> const& lval,
			ft::RandomAccessIterator<rvalue> const& rval)
	{
		return lval.base() - rval.base();
	}