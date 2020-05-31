#pragma once
#include <string>
#include "Date.h"
#include "Code.h"

const std::string ROW_PREFIX = "Row: ";
const std::string SEAT_PREFIX = "Seat: ";
const std::string NOTE_PREFIX = "Note: ";
const std::string CODE_PREFIX = "Code: ";

/*! \brief An enum class that keeps the current status of the ticket.
 * Possible statuses: free, booked, sold
*/
enum class TicketStatus
{
	free,
	booked,
	sold
};

/*! The class keeps number of row, number of seat in the hall. 
 * It has a status that indicates wheter the ticket is free, booked or sold. Innitially, the status if free.
 * The class also keeps a string, which represents a note in case the ticket was booked.
 * It contains a code that is innitially empty and fills only when the ticket is sold.
*/
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