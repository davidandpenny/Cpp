#ifndef META_STRUCT_H
#define META_STRUCT_H


#define PP_CAT(a, b) PP_CCAT(a, b)
#define PP_CCAT(a, b) a ## b



namespace Meta {

// Struct is used as a base class to be extended by subclasses adding static
// constexpr value members.
// The value of members can be "changed" by deriving a further subclass that has
// a new value possibly based on the parent class.
// The ultimate derived class's members can be accessed conventionally to get
// the "latest" value of the named member.

struct Struct {};

// Create templates to introduce/set/clear/invert/and/or/xor a boolean member.

#define META_MAKE_BOOL(member)                                          \
template <class Base = Struct, bool init = true>                        \
struct PP_CAT(Set_,member) : Base                                       \
{                                                                       \
  static constexpr bool member {init};                                  \
};                                                                      \
                                                                        \
template <class Base = Struct>                                          \
struct PP_CAT(Clear_, member) : PP_CAT(Set_, member)<Base, false>       \
{};                                                                     \
                                                                        \
template <class Base>                                                   \
struct PP_CAT(Toggle_, member) : Base                                   \
{                                                                       \
  static constexpr bool member = !Base::member;                         \
};                                                                      \
                                                                        \
template <class Base, bool value>                                       \
struct PP_CAT(AndEq_, member) : Base                                    \
{                                                                       \
  static constexpr bool member = Base::member & value;                  \
};                                                                      \
                                                                        \
template <class Base, bool value>                                       \
struct PP_CAT(OrEq_, member) : Base                                     \
{                                                                       \
  static constexpr bool member = Base::member | value;                  \
};                                                                      \
                                                                        \
template <class Base, bool value>                                       \
struct PP_CAT(XorEq_, member) : Base                                    \
{                                                                       \
  static constexpr bool member = Base::member ^ value;                  \
};

// Create templates to introduce/set/add/subtract an integer member.
// Uses long long ints so they shouldn't overflow.

#define META_MAKE_INTEGER(member)                                       \
template <class Base = Struct, long long int init = 0>                  \
struct PP_CAT(Set_,member) : Base                                       \
{                                                                       \
  static constexpr long long int member {init};                         \
};                                                                      \
                                                                        \
template <class Base>                                                   \
struct PP_CAT(Toggle_, member) : Base                                   \
{                                                                       \
  static constexpr long long int member = !Base::member;                \
};                                                                      \
                                                                        \
template <class Base, long long int addend>                             \
struct PP_CAT(Add_, member) : Base                                      \
{                                                                       \
  static constexpr long long int member = Base::member + addend;        \
};                                                                      \
                                                                        \
template <class Base, long long int subtrahend>                         \
struct PP_CAT(Subtract_, member) : Base                                 \
{                                                                       \
  static constexpr long long int member = Base::member - subtrahend;    \
};

// Exemplary flag member adder.
META_MAKE_BOOL(flag)
META_MAKE_INTEGER(value)

} // Meta

#endif // META_STRUCT_H
