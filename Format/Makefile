#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CPP = g++-7

# define any compile-time flags
CPPFLAGS = -Wall -O3 -std=c++17 -fconcepts

# define any directories containing header files other than /usr/include
#
INCLUDES = -I. -I..

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = 

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = 

# define the C++ source files
SRCS  = main.cpp
SRCS += Test/Format_test.cpp

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.cpp=.o)

# define the executable file 
MAIN = format
#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    $(MAIN)
	@echo  meta compiled and static tested.

$(MAIN): $(OBJS) 
	$(CPP) $(CPPFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) -I/usr/include/c++/4.9.4 -- $(CPPFLAGS) -- $^

# DO NOT DELETE THIS LINE -- make depend needs it

main.o: /usr/include/c++/4.9.4/iostream /usr/include/c++/4.9.4/ostream
main.o: /usr/include/c++/4.9.4/ios /usr/include/c++/4.9.4/iosfwd
main.o: /usr/include/c++/4.9.4/bits/stringfwd.h
main.o: /usr/include/c++/4.9.4/bits/memoryfwd.h
main.o: /usr/include/c++/4.9.4/bits/postypes.h /usr/include/c++/4.9.4/cwchar
main.o: /usr/include/c++/4.9.4/exception
main.o: /usr/include/c++/4.9.4/bits/atomic_lockfree_defines.h
main.o: /usr/include/c++/4.9.4/bits/char_traits.h
main.o: /usr/include/c++/4.9.4/bits/stl_algobase.h
main.o: /usr/include/c++/4.9.4/bits/functexcept.h
main.o: /usr/include/c++/4.9.4/bits/exception_defines.h
main.o: /usr/include/c++/4.9.4/bits/cpp_type_traits.h
main.o: /usr/include/c++/4.9.4/ext/type_traits.h
main.o: /usr/include/c++/4.9.4/ext/numeric_traits.h
main.o: /usr/include/c++/4.9.4/bits/stl_pair.h
main.o: /usr/include/c++/4.9.4/bits/move.h
main.o: /usr/include/c++/4.9.4/bits/concept_check.h
main.o: /usr/include/c++/4.9.4/bits/stl_iterator_base_types.h
main.o: /usr/include/c++/4.9.4/bits/stl_iterator_base_funcs.h
main.o: /usr/include/c++/4.9.4/debug/debug.h
main.o: /usr/include/c++/4.9.4/bits/stl_iterator.h
main.o: /usr/include/c++/4.9.4/bits/ptr_traits.h
main.o: /usr/include/c++/4.9.4/bits/predefined_ops.h
main.o: /usr/include/c++/4.9.4/bits/localefwd.h /usr/include/c++/4.9.4/cctype
main.o: /usr/include/ctype.h /usr/include/features.h
main.o: /usr/include/stdc-predef.h /usr/include/endian.h
main.o: /usr/include/xlocale.h /usr/include/c++/4.9.4/bits/ios_base.h
main.o: /usr/include/c++/4.9.4/ext/atomicity.h
main.o: /usr/include/c++/4.9.4/bits/locale_classes.h
main.o: /usr/include/c++/4.9.4/string /usr/include/c++/4.9.4/bits/allocator.h
main.o: /usr/include/c++/4.9.4/bits/ostream_insert.h
main.o: /usr/include/c++/4.9.4/bits/cxxabi_forced.h
main.o: /usr/include/c++/4.9.4/bits/stl_function.h
main.o: /usr/include/c++/4.9.4/backward/binders.h
main.o: /usr/include/c++/4.9.4/bits/range_access.h
main.o: /usr/include/c++/4.9.4/bits/basic_string.h
main.o: /usr/include/c++/4.9.4/bits/basic_string.tcc
main.o: /usr/include/c++/4.9.4/bits/locale_classes.tcc
main.o: /usr/include/c++/4.9.4/streambuf
main.o: /usr/include/c++/4.9.4/bits/streambuf.tcc
main.o: /usr/include/c++/4.9.4/bits/basic_ios.h
main.o: /usr/include/c++/4.9.4/bits/locale_facets.h
main.o: /usr/include/c++/4.9.4/cwctype
main.o: /usr/include/c++/4.9.4/bits/streambuf_iterator.h
main.o: /usr/include/c++/4.9.4/bits/locale_facets.tcc
main.o: /usr/include/c++/4.9.4/bits/basic_ios.tcc
main.o: /usr/include/c++/4.9.4/bits/ostream.tcc
main.o: /usr/include/c++/4.9.4/istream
main.o: /usr/include/c++/4.9.4/bits/istream.tcc
Test/Format_test.o: Format.h ../Meta/Sequence.h
Test/Format_test.o: /usr/include/c++/4.9.4/cstddef
Test/Format_test.o: /usr/include/c++/4.9.4/type_traits
Test/Format_test.o: /usr/include/c++/4.9.4/bits/c++0x_warning.h
Test/Format_test.o: ../Meta/String.h ../Meta/TypeTraits.h
Test/Format_test.o: ../Meta/TypeTraits.h
