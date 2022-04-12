#include "MapTest.hpp"
#include "UnitTester.hpp"
#include <iostream>
#include <map>
#include <vector>

namespace ft = std;

namespace MapTest {

// -------------------------------------------------------------------------- //
//                                    begin                                   //
// -------------------------------------------------------------------------- //

void _map_begin_basic()
{
	set_explanation_("does not return the right value");
	int               size = 12;
	ft::map<int, int> ft   = _set_map(size, true);

	UnitTester::assert_(ft.begin()->first == 0);
	UnitTester::assert_(ft.begin()->second == 0);
}

void _map_begin_increment()
{
	set_explanation_("post increment returns wrong value");
	int               size = 12;
	ft::map<int, int> ft   = _set_map(size, true);

	UnitTester::assert_(ft.begin()->first == 0);
	UnitTester::assert_((++ft.begin())->first == 1);
	UnitTester::assert_((++(++ft.begin()))->first == 2);
}

void _map_begin_decrement()
{
	set_explanation_("post decrement returns wrong value");
	int               size = 12;
	ft::map<int, int> ft   = _set_map(size, true);

	// ft::map<int, int>::iterator it = ft.begin();

	// UnitTester::assert_(it->first == 3);
	// UnitTester::assert_(it->first == 3);
	// UnitTester::assert_(it->first == 1);
	// UnitTester::assert_(it->first == 0);
}

void map_begin()
{
	load_subtest_(_map_begin_basic);
	// load_subtest_(_map_begin_increment);
}

// -------------------------------------------------------------------------- //
//                                    end                                   //
// -------------------------------------------------------------------------- //

void _map_end_basic()
{
	set_explanation_("does not return the right value");
	int               size = 7;
	ft::map<int, int> ft   = _set_map(size, true);

	UnitTester::assert_((--ft.end())->first == size - 1);
}

void _map_end_increment()
{
	set_explanation_("post increment returns wrong value");
	// ft::map<int, int> ft   = _set_map(size, true);

	// UnitTester::assert_(*--ft.end() == size - 1);
	// UnitTester::assert_(*--(--ft.end()) == size - 2);
	// UnitTester::assert_(*--(--(--ft.end())) == size - 3);
}

void map_end()
{
	load_subtest_(_map_end_basic);
	// load_subtest_(_map_end_increment);
}

// -------------------------------------------------------------------------- //
//                                    rbegin                                  //
// -------------------------------------------------------------------------- //

void _map_rbegin_basic()
{
	set_explanation_("does not return the right value");
	int               size = 12;
	ft::map<int, int> ft   = _set_map(size, true);

	UnitTester::assert_(ft.rbegin()->first == size - 1);
}

void _map_rbegin_increment()
{
	set_explanation_("post increment returns wrong value");
	int               size = 12;
	ft::map<int, int> ft   = _set_map(size, true);

	// UnitTester::assert_(ft.rbegin() == size - 1);
	// UnitTester::assert_(++ft.rbegin() == size - 2);
	// UnitTester::assert_(++(++ft.rbegin()) == size - 3);
}

void map_rbegin()
{
	load_subtest_(_map_rbegin_basic);
	// load_subtest_(_map_rbegin_increment);
}

// -------------------------------------------------------------------------- //
//                                    rend                                    //
// -------------------------------------------------------------------------- //

void _map_rend_basic()
{
	set_explanation_("does not return the right value");
	int               size = 7;
	ft::map<int, int> ft   = _set_map(size, true);

	UnitTester::assert_((--ft.rend())->first == 0);
}

void _map_rend_increment()
{
	set_explanation_("post increment returns wrong value");
	int               size = 9;
	ft::map<int, int> ft   = _set_map(size, true);

	// UnitTester::assert_(*--ft.rend() == 0);
	// UnitTester::assert_(*--(--ft.rend()) == 1);
	// UnitTester::assert_(*--(--(--ft.rend())) == 2);
}

void map_rend()
{
	load_subtest_(_map_rend_basic);
	// load_subtest_(_map_rend_increment);
}

} // namespace MapTest
