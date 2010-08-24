<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>index</name>
    <title>AFormula</title>
    <filename>index</filename>
    <docanchor file="index">Requirements</docanchor>
    <docanchor file="index">Thanks</docanchor>
    <docanchor file="index">Interface</docanchor>
  </compound>
  <compound kind="namespace">
    <name>AFormula</name>
    <filename>namespace_a_formula.html</filename>
    <namespace>AFormula::Private</namespace>
    <class kind="class">AFormula::Formula</class>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>signal_handler</name>
      <anchorfile>namespace_a_formula.html</anchorfile>
      <anchor>a69045ecbbbad4f45421a6a31a6af5401</anchor>
      <arglist>(int signum)</arglist>
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
      <anchor>aec665ae41ef8a72dcb5ddec2bfa46335</anchor>
      <arglist>(bool setAsDefault=true, bool printTimings=false)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>Formula</name>
      <anchorfile>class_a_formula_1_1_formula.html</anchorfile>
      <anchor>a8e6d50fc848b5a6ff5070f18b4d5934d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>AFormula::Private</name>
    <filename>namespace_a_formula_1_1_private.html</filename>
    <class kind="class">AFormula::Private::CodeGenerator</class>
    <class kind="class">AFormula::Private::JITFormula</class>
    <class kind="class">AFormula::Private::LibJITFormula</class>
    <class kind="class">AFormula::Private::LLVMFormula</class>
    <class kind="class">AFormula::Private::MuParserFormula</class>
    <class kind="class">AFormula::Private::Parser</class>
    <class kind="class">AFormula::Private::ExprAST</class>
    <class kind="class">AFormula::Private::NumberExprAST</class>
    <class kind="class">AFormula::Private::VariableExprAST</class>
    <class kind="class">AFormula::Private::UnaryMinusExprAST</class>
    <class kind="class">AFormula::Private::BinaryExprAST</class>
    <class kind="class">AFormula::Private::CallExprAST</class>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>compiledCppBenchmark</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>aa73b6a7b06e3a6e8c5dcc5398053bc17</anchor>
      <arglist>(float x, float y)</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>timerFrequency</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>a91c5f14e2808cc7d2a497a737e7d2202</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>timerTime</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>a6d9ae09aee8886a3994bf565b21105a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>defaultBackend</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>a079a9cbe9433b8deb2498befbd3bcbe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>boost::thread_specific_ptr&lt; std::string &gt;</type>
      <name>errorMessage</name>
      <anchorfile>namespace_a_formula_1_1_private.html</anchorfile>
      <anchor>affd7c9333c4c9b4943f5640287ff88d8</anchor>
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
    <base>AFormula::Formula</base>
    <member kind="function">
      <type></type>
      <name>JITFormula</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a063c0acb77ec9c2a9ae5109885606cb4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~JITFormula</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a0cd558d354fd19d077ba5cd3167e6d29</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>setExpression</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a0f12b39760a1c1b3f6cd81f4446f146c</anchor>
      <arglist>(const std::string &amp;str)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>expression</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>ac1d196d30652798c19a5a2e29969d128</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>setVariable</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a555f26e3d4c7b9312a5aada5ff4d8adc</anchor>
      <arglist>(const std::string &amp;variable, double *pointer)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>evaluate</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>ab866da7b27d8baa4f1c87990db67bb7f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>double(*</type>
      <name>FunctionPointer</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>ae1f13bd7b7d202feca4b0720368ce7e6</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>buildFunction</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>aaff7d5d04e06b82c1824e83d768e9b7d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>FunctionPointer</type>
      <name>func</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>afb5e6cd855800c3a8eb6050c2f7d54f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>expr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a7b795456e3b59e179a02a893c7ff43f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Parser</type>
      <name>parser</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>ab277cbcbe433bedca24d673e6ce1d328</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ExprAST *</type>
      <name>parseTree</name>
      <anchorfile>class_a_formula_1_1_private_1_1_j_i_t_formula.html</anchorfile>
      <anchor>a2ef9682a054ecea451fe4d615bb7c962</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::LibJITFormula</name>
    <filename>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</filename>
    <base>AFormula::Private::JITFormula</base>
    <base>AFormula::Private::CodeGenerator</base>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>aad8dfcc35e634e44cfa4dd4f7746e9bf</anchor>
      <arglist>(NumberExprAST *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>a1770eacbdea19f31561a62a2cec0b3bb</anchor>
      <arglist>(VariableExprAST *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>a2c92745634f473b335c0821c0dc60d08</anchor>
      <arglist>(UnaryMinusExprAST *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>a0c98d3305a18ab65e8150069aa21120a</anchor>
      <arglist>(BinaryExprAST *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>a61b67fe0727ae23c6757db0145e91301</anchor>
      <arglist>(CallExprAST *)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>buildFunction</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>a693601ea399d8fb840b6a741d7bf7318</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>jit_function_t</type>
      <name>function</name>
      <anchorfile>class_a_formula_1_1_private_1_1_lib_j_i_t_formula.html</anchorfile>
      <anchor>a6e3c8892220a37da0d56644a1c4d7a3b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AFormula::Private::LLVMFormula</name>
    <filename>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</filename>
    <base>AFormula::Private::JITFormula</base>
    <base>AFormula::Private::CodeGenerator</base>
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
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a87d0a39ed6d3e757772640cb949a7601</anchor>
      <arglist>(NumberExprAST *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a06bea0659f8df8da6c4d69860844470f</anchor>
      <arglist>(VariableExprAST *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a5abe6d5bc957ff187541674840eff035</anchor>
      <arglist>(UnaryMinusExprAST *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a4c8d30c40c06363f17832d51d52538f9</anchor>
      <arglist>(BinaryExprAST *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void *</type>
      <name>emit</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a0221c0f34d97485ccc8ab66891ca567a</anchor>
      <arglist>(CallExprAST *)</arglist>
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
      <name>module</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>afe38538e9a086b617875aac19d43ec16</anchor>
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
      <type>llvm::IRBuilder *</type>
      <name>builder</name>
      <anchorfile>class_a_formula_1_1_private_1_1_l_l_v_m_formula.html</anchorfile>
      <anchor>a6263141d8b59b1d655f3a9894a667331</anchor>
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
    <class kind="struct">AFormula::Private::Parser::Constant</class>
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
      <type>ExprAST *</type>
      <name>parseString</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>aa7eb721fb01832a11f798c2b4a0e41fb</anchor>
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
      <type>ExprAST *</type>
      <name>parseNumberExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>ade79ac44b79a92c15f897f710166be75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST *</type>
      <name>parseOpenParenExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>ac5a6f2ea6ea62c8fd2ea13840414d732</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST *</type>
      <name>parseFunctionIdentifierExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a0a8005aa748fff7e4cf6d1bc9996e6e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST *</type>
      <name>parseConstantIdentifierExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a1f1fce560248993e274d4e078245101f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST *</type>
      <name>parseVariableIdentifierExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a6304b4e4cd703819a59819dd9f2a0daf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST *</type>
      <name>parseUnaryMinusExpr</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a7ace9cfa72dbb8f1875985f732d411db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST *</type>
      <name>parsePrimary</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>acb1666c91a10b817fb94819a0f856042</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST *</type>
      <name>parseBinOpRHS</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a729da38c31ffe513a35981bf005ea48e</anchor>
      <arglist>(int exprPrecedence, ExprAST *LHS)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ExprAST *</type>
      <name>parseExpression</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>ab74a5794a994f76cbbf6e6afed7aa006</anchor>
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
      <anchor>aae107b95a9b2899f049ef2bce8efb5ed</anchor>
      <arglist>[NUM_FUNCTIONS]</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const int</type>
      <name>NUM_CONSTANTS</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>a303d6b7b668d0ddcb420e6a70c214b2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const Constant</type>
      <name>constants</name>
      <anchorfile>class_a_formula_1_1_private_1_1_parser.html</anchorfile>
      <anchor>af6886358347c7d582228d85b2cda0feb</anchor>
      <arglist>[NUM_CONSTANTS]</arglist>
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
      <anchor>a42642a3527fc35248d0b8f2bc2bce995</anchor>
      <arglist>[NUM_OPERATORS]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>AFormula::Private::Parser::Constant</name>
    <filename>struct_a_formula_1_1_private_1_1_parser_1_1_constant.html</filename>
    <member kind="variable">
      <type>const char *</type>
      <name>name</name>
      <anchorfile>struct_a_formula_1_1_private_1_1_parser_1_1_constant.html</anchorfile>
      <anchor>aee70e79f2d7d88feb43706587b5a3226</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>val</name>
      <anchorfile>struct_a_formula_1_1_private_1_1_parser_1_1_constant.html</anchorfile>
      <anchor>aaebf77969081305cbc86ef498ed7c096</anchor>
      <arglist></arglist>
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
      <anchor>aa35ac8fb32acb6c6ebf33c634346dc60</anchor>
      <arglist>(CodeGenerator *gen)=0</arglist>
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
      <anchor>ae21aeb1fcdfabfd5696f490d75a1c4d6</anchor>
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
      <type>virtual void *</type>
      <name>generate</name>
      <anchorfile>class_a_formula_1_1_private_1_1_call_expr_a_s_t.html</anchorfile>
      <anchor>af97315aeb12d5ab238511c50ed8108db</anchor>
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
