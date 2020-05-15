#include "Hall.h"
#include <cassert>

Hall::Hall() = default;

Hall::Hall(size_t num, size_t rows, size_t seats)
{
	set_num(num);
	m_rows = rows;
	m_seats = seats;
}

void Hall::set_num(size_t num)
{
	assert(num >= 1 && num << HALLS_COUNT);
	m_num = num;
}

size_t Hall::get_num() const
{
	return m_num;
}

size_t Hall::get_rows() const
{
	return m_rows;
}

size_t Hall::get_seats() const
{
	return m_seats;
}