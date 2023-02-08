/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:21:24 by jrocha            #+#    #+#             */
/*   Updated: 2023/02/03 10:50:12 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

#include "IteratorTraits.hpp"
#include "../../utils/conversions/include/conversions.hpp"

	namespace ft {
		template < typename T >
		class RandomAccessIterator
		{
			public:
				typedef T																		iterator_type;
				typedef typename ft::iterator_traits<iterator_type>::value_type					value_type;
				typedef typename ft::iterator_traits<iterator_type>::difference_type			difference_type;
				typedef typename ft::iterator_traits<iterator_type>::reference					reference;
				typedef typename ft::iterator_traits<iterator_type>::pointer					pointer;
				typedef typename ft::random_access_iterator_tag									iterator_category;
			protected:
				pointer _ptr;
			public:
				// Constructors
				
				RandomAccessIterator();
				RandomAccessIterator(pointer p);
				template <typename U>
				RandomAccessIterator(RandomAccessIterator<U> const &obj);
				RandomAccessIterator& operator=(RandomAccessIterator<T> const &obj);

				// Base
				pointer base() const;
				
				// Increment & Decrement
				RandomAccessIterator& operator++();
				RandomAccessIterator operator++(int);
				RandomAccessIterator& operator--();
				RandomAccessIterator operator--(int);
				RandomAccessIterator operator+(difference_type const &n) const;
				RandomAccessIterator operator+=(difference_type const &n);
				RandomAccessIterator operator-(difference_type const &n) const;
				RandomAccessIterator operator-=(difference_type const &n);

				// Reference & Dereference
				reference operator*() const;
				pointer operator->() const;

				// Subscription
				reference operator[](const difference_type n);


		};

		// Non-Member Functions
		// Equality operations
		template <typename lvalue, typename rvalue>
		bool operator==(RandomAccessIterator<lvalue> const &lval, RandomAccessIterator<rvalue> const &rval);

		template <typename lvalue, typename rvalue>
		bool operator!=(RandomAccessIterator<lvalue> const &lval, RandomAccessIterator<rvalue> const &rval);
		
		// Greater / Smaller than operators
		template <typename lvalue, typename rvalue>
		bool operator>(RandomAccessIterator<lvalue> const &lval, RandomAccessIterator<rvalue> const &rval);

		template <typename lvalue, typename rvalue>
		bool operator<(RandomAccessIterator<lvalue> const &lval, RandomAccessIterator<rvalue> const &rval);

		template <typename lvalue, typename rvalue>
		bool operator>=(RandomAccessIterator<lvalue> const &lval, RandomAccessIterator<rvalue> const &rval);

		template <typename lvalue, typename rvalue>
		bool operator<=(RandomAccessIterator<lvalue> const &lval, RandomAccessIterator<rvalue> const &rval);
		
		template <class Iter>
		typename RandomAccessIterator<Iter>::difference_type operator+(RandomAccessIterator<Iter> const& lval,
				RandomAccessIterator<Iter> const& rval);
		
		template <typename lvalue, typename rvalue>
		RandomAccessIterator<lvalue> operator-(typename RandomAccessIterator<lvalue>::difference_type const n,
				RandomAccessIterator<rvalue> const& rval);

		#include "RandomAccessIterator.tpp"
	};
		

#endif