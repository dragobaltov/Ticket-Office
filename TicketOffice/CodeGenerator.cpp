#include "CodeGenerator.h"

CodeGenerator::CodeGenerator() = default;

/*! @param code This is the last used code in the program.*/
CodeGenerator::CodeGenerator(const Code& code) : m_last_code{ code } {};

CodeGenerator::CodeGenerator(const CodeGenerator& other) : m_last_code{ other.m_last_code } {};

CodeGenerator::~CodeGenerator() = default;

CodeGenerator& CodeGenerator::operator=(const CodeGenerator& other)
{
	if (this != &other)
	{
		m_last_code = other.m_last_code;
	}

	return *this;
}

/*! Generates the next code.\n
 * Example: generate(5, 6, 1)\n
 *			Last code = A8B3C5B\n
 *			Next code = A5B6C1C\n
 * It increments the last letter. If it was Z, then it becomes A and the third letter increments.
 * If it was Z, then it becomes A and the second letter increments and so on.
 * Finnaly, sets the last code to the generated code.
*/
Code CodeGenerator::generate(size_t hall_num, size_t row, size_t seat)
{
	m_last_code.m_hall_num = hall_num;
	m_last_code.m_row = row;
	m_last_code.m_seat = seat;

	if (m_last_code.m_first == ' ')
	{
		m_last_code.m_first = 'A';
		m_last_code.m_second = 'A';
		m_last_code.m_third = 'A';
		m_last_code.m_forth = 'A';

		return m_last_code;
	}

	++m_last_code.m_forth;

	if (m_last_code.m_forth == 'Z' + 1)
	{
		m_last_code.m_forth = 'A';

		++m_last_code.m_third;

		if (m_last_code.m_third == 'Z' + 1)
		{
			m_last_code.m_third = 'A';

			++m_last_code.m_second;

			if (m_last_code.m_second == 'Z' + 1)
			{
				m_last_code.m_second = 'A';

				++m_last_code.m_first;

				if (m_last_code.m_first == 'Z' + 1)
				{
					m_last_code.m_first = 'A';
				}
			}
		}
	}

	return m_last_code;
}

const Code& CodeGenerator::get_last_code() const
{
	return m_last_code;
}