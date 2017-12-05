#include "../Format.h"

#include "Meta/Struct.h"

#include <type_traits>

using namespace Format;
using namespace Meta;
using std::is_same;

namespace {

#define S(s) decltype(PP_CAT(s, _S))

// Trivial formats
static_assert(is_same<Formatter<char>, Sequence<String<char>>>(), "OK");
static_assert(Formatter<char>{} == Sequence<S("")>{}, "OK");

static_assert(Formatter<char, 'a'>{} == Sequence<S("a")>{}, "OK");

static_assert(Formatter<char, 'a', 'b', 'c'>{} == Sequence<S("abc")>{}, "OK");
static_assert("abc"_Fmt == Sequence<S("abc")>{}, "OK");

static_assert("{{abc}}"_Fmt == Sequence<S("{abc}")>{}, "OK");
static_assert("{{}}"_Fmt == Sequence<S("{}")>{}, "OK");

static_assert("{}abc{}"_Fmt == Sequence<Printer<0>, S("abc"), Printer<1>>{},
    "OK");

static_assert("{}"_Fmt == Sequence<Printer<0>>{}, "OK");

static_assert("{{{}}}"_Fmt == Sequence<S("{"), Printer<0>, S("}")>{},
    "OK");

static_assert("x{}abc{}y"_Fmt ==
    Sequence<S("x"),  Printer<0>, S("abc"),  Printer<1>, S("y")>{}, "OK");

// Wide char formats
static_assert(is_same<Formatter<wchar_t>, Sequence<String<wchar_t>>>(), "OK");
static_assert(Formatter<wchar_t>{} == Sequence<S(L"")>{}, "OK");

static_assert(Formatter<wchar_t, L'a'>{} == Sequence<S(L"a")>{}, "OK");

static_assert(Formatter<wchar_t, L'a', L'b', L'c'>{} == Sequence<S(L"abc")>{}, "OK");
static_assert(L"abc"_Fmt == Sequence<S(L"abc")>{}, "OK");

static_assert(L"{{abc}}"_Fmt == Sequence<S(L"{abc}")>{}, "OK");
static_assert(L"{{}}"_Fmt == Sequence<S(L"{}")>{}, "OK");

static_assert(L"{}abc{}"_Fmt == Sequence<Printer<0>, S(L"abc"), Printer<1>>{},
    "OK");

static_assert(L"{}"_Fmt == Sequence<Printer<0>>{}, "OK");

static_assert(L"{{{}}}"_Fmt == Sequence<S(L"{"), Printer<0>, S(L"}")>{}, "OK");

static_assert(L"x{}abc{}y"_Fmt ==
    Sequence<S(L"x"), Printer<0>, S(L"abc"), Printer<1>, S(L"y")>{}, "OK");
}
