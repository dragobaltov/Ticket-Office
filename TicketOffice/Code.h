#pragma once
#include <string>

size_t to_int(const std::string&);

/*! \brief The class represents the code, which a ticket recieves when it's sold.
 *
 * Code format: LHLRLSL\n
 *				L - uppercase latin letter\n
 *				H - hall number\n
 *				R - row\n
 *				S - seat
*/
class Code
{
	friend std::ostream& operator<<(std::ostream&, const Code&);
	friend class CodeGenerator;
public:
	Code();
	/*! The constructor enables direct parsing from string to Code.*/
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

	/*! Parses string to Code*/
	void decypher_code(const std::string&);
	size_t get_num(const std::string&, size_t&) const;
};