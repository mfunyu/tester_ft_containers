#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "algorithm.hpp"
#include "iterators.hpp"
#include "type_traits.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector
{
  public:
	typedef T                                 value_type;
	typedef Allocator                         allocator_type;
	typedef std::size_t                       size_type;
	typedef std::ptrdiff_t                    difference_type;
	typedef value_type&                       reference;
	typedef const value_type&                 const_reference;
	typedef typename Allocator::pointer       pointer;
	typedef typename Allocator::const_pointer const_pointer;

	typedef random_access_iterator<T>            iterator;
	typedef random_access_iterator<T>            const_iterator;
	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  private:
	pointer        _begin;
	pointer        _end;
	pointer        _end_cap;
	allocator_type _alloc;

  public:
	vector() : _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(Allocator()) {}
	explicit vector(const Allocator& alloc);
	explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator());
	template <class InputIt>
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
	vector(const vector& other);
	// (destructor)
	~vector()
	{
		if (_begin == NULL)
			return;
		size_type s = capacity();
		_destruct_at_end(_begin);
		_alloc.deallocate(_begin, s);
	}
	// operator=
	vector& operator=(const vector& other);
	// assign
	void assign(size_type count, const T& value);
	template <class InputIt>
	void assign(InputIt first, InputIt last,
	    typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0);
	// get_allocator
	allocator_type get_allocator() const { return _alloc; }
	// --------------------------- Elements access -------------------------- //
	// at
	reference       at(size_type pos);
	const_reference at(size_type pos) const;
	// operator[]
	reference       operator[](size_type pos) { return _begin[pos]; }
	const_reference operator[](size_type pos) const { return _begin[pos]; }
	// front
	reference       front() { return *_begin; }
	const_reference front() const { return *_begin; }
	// back
	reference       back() { return *(_end - 1); }
	const_reference back() const { return *(_end - 1); }
	// data
	T*       data() { return static_cast<T*>(_begin); }
	const T* data() const { return static_cast<const T*>(_begin); }
	// ------------------------------ Iterators ----------------------------- //
	iterator               begin() { return iterator(_begin); }
	const_iterator         begin() const { return const_iterator(_begin); }
	iterator               end() { return iterator(_end); }
	const_iterator         end() const { return const_iterator(_end); }
	reverse_iterator       rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator       rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	// ------------------------------ Capacity ------------------------------ //
	bool      empty() const { return (size() == 0); }
	size_type size() const { return static_cast<size_type>(_end - _begin); }
	// max_size
	size_type max_size() const;
	void      reserve(size_type new_cap);
	size_type capacity() const { return static_cast<size_type>(_end_cap - _begin); }
	/* ------------------------------ Modifiers ----------------------------- */
	void clear() { _destruct_at_end(_begin); }
	// insert
	iterator insert(iterator pos, const T& value);
	void     insert(iterator pos, size_type count, const T& value);
	template <class InputIt>
	void insert(iterator pos, InputIt first, InputIt last,
	    typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0);
	// erase
	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);
	// push_back
	void push_back(const T& value);
	// pop_back
	void pop_back() { _destruct_at_end(1); }
	void resize(size_type count, T value = T());
	void swap(vector& other);

  private:
	void _vallocate(size_type n);
	void _construct_at_end(size_type n, T value);
	void _construct_at_end(size_type n);
	void _destruct_at_end(size_type n);
	void _destruct_at_end(pointer new_last);
};

/* -------------------------------------------------------------------------- */
/*                                 constructor                                */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
vector<T, Allocator>::vector(const Allocator& alloc) :
    _begin(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc)
{}

template <class T, class Allocator>
vector<T, Allocator>::vector(size_type count, const T& value, const Allocator& alloc) :
    _alloc(alloc)
{
	_vallocate(count);
	assign(count, value);
}

template <class T, class Allocator>
template <class InputIt>
vector<T, Allocator>::vector(InputIt first, InputIt last, const Allocator& alloc) : _alloc(alloc)
{
	size_type count = static_cast<size_type>(last - first);
	_vallocate(count);
	_construct_at_end(count);
	std::copy(first, last, _begin);
}

template <class T, class Allocator>
vector<T, Allocator>::vector(const vector& other) : _alloc(other._alloc)
{
	size_type count = other.size();

	_vallocate(other.capacity());
	_construct_at_end(count);
	std::copy(other._begin, other._end, _begin);
}

/* -------------------------------------------------------------------------- */
/*                                  operator=                                 */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector<T, Allocator>& other)
{
	if (this != &other) {
		_vallocate(other.capacity());
		_construct_at_end(other.size());
		std::copy(other._begin, other._end, _begin);
	}
	return *this;
}

/* -------------------------------------------------------------------------- */
/*                                   assign                                   */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::assign(size_type count, const T& value)
{
	pointer current;

	if (capacity() < count)
		reserve(count);
	current = _begin;
	for (size_type i = 0; i < count; ++i, ++current) {
		*current = value;
	}
	_end = _begin + count;
}

template <class T, class Allocator>
template <class InputIt>
void vector<T, Allocator>::assign(
    InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type*)
{
	size_type count = static_cast<size_type>(last - first);
	pointer   current;

	if (capacity() < count)
		reserve(count);
	current = _begin;
	for (InputIt it = first; it != last; ++it, ++current) {
		*current = *it;
	}
	_end = _begin + count;
}

/* -------------------------------------------------------------------------- */
/*                                     at                                     */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos)
{
	if (pos >= size())
		throw std::out_of_range("index out of range");
	return _begin[pos];
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type pos) const
{
	if (pos >= size())
		throw std::out_of_range("index out of range");
	return _begin[pos];
}

