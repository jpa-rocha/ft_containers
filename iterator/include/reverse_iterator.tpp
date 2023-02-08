/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:07:34 by jrocha            #+#    #+#             */
/*   Updated: 2023/02/03 10:29:02 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_iterator.hpp"

// Empty constructor
	template < typename T >
	ft::reverse_iterator<T>::reverse_iterator(): _ptr(iterator_type()) {}
	
	// Constructor with pointer
	template < typename T >
	ft::reverse_iterator<T>::reverse_iterator(iterator_type iter)
	{
		this->_ptr = iter.base();
	}
	
	// Copy constructor
	template < typename T >
	template <typename U>
	ft::reverse_iterator<T>::reverse_iterator(reverse_iterator<U> const &obj)
	{
		this->_ptr = obj.base();
	}
	
	// Assignment operator
	template < typename T >
	ft::reverse_iterator<T>& ft::reverse_iterator<T>::operator=(ft::reverse_iterator<T> const &obj)
	{
		if (this == &obj)
			return *this;
		this->_ptr = obj.base();
		return *this;
	}

	// Base - pointer to the first block
	template < typename T >
	typename ft::reverse_iterator<T>::iterator_type ft::reverse_iterator<T>::base() const
	{
		return this->_ptr;
	}
	
	// Increment
	template <typename T>
	ft::reverse_iterator<T>& ft::reverse_iterator<T>::operator++()
	{
		this->_ptr--;
		return *this;
	}

	// Return Iterator and Increment
	template <typename T>
	ft::reverse_iterator<T> ft::reverse_iterator<T>::operator++(int)
	{
		ft::reverse_iterator<T> temp;
		temp._ptr = this->_ptr;
		this->_ptr--;
		return (temp);
	}

	// Decrement
	template <typename T>
	ft::reverse_iterator<T>& ft::reverse_iterator<T>::operator--()
	{
		this->_ptr++;
		return *this;
	}
	
	// Return Iterator and Decrement
	template <typename T>
	ft::reverse_iterator<T> ft::reverse_iterator<T>::operator--(int)
	{
		ft::reverse_iterator<T> temp;
		temp._ptr = this->_ptr;
		this->_ptr++;
		return (temp);
	}

	// Increment iterator by n difference
	template <typename T>
	ft::reverse_iterator<T> ft::reverse_iterator<T>::operator+(difference_type const &n) const
	{
		return reverse_iterator(this->_ptr - n); 
	}
	
	// Increment and assign iterator by n difference
	template <typename T>
	ft::reverse_iterator<T> ft::reverse_iterator<T>::operator+=(difference_type const &n)
	{
		this->_ptr -= n;
		return *this;
	}
	
	// Decrement iterator by n difference
	template <typename T>
	ft::reverse_iterator<T> ft::reverse_iterator<T>::operator-(difference_type const &n) const
	{
		return reverse_iterator(this->_ptr + n);
	}
	
	// Decrement and assign iterator by n difference
	template <typename T>
	ft::reverse_iterator<T> ft::reverse_iterator<T>::operator-=(difference_type const &n)
	{
		this->_ptr += n;
		return *this;
	}

	// Return reference to iterator
	template <typename T>
	typename ft::reverse_iterator<T>::reference ft::reverse_iterator<T>::operator*() const
	{
		iterator_type tmp = this->base();
		return *(--tmp);
	}

	// Return iterator pointer
	template <typename T>
	typename ft::reverse_iterator<T>::pointer ft::reverse_iterator<T>::operator->() const
	{
		return &this->operator*();
	}
	
	// Subscription
	template <typename T>
	typename ft::reverse_iterator<T>::reference ft::reverse_iterator<T>::operator[](difference_type n)
	{
		return *(*this + n);
	}

	template <typename lvalue, typename rvalue>
	bool operator==(ft::reverse_iterator<lvalue> const &lval, ft::reverse_iterator<rvalue> const &rval)
	{
		return lval.base() == rval.base();
	}

	template <typename lvalue, typename rvalue>
	bool operator!=(ft::reverse_iterator<lvalue> const &lval, ft::reverse_iterator<rvalue> const &rval)
	{
		return lval.base() != rval.base();
	}
	
	// Greater / Smaller than operators
	template <typename lvalue, typename rvalue>
	bool operator>(ft::reverse_iterator<lvalue> const &lval, ft::reverse_iterator<rvalue> const &rval)
	{
		return lval.base() < rval.base();
	}

	template <typename lvalue, typename rvalue>
	bool operator<(ft::reverse_iterator<lvalue> const &lval, ft::reverse_iterator<rvalue> const &rval)
	{
		return lval.base() > rval.base();
	}

	template <typename lvalue, typename rvalue>
	bool operator>=(ft::reverse_iterator<lvalue> const &lval, ft::reverse_iterator<rvalue> const &rval)
	{
		return lval.base() <= rval.base();
	}

	template <typename lvalue, typename rvalue>
	bool operator<=(ft::reverse_iterator<lvalue> const &lval, ft::reverse_iterator<rvalue> const &rval)
	{
		return lval.base() >= rval.base();
	}

	template <typename T>
	ft::reverse_iterator<T> operator+(typename ft::reverse_iterator<T>::difference_type const n,
			ft::reverse_iterator<T> const& rval)
	{
		return (ft::reverse_iterator<T>(rval.base() - n));
	};

	template <typename lvalue, typename rvalue>
	typename ft::reverse_iterator<lvalue>::difference_type operator-(ft::reverse_iterator<lvalue> const& lval,
			ft::reverse_iterator<rvalue> const& rval)
	{
		return rval.base() - lval.base();
	};