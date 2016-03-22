#include "steps.h"
#include "lambda.h"

#include "../support/test.h"


namespace Xi {

void Steps::update_routine(const Update_Details &ud)
{
  while (!reached_eol() && (*current)->complete())
    ++current;

  if (reached_eol())
    return;

  (*current)->update(ud);

  // XXX: this is ugly
  // 2016-03-16 18:38:01
  while (!reached_eol() && (*current)->complete())
    ++current;
}

void Steps::rewind()
{
  current = list.begin();

  for (auto &step : list)
    step->rewind();
}

XI_UNIT_TEST_SCOPE
{
  bool g_done = false;

  auto until_g_done = lambda([&g_done] (const Update_Details &)
                             {
                               return g_done;
                             });

  auto three_times = lambda([counter = std::make_shared<int>(0)] (const Update_Details &)
                            {
                              if (++*counter == 3)
                              {
                                *counter = 0;
                                return true;
                              }

                              return false;
                            });

  auto steps = make_handle<Steps>(until_g_done, three_times);

  Update_Details ud;

  XI_UNIT_TEST_CASE("steps.g_done")
  {
    for (ud.frame = 0; ud.frame != 10; ++ud.frame)
    {
      steps->update(ud);

      XI_UT_EXPECT(!steps->complete());
    }
  }

  g_done = true;

  XI_UNIT_TEST_CASE("steps.g_done done")
  {
    ud.frame++;
    steps->update(ud);
    XI_UT_EXPECT(!steps->complete());
  }

  XI_UNIT_TEST_CASE("steps.three_times.1")
  { ++ud.frame; steps->update(ud); XI_UT_EXPECT(!steps->complete()); }

  XI_UNIT_TEST_CASE("steps.three_times.2")
  { ++ud.frame; steps->update(ud); XI_UT_EXPECT(!steps->complete()); }

  XI_UNIT_TEST_CASE("steps.three_times.3")
  { ++ud.frame; steps->update(ud); XI_UT_EXPECT(steps->complete()); }

  steps->rewind();

  XI_UNIT_TEST_CASE("steps.rewind.three_times.0")
  { ++ud.frame; steps->update(ud); XI_UT_EXPECT(!steps->complete()); }

  XI_UNIT_TEST_CASE("steps.rewind.three_times.1")
  { ++ud.frame; steps->update(ud); XI_UT_EXPECT(!steps->complete()); }

  XI_UNIT_TEST_CASE("steps.rewind.three_times.2")
  { ++ud.frame; steps->update(ud); XI_UT_EXPECT(!steps->complete()); }

  XI_UNIT_TEST_CASE("steps.rewind.three_times.3")
  { ++ud.frame; steps->update(ud); XI_UT_EXPECT(steps->complete()); }
}

} // namespace Xi

