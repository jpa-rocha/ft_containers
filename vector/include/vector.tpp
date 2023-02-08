/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:57:03 by jrocha            #+#    #+#             */
/*   Updated: 2023/02/08 13:24:19 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vector.hpp"

// construct/copy/destroy

template <class T, class Allocator>
/**
 * @brief Default constructor. Constructs an empty container
 * 		with a default-constructed allocator.
 * 
 */
ft::vector<T, Allocator>::vector()
{ 
	this->_M_alloc = allocator_type();
	this->_M_start = 0;
	this->_M_finish = 0;
	this->_M_end_of_storage = 0;
}

template <class T, class Allocator>
/**
 * @brief Constructs an empty container with the given
 * 		\b allocator.
 * 
 * @param allocator allocator to use for all memory 
 * 				allocations of this container.
 */
ft::vector<T, Allocator>::vector(const allocator_type& allocator)
{
	this->_M_alloc = allocator;
	this->_M_start = 0;
	this->_M_finish = 0;
	this->_M_end_of_storage = 0;
}

template <class T, class Allocator>
/**
 * @brief  Constructs the container with count copies
 * 		of elements with value \b value.
 * 
 * @param n the size of the container.
 * @param value the value to initialize elements of the container with.
 * @param allocator allocator to use for all memory allocations of this container.
 * 
 */
ft::vector<T, Allocator>::vector(size_type n, const T& value, const allocator_type& allocator)
{
	this->_M_alloc = allocator;
	this->_M_start = this->get_allocator().allocate(n);
	this->_M_finish = this->_M_start + n;
	this->_M_end_of_storage = this->_M_finish;
	for (size_type i = 0; i < n; i++)
		this->_M_alloc.construct(this->_M_start + i, value);
}

template<class T, class Allocator>
template<class InputIt>
/**
 * @brief Constructs the container with the contents of the range [first, last).
 * 
 * @param first  first element of the range to copy the elements from.
 * @param last 	last element of the range to copy the elements from.
 * @param allocator allocator to use for all memory allocations of this container.
 */
