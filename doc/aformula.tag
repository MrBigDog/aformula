<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>aformula.h</name>
    <path>/Users/cpence/Development/aformula/include/</path>
    <filename>aformula_8h</filename>
    <class kind="class">AFormula::Formula</class>
    <namespace>AFormula</namespace>
  </compound>
  <compound kind="file">
    <name>codegenerator.h</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>codegenerator_8h</filename>
    <class kind="class">AFormula::Private::CodeGenerator</class>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
  </compound>
  <compound kind="file">
    <name>formula.cpp</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>formula_8cpp</filename>
    <includes id="aformula_8h" name="aformula.h" local="no" imported="no">aformula.h</includes>
    <includes id="formula_8cpp" name="formula.cpp" local="no" imported="no">config.h</includes>
    <includes id="jitformula_8h" name="jitformula.h" local="yes" imported="no">jitformula.h</includes>
    <includes id="codegenerator_8h" name="codegenerator.h" local="yes" imported="no">codegenerator.h</includes>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>timerFrequency</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>af86fb721a7608baae99cea974b5f9db4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>timerTime</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>a2d9a9ed65454515db780a7bc04c7c40b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>signal_handler</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>adf2fc54853c619a6b97b68e4433f6284</anchor>
      <arglist>(int signum)</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>errorMessage</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>ac938af24f2ad5efc3153d39d0470e7aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static int</type>
      <name>defaultBackend</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>a114f015fb38570e033e7b2bb470214a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile sig_atomic_t</type>
      <name>errorflag</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>ade6b09620039807bffcc3a6fcac49e9b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>jitformula.h</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>jitformula_8h</filename>
    <includes id="parser_8h" name="parser.h" local="yes" imported="no">parser.h</includes>
    <class kind="class">AFormula::Private::JITFormula</class>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
  </compound>
  <compound kind="file">
    <name>libjitformula.cpp</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>libjitformula_8cpp</filename>
    <includes id="aformula_8h" name="aformula.h" local="no" imported="no">aformula.h</includes>
    <includes id="libjitformula_8h" name="libjitformula.h" local="yes" imported="no">libjitformula.h</includes>
    <includes id="libjitformula_8cpp" name="libjitformula.cpp" local="yes" imported="no">parsetree.h</includes>
    <includes id="codegenerator_8h" name="codegenerator.h" local="yes" imported="no">codegenerator.h</includes>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
  </compound>
  <compound kind="file">
    <name>libjitformula.h</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>libjitformula_8h</filename>
    <includes id="jitformula_8h" name="jitformula.h" local="yes" imported="no">jitformula.h</includes>
    <includes id="codegenerator_8h" name="codegenerator.h" local="yes" imported="no">codegenerator.h</includes>
    <class kind="class">AFormula::Private::LibJITFormula</class>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
  </compound>
  <compound kind="file">
    <name>llvmformula.cpp</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>llvmformula_8cpp</filename>
    <includes id="aformula_8h" name="aformula.h" local="no" imported="no">aformula.h</includes>
    <includes id="llvmformula_8h" name="llvmformula.h" local="yes" imported="no">llvmformula.h</includes>
    <includes id="parsetree_8h" name="parsetree.h" local="yes" imported="no">parsetree.h</includes>
    <class kind="class">AFormula::Private::LLVMInitializer</class>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
    <member kind="variable">
      <type>LLVMInitializer</type>
      <name>llvmInitializer</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>af18dc43e3908720ae81abaf1b19376b2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>llvmformula.h</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>llvmformula_8h</filename>
    <includes id="jitformula_8h" name="jitformula.h" local="yes" imported="no">jitformula.h</includes>
    <includes id="codegenerator_8h" name="codegenerator.h" local="yes" imported="no">codegenerator.h</includes>
    <class kind="class">AFormula::Private::LLVMFormula</class>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
  </compound>
  <compound kind="file">
    <name>muparserformula.cpp</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>muparserformula_8cpp</filename>
    <includes id="aformula_8h" name="aformula.h" local="no" imported="no">aformula.h</includes>
    <includes id="muparserformula_8h" name="muparserformula.h" local="yes" imported="no">muparserformula.h</includes>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
  </compound>
  <compound kind="file">
    <name>muparserformula.h</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>muparserformula_8h</filename>
    <class kind="class">AFormula::Private::MuParserFormula</class>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
  </compound>
  <compound kind="file">
    <name>parser.cpp</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>parser_8cpp</filename>
    <includes id="aformula_8h" name="aformula.h" local="no" imported="no">aformula.h</includes>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
    <member kind="function">
      <type>void</type>
      <name>clearVariables</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>a86eb95b49c0c0ceb0263bac304dd113f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setVariable</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>aafa829130cf8d4c2939f63652447e11b</anchor>
      <arglist>(const std::string &amp;name, double *pointer)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>parser.h</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>parser_8h</filename>
    <class kind="class">AFormula::Private::Parser</class>
    <class kind="struct">AFormula::Private::Parser::Function</class>
    <class kind="struct">AFormula::Private::Parser::Operator</class>
    <class kind="struct">AFormula::Private::Parser::Variable</class>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
  </compound>
  <compound kind="file">
    <name>parsetree.h</name>
    <path>/Users/cpence/Development/aformula/src/</path>
    <filename>parsetree_8h</filename>
    <includes id="codegenerator_8h" name="codegenerator.h" local="yes" imported="no">codegenerator.h</includes>
    <class kind="class">AFormula::Private::ExprAST</class>
    <class kind="class">AFormula::Private::NumberExprAST</class>
    <class kind="class">AFormula::Private::VariableExprAST</class>
    <class kind="class">AFormula::Private::UnaryMinusExprAST</class>
    <class kind="class">AFormula::Private::BinaryExprAST</class>
    <class kind="class">AFormula::Private::CallExprAST</class>
    <namespace>AFormula</namespace>
    <namespace>AFormula::Private</namespace>
  </compound>
  <compound kind="namespace">
    <name>AFormula</name>
    <filename>namespace_a_formula.html</filename>
    <namespace>AFormula::Private</namespace>
    <class kind="class">AFormula::Formula</class>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>timerFrequency</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>af86fb721a7608baae99cea974b5f9db4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>timerTime</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>a2d9a9ed65454515db780a7bc04c7c40b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>signal_handler</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>adf2fc54853c619a6b97b68e4433f6284</anchor>
      <arglist>(int signum)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static int</type>
      <name>defaultBackend</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>a114f015fb38570e033e7b2bb470214a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>volatile sig_atomic_t</type>
      <name>errorflag</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>ade6b09620039807bffcc3a6fcac49e9b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Formula</name>
    <filename>class_a_formula_1_1_formula.html</filename>
    <member kind="enumvalue">
      <name>BACKEND_DEFAULT</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a37115887bbd8a788ce61356febaf0b35a8d8b83347fdd34c44a34c47453f81bb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BACKEND_MUPARSER</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a37115887bbd8a788ce61356febaf0b35a2e11dbf3ee10f12d706374861bf4ea06</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BACKEND_LLVM</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a37115887bbd8a788ce61356febaf0b35af2b5a2ec39d02c7dbb630595b2c5a08f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BACKEND_LIBJIT</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a37115887bbd8a788ce61356febaf0b35aa3900bd1945ca1682483795ff6777d80</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NUM_BACKENDS</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a37115887bbd8a788ce61356febaf0b35acea1d69ae5a13fbe0ea0c071dbd27def</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Formula</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>aedb8258a55cf8312a4a4594a29e2a8c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>errorString</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a391a1154676be8c8529d58267ace65d8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>setExpression</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>ab444548983e200013dc7c9b6d45072de</anchor>
      <arglist>(const std::string &amp;str)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::string</type>
      <name>expression</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a9854670c506947363b886c213fbffb32</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>setVariable</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a42f3fe0cc07731ebfbb55b83bd241fd3</anchor>
      <arglist>(const std::string &amp;variable, double *pointer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>evaluate</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a6a7111f86c5ca24ec033ed516f795075</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Formula *</type>
      <name>createFormula</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a080245c4cdf6211826c763d9e814b112</anchor>
      <arglist>(int withBackend=BACKEND_DEFAULT)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>fastestBackend</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>afa83275c5418bc9b4ccf5595bdc6cc74</anchor>
      <arglist>(bool setAsDefault=true)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>Formula</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a8e6d50fc848b5a6ff5070f18b4d5934d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>Formula</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a6fdad711314eac734a586852de60c501</anchor>
      <arglist>(const Formula &amp;rhs)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>Formula &amp;</type>
      <name>operator=</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>aced2ad07beb88adb78f2288346ab3a93</anchor>
      <arglist>(const Formula &amp;rhs)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>AFormula::Private</name>
    <filename>namespace_a_formula_1_1_private.html</filename>
    <class kind="class">AFormula::Private::CodeGenerator</class>
    <class kind="class">AFormula::Private::JITFormula</class>
    <class kind="class">AFormula::Private::LibJITFormula</class>
    <class kind="class">AFormula::Private::LLVMInitializer</class>
    <class kind="class">AFormula::Private::LLVMFormula</class>
    <class kind="class">AFormula::Private::MuParserFormula</class>
    <class kind="class">AFormula::Private::Parser</class>
    <class kind="class">AFormula::Private::ExprAST</class>
    <class kind="class">AFormula::Private::NumberExprAST</class>
    <class kind="class">AFormula::Private::VariableExprAST</class>
    <class kind="class">AFormula::Private::UnaryMinusExprAST</class>
    <class kind="class">AFormula::Private::BinaryExprAST</class>
    <class kind="class">AFormula::Private::CallExprAST</class>
    <member kind="function">
      <type>void</type>
      <name>clearVariables</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>a86eb95b49c0c0ceb0263bac304dd113f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setVariable</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>aafa829130cf8d4c2939f63652447e11b</anchor>
      <arglist>(const std::string &amp;name, double *pointer)</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>errorMessage</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>ac938af24f2ad5efc3153d39d0470e7aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>LLVMInitializer</type>
      <name>llvmInitializer</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>af18dc43e3908720ae81abaf1b19376b2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::CodeGenerator</name>
    <filename>class_a_formula_1_1_private_1_1_code_generator.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CodeGenerator</name>
      <anchorfile>class_a_formula_1_1_private_1_1_code_generator.html</anchorfile>
      <anchor>a5a222b715085b474308a18837f13f383</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_code_generator.html</anchorfile>
      <anchor>a0a29273cebbbb490c4940f397d4a74b4</anchor>
      <arglist>(NumberExprAST *)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_code_generator.html</anchorfile>
      <anchor>a044520668a6e310a473264c9dfb266ba</anchor>
      <arglist>(VariableExprAST *)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_code_generator.html</anchorfile>
      <anchor>a8b31ff34c1627f4c0a7811291bae30fb</anchor>
      <arglist>(UnaryMinusExprAST *)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_code_generator.html</anchorfile>
      <anchor>a1910e8ba3232ae57cdabbda44708eeb3</anchor>
      <arglist>(BinaryExprAST *)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_code_generator.html</anchorfile>
      <anchor>ab5c1c93aa30ad8e9d43f807eab81ad13</anchor>
      <arglist>(CallExprAST *)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::JITFormula</name>
    <filename>class_a_formula_1_1_private_1_1_j_i_t_formula.html</filename>
    <templarg>T</templarg>
    <base>AFormula::Formula</base>
    <member kind="function">
      <type></type>
      <name>JITFormula</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>ac836b704f8e3ec9857334dd2e387b48c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~JITFormula</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>afdeb1f712f114d3957a2b3e28036d27b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>setExpression</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a156ce32261f1864e012b33bcd66c6686</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>expression</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a2afb8ab1cbf3d72d8f9908ae5a135c76</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>setVariable</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a7e71e5a4214d7d52321d0de622393819</anchor>
      <arglist>(const std::string &amp;variable, double *pointer)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>evaluate</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>acdfc6e402414d8ee6f7791f20bc20fc3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>double(*</type>
      <name>FunctionPointer</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>ac8fec2c1c012d5b4f0a70b1dbfce1dc3</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>buildFunction</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>ac3f8bb2a19ce64908a7ad8419860f1fc</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>FunctionPointer</type>
      <name>func</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a82f677d0dd24b095fe0c2952dc622429</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>expr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>aed13c8ae98b80b8fd2e0c639057935ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Parser&lt; T &gt; *</type>
      <name>parser</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a9964690dd57fa923a235bd4af4db4f90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parseTree</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a3e00d707b1fe50ad1bb7761cac9443fc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::LibJITFormula</name>
    <filename>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</filename>
    <base>JITFormula&lt; void &gt;</base>
    <base>CodeGenerator&lt; void &gt;</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>ad90d6067bdfb9f72aaef80828a7606df</anchor>
      <arglist>(NumberExprAST&lt; void &gt; *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>a12c991c065bb1d5b026e27f53cc1d1e8</anchor>
      <arglist>(VariableExprAST&lt; void &gt; *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>a9f5505ad182a8ded4651af6f14238718</anchor>
      <arglist>(UnaryMinusExprAST&lt; void &gt; *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>a82249f5163a8438ab011dc5042b3c40f</anchor>
      <arglist>(BinaryExprAST&lt; void &gt; *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>aeca9ab8096915ab720737f372fa05a41</anchor>
      <arglist>(CallExprAST&lt; void &gt; *)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>buildFunction</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>a693601ea399d8fb840b6a741d7bf7318</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::LLVMInitializer</name>
    <filename>class_a_formula_1_1_private_1_1_l_l_v_m_initializer.html</filename>
    <member kind="function">
      <type></type>
      <name>LLVMInitializer</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_initializer.html</anchorfile>
      <anchor>a6745f7c81992b652833e8e60a3005061</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::LLVMFormula</name>
    <filename>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</filename>
    <base>JITFormula&lt; llvm::Value * &gt;</base>
    <base>CodeGenerator&lt; llvm::Value * &gt;</base>
    <member kind="function">
      <type></type>
      <name>LLVMFormula</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a62fa54b491ee9430ab0db88d8afd6a82</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~LLVMFormula</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a9624146deb7985200c22d82f61a1aea8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual llvm::Value *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a92f6907db93b775fc4dfe86aedeca1f9</anchor>
      <arglist>(NumberExprAST&lt; llvm::Value * &gt; *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual llvm::Value *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a2869524bb401c92f116aea611bdee834</anchor>
      <arglist>(VariableExprAST&lt; llvm::Value * &gt; *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual llvm::Value *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a7a3c335ea5d8c2d4fad48e9cbb089aad</anchor>
      <arglist>(UnaryMinusExprAST&lt; llvm::Value * &gt; *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual llvm::Value *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a27e21c1510ebb875b5d75295b5c130f7</anchor>
      <arglist>(BinaryExprAST&lt; llvm::Value * &gt; *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual llvm::Value *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a6e91638d09756e9b4860c39f72e69d5b</anchor>
      <arglist>(CallExprAST&lt; llvm::Value * &gt; *)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>buildFunction</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a36c3a7519222f4b7affcd8c4f98ea189</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>llvm::Constant *</type>
      <name>getGlobalVariableFor</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a6cc476d4c5e37e35d91096431eade274</anchor>
      <arglist>(double *ptr)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>llvm::Module *</type>
      <name>theModule</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a880a9f8ec5ccfb03ff83e9ee03d27d0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>llvm::ModuleProvider *</type>
      <name>MP</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a41f80b5f99788eb4f1937c2bc0f84d95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>llvm::IRBuilder</type>
      <name>builder</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>ab3b423f97a64aeb06108dd43cddc96ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>llvm::FunctionPassManager *</type>
      <name>FPM</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a52cf763a5471f260cc23b5731d2a32ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>llvm::ExecutionEngine *</type>
      <name>engine</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a5e2bdb086cf9664f15407fad54ea3df8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::MuParserFormula</name>
    <filename>class_a_formula_1_1_private_1_1_mu_parser_formula.html</filename>
    <base>AFormula::Formula</base>
    <member kind="function">
      <type></type>
      <name>MuParserFormula</name>
      <anchorfile>class_a_formula_1_1_private_1_1_mu_parser_formula.html</anchorfile>
      <anchor>a67e313efefc3309e22e56b526d7819ac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~MuParserFormula</name>
      <anchorfile>class_a_formula_1_1_private_1_1_mu_parser_formula.html</anchorfile>
      <anchor>aeb888283943f3664943096628fc2bf7e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>setExpression</name>
      <anchorfile>class_a_formula_1_1_private_1_1_mu_parser_formula.html</anchorfile>
      <anchor>ac012ab4de57c270594934bb8fb2b0f3b</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>expression</name>
      <anchorfile>class_a_formula_1_1_private_1_1_mu_parser_formula.html</anchorfile>
      <anchor>a4a197462ef5bd1757feaa6618df42970</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>setVariable</name>
      <anchorfile>class_a_formula_1_1_private_1_1_mu_parser_formula.html</anchorfile>
      <anchor>a61b4222238a85a2b4e3808786ffdf773</anchor>
      <arglist>(const std::string &amp;variable, double *pointer)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>evaluate</name>
      <anchorfile>class_a_formula_1_1_private_1_1_mu_parser_formula.html</anchorfile>
      <anchor>a62b7ca8ee7012070ef787eb98b2d09ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>mu::Parser</type>
      <name>muParser</name>
      <anchorfile>class_a_formula_1_1_private_1_1_mu_parser_formula.html</anchorfile>
      <anchor>a5e2081883a6c387354eb150a36867e1a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::Parser</name>
    <filename>class_a_formula_1_1_private_1_1_parser.html</filename>
    <class kind="struct">AFormula::Private::Parser::Function</class>
    <class kind="struct">AFormula::Private::Parser::Operator</class>
    <class kind="struct">AFormula::Private::Parser::Variable</class>
    <member kind="function">
      <type>void</type>
      <name>clearVariables</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a34fb1c252c3f8cc84ec637d04a1d3996</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setVariable</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a4fb4f3ce7e51c06ccd4b149e733a4a24</anchor>
      <arglist>(const std::string &amp;name, double *pointer)</arglist>
    </member>
    <member kind="function">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parseString</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>aabcc23a09b93872c31ff5b1a3f5cfe9c</anchor>
      <arglist>(const std::string &amp;f)</arglist>
    </member>
    <member kind="enumvalue">
      <name>TOKEN_BAD</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2603119ef9f6962cf3ba3e2653d304ddadd7239251dca90a31051637f4e3f74ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TOKEN_END</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2603119ef9f6962cf3ba3e2653d304dda362a2cef525d587e8e78a3a04f63a992</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TOKEN_IDENTIFIER_FUNCTION</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2603119ef9f6962cf3ba3e2653d304ddae0ef72106ac5daeedd818804f4b437d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TOKEN_IDENTIFIER_CONSTANT</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2603119ef9f6962cf3ba3e2653d304dda7277dd987298d9ca521ed14658287432</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TOKEN_IDENTIFIER_VARIABLE</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2603119ef9f6962cf3ba3e2653d304dda468e1fec2f4aca23786791a5f38c7f7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TOKEN_OPERATOR</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2603119ef9f6962cf3ba3e2653d304dda84ec8d4c33d1881c09b38120524e0a30</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TOKEN_NUMBER</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2603119ef9f6962cf3ba3e2653d304dda05520a2cd40359a48dc5e1bc1cc6f5af</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TOKEN_PAREN_OPEN</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2603119ef9f6962cf3ba3e2653d304dda1193d42a6b3940652e05b2ac94a1860b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TOKEN_PAREN_CLOSE</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2603119ef9f6962cf3ba3e2653d304dda0995a1b3a108543a3a164b5ff5a504fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TOKEN_COMMA</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2603119ef9f6962cf3ba3e2653d304dda5b6b790aca77d61a5dcf0622bb6decfe</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>error</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>af2a2ac739c33b99264ad218b0dc94403</anchor>
      <arglist>(const std::string &amp;err) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>error</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>ae42921629239cf0359262ff6ba92bde5</anchor>
      <arglist>(const boost::format &amp;fmt) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>std::string</type>
      <name>formatToken</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a4195007b87c2867d1f285a6192f46540</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>getToken</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>af0efe8ba9cbfdee50bcffb9e17247e41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>getNextToken</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2a307129d736d4214d3045fc0768feb4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>getIdentifierType</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a3e0a98183bac3ee5026ac06a31aa6248</anchor>
      <arglist>(const std::string &amp;ident) const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parseNumberExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>ae331f3dbb39c9f59626e40b19f78f93f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parseOpenParenExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a22be19ed4cae088f04fed52073ecb1f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parseFunctionIdentifierExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>ac9edb89a684334ab5331079557c5e492</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parseConstantIdentifierExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>ace90cb5c77dfaa3729d77af542581ab2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parseVariableIdentifierExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a31ed870754a5a98e528a3b8f47c70b46</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parseUnaryMinusExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a0fc6ffa906a5a927bfd7094407cd43e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parsePrimary</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>acfeadc0303e5421b505667466956b279</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parseBinOpRHS</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a8fecdda1a6584a6a1718d4976625357a</anchor>
      <arglist>(int exprPrecedence, ExprAST&lt; T &gt; *LHS)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST&lt; T &gt; *</type>
      <name>parseExpression</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>aea6dcea2460b3e5e307a853113ef764c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; Variable &gt;</type>
      <name>variables</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a831317b4837fc70fa42b4f74601b4056</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::string</type>
      <name>strToken</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>ab32c4b5ec54b7fac480a0315ac9b4d53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>numToken</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a171a2572bcb46cdaa86e6ce6681bc4bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>currentToken</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a258e5715b3a6565155f5db4a890df150</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::string</type>
      <name>formula</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a09fe490dde71024f7ce63ef9c597714f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::string</type>
      <name>parseBuffer</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a023c94771b1ad468354d5195d5a233ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const char *</type>
      <name>tokenStrings</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>ab9c5d3bb266367641afe7a94dcf9ac74</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const int</type>
      <name>NUM_FUNCTIONS</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a2f45b07dc3fadf6a1664da9770259773</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const Function</type>
      <name>functions</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>adf71d3768a4e80050ee88e6f13099813</anchor>
      <arglist>[NUM_FUNCTIONS]</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const char *</type>
      <name>constantNames</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a22bbc8c69ba64a230d6e2bcea4efc4cf</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const int</type>
      <name>NUM_OPERATORS</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a134871fe9f75675c530422b55e88df4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const Operator</type>
      <name>operators</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>ac96962ae509c90e81a759eebc4d9ab4d</anchor>
      <arglist>[NUM_OPERATORS]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>AFormula::Private::Parser::Function</name>
    <filename>struct_a_formula_1_1_private_1_1_parser_1_1_function.html</filename>
    <member kind="variable">
      <type>const char *</type>
      <name>name</name>
      <anchorfile>struct_a_formula_1_1_private_1_1_parser_1_1_function.html</anchorfile>
      <anchor>a0c7b0d41aa7c11952fee4f95a5b56906</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>numArgs</name>
      <anchorfile>struct_a_formula_1_1_private_1_1_parser_1_1_function.html</anchorfile>
      <anchor>a9ced86af842e48e12f32cbe2fbe4dec3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>AFormula::Private::Parser::Operator</name>
    <filename>struct_a_formula_1_1_private_1_1_parser_1_1_operator.html</filename>
    <member kind="variable">
      <type>const char *</type>
      <name>name</name>
      <anchorfile>struct_a_formula_1_1_private_1_1_parser_1_1_operator.html</anchorfile>
      <anchor>a17a2812c7dffb888411685b329d6eadf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>precedence</name>
      <anchorfile>struct_a_formula_1_1_private_1_1_parser_1_1_operator.html</anchorfile>
      <anchor>ae5d848e35fa19e19608f8bac3e401645</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>AFormula::Private::Parser::Variable</name>
    <filename>struct_a_formula_1_1_private_1_1_parser_1_1_variable.html</filename>
    <member kind="variable">
      <type>std::string</type>
      <name>name</name>
      <anchorfile>struct_a_formula_1_1_private_1_1_parser_1_1_variable.html</anchorfile>
      <anchor>a0f394b13da1a5162e8852408c5d920b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double *</type>
      <name>pointer</name>
      <anchorfile>struct_a_formula_1_1_private_1_1_parser_1_1_variable.html</anchorfile>
      <anchor>a388c6f532334cdc18fec549e587e4ad1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::ExprAST</name>
    <filename>class_a_formula_1_1_private_1_1_expr_a_s_t.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ExprAST</name>
      <anchorfile>class_a_formula_1_1_private_1_1_expr_a_s_t.html</anchorfile>
      <anchor>ab6d33a252d3fc16a85f93ee4165d6d31</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void *</type>
      <name>generate</name>
      <anchorfile>class_a_formula_1_1_private_1_1_expr_a_s_t.html</anchorfile>
      <anchor>ad075e22328e4c06a4c309a175163917b</anchor>
      <arglist>(CodeGenerator *)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::NumberExprAST</name>
    <filename>class_a_formula_1_1_private_1_1_number_expr_a_s_t.html</filename>
    <base>AFormula::Private::ExprAST</base>
    <member kind="function">
      <type></type>
      <name>NumberExprAST</name>
      <anchorfile>class_a_formula_1_1_private_1_1_number_expr_a_s_t.html</anchorfile>
      <anchor>a868bcacf4221e4d3f158373c941faf39</anchor>
      <arglist>(double d)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>generate</name>
      <anchorfile>class_a_formula_1_1_private_1_1_number_expr_a_s_t.html</anchorfile>
      <anchor>a1c4c9990abbcdfc506e492a590ab8e51</anchor>
      <arglist>(CodeGenerator *gen)</arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>val</name>
      <anchorfile>class_a_formula_1_1_private_1_1_number_expr_a_s_t.html</anchorfile>
      <anchor>abb140344f702ae2ef9ccdfb150b2355a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::VariableExprAST</name>
    <filename>class_a_formula_1_1_private_1_1_variable_expr_a_s_t.html</filename>
    <base>AFormula::Private::ExprAST</base>
    <member kind="function">
      <type></type>
      <name>VariableExprAST</name>
      <anchorfile>class_a_formula_1_1_private_1_1_variable_expr_a_s_t.html</anchorfile>
      <anchor>af7558d8cc7363a6274c8ef6719b8f819</anchor>
      <arglist>(const std::string &amp;n, double *p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>generate</name>
      <anchorfile>class_a_formula_1_1_private_1_1_variable_expr_a_s_t.html</anchorfile>
      <anchor>ad3e07831e37499a98c5a5a1f80774075</anchor>
      <arglist>(CodeGenerator *gen)</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>name</name>
      <anchorfile>class_a_formula_1_1_private_1_1_variable_expr_a_s_t.html</anchorfile>
      <anchor>a25e9ca70b784a6cbd90772e339ba7c73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double *</type>
      <name>pointer</name>
      <anchorfile>class_a_formula_1_1_private_1_1_variable_expr_a_s_t.html</anchorfile>
      <anchor>a9ef85f40ca0d9a6847c33a025dd95673</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::UnaryMinusExprAST</name>
    <filename>class_a_formula_1_1_private_1_1_unary_minus_expr_a_s_t.html</filename>
    <base>AFormula::Private::ExprAST</base>
    <member kind="function">
      <type></type>
      <name>UnaryMinusExprAST</name>
      <anchorfile>class_a_formula_1_1_private_1_1_unary_minus_expr_a_s_t.html</anchorfile>
      <anchor>a1063836d8140dcacac624130e0be2a0d</anchor>
      <arglist>(ExprAST *c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~UnaryMinusExprAST</name>
      <anchorfile>class_a_formula_1_1_private_1_1_unary_minus_expr_a_s_t.html</anchorfile>
      <anchor>aa434550bff4e0f85dd66c70600c4df40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>generate</name>
      <anchorfile>class_a_formula_1_1_private_1_1_unary_minus_expr_a_s_t.html</anchorfile>
      <anchor>ad465d8d645321b61af15feedab97a3a5</anchor>
      <arglist>(CodeGenerator *gen)</arglist>
    </member>
    <member kind="variable">
      <type>ExprAST *</type>
      <name>child</name>
      <anchorfile>class_a_formula_1_1_private_1_1_unary_minus_expr_a_s_t.html</anchorfile>
      <anchor>adbdd5b74ac9a88f1f97d30037f5d4f4c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::BinaryExprAST</name>
    <filename>class_a_formula_1_1_private_1_1_binary_expr_a_s_t.html</filename>
    <base>AFormula::Private::ExprAST</base>
    <member kind="function">
      <type></type>
      <name>BinaryExprAST</name>
      <anchorfile>class_a_formula_1_1_private_1_1_binary_expr_a_s_t.html</anchorfile>
      <anchor>a5e780eeaa389ae8e4f211fb9aef39264</anchor>
      <arglist>(const std::string &amp;o, ExprAST *l, ExprAST *r)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BinaryExprAST</name>
      <anchorfile>class_a_formula_1_1_private_1_1_binary_expr_a_s_t.html</anchorfile>
      <anchor>a000b9a6a81624b2c9d0a54d8a41f1643</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>generate</name>
      <anchorfile>class_a_formula_1_1_private_1_1_binary_expr_a_s_t.html</anchorfile>
      <anchor>a84c8fa802b5538a944e44d9b3df30438</anchor>
      <arglist>(CodeGenerator *gen)</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>op</name>
      <anchorfile>class_a_formula_1_1_private_1_1_binary_expr_a_s_t.html</anchorfile>
      <anchor>af0e423862b6b5884d08304f4683f4416</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ExprAST *</type>
      <name>LHS</name>
      <anchorfile>class_a_formula_1_1_private_1_1_binary_expr_a_s_t.html</anchorfile>
      <anchor>a5e1f32b03ed3e364b0d78ac33f5077e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ExprAST *</type>
      <name>RHS</name>
      <anchorfile>class_a_formula_1_1_private_1_1_binary_expr_a_s_t.html</anchorfile>
      <anchor>a6486c908e52a4f41389ed3cc54fe4212</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::CallExprAST</name>
    <filename>class_a_formula_1_1_private_1_1_call_expr_a_s_t.html</filename>
    <base>AFormula::Private::ExprAST</base>
    <member kind="function">
      <type></type>
      <name>CallExprAST</name>
      <anchorfile>class_a_formula_1_1_private_1_1_call_expr_a_s_t.html</anchorfile>
      <anchor>a150d1fcc1142b46e0405c1d1b63232ae</anchor>
      <arglist>(const std::string &amp;fun, const std::vector&lt; ExprAST * &gt; &amp;a)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CallExprAST</name>
      <anchorfile>class_a_formula_1_1_private_1_1_call_expr_a_s_t.html</anchorfile>
      <anchor>adcd80f4d6ae269c8e21aeab5feeff861</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual T</type>
      <name>generate</name>
      <anchorfile>class_a_formula_1_1_private_1_1_call_expr_a_s_t.html</anchorfile>
      <anchor>a036c08e0a9928120125e8574b86d7472</anchor>
      <arglist>(CodeGenerator *gen)</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>function</name>
      <anchorfile>class_a_formula_1_1_private_1_1_call_expr_a_s_t.html</anchorfile>
      <anchor>aa05092f750c479a2b4dcead9b41e2bbf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; ExprAST * &gt;</type>
      <name>args</name>
      <anchorfile>class_a_formula_1_1_private_1_1_call_expr_a_s_t.html</anchorfile>
      <anchor>aac9c6f61d8256643e348877424c4871a</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
