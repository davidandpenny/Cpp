#include "../Struct.h"

namespace Meta {

namespace flag_tests {

//Struct::flag; -- "‘flag’ is not a member of ‘Meta::Struct’"

// Simple setting.
  static_assert(Set_flag<Struct, true>::flag, "flag set");
  static_assert(Set_flag<>::flag, "flag set");

  static_assert(!Clear_flag<Struct>::flag, "flag set false");
  static_assert(!Clear_flag<>::flag, "flag set false");

// Resetting.
  static_assert(Set_flag<Set_flag<>>::flag, "flag set twice");
  static_assert(!Set_flag<Set_flag<>, false>::flag, "flag cleared");
  static_assert(!Clear_flag<Set_flag<>>::flag, "flag cleared");

  static_assert(Set_flag<Clear_flag<>>::flag, "flag set from clear");
  static_assert(!Set_flag<Clear_flag<>, false>::flag,
      "flag cleared twice");

// Complementing.
//Toggle_flag<Struct>::flag; -- "‘flag’ is not a member of ‘Meta::Struct’"
  static_assert(!Toggle_flag<Set_flag<>>::flag, "true flag toggled");
  static_assert(Toggle_flag<Clear_flag<>>::flag, "false flag toggled");

//AndEq_flag<Struct, true>; -- "‘flag’ is not a member of ‘Meta::Struct’"
  static_assert(!AndEq_flag<Clear_flag<>, true>::flag,
      "false & true flag unset");
  static_assert(!AndEq_flag<Clear_flag<>, false>::flag,
      "false & false flag unset");
  static_assert(AndEq_flag<Set_flag<>, true>::flag,
      "true & true flag set");
  static_assert(!AndEq_flag<Set_flag<>, false>::flag,
      "true & false flag unset");

//OrEq_flag<Struct, true>; -- "‘flag’ is not a member of ‘Meta::Struct’"
  static_assert(OrEq_flag<Clear_flag<>, true>::flag,
      "false | true flag set");
  static_assert(!OrEq_flag<Clear_flag<>, false>::flag,
      "false | false flag unset");
  static_assert(OrEq_flag<Set_flag<>, true>::flag,
      "true | true flag set");
  static_assert(OrEq_flag<Set_flag<>, false>::flag,
      "true | false flag set");

//XorEq_flag<Struct, true>; -- "‘flag’ is not a member of ‘Meta::Struct’"
  static_assert(XorEq_flag<Clear_flag<>, true>::flag,
      "false ^ true flag set");
  static_assert(!XorEq_flag<Clear_flag<>, false>::flag,
      "false ^ false flag unset");
  static_assert(!XorEq_flag<Set_flag<>, true>::flag,
      "true ^ true flag unset");
  static_assert(XorEq_flag<Set_flag<>, false>::flag,
      "true ^ false flag set");

  META_MAKE_BOOL(enabled)

  META_MAKE_BOOL(super_user)

  // Model a compile-time struct equivalent to:
  //   struct User { bool enabled{true}; bool super_user{false}; };
  using User = Set_enabled<Clear_super_user<>>;
  static_assert(User::enabled, "user is enabled");
  static_assert(!User::super_user, "user can't jump tall buildings");

  using SuperUser = Set_super_user<User>;
  static_assert(SuperUser::enabled, "user is still enabled");
  static_assert(SuperUser::super_user, "user now has super powers");

  using DisabledUser = Clear_enabled<User>;
  static_assert(User::enabled, "user is no longer enabled");
  static_assert(!DisabledUser::super_user, "user still can't jump");

} // flag_tests.

namespace value_tests {

//Struct::value; -- "‘value’ is not a member of ‘Meta::Struct’"

// Simple setting.
  static_assert(Set_value<>::value == 0, "default value set");
  static_assert(Set_value<Struct, 42>::value == 42, "value set");

// Resetting.
  static_assert(Set_value<Set_value<>, 66>::value == 66, "value updated");
  static_assert(Set_value<Set_value<Struct, 42>>::value == 0, "value reset");

// Adding
//Add_value<Struct, 1>; -- "‘value’ is not a member of ‘Meta::Struct’"
  static_assert(Add_value<Set_value<>, 1>::value == 1,
      "adding 1 to zero");
  static_assert(Add_value<Add_value<Set_value<>, 1>, 1>::value == 2,
      "adding 1 to zero twice");
  static_assert(Add_value<Add_value<Add_value<Set_value<>, 1>, 1>, 1>::value
      == 3, "now we're counting");

// Subtracting
//Subtract_value<Struct, 1>; -- "‘value’ is not a member of ‘Meta::Struct’"
  static_assert(Subtract_value<Set_value<>, 1>::value == -1,
      "subtracting 1 from zero");
  static_assert(Subtract_value<Subtract_value<Set_value<>, 1>, 1>::value == -2,
      "subtracting 1 from zero twice");
  static_assert(Subtract_value<Subtract_value<Set_value<Struct,2>, 1>, 1>::value
      == 0, "counting down");


} // value_tests

}
