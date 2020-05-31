#pragma once
#include "Code.h"

/*! \brief Generates codes for the sold tickets
 *
 * Keeps the last used code in the program as a field
*/
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