ft::vector<T, Allocator>::vector(InputIt first, InputIt last, const allocator_type& allocator, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
{
	this->_M_alloc = allocator;
	difference_type amount(last - first);
	this->_M_start = this->get_allocator().allocate(amount);
	this->_M_finish = this->_M_start + (amount);
	this->_M_end_of_storage = this->_M_finish;
	for (int i = 0; i < amount; i++)
		this->_M_alloc.construct(this->_M_start + i, *(first.base() + i));
 }


template <class T, class Allocator>
/**
 * @brief Copy constructor.
 * 		Constructs the container with the copy of the
 * 		contents of \b other. 
 * 
 * @param other another container to be used as source to initialize the elements of the container with.
 */
ft::vector<T, Allocator>::vector(const vector& other)
{
	this->_M_alloc = other.get_allocator();
	this->_M_start = this->get_allocator().allocate(other.size());
	this->_M_finish = this->_M_start + other.size();
	this->_M_end_of_storage = this->_M_start + other.size();
	for(size_type i = 0; i < this->size(); i++)
		this->get_allocator().construct(this->_M_start + i, *(other._M_start + i));
}

template <class T, class Allocator>
/**
 * @brief Destructs the vector.
 * 		The destructors of the elements are called
 * 		and the used storage is deallocated.
 * 		Note, that if the elements are pointers,
 * 		the pointed-to objects are not destroyed. 
 * 
 */
ft::vector<T, Allocator>::~vector()
{
	this->clear();
	this->get_allocator().deallocate(this->_M_start, this->capacity());
}

// assignment

template <class T, class Allocator>
/**
 * @brief Copy assignment operator. Replaces the contents
 * 		with a copy of the contents of \b other. 
 * 
 * @param other another container to use as data source.
 * @return ft::vector<T, Allocator>& 
 */
ft::vector<T, Allocator>& ft::vector<T, Allocator>::operator=(const vector& other)
{
	if(this == &other)
		return *this;
	this->clear();
	this->get_allocator().deallocate(this->_M_start, this->capacity());
	this->_M_alloc = other.get_allocator();
	this->_M_start = this->get_allocator().allocate(other.capacity());
	this->_M_finish = this->_M_start + other.size();
	this->_M_end_of_storage = this->_M_start + other.capacity();
	for(size_type i = 0; i < this->size(); i++)
		this->get_allocator().construct(this->_M_start + i, *(other._M_start + i));
	return *this;
}

template <class T, class Allocator>
/**
 * @brief Copy assignment operator. Replaces the contents
 * 		with a copy of the contents of \b other. 
 * 
 * @param other another container to use as data source.
 * @return ft::vector<T, Allocator>& 
 */
ft::vector<T, Allocator>& ft::vector<T, Allocator>::operator=(vector& other)
{
	if(this == &other)
		return *this;
	this->clear();
	this->get_allocator().deallocate(this->_M_start, this->capacity());
	this->_M_alloc = other.get_allocator();
	this->_M_start = this->get_allocator().allocate(other.size());
	this->_M_finish = this->_M_start + other.size();
	this->_M_end_of_storage = this->_M_start + other.size();
	for(size_type i = 0; i < this->size(); i++)
		this->get_allocator().construct(this->_M_start + i, *(other._M_start + i));
	return *this;
}

template <class T, class Allocator>
template<class InputIt>
/**
 * @brief Replaces the contents of the container.
 * 		Replaces the contents with copies of those in the range [first, last).
 * 		The behavior is undefined if either argument is an iterator into *this.
 * 		All iterators, pointers and references to
 * 		the elements of the container are invalidated.
 * 		The past-the-end iterator is also invalidated. 
 * 
 * @param first  first element of the range to copy the elements from.
 * @param last 	last element of the range to copy the elements from.
 */
void ft::vector<T, Allocator>::assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
{
	size_type amount(last - first);
	if (amount > this->capacity()) {
		this->get_allocator().deallocate(this->_M_start, this->capacity());
		this->_M_start = this->get_allocator().allocate(amount);
		this->_M_end_of_storage = this->_M_start + amount;
	}
	//iterator it(first);
	size_type i(0);
	while (first != last) {
		this->get_allocator().construct(this->_M_start + i, *first);
		first++;
		i++;
	}
	this->_M_finish = this->_M_start + amount;
}

template <class T, class Allocator>
/**
 * @brief Replaces the contents with \b n copies
 * 		of value \b u.
 * 		All iterators, pointers and references to
 * 		the elements of the container are invalidated.
 * 		The past-the-end iterator is also invalidated. 
 * 
 * @param n the new size of the container.
 * @param u the value to initialize elements of the container with.
 */
void ft::vector<T, Allocator>::assign(size_type n, const T& u)
{
	if (n > this->capacity()) {
		this->get_allocator().deallocate(this->_M_start, this->capacity());
		this->_M_start = this->get_allocator().allocate(n);
		this->_M_end_of_storage = this->_M_start + n;
	}
	for (size_type i = 0; i < n; i++)
		this->get_allocator().construct(this->_M_start + i, u);
	this->_M_finish = this->_M_start + n;
}

template <class T, class Allocator>
/**
 * @brief Returns the allocator associated
 * 		with the container. 
 * 
 * @return ft::vector<T, Allocator>::allocator_type 
 */
typename ft::vector<T, Allocator>::allocator_type ft::vector<T, Allocator>::get_allocator() const
{
	return this->_M_alloc;
}

// iterators

template <class T, class Allocator>
/**
 * @brief Returns an iterator to the first element
 * 		of the vector.
 * 		If the vector is empty, the returned iterator
 * 		will be equal to end(). 
 * 
 * @return ft::vector<T, Allocator>::iterator 
 */
typename ft::vector<T, Allocator>::iterator	ft::vector<T, Allocator>::begin()
{
	return iterator(ft::is_const(this->_M_start));
}

template <class T, class Allocator>
/**
 * @brief Returns an iterator to the first element
 * 		of the vector.
 * 		If the vector is empty, the returned iterator
 * 		will be equal to end(). 
 * 
 * @return ft::vector<T, Allocator>::iterator 
 */
typename ft::vector<T, Allocator>::const_iterator ft::vector<T, Allocator>::begin() const
{
	return const_iterator(ft::is_const(this->_M_start));
}

template <class T, class Allocator>
/**
 * @brief Returns an iterator to the element following
 * 		the last element of the vector.
 *		This element acts as a placeholder;
 *		attempting to access it results in undefined behavior. 
 * 
 * @return ft::vector<T, Allocator>::iterator 
 */
typename ft::vector<T, Allocator>::iterator ft::vector<T, Allocator>::end()
{
	return iterator(ft::is_const(this->_M_finish));
}

template <class T, class Allocator>
/**
 * @brief Returns an iterator to the element following
 * 		the last element of the vector.
 *		This element acts as a placeholder;
 *		attempting to access it results in undefined behavior. 
 * 
 * @return ft::vector<T, Allocator>::iterator 
 */
typename ft::vector<T, Allocator>::const_iterator ft::vector<T, Allocator>::end() const
{
	return const_iterator(ft::is_const(this->_M_finish));
}

template <class T, class Allocator>
/**
 * @brief Returns a reverse iterator to the first element
 * 		of the reversed vector. It corresponds to the last
 * 		element of the non-reversed vector.
 * 		If the vector is empty, the returned iterator
 * 		is equal to rend(). 
 * 
 * @return ft::vector<T, Allocator>::reverse_iterator 
 */
typename ft::vector<T, Allocator>::reverse_iterator ft::vector<T, Allocator>::rbegin()
{
	return reverse_iterator(this->end());
}

template <class T, class Allocator>
/**
 * @brief Returns a reverse iterator to the first element
 * 		of the reversed vector. It corresponds to the last
 * 		element of the non-reversed vector.
 * 		If the vector is empty, the returned iterator
 * 		is equal to rend(). 
 * 
 * @return ft::vector<T, Allocator>::reverse_iterator 
 */
typename ft::vector<T, Allocator>::const_reverse_iterator ft::vector<T, Allocator>::rbegin() const
{
	return const_return_iterator(this->end());
}

template <class T, class Allocator>
/**
 * @brief Returns a reverse iterator to the element following
 * 		the last element of the reversed vector. It corresponds
 * 		to the element preceding the first element of the 
 * 		non-reversed vector. This element acts as a placeholder,
 * 		attempting to access it results in undefined behavior. 
 * 
 * @return ft::vector<T, Allocator>::const_reverse_iterator 
 */
typename ft::vector<T, Allocator>::reverse_iterator ft::vector<T, Allocator>::rend()
{
	return reverse_iterator(this->begin());
}

template <class T, class Allocator>
/**
 * @brief Returns a reverse iterator to the element following
 * 		the last element of the reversed vector. It corresponds
 * 		to the element preceding the first element of the 
 * 		non-reversed vector. This element acts as a placeholder,
 * 		attempting to access it results in undefined behavior. 
 * 
 * @return ft::vector<T, Allocator>::const_reverse_iterator 
 */
typename ft::vector<T, Allocator>::const_reverse_iterator ft::vector<T, Allocator>::rend() const
{
	return const_reverse_iterator(this->begin());
}

// capacity

template <class T, class Allocator>
/**
 * @brief Checks if the container has no elements,
 * 		i.e. whether begin() == end().
 * 
 * @return true - vector is empty.\\
 * @return false - vector is not empty.
 */
bool ft::vector<T, Allocator>::empty() const
{
	return this->begin() == this->end();
}

template <class T, class Allocator>
/**
 * @brief Returns the number of elements in the container.
 * 
 * @return ft::vector<T, Allocator>::size_type 
 */
typename ft::vector<T, Allocator>::size_type ft::vector<T, Allocator>::size() const
{
	return size_type(this->_M_finish - this->_M_start);
}

template <class T, class Allocator>
/**
 * @brief Returns the maximum number of elements
 * 		the container is able to hold due to system
 * 		or library implementation limitations.
 * 
 * @return ft::vector<T, Allocator>::size_type 
 */
typename ft::vector<T, Allocator>::size_type ft::vector<T, Allocator>::max_size() const
{
	return this->get_allocator().max_size();
}

template <class T, class Allocator>
/**
 * @brief Returns the number of elements that the container
 *		has currently allocated space for. 
 * 
 * @return ft::vector<T, Allocator>::size_type
 */
typename ft::vector<T, Allocator>::size_type ft::vector<T, Allocator>::capacity() const
{
	return size_type(this->_M_end_of_storage - this->_M_start);
}

template <class T, class Allocator>
/**
 * @brief Increase the capacity of the vector
 * 		(the total number of elements that the vector can hold
 * 		without requiring reallocation) to a value that's greater
 * 		or equal to \b new_cap.
 * 		If \b new_cap is greater than the current capacity(),
 * 		new storage is allocated, otherwise the function does nothing.
 * 		reserve() does not change the size of the vector.
 * 		If new_cap is greater than capacity(), all iterators,
 * 		including the past-the-end iterator, and all references
 * 		to the elements are invalidated.
 * 		Otherwise, no iterators or references are invalidated. 
 * 
 * @param new_cap new capacity of the vector, in number of elements.
 */
void     ft::vector<T, Allocator>::reserve(size_type new_cap)
{
	if (new_cap > this->max_size())
		throw std::length_error("  what():  vector::_M_default_append");
	if (new_cap > this->capacity()) {
		pointer start = this->get_allocator().allocate(new_cap);
		size_type org_size(this->size());
		for (size_type i = 0; i < this->size(); i++)
			this->get_allocator().construct(start + i, *(this->_M_start + i));
		this->clear();
		this->get_allocator().deallocate(this->_M_start, this->capacity());
		this->_M_start = start;
		this->_M_finish = this->_M_start + org_size;
		this->_M_end_of_storage = this->_M_start + new_cap;
	}
}

template <class T, class Allocator>
/**
 * @brief Resizes the container to contain \b size elements.

		If the current size is greater than \b size, the container is
		reduced to its first \b size elements.

		If the current size is less than \b size,
			1) additional default-inserted elements are appended
			2) additional copies of \b c are appended.
 * 
 * @param size new size of the container
 * @param c the value to initialize the new elements with
 */
void ft::vector<T, Allocator>::resize(size_type size, const T& c)
{
	if (size > this->max_size())
		throw std::length_error("  what():  vector::_M_default_append");
	//
	size_type prev_size = this->capacity();
	if (size < prev_size) {
		for (size_t i = prev_size; i >= size; i--)
			this->get_allocator().destroy(this->_M_start + i);
	}
	else if (size > prev_size) {
		if (size == this->capacity() + 1 || size < this->size() * 2)
				reserve(this->size() * 2);
		else if (this->capacity() * 2 < this->max_size() && this->capacity() == this->size())
				reserve(this->capacity() * 2);
		else if (this->capacity() * 2 < this->max_size() && this->capacity() * 2 >= size)
				reserve(size);
		for (size_t i = size - 1; i >= this->size(); i--)
			this->get_allocator().construct(this->_M_start + i, c);
	}
	this->_M_finish = this->_M_start + size;
	if (size >= this->capacity())
		this->_M_end_of_storage = this->_M_finish;
}

template <class T, class Allocator>
/**
 * @brief Resizes the container to contain \b size elements.

		If the current size is greater than \b size, the container is
		reduced to its first \b size elements.

		If the current size is less than \b size,
			1) additional default-inserted elements are appended
			2) additional copies of \b c are appended.
 * 
 * @param size new size of the container
 * @param c the value to initialize the new elements with
 */
void ft::vector<T, Allocator>::resize(size_type size)
{
	if (size > this->max_size())
		throw std::length_error("  what():  vector::_M_default_append");
	size_type prev_size = this->capacity();
	if (size < prev_size) {
		for (size_t i = prev_size; i >= size; i--) {
			this->get_allocator().destroy(this->_M_start + i);
			if (i == 0)
				break;	
		}
	}
	else if (size > prev_size) {
		if (size == this->capacity() + 1 || size < this->size() * 2)
				reserve(this->size() * 2);
		else if (this->capacity() * 2 < this->max_size() && this->capacity() == this->size())
				reserve(this->capacity() * 2);
		else if (this->capacity() * 2 < this->max_size() && this->capacity() * 2 >= size)
				reserve(size);
	}
	this->_M_finish = this->_M_start + size;
	if (size > this->capacity())
		this->_M_end_of_storage = this->_M_finish;
}

// element access

template <class T, class Allocator>
/**
 * @brief Returns a reference to the element at specified
 * 		location \b n. No bounds checking is performed. 
 * 
 * @param n position of the element to return.
 * @return ft::vector<T, Allocator>::reference 
 */
typename ft::vector<T, Allocator>::reference ft::vector<T, Allocator>::operator[](size_type n)
{
	return *(this->_M_start + n);
}

template <class T, class Allocator>
/**
 * @brief Returns a reference to the element at specified
 * 		location \b n. No bounds checking is performed. 
 * 
 * @param n position of the element to return.
 * @return ft::vector<T, Allocator>::reference 
 */
typename ft::vector<T, Allocator>::const_reference ft::vector<T, Allocator>::operator[](size_type n) const
{
	return *(this->_M_start + n);
}
template <class T, class Allocator>
/**
 * @brief Returns a reference to the element at specified
 * 		location \b n, with bounds checking.
 * 		If \b n is not within the range of the container,
 * 		an exception of type std::out_of_range is thrown. 
 * 
 * @param n position of the element to return.
 * @return ft::vector<T, Allocator>::reference 
 */
typename ft::vector<T, Allocator>::const_reference ft::vector<T, Allocator>::at(size_type n) const
{
	if(n >= this->size())
		throw std::out_of_range("  what():  vector::_M_range_check: __n >= this->size()");
	return *(this->_M_start + n);
}

template <class T, class Allocator>
/**
 * @brief Returns a reference to the element at specified
 * 		location \b n, with bounds checking.
 * 		If \b n is not within the range of the container,
 * 		an exception of type std::out_of_range is thrown. 
 * 
 * @param n position of the element to return.
 * @return ft::vector<T, Allocator>::reference 
 */
typename ft::vector<T, Allocator>::reference ft::vector<T, Allocator>::at(size_type n)
{
	if(n >= this->size())
		throw std::out_of_range("  what():  vector::_M_range_check: __n >= this->size()");
	return *(this->_M_start + n);
}

template <class T, class Allocator>
/**
 * @brief Returns a reference to the first element in the container.
		Calling front on an empty container is undefined. 
 * 
 * @return ft::vector<T, Allocator>::reference 
 */
typename ft::vector<T, Allocator>::reference ft::vector<T, Allocator>::front()
{
	return *this->_M_start;
}

template <class T, class Allocator>
/**
 * @brief Returns a reference to the first element in the container.
		Calling front on an empty container is undefined. 
 * 
 * @return ft::vector<T, Allocator>::reference 
 */
typename ft::vector<T, Allocator>::const_reference ft::vector<T, Allocator>::front() const
{
	return *this->_M_start;
}

template <class T, class Allocator>
/**
 * @brief Returns a reference to the last element in the container.
 * 		Calling back on an empty container causes undefined behavior.

 * 
 * @return ft::vector<T, Allocator>::reference 
 */
typename ft::vector<T, Allocator>::reference ft::vector<T, Allocator>::back()
{
	return *(this->_M_finish - 1);
}

template <class T, class Allocator>
/**
 * @brief Returns a reference to the last element in the container.
 * 		Calling back on an empty container causes undefined behavior.

 * 
 * @return ft::vector<T, Allocator>::reference 
 */
typename ft::vector<T, Allocator>::const_reference ft::vector<T, Allocator>::back() const
{
	return *(this->_M_finish - 1);
}

// data access

template <class T, class Allocator>
/**
 * @brief Returns pointer to the underlying array serving
 * 		as element storage.
 * 		The pointer is such that range [data(); data()+size())
 * 		is always a valid range, even if the container is empty
 * 		(data() is not dereferenceable in that case).
 * 		If size() is ​0​, data() may or may not return a null pointer. 
 * 
 * @return ft::vector<T, Allocator>::pointer 
 */
typename ft::vector<T, Allocator>::pointer ft::vector<T, Allocator>::data()
{
	return this->_M_start;
}

template <class T, class Allocator>
/**
 * @brief Returns pointer to the underlying array serving
 * 		as element storage.
 * 		The pointer is such that range [data(); data()+size())
 * 		is always a valid range, even if the container is empty
 * 		(data() is not dereferenceable in that case).
 * 		If size() is ​0​, data() may or may not return a null pointer. 
 * 
 * @return ft::vector<T, Allocator>::pointer 
 */
typename ft::vector<T, Allocator>::const_pointer ft::vector<T, Allocator>::data() const
{
	return this->_M_start;
}
// modifiers

template <class T, class Allocator>
/**
 * @brief Appends the given element \b x to the end of the
 * 		container.
 * 		The new element is initialized as a copy of \b x.
 * 		If the new size() is greater than capacity()
 * 		then all iterators and references
 * 		(including the past-the-end iterator) are invalidated.
 * 		Otherwise only the past-the-end iterator is invalidated. 
 * 
 * @param x the value of the element to append.
 */
void ft::vector<T, Allocator>::push_back(const T& x)
{
	if (this->size() + 1 > this->max_size())
		throw std::length_error("  what():  vector::_M_default_append");
	if (this->size() >= this->capacity()) {
		if (this->capacity() > 0 && (this->capacity() * 2 < this->max_size()))
			reserve(this->capacity() * 2);
		else
			reserve(this->capacity() + 1);
	}
	this->get_allocator().construct(this->_M_start + this->size(), x);
	this->_M_finish += 1;
}

template <class T, class Allocator>
/**
 * @brief Removes the last element of the container.
 * 		Calling pop_back on an empty container results
 * 		in undefined behavior.
 * 		Iterators and references to the last element,
 * 		as well as the end() iterator, are invalidated. 
 * 
 */
void ft::vector<T, Allocator>::pop_back()
{
	if (!this->empty()) {
		this->get_allocator().destroy(this->_M_start + this->size() - 1);
		this->_M_finish -= 1;
	}
}

template <class T, class Allocator>
/**
 * @brief Inserts elements at the specified location in the container.
		Inserts value \b x before \b position.
 * 
 * @param position 
 * @param x 
 * @return ft::vector<T, Allocator>::iterator 
 */
typename ft::vector<T, Allocator>::iterator ft::vector<T, Allocator>::insert(const_iterator position, const value_type& x)
{
	if (this->size() + 1 > this->max_size())
		throw std::length_error("  what():  vector::_M_fill_insert");
	iterator ret = iterator(this->insert(position, 1, x));
	return ret;
}

template <class T, class Allocator>
/**
 * @brief Inserts elements at the specified location in the container.
		Inserts value \b x before \b position.
 * 
 * @param position iterator before which the content will be inserted.
 * 				position may be the end() iterator.
 * @param x element value to insert.
 * @return ft::vector<T, Allocator>::iterator 
 */
typename ft::vector<T, Allocator>::iterator ft::vector<T, Allocator>::insert(const_iterator position, value_type& x)
{
	if (this->size() + 1 > this->max_size())
		throw std::length_error("  what():  vector::_M_fill_insert");
	iterator ret = iterator(this->insert(position, 1, x));
	return ret;
}

template <class T, class Allocator>
/**
 * @brief Inserts elements at the specified location in the container.
		Inserts \b n copies of the \b x before \b posistion.
 * 
 * @param position iterator before which the content will be inserted.
 * 				position may be the end() iterator.
 * @param n number of elements to insert.
 * @param x element value to insert.
 * @return ft::vector<T, Allocator>::iterator 
 */
typename ft::vector<T, Allocator>::iterator ft::vector<T, Allocator>::insert(const_iterator position, size_type n, const T& x)
{
	if (n == 0)
		return position;
	if (this->size() + n > this->max_size())
		throw std::length_error("  what():  vector::_M_fill_insert");
	difference_type difference(0);
	if (this->size() != 0)
		difference = position - const_iterator(this->begin());
	if (this->capacity() == 0 || this->size() + n > this->capacity() * 2)
		this->reserve(this->size() + n);
	else if ((this->size() + n) > this->capacity() && this->size() * 2 < this->capacity() * 2)
		this->reserve(this->size() * 2);
	else if ((this->size() + n) > this->capacity() && this->capacity() > 0)
		this->reserve(this->capacity() * 2);
	ft::vector<value_type> help = vector(*this);
	pointer it = this->begin().base();
	pointer help_begin = help.begin().base();
	pointer help_mid = help.begin().base() + difference;
	while (help_begin != help_mid) {
		this->get_allocator().construct(it, *help_begin);
		it++;
		help_begin++;
	}
	for (size_type i = 0; i < n; i++) {
		this->get_allocator().construct(it, x);
		it++;
	}
	while (help_mid != help.end().base()) {
		this->get_allocator().construct(it, *help_mid);
		it++;
		help_mid++;
	}
	this->_M_finish += n;
	return (this->_M_start + difference);
}

template <class T, class Allocator>
template<class InputIt>
/**
 * @brief Inserts elements at the specified location in the container.
		Inserts elements from range [ \b first, \b last) before \b position. 
 * 
 * @param position iterator before which the content will be inserted.
 * 				position may be the end() iterator.
 * @param first first iterator from the range of elements to insert, 
 * 			can't be iterators into container for which insert is called.
 * @param last last iterator from the range of elements to insert, 
 * 			can't be iterators into container for which insert is called.
 * @return ft::vector<T, Allocator>::iterator 
 */
typename ft::vector<T, Allocator>::iterator ft::vector<T, Allocator>::insert(const_iterator position, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
{
	/* size_type amount(last - first);
	size_type difference(0);
	ft::vector<value_type> to_insert = vector(first, last);
	if (this->size() != 0)
		difference = position - const_iterator(this->begin());
	if (this->size() + amount > this->max_size())
		throw std::length_error("  what():  vector::_M_fill_insert");
	if (this->capacity() == 0 || this->size() + amount > this->capacity() * 2)
		this->reserve(this->size() + amount);
	else if ((this->size() + amount) > this->capacity() && this->size() * 2 < this->capacity() * 2)
		this->reserve(this->size() * 2);
	else if ((this->size() + amount) > this->capacity() && this->capacity() > 0)
		this->reserve(this->capacity() * 2);
	ft::vector<value_type> help = vector(*this);
	pointer it = this->begin().base();
	pointer help_begin = help.begin().base();
	pointer help_mid = help.begin().base() + difference;
	while (help_begin != help_mid) {
		this->get_allocator().construct(it, *help_begin);
		it++;
		help_begin++;
	}
	while (first != last) {
		this->get_allocator().construct(it, *first);
		it++;
		first++;
	}
	while (help_mid != help.end().base()) {
		this->get_allocator().construct(it, *help_mid);
		it++;
		help_mid++;
	}
	this->_M_finish += amount;
	return (this->_M_start + difference); */
	size_type amount(last - first);
	size_type difference(0);
	ft::vector<value_type> to_insert = vector(first, last);
	if (this->size() != 0)
		difference = position - const_iterator(this->begin());
	if (this->size() + amount > this->max_size())
		throw std::length_error("  what():  vector::_M_fill_insert");
	if (this->capacity() == 0 || this->size() + amount > this->capacity() * 2)
		this->reserve(this->size() + amount);
	else if ((this->size() + amount) > this->capacity() && this->size() * 2 < this->capacity() * 2)
		this->reserve(this->size() * 2);
	else if ((this->size() + amount) > this->capacity() && this->capacity() > 0)
		this->reserve(this->capacity() * 2);
	ft::vector<value_type> help = vector(*this);
	pointer it = this->begin().base();
	pointer help_begin = help.begin().base();
	pointer help_mid = help.begin().base() + difference;
	while (help_begin != help_mid) {
		this->get_allocator().construct(it, *help_begin);
		it++;
		help_begin++;
	}
	try {
		
		std::memcpy(it, &first, amount);
		it += amount;
	}
	catch (...) {}
	while (help_mid != help.end().base()) {
		this->get_allocator().construct(it, *help_mid);
		it++;
		help_mid++;
	}
	this->_M_finish += amount;
	return (this->_M_start + difference);
}

template <class T, class Allocator>
/**
 * @brief Erases the specified element from the container.
		Removes the element at \b position.
		Invalidates iterators and references at or after the point
		of the erase, including the end() iterator.
		The iterator \b position must be valid and dereferenceable.
		Thus the end() iterator (which is valid, but is not dereferenceable)
		cannot be used as a value for \b position. 
 * 
 * @param position  iterator to the element to remove 
 * @return ft::vector<T, Allocator>::iterator 
 */
typename ft::vector<T, Allocator>::iterator ft::vector<T, Allocator>::erase(const_iterator position)
{
	difference_type difference(position - const_iterator(this->begin()));
	for (std::size_t i = 0; difference + i + 1 < this->size(); i++)
		this->get_allocator().construct(this->_M_start + difference + i, *(this->_M_start + difference + i + 1));
	this->get_allocator().destroy(this->_M_start + this->size() - 1);
	this->_M_finish -= 1;
	return (this->_M_start + difference);
}

template <class T, class Allocator>
/**
 * @brief Erases the specified elements from the container.
 * 		Removes the elements in the range [ \b first, \b last). 
 * 		Invalidates iterators and references at or after the point
 * 		of the erase, including the end() iterator.
 * 		The iterator \b first does not need to be dereferenceable if
 * 		\b first == \b last: erasing an empty range is a no-op.

 * 
 * @param first iterator to the first element of range of elements to remove.
 * @param last iterator to the last element of range of elements to remove.
 * @return ft::vector<T, Allocator>::iterator 
 */
typename ft::vector<T, Allocator>::iterator ft::vector<T, Allocator>::erase(const_iterator first, const_iterator last)
{
	if (last == this->end()) {
		const_iterator it(last);
		while (it != first) {
			erase(it);		
			it--;
		}
	}
	else {
		difference_type difference(first - const_iterator(this->begin()));
		difference_type amount(last - first);
		for (difference_type i = 0; i < amount; i++)
			this->erase(this->_M_start + difference);
	}
	return (first);
}

template <class T, class Allocator>
/**
 * @brief Exchanges the contents and capacity of the container
 * 		with those of other. Does not invoke any move, copy, or swap
 * 		operations on individual elements.
 * 		All iterators and references remain valid.
 * 		The past-the-end iterator is invalidated. 
 * 
 * @param other container to exchange the contents with.
 */
void ft::vector<T, Allocator>::swap(vector& other)
{
	std::swap(this->_M_start, other._M_start);
	std::swap(this->_M_finish, other._M_finish);
	std::swap(this->_M_end_of_storage, other._M_end_of_storage);
	std::swap(this->_M_alloc, other._M_alloc);
	return ;
}

template <class T, class Allocator>
/**
 * @brief Erases all elements from the container.
 * 		After this call, size() returns zero. 
 * 		Invalidates any references, pointers, or iterators referring to
 * 		contained elements.
 * 		Any past-the-end iterators are also invalidated.
 * 		Leaves the capacity() of the vector unchanged.
 *  
 */
void     ft::vector<T, Allocator>::clear()
{
	size_type cap(this->capacity());
	this->get_allocator().deallocate(this->_M_start, cap);
	this->_M_start = this->get_allocator().allocate(cap);
	this->_M_finish = this->_M_start;
	this->_M_end_of_storage = this->_M_start + cap;
}

/*
 *  NON-MEMBER FUNCTIONS
*/

template <class T, class Alloc >
/**
 * @brief Compares the contents of two vectors.
		Checks if the contents of lhs and rhs are equal,
		that is, they have the same number of elements
		and each element in lhs compares equal with the element in rhs
		at the same position.
 * 
 * @param lhs  	vector to compare. 
 * @param rhs  	vector to compare.
 * @return true 
 * @return false 
 */
bool	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	for (std::size_t i = 0; i < lhs.size(); i++) {
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}

template <class T, class Alloc >
/**
 * @brief Compares the contents of two vectors.
		Checks if the contents of lhs and rhs are equal,
		that is, they have the same number of elements
		and each element in lhs compares equal with the element in rhs
		at the same position.
 * 
 * @param lhs  	vector to compare.
 * @param rhs  	vector to compare.
 * @return true 
 * @return false 
 */
bool	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Alloc >
/**
 * @brief Compares the contents of lhs and rhs lexicographically.
 * 		The comparison is performed by a function equivalent to 
 * 		std::lexicographical_compare.
 * 
 * @param lhs  	vector to compare.
 * @param rhs  	vector to compare.
 * @return true 
 * @return false 
 */
bool	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc >
/**
 * @brief Compares the contents of lhs and rhs lexicographically.
 * 		The comparison is performed by a function equivalent to 
 * 		std::lexicographical_compare.
 * 
 * @param lhs  	vector to compare.
 * @param rhs  	vector to compare.
 * @return true 
 * @return false 
 */
bool	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return rhs < lhs;
}

template <class T, class Alloc >
/**
 * @brief Compares the contents of lhs and rhs lexicographically.
 * 		The comparison is performed by a function equivalent to 
 * 		std::lexicographical_compare.
 * 
 * @param lhs  	vector to compare.
 * @param rhs  	vector to compare.
 * @return true 
 * @return false 
 */
bool	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return !(lhs > rhs);
}

template <class T, class Alloc >
/**
 * @brief Compares the contents of lhs and rhs lexicographically.
 * 		The comparison is performed by a function equivalent to 
 * 		std::lexicographical_compare.
 * 
 * @param lhs  	vector to compare.
 * @param rhs  	vector to compare.
 * @return true 
 * @return false 
 */
bool	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return !(lhs < rhs);
}

namespace std {
	template< class T, class Alloc>
	void	swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

namespace ft {
	template< class T, class Alloc>
	void	swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}