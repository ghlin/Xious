#ifndef CHAPTER_H_INCLUDED_UNGDAVZU
#define CHAPTER_H_INCLUDED_UNGDAVZU

#include "demo.h"

namespace Xi {

class Chapter : public Actor
{
  using Super = Actor;

public:
  Str         title;

  Chapter(Str title) : title(std::move(title)) { }
protected:
  Game_Loop  *game_loop;
public:

  inline void initialize_chapter(Game_Loop *gl)
  {
    game_loop = gl;
    do_initialize_chapter();
  }
protected:
  virtual void do_initialize_chapter() = 0;
};

attr_export
void register_chapter(Handle<Chapter> chapter);

attr_export
const std::vector<Handle<Chapter>> &get_chapters();

#define XI_DEF_CHAPTER(token)                                     \
  class token;                                                    \
  using The_Chapter = token;                                      \
  constexpr static char Chapter_Title[] = XI_STRINGIFY(token);    \
  static Handle<Chapter> create();                                \
  XI_BOOTSTRAP_SCOPE()                                            \
  { register_chapter(create()); }                                 \
  class token : public Chapter                                    \
  { using Super = Chapter;                                        \
  public:                                                         \
    token() : Chapter(Chapter_Title) { }                          \
    virtual void do_initialize_chapter() override;                \
  protected:                                                      \
    virtual void update_logic(const Update_Details &ud) override; \
  public:

#define XI_CHAPTER_INIT() };                                           \
  Handle<Chapter> create() { return std::make_shared<The_Chapter>(); } \
  void The_Chapter::do_initialize_chapter()

#define XI_CHAPTER_UPDATE(ud) void The_Chapter::update_logic(const Update_Details &ud)

} // namespace Xi

#endif // end of include guard: CHAPTER_H_INCLUDED_UNGDAVZU

