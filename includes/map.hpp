#ifndef MAP_HPP
#define MAP_HPP

#include "iterators.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> > >
class map
{
  public:
	typedef Key                               key_type;
	typedef T                                 mapped_type;
	typedef std::pair<const Key, T>           value_type;
	typedef std::size_t                       size_type;
	typedef std::ptrdiff_t                    difference_type;
	typedef Compare                           key_compare;
	typedef Allocator                         allocator_type;
	typedef value_type&                       reference;
	typedef const value_type&                 const_reference;
	typedef typename Allocator::pointer       pointer;
	typedef typename Allocator::const_pointer const_pointer;

	typedef ft::random_access_iterator<value_type>       iterator;
	typedef ft::random_access_iterator<const value_type> const_iterator;
	typedef ft::reverse_iterator<iterator>               reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;

	class value_compare
	{
	  public:
		typedef bool       result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;

	  protected:
		Compare comp;
		value_compare(Compare c){};

	  public:
		bool operator()(const value_type& lhs, const value_type& rhs) const {};
	};

  private:
	// _base _tree;

  public:
	// (constructor)
	map(){};
	explicit map(const Compare& comp, const Allocator& alloc = Allocator()){};
	template <class InputIt>
	map(InputIt first, InputIt last, const Compare& comp = Compare(),
	    const Allocator& alloc = Allocator()){};
	map(map const& other){};
	// (destructor)
	~map(){};
	map&           operator=(map const& other){};
	allocator_type get_allocator() const {};
	// ---------------------------- Elements access ---------------------------- //
	// at
	T&       at(const Key& key){};
	const T& at(const Key& key) const {};
	// operator[]
	T& operator[](const Key& key){};
	// ------------------------------- Iterators ------------------------------- //
	iterator               begin(){};
	const_iterator         begin() const {};
	iterator               end(){};
	const_iterator         end() const {};
	reverse_iterator       rbegin(){};
	const_reverse_iterator rbegin() const {};
	reverse_iterator       rend(){};
	const_reverse_iterator rend() const {};
	/* -------------------------------- Capacity ------------------------------- */
	bool      empty() const {};
	size_type size() const {};
	size_type max_size() const {};
	/* ------------------------------- Modifiers ------------------------------- */
	void clear(){};
	// insert
	std::pair<iterator, bool> insert(const value_type& value){};
	iterator                  insert(iterator hint, const value_type& value){};
	template <class InputIt>
	void insert(InputIt first, InputIt last){};
	// erase
	void      erase(iterator pos){};
	void      erase(iterator first, iterator last){};
	size_type erase(const Key& key){};
	// swap
	void swap(map& other){};
	/* --------------------------------- Lookup -------------------------------- */
	size_type                                 count(const Key& key) const {};
	iterator                                  find(const Key& key){};
	const_iterator                            find(const Key& key) const {};
	std::pair<iterator, iterator>             equal_range(const Key& key){};
	std::pair<const_iterator, const_iterator> equal_range(const Key& key) const {};
	iterator                                  lower_bound(const Key& key){};
	const_iterator                            lower_bound(const Key& key) const {};
	iterator                                  upper_bound(const Key& key){};
	const_iterator                            upper_bound(const Key& key) const {};
	/* ------------------------------- Observers ------------------------------- */
	key_compare   key_comp() const {};
	value_compare value_comp() const {};
};

/* -------------------------------------------------------------------------- */
/*                            Non-member functions                            */
/* -------------------------------------------------------------------------- */
template <class Key, class T, class Compare, class Alloc>
bool operator==(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
bool operator<(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
bool operator>(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(
    const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{}

/* -------------------------------------------------------------------------- */
/*                                  std::swap                                 */
/* -------------------------------------------------------------------------- */
template <class Key, class T, class Compare, class Alloc>
void swap(std::map<Key, T, Compare, Alloc>& lhs, std::map<Key, T, Compare, Alloc>& rhs)
{}

} // namespace ft

#endif /* MAP_HPP */
