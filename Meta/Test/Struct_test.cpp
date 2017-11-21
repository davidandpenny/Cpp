#include "../Struct.h"

namespace Meta {

// flag.

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

  META_MAKE_FLAG(enabled)
  META_MAKE_FLAG(super_user)

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
}
