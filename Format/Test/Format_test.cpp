#include "../Format.h"

#include "Meta/Struct.h"

#include <type_traits>

using namespace Format;
using namespace Meta;
using std::is_same;

namespace {

#define S(s) decltype(PP_CAT(s, _S))

// Trivial formats
static_assert(is_same<Formatter<char>, Sequence<String<char>>>(), "");
static_assert(Formatter<char>{} == Sequence<S("")>{}, "");

static_assert(Formatter<char, 'a'>{} == Sequence<S("a")>{}, "");

static_assert(Formatter<char, 'a', 'b', 'c'>{} == Sequence<S("abc")>{}, "");
static_assert("abc"_Fmt == Sequence<S("abc")>{}, "");

static_assert("{{abc}}"_Fmt == Sequence<S("{abc}")>{}, "");

static_assert("{}abc{}"_Fmt == // wrong!
    Sequence<S(""), S("*"), S("abc"), S("*"), S("")>{}, "");

static_assert("{}abc{}"_Fmt == // right, but fails.
    Sequence<S("*"), S("abc"), S("*")>{}, "");

static_assert("x{}abc{}y"_Fmt ==
    Sequence<S("y"), S("*"), S("abc"), S("*"), S("x")>{}, "");

// Wide char formats
static_assert(is_same<Formatter<wchar_t>, Sequence<String<wchar_t>>>(), "");
static_assert(Formatter<wchar_t>{} == Sequence<S(L"")>{}, "");

static_assert(Formatter<wchar_t, 'a'>{} == Sequence<S(L"a")>{}, "");

static_assert(Formatter<wchar_t, 'a', 'b', 'c'>{} == Sequence<S(L"abc")>{}, "");
static_assert(L"abc"_Fmt == Sequence<S(L"abc")>{}, "");

static_assert(L"{{abc}}"_Fmt == Sequence<S(L"{abc}")>{}, "");



}
