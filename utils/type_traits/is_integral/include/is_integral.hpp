/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:59:16 by jrocha            #+#    #+#             */
/*   Updated: 2023/01/11 13:23:33 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP
# include <stdint.h>
# include <uchar.h>
	namespace ft {
		
		template< class T, T v >
		/**
		 *  @brief \b integral_constant wraps a static constant of specified type.
		 * 			It is the base class for the C++ type traits.
		 * 			The behavior of a program that adds specializations
		 * 			for integral_constant is undefined.
		*/
		struct integral_constant 
		{
			static const T 						value = v;
			typedef T							value_type;
			typedef integral_constant<T, v>		type;
			operator T()						{ return value; }
		};

		typedef integral_constant<bool, true> true_type;
		typedef integral_constant<bool, false> false_type;

		
		template <typename T>
		/**
		 * @brief Checks whether T is an integral type.
		 * 		Provides the member constant value which is equal to true,
		 * 		if T is the type bool, char, char16_t, char32_t, wchar_t, short, int, long, long long,
		 * 		or any implementation-defined extended integer types, including any
		 * 		signed, unsigned, and cv-qualified variants. Otherwise, value is equal to false. 
		 * 
		 */
		struct is_integral : public false_type {};

		template <>
		struct is_integral<bool> : public true_type {};
		
		template <>
		struct is_integral<char> : public true_type {};
		
		template <>
		struct is_integral<unsigned char> : public true_type {};
		
		template <>
		struct is_integral<signed char> : public true_type {};
		
		template <>
		struct is_integral<char16_t> : public true_type {};
		
		template <>
		struct is_integral<char32_t> : public true_type {};
		
		template <>
		struct is_integral<wchar_t> : public true_type {};
		
		template <>
		struct is_integral<short> : public true_type {};
		
		template <>
		struct is_integral<long> : public true_type {};
		
		template <>
		struct is_integral<unsigned long> : public true_type {};
		
		template <>
		struct is_integral<long long> : public true_type {};
		
		template <>
		struct is_integral<unsigned long long> : public true_type {};
		
		template <>
		struct is_integral<int> : public true_type {};
		
		template <typename T>
		struct is_integral<const T> : is_integral<T> {};
		
		template <typename T>
		struct is_integral<volatile T> : is_integral<T> {};
		
		template <typename T>
		struct is_integral<const volatile T> : is_integral<T> {};
	}
#endif