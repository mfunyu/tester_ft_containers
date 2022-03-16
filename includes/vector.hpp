#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector
{
  private:
  public:
	typedef T                                 value_type;
	typedef Allocator                         allocator_type;
	typedef std::size_t                       size_type;
	typedef std::ptrdiff_t                    difference_type;
	typedef value_type&                       reference;
	typedef const value_type&                 const_reference;
	typedef typename Allocator::pointer       pointer;
	typedef typename Allocator::const_pointer const_pointer;

	/*
	typedef iterator;
	typedef const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	*/

	// (constructor)
	vector(){};
	explicit vector(const Allocator& alloc);
	explicit vector(size_type count, const T& value = T(),
	    const Allocator& alloc = Allocator());
	template <class InputIt>
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
	vector(const vector& other);
	// (destructor)
	~vector(){};
	// operator=
	vector& operator=(const vector& other);
	// assign
	void assign(size_type count, const T& value);
	template <class InputIt>
	void assign(InputIt first, InputIt last);
	// get_allocator
	allocator_type get_allocator() const {};
	/* --------------------------- Elements access -------------------------- */
	// at
	reference       at(size_type pos);
	const_reference at(size_type pos) const;
	// operator[]
	reference       operator[](size_type pos){};
	const_reference operator[](size_type pos) const {};
	// front
	reference       front(){};
	const_reference front() const {};
	// back
	reference       back(){};
	const_reference back() const {};
	// data
	T*       data(){};
	const T* data() const {};

	size_t size() { return 0; };
	void   push_back(T t) { (void)t; };
};

/* -------------------------------------------------------------------------- */
/*                                 constructor                                */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
vector<T, Allocator>::vector(const Allocator& alloc)
{}

template <class T, class Allocator>
vector<T, Allocator>::vector(
    size_type count, const T& value, const Allocator& alloc)
{}
template <class T, class Allocator>
template <class InputIt>
vector<T, Allocator>::vector(
    InputIt first, InputIt last, const Allocator& alloc)
{}
template <class T, class Allocator>
vector<T, Allocator>::vector(const vector& other)
{}

/* -------------------------------------------------------------------------- */
/*                                  operator=                                 */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
vector<T, Allocator>&
vector<T, Allocator>::operator=(const vector<T, Allocator>& other)
{}

/* -------------------------------------------------------------------------- */
/*                                   assign                                   */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
void vector<T, Allocator>::assign(size_type count, const T& value)
{}

template <class T, class Allocator>
template <class InputIt>
void vector<T, Allocator>::assign(InputIt first, InputIt last)
{}

/* -------------------------------------------------------------------------- */
/*                                     at                                     */
/* -------------------------------------------------------------------------- */
template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos)
{}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::at(size_type pos) const
{}

} // namespace ft

#endif /* VECTOR_HPP */
