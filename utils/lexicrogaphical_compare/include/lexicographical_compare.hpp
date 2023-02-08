/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:00:28 by jrocha            #+#    #+#             */
/*   Updated: 2023/01/17 14:27:01 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {
	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
	{
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
			first1++;
			first2++;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
	{
		while (first1 != last1 && first2 != last2) {
			if (comp(*first1, *first2))
						return true;
			if (comp(*first2, *first1))
				return false;
			first1++;
			first2++;
		}
		return (first1 == last1) && (first2 != last2);
	}
}


#endif