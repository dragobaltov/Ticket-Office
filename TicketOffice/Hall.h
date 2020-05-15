#pragma once

const size_t HALLS_COUNT = 10;

class Hall
{
	Hall();
	Hall(size_t, size_t, size_t);

	void set_num(size_t);

	size_t get_num() const;
	size_t get_rows() const;
	size_t get_seats() const;
private:
	size_t m_num{ 0 };
	size_t m_rows{ 0 };
	size_t m_seats{ 0 };
};