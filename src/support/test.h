#ifndef TEST_H_INCLUDED_CHJOGUND
#define TEST_H_INCLUDED_CHJOGUND

#include "bootstrap.h"

namespace Xi { namespace test_util {

extern void push_test(const Str &test,
                      const Src_Location &sl);
extern void pop_test();
extern void mark_passed();
extern void mark_failed();
extern void mark(bool result);
extern bool marked();
extern bool marked_passed();
extern bool marked_failed();

extern size_t total_tests();
extern size_t passed_tests();
extern size_t failed_tests();

struct Test_Unit
{
  Str            name;
  Src_Location   src_location;
  bool           result;
};

extern const std::vector<Test_Unit> &get_all_tests();

} // namespace test_util
} // namespace Xi

namespace Xi { namespace details {

struct Test_Dummy
{
  Test_Dummy(const Str &test, const Src_Location &sl)
  {
    ::Xi::xprintf("Running test %s (from %s - %u)\n", test, sl.file, sl.line);

    ::Xi::test_util::push_test(test, sl);
  }

  inline operator bool() const
  {
    return true;
  }

  ~Test_Dummy()
  {
    if (!::Xi::test_util::marked())
      ::Xi::test_util::mark_passed();

    ::Xi::test_util::pop_test();
  }
};

} // namespace details
} // namespace Xi

#define XI_UNIT_TEST_SCOPE XI_BOOTSTRAP_ON("run-unit-tests", { })

#define XI_UNIT_TEST_CASE(token)                                     \
  if (auto _ = ::Xi::details::Test_Dummy(token, XI_THIS_LOCATION())) \
    for (int _ = 0; _ != 1; ++_)

#define XI_UNIT_MARK_RESULT(result) \
  if (true) { ::Xi::test_util::mark(result); break; } else do { } while(false)

#define XI_UNIT_MARK_PASSED() XI_UNIT_MARK_RESULT(true)

#define XI_UNIT_MARK_FAILED() XI_UNIT_MARK_RESULT(false)


#endif // end of include guard: TEST_H_INCLUDED_CHJOGUND

