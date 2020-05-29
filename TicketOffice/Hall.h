#pragma once
#include "Ticket.h"
#include <memory>
#include <string>

const size_t HALLS_COUNT = 10;
const size_t ROWS_COUNT = 10;
const size_t SEATS_IN_ROW = 10;
const std::string HALL_NUM_PREFIX = "Hall: ";

void parse_ticket_line(std::string&, size_t&, size_t&, std::string&);

class Hall
{
	friend std::ostream& operator<<(std::ostream&, const Hall&);
	friend std::istream& operator>>(std::istream&, Hall&);
public:
	Hall();
	Hall(size_t, size_t, size_t);
	Hall(const Hall&);
	~Hall();
	Hall& operator=(const Hall&);

	void set_num(size_t);

	size_t get_num() const;
	size_t get_rows() const;
	size_t get_seats() const;
	size_t get_sold_places_count() const;

	bool place_is_valid(size_t, size_t) const;
	void change_ticket_status(size_t, size_t, TicketStatus);
	bool print_tickets_with_status(TicketStatus, std::ostream&) const;
	Ticket& operator[](size_t);
	bool book_ticket(size_t, size_t, const std::string&);
	bool unbook_ticket(size_t, size_t);
	bool buy_ticket(size_t, size_t, const Code&);
	bool check_code(const Code&) const;
private:
	size_t m_num{ 0 };
	size_t m_rows{ 0 };
	size_t m_seats{ 0 };
	std::vector<Ticket> m_tickets{};

	size_t get_index(size_t, size_t) const;
};