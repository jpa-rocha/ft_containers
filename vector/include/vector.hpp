/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:11:58 by jrocha            #+#    #+#             */
/*   Updated: 2023/02/08 13:21:53 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

	// https://en.cppreference.com/w/cpp/container/vector
	#include <vector>
	#include <iostream>

	#include "../../iterator/include/RandomAccessIterator.hpp"
	#include "../../iterator/include/reverse_iterator.hpp"
	#include "../../utils/type_traits/enable_if/include/enable_if.hpp"
	#include "../../utils/type_traits/is_integral/include/is_integral.hpp"
	#include "../../utils/lexicrogaphical_compare/include/lexicographical_compare.hpp"
	#include <cstring>
	#include <memory>

	namespace ft {
		template < class T, class Allocator = std::allocator<T> >
		/**
		 * @brief ft::vector is a sequence container that encapsulates
		 * 		dynamic size arrays.
		 * 		The elements are stored contiguously, which means that elements
		 * 		can be accessed not only through iterators,
		 * 		but also using offsets to regular pointers to elements.
		 * 		This means that a pointer to an element of a vector
		 * 		may be passed to any function that expects a pointer
		 * 		to an element of an array.
		 * 		The storage of the vector is handled automatically,
		 * 		being expanded as needed.
		 * 		Vectors usually occupy more space than static arrays,
		 * 		because more memory is allocated to handle future growth.
		 * 		This way a vector does not need to reallocate each time an
		 * 		element is inserted, but only when the additional memory
		 * 		is exhausted.
		 * 		The total amount of allocated memory can be queried
		 * 		using capacity() function. 
		 * 
		 */
		class vector {
			public:
				typedef T 																value_type;
				typedef Allocator														allocator_type;
				typedef std::size_t														size_type;
				typedef std::ptrdiff_t													difference_type;
				typedef value_type&														reference;
				typedef const value_type&												const_reference;
				typedef typename Allocator::pointer										pointer;
				typedef typename Allocator::const_pointer								const_pointer;
				typedef typename ft::RandomAccessIterator<pointer>						iterator;	
				typedef typename ft::RandomAccessIterator<const_pointer>				const_iterator;
				typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
				
			protected:
				allocator_type	_M_alloc;
				pointer 		_M_start;
				pointer 		_M_finish;
				pointer 		_M_end_of_storage;
			
			public:
				// construct/copy/destroy
				
				vector();
				explicit vector(const allocator_type& allocator);
				explicit vector(size_type n, const T& value = value_type(), const allocator_type& allocator = allocator_type());
				template<class InputIt>
				vector(InputIt first, InputIt last, const allocator_type& allocator = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL);
				vector(const vector& x);
				~vector();
				
				// assignment
				
				vector& 				operator=(const vector& other);
				vector& 				operator=(vector& other);
				template<class InputIt>
				void 					assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL);
				void 					assign(size_type n, const T& u);
				allocator_type 			get_allocator() const ;
			
				// iterators
				
				iterator              	begin() ;
				const_iterator         	begin() const ;
				iterator               	end() ;
				const_iterator         	end() const ;
				reverse_iterator       	rbegin() ;
				const_reverse_iterator 	rbegin() const ;
				reverse_iterator       	rend() ;
				const_reverse_iterator 	rend() const ;
			
				// capacity
				
				bool 					empty() const ;
				size_type 				size() const ;
				size_type 				max_size() const ;
				size_type 				capacity() const ;
				void      				reserve(size_type new_cap);
				void      				resize(size_type size, const T& c);
				void 					resize(size_type size);
			
				// element access
				
				reference      			operator[](size_type n);
				const_reference 		operator[](size_type n) const;
				const_reference 		at(size_type n) const;
				reference       		at(size_type n);
				reference       		front();
				const_reference 		front() const;
				reference       		back();
				const_reference 		back() const;
			
				// data access
				
				pointer       			data() ;
				const_pointer 			data() const ;
			
				// modifiers
				
				void 					push_back(const T& x);
				void 					pop_back();
				iterator 				insert(const_iterator position, const value_type& x);
				iterator 				insert(const_iterator position, value_type& x);
				iterator 				insert(const_iterator position, size_type n, const value_type& x);
				template<class InputIt>
				iterator 				insert(const_iterator position, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL);
				iterator 				erase(const_iterator position);
				iterator 				erase(const_iterator first, const_iterator last);
				void     				swap(vector& other);
				void     				clear() ;
			};
			
			// TODO what specialization is this?
			/* template<class InputIt, class Allocator = allocator<<InputIt>>>
				vector(InputIt, InputIt, Allocator = Allocator());
			 */
			
			// swap
			template<class T, class Allocator>
			void swap(vector<T, Allocator>& x, vector<T, Allocator>& y);
	};
	template <class T, class Alloc >
	bool	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);

	template <class T, class Alloc >
	bool	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);

	template <class T, class Alloc >
	bool	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);

	template <class T, class Alloc >
	bool	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);

	template <class T, class Alloc >
	bool	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);

	template <class T, class Alloc >
	bool	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs);
	
	namespace std {
		template< class T, class Alloc>
		void	swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs);
	}
	 //namespace std
	#include "vector.tpp"
#endif
