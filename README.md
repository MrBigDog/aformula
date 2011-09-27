AFormula
========

[![StillMaintained](http://stillmaintained.com/cpence/aformula.png)](http://stillmaintained.com/cpence/aformula)

AFormula is a library for dynamically calculating the value of mathematical
formulas, passed in as strings.  It is designed to mirror roughly the API of
the muParser library <http://muparser.sourceforge.net/> as well as offer me
a place to experiment with more advanced formula evaluation techniques such as
JIT-compiling formulas.

Support is included for all the standard arithmetic and comparative operators,
including <=, >=, !=, ==, <, >, +, -, *, /, and ^ (power).  Arbitrary
variables may be defined (as pointers to double-values), and the assignment
operator (=) may be used to assign values to them.  A full suite of builtin
functions is supported, including:

 * Trigonometry (sin, cos, tan, asin, acos, atan, atan2)
 * Hyperbolic trigonometry (sinh, cosh, tanh, asinh, acosh, atanh)
 * Exponentials (log2, log10 [= log], ln, exp, sqrt)
 * Miscellaneous (sign, rint, abs)
 * Logical control (if(x,if-true,if-false))

Finally, the constants 'pi' and 'e' are supported.

The priority of operations is:

    =                       (assignment, lowest)
    <=, >=, !=, ==, <, >    (comparisons)
    +, -                    (addition/subtraction)
    *, /                    (multiplication/division)
    ^                       (exponentiation)

AFormula is designed to be quite robust to invalid formulas, and is careful to
return appropriate errors when necessary.

There are two JIT backends which AFormula can use in order to compile functions
on the fly: LLVM and libjit.  In general, both should provide roughly the same
performance, though there is a performance test included which will benchmark
the library and permit selection at runtime.


Requirements
------------

The Boost C++ Libraries <http://www.boost.org> are required to build AFormula.

If you want either of the dynamic-compilation backends to be built, you will
need to install either LLVM (version 2.7) <http://www.llvm.org>, or libjit 
<http://freshmeat.net/projects/libjit/>.

Compile LLVM with the --enable-shared option, to create the large libLLVM-2.7
shared library.

Note that at the time of this writing I was not able to get libjit to compile 
without a fair bit of hacking around on its source code.  I've pushed my 
changes to an unofficial clone of libjit, available at 
<http://github.com/cpence/libjit>.

Neither of these libraries are necessary (the included muParser backend will be
built regardless), but they will provide a large speed boost.


Thanks
------

Thanks are most obviously due to the author of muParser, Ingo Berg.  Without
muParser having been written, I never would have been able to start on the
project that produced the need for AFormula.  muParser, which is licensed under
the MIT license, is Copyright (C) 2004-2006 Ingo Berg.

Also, thanks is due to the pair of massively cross-platform JIT compilation
libraries, LLVM and libjit, without which a JIT-compilation backend (for 
something like an order of magnitude of performance) would be impossible.

