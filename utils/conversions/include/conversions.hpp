/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 06:41:34 by jrocha            #+#    #+#             */
/*   Updated: 2023/01/25 12:59:35 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSIONS_HPP
# define CONVERSIONS_HPP
		
namespace ft {
	template <class T>
	T* is_const(const T* x)
	{
		return const_cast<T*>(x);
	}

	template <class T>
	T* is_const(T* x)
	{
		return x;
	}
}

#endif