#pragma once
#include <string>

size_t to_int(const std::string&);

class Code
{
	friend std::ostream& operator<<(std::ostream&, const Code&);
	friend class CodeGenerator;
public:
	Code();
	Code(const std::string&);
	Code(const Code&);
	~Code();
	Code& operator=(const Code&);

	size_t get_hall_num() const;
	size_t get_row() const;
	size_t get_seat() const;

	void print_place() const;
	bool operator==(const Code&) const;
private:
	size_t m_hall_num{0};
	size_t m_row{0};
	size_t m_seat{0};
	char m_first{' '};
	char m_second{' '};
	char m_third{' '};
	char m_forth{' '};

	void decypher_code(const std::string&);
	size_t get_num(const std::string&, size_t&) const;
};