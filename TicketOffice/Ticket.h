#pragma once
#include <string>
#include "Date.h"
#include "Code.h"

const std::string ROW_PREFIX = "Row: ";
const std::string SEAT_PREFIX = "Seat: ";
const std::string NOTE_PREFIX = "Note: ";
const std::string CODE_PREFIX = "Code: ";

enum class TicketStatus
{
	free,
	booked,
	sold
};

class Ticket
{
	friend std::ostream& operator<<(std::ostream&, const Ticket&);
public:
	Ticket();
	Ticket(size_t, size_t);
	Ticket(const Ticket&);
	~Ticket();
	Ticket& operator=(const Ticket&);

	void set_code(const Code&);
	void set_note(const std::string&);
	void set_status(TicketStatus);

	size_t get_row() const;
	size_t get_seat() const;
	const std::string& get_note() const;
	const Code& get_code() const;
	TicketStatus get_status() const;

	bool operator==(const Ticket&) const;
private:
	size_t m_row{ 0 };
	size_t m_seat{ 0 };
	std::string m_note{ "" };
	Code m_code{};
	TicketStatus m_status{ TicketStatus::free };
};

std::ostream& operator<<(std::ostream&, TicketStatus);