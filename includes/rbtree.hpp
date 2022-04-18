#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

namespace ft {

template <class T>
class _tree_node
{
  public:
	typedef _tree_node<T>* pointer;
	typedef T              _node_value_type;

	pointer          _left;
	pointer          _right;
	pointer          _parent;
	_node_value_type _value;
	bool             _is_black;

	_tree_node() : _left(NULL), _right(NULL), _parent(NULL), _value(0), _is_black(false){};
	_tree_node& operator=(_tree_node const& other)
	{
		if (*this != other) {
			_left     = other._left;
			_right    = other._right;
			_parent   = other._parent;
			_value    = other._value;
			_is_black = other._is_black;
		}
		return *this;
	};

  private:
	_tree_node(_tree_node const& other);
};

template <class T, class Comp, class Allocator>
class _rbtree
{
  public:
	typedef T              node_value_type;
	typedef Comp           value_compare;
	typedef Allocator      allocator_type;
	typedef _tree_node<T>  node_type;
	typedef _tree_node<T>* node_pointer;

  private:
	node_pointer   _begin_node;
	node_pointer   _nil_node;
	value_compare  _comp;
	allocator_type _alloc;

  public:
	_rbtree()
	{
		_nil_node            = new node_type;
		_nil_node->_is_black = true;
		_nil_node->_parent   = _nil_node;
		_nil_node->_left     = _nil_node;
		_nil_node->_right    = _nil_node;
		_nil_node->_value    = 0;
		_begin_node          = _nil_node;
	};
	~_rbtree(){};
	_rbtree(_rbtree const& other);
	_rbtree& operator=(_rbtree const& other);

  private:
	node_pointer _init_tree_node(node_value_type v);

	bool         _is_left_child(node_pointer ptr);
	bool         _is_right_child(node_pointer ptr);
	bool         _is_black(node_pointer ptr);
	bool         _is_black(bool _is_black_);
	bool         _is_red(node_pointer ptr);
	node_pointer _tree_min(node_pointer ptr) const;

	void _transplant(node_pointer old_, node_pointer new_);

	void _rotate_left(node_pointer ptr);
	void _rotate_right(node_pointer ptr);

	void _delete_fixup(node_pointer ptr);

	void _insert_fixup(node_pointer v);

	std::string   _node_to_dir(node_pointer& v, std::string dirprefix, bool is_right);
	node_pointer& _find_parent(node_pointer p);

	node_pointer _find_recursive(const node_pointer ptr, const node_value_type& v) const;