/* -------------------------------------------------------------------------- */
/*                                   reserve                                  */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::reserve(size_type new_cap)
{
	if (new_cap <= size())
		return;
	if (capacity() > new_cap)
		return;
	if (capacity() * 2 > new_cap)
		new_cap = capacity() * 2;
	size_type _size     = size();
	pointer   new_begin = _alloc.allocate(new_cap);
	std::uninitialized_copy(_begin, _end, new_begin);
	_destruct_at_end(_begin);
	_alloc.deallocate(_begin, _size);

	_begin   = new_begin;
	_end     = _begin + _size;
	_end_cap = _begin + new_cap;
}

/* -------------------------------------------------------------------------- */
/*                                  max_size                                  */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const
{
	return std::min<size_type>(std::numeric_limits<difference_type>::max(), _alloc.max_size());
}

/* -------------------------------------------------------------------------- */
/*                                   insert                                   */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator pos, const T& value)
{
	difference_type offset = pos - begin();

	if (size() + 1 > capacity()) {
		reserve(size() + 1);
	}
	pointer insert_p = _begin + offset;
	_construct_at_end(1);
	std::copy_backward(insert_p, _end - 1, _end);

	*insert_p = value;
	return iterator(insert_p);
}

template <class T, class Allocator>
void vector<T, Allocator>::insert(iterator pos, size_type count, const T& value)
{
	difference_type offset = pos - begin();

	if (size() + count > capacity()) {
		reserve(size() + count);
	}

	pointer insert_p = _begin + offset;
	_construct_at_end(count);
	std::copy_backward(insert_p, _end - count, _end);

	for (size_type i = 0; i < count; ++i) {
		insert_p[i] = value;
	}
}

template <class T, class Allocator>
template <class InputIt>
void vector<T, Allocator>::insert(iterator pos, InputIt first, InputIt last,
    typename ft::enable_if<!ft::is_integral<InputIt>::value>::type*)
{
	difference_type count  = last - first;
	difference_type offset = pos - begin();

	if (size() + count >= capacity()) {
		reserve(size() + count);
	}

	pos = _begin + offset;
	_construct_at_end(count);
	std::copy_backward(pos, end() - count, end());

	for (InputIt it = first; it != last; ++it, ++pos) {
		*pos = *it;
	}
}

/* -------------------------------------------------------------------------- */
/*                                    erase                                   */
/* -------------------------------------------------------------------------- */

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator pos)
{
	difference_type count    = pos - begin();
	pointer         position = _begin + count;

	std::copy(position + 1, _end, position);
	_destruct_at_end(1);
	return position;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last)
{
	size_type count = last - first;

	std::copy(last, end(), first);
	_destruct_at_end(count);
	return first;
}

/* -------------------------------------------------------------------------- */
/*                                  push_back                                 */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::push_back(const T& value)
{
	size_type new_size = size() + 1;
	if (capacity() < new_size)
		reserve(new_size);
	_construct_at_end(1);
	*(_end - 1) = value;
}

/* -------------------------------------------------------------------------- */
/*                                   resize                                   */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::resize(size_type count, T value)
{
	size_type diff;

	if (size() > count) {
		diff = size() - count;
		_destruct_at_end(diff);
	} else if (size() < count) {
		diff = count - size();
		if (capacity() < count)
			reserve(count);
		_construct_at_end(diff, value);
	}
}

/* -------------------------------------------------------------------------- */
/*                                    swap                                    */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::swap(vector& other)
{
	vector<T, Allocator> save = *this;

	*this = other;
	other = save;
}

/* -------------------------------------------------------------------------- */
/*                            Non-member functions                            */
/* -------------------------------------------------------------------------- */

template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (lhs == rhs || lhs < rhs);
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return !(lhs <= rhs);
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (lhs == rhs || lhs > rhs);
}

/* -------------------------------------------------------------------------- */
/*                                  std::swap                                 */
/* -------------------------------------------------------------------------- */

template <class T, class Alloc>
void swap(std::vector<T, Alloc>& lhs, std::vector<T, Alloc>& rhs)
{
	std::vector<T, Alloc> save = lhs;

	lhs._begin   = rhs._begin;
	lhs._end     = rhs._end;
	lhs._end_cap = rhs._end_cap;
	rhs._begin   = save._begin;
	rhs._end     = save._end;
	rhs._end_cap = save._end_cap;
}

/* -------------------------------------------------------------------------- */
/*                          private member functions                          */
/* -------------------------------------------------------------------------- */

template <class T, class Alloc>
void vector<T, Alloc>::_vallocate(size_type n)
{
	if (n > max_size())
		throw std::length_error("allocation size too large");
	_begin   = _alloc.allocate(n);
	_end     = _begin;
	_end_cap = _begin + n;
}

template <class T, class Alloc>
void vector<T, Alloc>::_construct_at_end(size_type n, T value)
{
	while (n > 0) {
		_alloc.construct(_end);
		*_end = value;
		++_end;
		--n;
	}
}

template <class T, class Alloc>
void vector<T, Alloc>::_construct_at_end(size_type n)
{
	while (n > 0) {
		_alloc.construct(_end);
		++_end;
		--n;
	}
}

template <class T, class Alloc>
void vector<T, Alloc>::_destruct_at_end(size_type n)
{
	while (n > 0) {
		--_end;
		_alloc.destroy(_end);
		--n;
	}
}

template <class T, class Alloc>
void vector<T, Alloc>::_destruct_at_end(pointer new_last)
{
	while (_end != new_last) {
		--_end;
		_alloc.destroy(_end);
	}
}

} // namespace ft

#endif /* VECTOR_HPP */
