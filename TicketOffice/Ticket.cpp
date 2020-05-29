#include "Ticket.h"
#include <cassert>
#include <iostream>

Ticket::Ticket() = default;

Ticket::Ticket(size_t row, size_t seat)
{
	m_row = row;
	m_seat = seat;
}

Ticket::Ticket(const Ticket & other) : m_row{ other.m_row }, m_seat{ other.m_seat }, m_note{ other.m_note },
m_code{ other.m_code }, m_status{ other.m_status } {}

Ticket::~Ticket() = default;

Ticket& Ticket::operator=(const Ticket & other)
{
	if (this != &other)
	{
		m_row = other.m_row;
		m_seat = other.m_seat;
		m_note = other.m_note;
		m_code = other.m_code;
		m_status = other.m_status;
	}

	return *this;
}

void Ticket::set_code(const Code & code)
{
	m_code = code;
}

void Ticket::set_note(const std::string & note)
{
	m_note = note;
}

void Ticket::set_status(TicketStatus status)
{
	m_status = status;
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

const Code& Ticket::get_code() const
{
	return m_code;
}

TicketStatus Ticket::get_status() const
{
	return m_status;
}

bool Ticket::operator==(const Ticket & other) const
{
	return m_row == other.m_row && m_seat == other.m_seat;
}

std::ostream& operator<<(std::ostream & out, const Ticket & ticket)
{
	out << ROW_PREFIX << ticket.m_row << ", " << SEAT_PREFIX << ticket.m_seat;

	if (ticket.m_status == TicketStatus::sold)
	{
		out << ", " << CODE_PREFIX << ticket.m_code;
	}
	else if (ticket.m_status == TicketStatus::booked)
	{
		out << ", " << NOTE_PREFIX << ticket.m_note;
	}

	out << '\n';
	return out;
}

std::ostream& operator<<(std::ostream & out, TicketStatus status)
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
