#include "Code.h"
#include <iostream>

Code::Code() = default;

Code::Code(const std::string& str_code)
{
	decypher_code(str_code);
}

Code::Code(const Code& other) : m_hall_num{ other.m_hall_num }, m_row{ other.m_row }, m_seat{other.m_seat},
m_first{ other.m_first }, m_second{ other.m_second }, m_third{ other.m_third }, m_forth{ other.m_forth } {}

Code::~Code() = default;

Code& Code::operator=(const Code& other)
{
	if (this != &other)
	{
		m_hall_num = other.m_hall_num;
		m_row = other.m_row;
		m_seat = other.m_seat;
		m_first = other.m_first;
		m_second = other.m_second;
		m_third = other.m_third;
		m_forth = other.m_forth;
	}

	return *this;
}

void Code::print_place() const
{
	std::cout << "Hall: " << m_hall_num << ", Row: " << m_row << ", Seat: " << m_seat << '\n';
}

bool Code::operator==(const Code& other) const
{
	return m_hall_num == other.m_hall_num && m_row == other.m_row && m_seat == other.m_seat &&
		m_first == other.m_first && m_second == other.m_second && m_third == other.m_third && m_forth == other.m_forth;
}

size_t Code::get_hall_num() const
{
	return m_hall_num;
}

size_t Code::get_row() const
{
	return m_row;
}

size_t Code::get_seat() const
{
	return m_seat;
}

void Code::decypher_code(const std::string& str_code)
{
	m_first = str_code[0];

	size_t i = 1;

	m_hall_num = get_num(str_code, i);
	m_second = str_code[i];
	++i;

	m_row = get_num(str_code, i);
	m_third = str_code[i];
	++i;

	m_seat = get_num(str_code, i);
	m_forth = str_code[i];
}

size_t Code::get_num(const std::string& text, size_t& start) const
{
	std::string str_num = "";

	while (text[start] >= '0' && text[start] <= '9')
	{
		str_num += text[start];
		++start;
	}

	return to_int(str_num);
}

size_t to_int(const std::string& str_num)
{
	size_t num = 0;

	for (size_t i = 0; i < str_num.length(); ++i)
	{
		num = num * 10 + (str_num[i] - '0');
	}

	return num;
}

std::ostream& operator<<(std::ostream& out, const Code& code)
{
	out << code.m_first << code.m_hall_num << code.m_second 
		<< code.m_row << code.m_third << code.m_seat << code.m_forth;
	return out;
}