/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorTraits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:35:08 by jrocha            #+#    #+#             */
/*   Updated: 2023/01/25 18:38:28 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORTRAITS_HPP
# define ITERATORTRAITS_HPP
	
	namespace ft {
		
		struct input_iterator_tag { };
		struct output_iterator_tag { }; 	
		struct forward_iterator_tag { }; 	
		struct bidirectional_iterator_tag { };	
		struct random_access_iterator_tag { };

		template< class Iter >
		struct iterator_traits
		{
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;
		};

		//Specializations
		
		template < class T >
		struct iterator_traits<T*>
		{
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::random_access_iterator_tag	iterator_category;
		};

		template <class T >
		struct iterator_traits<const T*>
		{
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef ft::random_access_iterator_tag	iterator_category;
		};

		
	};
#endif