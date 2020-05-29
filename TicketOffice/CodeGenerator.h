#pragma once
#include "Code.h"

class CodeGenerator
{
public:
	CodeGenerator();
	CodeGenerator(const Code&);
	CodeGenerator(const CodeGenerator&);
	~CodeGenerator();
	CodeGenerator& operator=(const CodeGenerator&);

	Code generate(size_t, size_t, size_t);
	const Code& get_last_code() const;
private:
	Code m_last_code{};
};