  public:
	node_pointer _delete(const node_value_type& v);
	node_pointer _find(const node_value_type& v) const;
	node_pointer insert(const node_value_type& v);
	void         display(std::string func_name = "", int line = -1);
};

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
bool _rbtree<T, Comp, Allocator>::_is_left_child(
    const _rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	return (ptr == ptr->_parent->_left);
}

template <class T, class Comp, class Allocator>
bool _rbtree<T, Comp, Allocator>::_is_right_child(
    const _rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	return (ptr == ptr->_parent->_right);
}

template <class T, class Comp, class Allocator>
bool _rbtree<T, Comp, Allocator>::_is_black(const _rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	return (ptr->_is_black);
}

template <class T, class Comp, class Allocator>
bool _rbtree<T, Comp, Allocator>::_is_black(bool _is_black_)
{
	return (_is_black_);
}

template <class T, class Comp, class Allocator>
bool _rbtree<T, Comp, Allocator>::_is_red(const _rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	return (!ptr->_is_black);
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_tree_min(_rbtree<T, Comp, Allocator>::node_pointer ptr) const
{
	while (ptr->_left != _nil_node) {
		ptr = ptr->_left;
	}
	return ptr;
}

/* -------------------------------------------------------------------------- */
/*                                    find                                    */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_find_recursive(const _rbtree<T, Comp, Allocator>::node_pointer ptr,
    const _rbtree<T, Comp, Allocator>::node_value_type& value) const
{
	node_pointer found;
	// node
	if (ptr == _nil_node) {
		return NULL;
	} else if (ptr->_value == value) {
		return ptr;
	}

	found = _find_recursive(ptr->_right, value);
	if (found) {
		return found;
	}
	found = _find_recursive(ptr->_left, value);
	return found;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_find(const _rbtree<T, Comp, Allocator>::node_value_type& value) const
{
	return _find_recursive(_begin_node, value);
}

/* -------------------------------------------------------------------------- */
/*                                 transplant                                 */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_transplant(
    _rbtree<T, Comp, Allocator>::node_pointer old_, _rbtree<T, Comp, Allocator>::node_pointer new_)
{
	if (old_->_parent == _nil_node) {
		_begin_node = new_;
	} else if (_is_left_child(old_)) {
		old_->_parent->_left = new_;
	} else {
		old_->_parent->_right = new_;
	}
	new_->_parent = old_->_parent;
}

/* -------------------------------------------------------------------------- */
/*                                   deletes                                  */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_delete_fixup(const _rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	node_pointer cousin;

	while (ptr != _begin_node && _is_black(ptr)) {
		if (_is_left_child(ptr)) {
			cousin = ptr->_parent->_right;
			if (_is_red(cousin)) {
				cousin->_is_black       = true;
				ptr->_parent->_is_black = false;
				_rotate_left(ptr->_parent);
				cousin = ptr->_parent->_right;
			}
			if (_is_black(cousin->_left) && _is_black(cousin->_right)) {
				cousin->_is_black = false;
				ptr               = ptr->_parent;
			} else if (_is_black(cousin->_right)) {
				cousin->_left->_is_black = true;
				cousin->_is_black        = false;
				_rotate_right(cousin);
				cousin = ptr->_parent->_right;
			}
			cousin->_is_black         = ptr->_parent->_is_black;
			ptr->_parent->_is_black   = true;
			cousin->_right->_is_black = true;
			_rotate_left(ptr->_parent);
			ptr = _begin_node;
		} else {
			cousin = ptr->_parent->_left;
			if (_is_red(cousin)) {
				cousin->_is_black       = true;
				ptr->_parent->_is_black = false;
				_rotate_left(ptr->_parent);
				cousin = ptr->_parent->_left;
			}
			if (_is_black(cousin->_right) && _is_black(cousin->_left)) {
				cousin->_is_black = false;
				ptr               = ptr->_parent;
			} else if (_is_black(cousin->_left)) {
				cousin->_right->_is_black = true;
				cousin->_is_black         = false;
				_rotate_left(cousin);
				cousin = ptr->_parent->_left;
			}
			cousin->_is_black        = ptr->_parent->_is_black;
			ptr->_parent->_is_black  = true;
			cousin->_left->_is_black = true;
			_rotate_right(ptr->_parent);
			ptr = _begin_node;
		}
	}
	ptr->_is_black = true;
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_delete(const _rbtree<T, Comp, Allocator>::node_value_type& value)
{
	node_pointer ptr              = _find(value);
	node_pointer fix_trigger_node = ptr;
	node_pointer child_to_recolor;
	bool         original_color = _is_black(fix_trigger_node);

	if (ptr->_left == _nil_node) {
		child_to_recolor = ptr->_right;
		_transplant(ptr, ptr->_right);
	} else if (ptr->_right == _nil_node) {
		child_to_recolor = ptr->_left;
		_transplant(ptr, ptr->_left);
	} else {
		fix_trigger_node = _tree_min(ptr->_right);
		original_color   = _is_black(fix_trigger_node);
		child_to_recolor = fix_trigger_node->_right;
		if (fix_trigger_node->_parent == ptr) {
			child_to_recolor->_parent = fix_trigger_node;
		} else {
			_transplant(fix_trigger_node, fix_trigger_node->_right);
			fix_trigger_node->_right          = ptr->_right;
			fix_trigger_node->_right->_parent = fix_trigger_node;
		}
		_transplant(ptr, fix_trigger_node);
		fix_trigger_node->_left          = ptr->_left;
		fix_trigger_node->_left->_parent = fix_trigger_node;
		fix_trigger_node->_is_black      = ptr->_is_black;
	}

	if (_is_black(original_color)) {
		_delete_fixup(child_to_recolor);
	}
	return ptr;
}

/* -------------------------------------------------------------------------- */
/*                                   rotates                                  */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_rotate_left(const _rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	node_pointer child = ptr->_right;
	ptr->_right        = child->_left;
	if (ptr->_right != _nil_node) {
		ptr->_right->_parent = ptr;
	}

	node_pointer parent = ptr->_parent;
	child->_parent      = parent;
	if (parent == _nil_node) {
		_begin_node = child;
	} else if (_is_left_child(ptr)) {
		parent->_left = child;
	} else {
		parent->_right = child;
	}
	child->_left = ptr;
	ptr->_parent = child;
	display(__FUNCTION__, __LINE__);
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_rotate_right(const _rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	display(__FUNCTION__, __LINE__);
	node_pointer child = ptr->_left;
	ptr->_left         = child->_right;
	if (ptr->_right != _nil_node) {
		ptr->_right->_parent = ptr;
	}
	node_pointer parent = ptr->_parent;
	child->_parent      = parent;
	if (parent == _nil_node) {
		_begin_node = child;
	} else if (_is_left_child(ptr)) {
		parent->_left = child;
	} else {
		parent->_right = child;
	}
	child->_right = ptr;
	ptr->_parent  = child;
	display(__FUNCTION__, __LINE__);
}

/* -------------------------------------------------------------------------- */
/*                                   inserts                                  */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::_insert_fixup(_rbtree<T, Comp, Allocator>::node_pointer ptr)
{
	node_pointer uncle;
	while (_is_red(ptr->_parent)) {
		if (_is_left_child(ptr->_parent)) {
			uncle = ptr->_parent->_parent->_right;
			if (_is_red(uncle)) {
				ptr->_parent->_is_black   = true;
				uncle->_is_black          = true;
				uncle->_parent->_is_black = false;

				ptr = uncle->_parent;
			} else {
				if (_is_right_child(ptr)) {
					ptr = ptr->_parent;
					_rotate_left(ptr);
				}
				ptr->_parent->_is_black          = true;
				ptr->_parent->_parent->_is_black = false;
				_rotate_right(ptr->_parent->_parent);
			}
		} else {
			uncle = ptr->_parent->_parent->_left;
			if (_is_red(uncle)) {
				ptr->_parent->_is_black   = true;
				uncle->_is_black          = true;
				uncle->_parent->_is_black = false;

				ptr = uncle->_parent;
			} else {
				if (_is_left_child(ptr)) {
					ptr = ptr->_parent;
					_rotate_right(ptr);
				}
				ptr->_parent->_is_black          = true;
				ptr->_parent->_parent->_is_black = false;
				_rotate_left(ptr->_parent->_parent);
			}
		}
	}
	_begin_node->_is_black = true;
	display(__FUNCTION__, __LINE__);
}

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::insert(const _rbtree<T, Comp, Allocator>::node_value_type& value)
{
	node_pointer new_   = _init_tree_node(value);
	node_pointer parent = _nil_node;

	for (node_pointer current = _begin_node; current != _nil_node;) {
		parent = current;
		if (value < current->_value) {
			current = current->_left;
		} else {
			current = current->_right;
		}
	}
	if (parent == _nil_node) {
		_begin_node = new_;
	} else if (value < parent->_value) {
		parent->_left = new_;
	} else {
		parent->_right = new_;
	}
	new_->_parent = parent;
	display(__FUNCTION__, __LINE__);
	_insert_fixup(new_);
	return new_;
}

/* -------------------------------------------------------------------------- */
/*                              private functions                             */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
typename _rbtree<T, Comp, Allocator>::node_pointer
_rbtree<T, Comp, Allocator>::_init_tree_node(_rbtree<T, Comp, Allocator>::node_value_type v)
{
	node_pointer ptr = new node_type;
	ptr->_parent     = _nil_node;
	ptr->_right      = _nil_node;
	ptr->_left       = _nil_node;
	ptr->_value      = v;
	ptr->_is_black   = false;

	return ptr;
}

/* -------------------------------------------------------------------------- */
/*                                    debug                                   */
/* -------------------------------------------------------------------------- */

template <class T, class Comp, class Allocator>
std::string _rbtree<T, Comp, Allocator>::_node_to_dir(
    _rbtree<T, Comp, Allocator>::node_pointer& v, std::string dirprefix, bool is_right)
{
	if (v == _nil_node)
		return "";

	std::stringstream current_dirname;
	current_dirname << dirprefix << (is_right ? "-R_" : "_L_") << v->_value;

	/* delete all before creating the root directory */
	if (dirprefix == "./") {
		std::string cmd = "rm -Rf " + current_dirname.str();
		system(cmd.c_str());
	}
	dirprefix = current_dirname.str();

	mode_t mode;
	mode = v->_is_black ? 0777 : 0755; /* to create color difference */
	mkdir(dirprefix.c_str(), mode);
	chmod(dirprefix.c_str(), mode);

	_node_to_dir(v->_right, dirprefix + "/", true);
	_node_to_dir(v->_left, dirprefix + "/", false);
	return dirprefix;
}

template <class T, class Comp, class Allocator>
void _rbtree<T, Comp, Allocator>::display(std::string func_name, int line)
{
	std::string dirpath;
	std::string cmd;
	dirpath = _node_to_dir(_begin_node, "./", true);

	std::cout << __FILE__ << ":" << line << " (" << func_name << ")" << std::endl;
	if (dirpath == "") {
		std::cerr << "Error: root deleted" << std::endl;
		exit(1);
	}

	setenv("LS_COLORS", "di=00;91:ow=30;107", 1); /* set Red & Black color */
	cmd = "tree -C --noreport " + dirpath;
	system(cmd.c_str());
	cmd = "rm -Rf " + dirpath;
	system(cmd.c_str());
}

} // namespace ft

#endif /* RBTREE_HPP */
