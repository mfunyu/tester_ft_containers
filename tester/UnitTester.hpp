#ifndef UNITTESTER_HPP
#define UNITTESTER_HPP

#include "Log.hpp"
#include <list>
#include <string>

#define COLOR_SUCCESS "\033[32m"
#define COLOR_FAILED  "\033[31m"
#define COLOR_CLEAR   "\033[0m"

#define load_subtest_(x) UnitTester::load_subtest(x)

typedef enum e_test_status
{
	TEST_SUCCESS,
	TEST_FAILED
} t_test_status;

typedef struct s_unit_tests
{
	const char* func_name;
	void (*func_test_ptr)();
	t_test_status result;
} t_unit_tests;

class UnitTester
{
  private:
	static std::list<t_unit_tests> _func_subtest_table;
	static const char*             _current_func_name;
	Log                            _log;
	int                            _cnt_success;
	int                            _cnt_total;

  public:
	UnitTester();
	~UnitTester();
	void load_tests();
	void run_tests();
	void launcher(int argc, char** argv);

	static void load_subtest(void (*func)(void));
	static void assert_(bool evaluate);

  private:
	void _load_test(t_unit_tests* func_test_table);
	void _sandbox(t_unit_tests& current_test);
	void _display_result(t_unit_tests& current_test);
	void _display_total();
	UnitTester(UnitTester const& other);
	UnitTester& operator=(UnitTester const& other);
};

#endif /* UNITTESTER_HPP */
