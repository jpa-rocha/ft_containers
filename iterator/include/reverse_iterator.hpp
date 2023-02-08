/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:46:45 by jrocha            #+#    #+#             */
/*   Updated: 2023/01/26 13:05:19 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "IteratorTraits.hpp"
#include "../../utils/conversions/include/conversions.hpp"

namespace ft {
	template<  typename T >
	class reverse_iterator 
	{
		public:
			typedef T																		iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::value_type					value_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type			difference_type;
			typedef typename ft::iterator_traits<iterator_type>::reference					reference;
			typedef typename ft::iterator_traits<iterator_type>::pointer					pointer;
			typedef typename ft::random_access_iterator_tag									iterator_category;
		protected:
			iterator_type _ptr;
		public:
			// Constructors
			
			reverse_iterator();
			explicit reverse_iterator(iterator_type iter);
			template <typename U>
			reverse_iterator(const reverse_iterator<U> &obj);
			reverse_iterator& operator=(reverse_iterator<T> const &obj);

			// Base
			iterator_type base() const;
			
			// Increment & Decrement
			reverse_iterator& operator++();
			reverse_iterator operator++(int);
			reverse_iterator& operator--();
			reverse_iterator operator--(int);
			reverse_iterator operator+(difference_type const &n) const;
			reverse_iterator operator+=(difference_type const &n);
			reverse_iterator operator-(difference_type const &n) const;
			reverse_iterator operator-=(difference_type const &n);

			// Reference & Dereference
			reference operator*() const;
			pointer operator->() const;

			// Subscription
			reference operator[](difference_type n);
	};

	// Non-Member Functions
	// Equality operations
	template <typename lvalue, typename rvalue>
	bool operator==(reverse_iterator<lvalue> const &lval, reverse_iterator<rvalue> const &rval);

	template <typename lvalue, typename rvalue>
	bool operator!=(reverse_iterator<lvalue> const &lval, reverse_iterator<rvalue> const &rval);
	
	// Greater / Smaller than operators
	template <typename lvalue, typename rvalue>
	bool operator>(reverse_iterator<lvalue> const &lval, reverse_iterator<rvalue> const &rval);

	template <typename lvalue, typename rvalue>
	bool operator<(reverse_iterator<lvalue> const &lval, reverse_iterator<rvalue> const &rval);

	template <typename lvalue, typename rvalue>
	bool operator>=(reverse_iterator<lvalue> const &lval, reverse_iterator<rvalue> const &rval);

	template <typename lvalue, typename rvalue>
	bool operator<=(reverse_iterator<lvalue> const &lval, reverse_iterator<rvalue> const &rval);
	
	template <typename T>
	reverse_iterator<T> operator+(typename ft::reverse_iterator<T>::difference_type const n,
			ft::reverse_iterator<T> const& rval);

	template <typename lvalue, typename rvalue>
	typename ft::reverse_iterator<lvalue>::difference_type operator-(ft::reverse_iterator<lvalue> const& lval,
			ft::reverse_iterator<rvalue> const& rval);
	
	#include "reverse_iterator.tpp"
}
	

#endif