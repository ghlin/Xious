#include "test.h"

namespace Xi { namespace test_util {

struct Unit_Test_Status
{
  bool marked;
  bool result; /// true for passed, false for failed.
};

struct Unit_Test_Details
{
  Str              name;
  Src_Location     src_location;
  Unit_Test_Status status;
};

static inline
Unit_Test_Details make(const Str &name,
                       const Src_Location &sl)
{
  return { name, sl, { false, false } };
}

struct Test_Util_Details
{
  std::stack<Unit_Test_Details>  tests;
  std::vector<Unit_Test_Details> history;
  std::vector<Test_Unit>         all;

  size_t total  = 0;
  size_t passed = 0;
  size_t failed = 0;

  void push(const Str &test,
            const Src_Location &sl)
  {
    ++total;
    tests.push(make(test, sl));
  }

  void mark(bool result)
  {
    tests.top().status.marked = true;
    tests.top().status.result = result;
  }

  bool marked() const
  {
    return tests.top().status.marked;
  }

  bool result() const
  {
    return tests.top().status.result;
  }

  void pop()
  {
    auto last = std::move(tests.top());

    if (last.status.result)
      ++passed;
    else
      ++failed;

    all.push_back({ last.name, last.src_location, last.status.result });

    tests.pop();
  }
};

static
Test_Util_Details &the_test_util()
{
  static Test_Util_Details _;
  return _;
}

#define the_test_util the_test_util()

void push_test(const Str &test,
               const Src_Location &sl)
{
  the_test_util.push(test, sl);
}

void pop_test() { the_test_util.pop(); }
void mark(bool result) { the_test_util.mark(result); }
void mark_passed() { mark(true);  }
void mark_failed() { mark(false); }
bool marked() { return the_test_util.marked(); }
bool marked_passed() { return the_test_util.result(); }
bool marked_failed() { return !the_test_util.result(); }
size_t total_tests() { return the_test_util.total; }
size_t passed_tests() { return the_test_util.passed; }
size_t failed_tests() { return the_test_util.failed; }

const std::vector<Test_Unit> &get_all_tests()
{
  return the_test_util.all;
}

XI_BOOTSTRAP_ON("run-unit-tests", { }) { }

XI_BOOTSTRAP_CLEANUP("run-unit-tests", { })
{
  Xi_log("Passed / Total : %zu/%zu (%.2lf%%)",
         passed_tests(),
         total_tests(),
         100.0 * passed_tests() / total_tests());
}

} // namespace test_util
} // namespace Xi

