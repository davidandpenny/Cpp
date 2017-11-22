#ifndef META_STRUCT_H
#define META_STRUCT_H

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

namespace details {

} // namespace details

template <class Base = Struct, bool init = true>
struct Set_flag : Base
{
  static constexpr bool flag = init;
};

template <class Base = Struct>
struct Clear_flag : Set_flag<Base, false>
{};

template <class Base>
struct Toggle_flag : Base
{
  static constexpr bool flag = !Base::flag;
};

template <class Base, bool value>
struct AndEq_flag : Base
{
  static constexpr bool flag = value & Base::flag;
};

template <class Base, bool value>
struct OrEq_flag : Base
{
  static constexpr bool flag = value | Base::flag;
};

} // Meta

#define PP_CAT(a, b) PP_CCAT(a, b)
#define PP_CCAT(a, b) a ## b


#define MAKE_META_FLAG(member) \
template <class Base = Struct, bool init = true> \
struct Set_flag : Base \
{ \
  static constexpr bool flag = init; \
}; \
 \
template <class Base = Struct> \
struct Clear_flag : Set_flag<Base, false> \
{}; \
 \
template <class Base, bool value> \
struct AndEq_flag : Base \
{ \
  static constexpr bool flag = value & Base::flag; \
}; \
 \
template <class Base, bool value> \
struct OrEq_flag : Base \
{ \
  static constexpr bool flag = value | Base::flag; \
};

#endif // META_STRUCT_H
