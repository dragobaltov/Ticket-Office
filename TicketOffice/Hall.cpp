#include "Hall.h"
#include <cassert>
#include <iostream>

Hall::Hall() = default;

/*! Sets default values of (rows*seats) number of tickets.*/
Hall::Hall(size_t num, size_t rows, size_t seats)
{
	set_num(num);
	m_rows = rows;
	m_seats = seats;

	m_tickets.reserve(rows * seats);

	for (size_t i = 1; i <= rows; ++i)
	{
		for (size_t j = 1; j <= seats; ++j)
		{
			m_tickets.emplace_back(Ticket(i, j));
		}
	}
}

Hall::Hall(const Hall& other) : m_num{ other.m_num }, m_rows{ other.m_rows },
m_seats{ other.m_seats }, m_tickets{other.m_tickets} {}

Hall::~Hall() = default;

Hall& Hall::operator=(const Hall& other)
{
	if (this != &other)
	{
		m_num = other.m_num;
		m_rows = other.m_rows;
		m_seats = other.m_seats;
		m_tickets = other.m_tickets;
	}

	return *this;
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

/*! Gets the count of all sold tickets in the hall.*/
size_t Hall::get_sold_places_count() const
{
	size_t count = 0;

	for (const Ticket& t : m_tickets)
	{
		if (t.get_status() == TicketStatus::sold)
		{
			++count;
		}
	}

	return count;
}

/*! Checks whether row and seat are valid for this hall.*/
bool Hall::place_is_valid(size_t row, size_t seat) const
{
	return row >= 1 && row <= m_rows && seat >= 1 && seat <= m_seats;
}

/*! Changes the status of the ticket on the given row and seat.*/
void Hall::change_ticket_status(size_t row, size_t seat, TicketStatus status)
{
	m_tickets[(row - 1) * m_seats + seat - 1].set_status(status);
}

/*! Prints all tickets with the given status.*/
bool Hall::print_tickets_with_status(TicketStatus status, std::ostream& out) const
{
	bool has_sold_tickets = false;

	for (size_t i = 1; i <= m_rows; ++i)
	{
		for (size_t j = 1; j <= m_seats; ++j)
		{
			size_t index = get_index(i, j);

			if (m_tickets[index].get_status() == status)
			{
				out << m_tickets[index];
				has_sold_tickets = true;
			}
		}
	}

	return has_sold_tickets;
}

Ticket& Hall::operator[](size_t index)
{
	return m_tickets[index];
}

/* Set the ticket status to booked and adds the note if the given place is valid and if the ticket is not already booked or sold.*/
bool Hall::book_ticket(size_t row, size_t seat, const std::string& note)
{
	if (!place_is_valid(row, seat))
	{
		return false;
	}

	size_t index = get_index(row, seat);

	if (m_tickets[index].get_status() != TicketStatus::free)
	{
		return false;
	}

	m_tickets[index].set_status(TicketStatus::booked);
	m_tickets[index].set_note(note);

	return true;
}

/* Set the ticket status to free if the given place is valid and if the ticket is not already sold.*/
bool Hall::unbook_ticket(size_t row, size_t seat)
{
	if (!place_is_valid(row, seat))
	{
		return false;
	}

	size_t index = get_index(row, seat);

	if (m_tickets[index].get_status() != TicketStatus::booked)
	{
		return false;
	}

	m_tickets[index].set_status(TicketStatus::free);

	return true;
}

/* Set the ticket status to sold and gives it a code if the given place is valid and if the ticket is not already sold.*/
bool Hall::buy_ticket(size_t row, size_t seat, const Code& code)
{
	if (!place_is_valid(row, seat))
	{
		return false;
	}

	size_t index = get_index(row, seat);

	if (m_tickets[index].get_status() == TicketStatus::sold)
	{
		return false;
	}

	m_tickets[index].set_status(TicketStatus::sold);
	m_tickets[index].set_code(code);

	return true;
}

/*! Checks if there is a ticket with the same code in this hall.*/
bool Hall::check_code(const Code& code) const
{
	if (code.get_hall_num() != m_num)
	{
		return false;
	}

	size_t row = code.get_row();
	size_t seat = code.get_seat();

	if (!place_is_valid(row, seat))
	{
		return false;
	}

	size_t index = get_index(row, seat);

	return m_tickets[index].get_code() == code;
}

size_t Hall::get_index(size_t row, size_t seat) const
{
	return (row - 1) * m_rows + seat - 1;
}

std::ostream& operator<<(std::ostream& out, const Hall& hall)
{
	out << "Hall: " << hall.m_num << '\n';
	out << "Sold tickets:\n";
	hall.print_tickets_with_status(TicketStatus::sold, out);
	out << "Booked tickets:\n";
	hall.print_tickets_with_status(TicketStatus::booked, out);

	return out;
}

/*! First, prints the hall number. Then, all booked tickets and finnaly all sold ones.*/
std::istream& operator>>(std::istream& in, Hall& hall)
{
	std::string line = "";
	std::getline(in, line);

	size_t hall_num = to_int(line.substr(HALL_NUM_PREFIX.length()));
	hall = Hall(hall_num, ROWS_COUNT, SEATS_IN_ROW);

	std::getline(in, line);
	std::getline(in, line);
	size_t row = 0;
	size_t seat = 0;
	std::string additional = "";

	while (line != "Booked tickets:")
	{
		parse_ticket_line(line, row, seat, additional);
		hall.buy_ticket(row, seat, { additional });
		std::getline(in, line);
	}

	std::getline(in, line);

	while (!in.eof() && line != "")
	{
		parse_ticket_line(line, row, seat, additional);
		hall.book_ticket(row, seat, additional);
		std::getline(in, line);
	}

	return in;
}

void parse_ticket_line(std::string& line, size_t& row, size_t& seat, std::string& additional)
{
	// Row: 12, Seat: 101, Note: az sam note

	size_t delim_index = line.find(", ");
	row = to_int(line.substr(ROW_PREFIX.length(), delim_index - ROW_PREFIX.length()));

	line = line.substr(delim_index + 2);

	delim_index = line.find(", ");
	seat = to_int(line.substr(SEAT_PREFIX.length(), delim_index - SEAT_PREFIX.length()));

	line = line.substr(delim_index + 2);

	additional = line.substr(line.find(": ") + 2);
}