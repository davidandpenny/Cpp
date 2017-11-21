// #include <cstddef> // for size_t.
// #include <type_traits>

namespace Meta {

// Struct is used as a base class to be extended by subclasses adding static
// constexpr value members.
// The value of members can be "changed" by deriving a further subclass that has
// a new value possibly based on the parent class.
// The ultimate derived class's members can be accessed conventionally to get
// the "latest" value of the named member.

struct Struct {};

#define PP_CAT(a, b) PP_CCAT(a, b)
#define PP_CCAT(a, b) a ## b

#define META_MAKE_FLAG(member)                                          \
  template <class Base = Struct, bool init = true>                      \
  struct PP_CAT(Set_, member) : Base                                    \
  {                                                                     \
    static constexpr bool member = init;                                \
  };                                                                    \
                                                                        \
  template <class Base = Struct>                                        \
  struct PP_CAT(Clear_, member) : PP_CAT(Set_,member)<Base, false>      \
  {};                                                                   \
                                                                        \
  template <class Base>                                                 \
  struct PP_CAT(Toggle_, member) : Base                                 \
  {                                                                     \
    static constexpr bool member = !Base::member;                       \
  };                                                                    \
                                                                        \
  template <class Base, bool value>                                     \
  struct PP_CAT(AndEq_, member) : Base                                  \
  {                                                                     \
    static constexpr bool member = value & Base::member;                \
  };                                                                    \
                                                                        \
  template <class Base, bool value>                                     \
  struct PP_CAT(OrEq_, member) : Base                                   \
  {                                                                     \
    static constexpr bool member = value | Base::member;                \
  };                                                                    \
                                                                        \
  template <class Base, bool value>                                     \
  struct PP_CAT(XorEq_, member) : Base                                  \
  {                                                                     \
    static constexpr bool member = value ^ Base::member;                \
  };

// Create sample templates for:
//   
//   Set_flag<class Base = Struct, bool init = true> 
//   Clear_flag<class Base = Struct>
//   Toggle_flag<class Base>
//   AndEq_flag<class Base, bool value>
//   OrEq_flag<class Base, bool value>
//   XorEq_flag<class Base, bool value>

META_MAKE_FLAG(flag)

}
