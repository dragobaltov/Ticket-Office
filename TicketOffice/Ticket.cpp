#include "Ticket.h"
#include <cassert>
#include <iostream>

Ticket::Ticket() = default;

Ticket::Ticket(const std::string& event_name, const Date& date, size_t row, size_t seat, const std::string& note)
{
	set_event_name(event_name);
	m_date = date;
	m_row = row;
	m_seat = seat;
	m_note = note;
}

Ticket::Ticket(const Ticket& other) : m_event_name{ other.m_event_name }, m_date{ other.m_date }, m_row{other.m_row},
m_seat{ other.m_seat }, m_note{ other.m_note }, m_code{ other.m_code }, m_status{other.m_status} {}

Ticket::~Ticket() = default;

Ticket& Ticket::operator=(const Ticket& other)
{
	if (this != &other)
	{
		m_event_name = other.m_event_name;
		m_date = other.m_date;
		m_row = other.m_row;
		m_seat = other.m_seat;
		m_note = other.m_note;
		m_code = other.m_code;
		m_status = other.m_status;
	}

	return *this;
}

void Ticket::set_event_name(const std::string& event_name)
{
	assert(event_name.length());
	m_event_name = event_name;
}

void Ticket::set_code(const std::string& code)
{
	m_code = code;
}

void Ticket::set_status(TicketStatus status)
{
	m_status = status;
}

const std::string& Ticket::get_event_name() const
{
	return m_event_name;
}

const Date& Ticket::get_date() const
{
	return m_date;
}

size_t Ticket::get_row() const
{
	return m_row;
}

size_t Ticket::get_seat() const
{
	return m_seat;
}

const std::string& Ticket::get_note() const
{
	return m_note;
}

const std::string& Ticket::get_code() const
{
	return m_code;
}

TicketStatus Ticket::get_status() const
{
	return m_status;
}

std::ostream& operator<<(std::ostream& out, const Ticket& ticket)
{
	out << "Event name: " << ticket.m_event_name << '\n' << "Date: " << ticket.m_date << '\n'
		<< "Row: " << ticket.m_row << '\n' << "Seat: " << ticket.m_seat << '\n'<< "Code: " << ticket.m_code 
		<< '\n' << "Status: " << ticket.m_status << '\n' << "Note: " << ticket.m_note << '\n';

	return out;
}

std::ostream& operator<<(std::ostream& out, TicketStatus status)
{
	switch (status)
	{
	case TicketStatus::free:
		out << "free";
		break;
	case TicketStatus::booked:
		out << "booked";
		break;
	case TicketStatus::sold:
		out << "sold";
		break;
	default:
		break;
	}

	return out;
}
