#各编译器对C++11特性的支持情况

	|-------------------------------------------------------|----------|-----------|-------------|--------------|
	|feature                                			 	|  VS2013  |  g++ 4.8  |  Clang 3.3  |  Intel 13.0  |
	|-------------------------------------------------------|----------|-----------|-------------|--------------|
	|auto                                    				|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|decltype                                				|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|Rvalue references and move semantics 	 				|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|Lambda expressions					     				|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|nullptr   								 				|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|static_assert							 				|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|Range based for loop					 				|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|Trailing return type in functions		 				|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|extern templates						 				|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|>> for nested templates				 				|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|Local and unnamed types as template arguments			|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|Variadic macros										|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|Variadic templates										|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|Default template arguments in function templates		|   Yes	   |   Yes	   |    Yes	     |     Yes      |
	|final method keyword									|   Yes	   |   Yes	   |    Yes	     |     No       |
	|override method keyword								|   Yes	   |   Yes	   |    Yes	     |     No       |
	|Strongly typed enums									|   Yes	   |   Yes	   |    Yes	     |   Partial    |
	|Forward declared enums									|   Yes	   |   Yes	   |    Yes	     |   Partial    |
	|Initializer lists										|   Yes	   |   Yes	   |    Yes	     |   Partial    |
	|explicit type conversion operators						|   Yes	   |   Yes	   |    Yes	     |     No       |
	|Raw string literals									|   Yes	   |   Yes	   |    Yes	     |     No       |
	|Forwarding constructors								|   Yes	   |   Yes	   |    Yes	     |     No       |
	|Template aliases										|   No	   |   Yes	   |    Yes	     |     Yes      |
	|Defaulted methods										|   No	   |   Yes	   |    Yes	     |     Yes      |
	|Deleted methods										|   No	   |   Yes	   |    Yes	     |     Yes      |
	|New built-in types										|  Partial |   Yes	   |    Yes		 |   Partial    |
	|Alignment support										|  Partial |   Yes	   |    Yes		 |     No	    |
	|Inline namespaces										|   No	   |   Yes	   |    Yes		 |     No	    |
	|sizeof on non-static data members without an instance	|   No	   |   Yes	   |    Yes		 |     No	    |
	|Changed restrictions on union members					|   No	   |   Yes	   |    Yes		 |     No	    |
	|User defined literals									|   No	   |   Yes	   |    Yes		 |     No	    |
	|Encoding support in literals							|   No	   |   Yes	   |    Yes		 |     No	    |
	|Arbitrary expressions in template deduction contexts	|   No	   |   Yes	   |    Yes		 | Don’t know   |
	|Non-static data member initializers					|   No	   |   Yes	   |    Yes		 | Don’t know   |
	|noexcept												|   No	   |   Yes	   |    Yes		 |  Partial	    |
	|constexpr												|   No	   |   Yes	   |    Yes		 |  Partial	    |
	|C99 compatibility										|  Partial |   Yes	   |  Partial	 |    Yes	    |
	|Generalized attributes									|   No	   |   Yes	   |  Partial	 |    Yes	    |
	|Thread local storage									|  Partial |   Yes	   |    No		 |  Partial	    |
	|Inheriting constructors								|   No	   |   Yes	   |    No		 |    No	    |
	|Rvalue references for *this							|   No	   |   No	   |    Yes		 |    No	    |
	|Minimal support for garbage collection					|   Yes	   |   No	   |    No		 | Don’t know   |
	|-------------------------------------------------------|----------|-----------|-------------|--------------|


参考：

[http://developer.51cto.com/art/201303/384630.htm](http://developer.51cto.com/art/201303/384630.htm)

[http://www.csdn.net/article/2013-03-18/2814528-c11-compiler-support-shootout-visual-studio-gcc-clang-intel](http://www.csdn.net/article/2013-03-18/2814528-c11-compiler-support-shootout-visual-studio-gcc-clang-intel)
