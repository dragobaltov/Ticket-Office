#include "Event.h"
#include <cassert>
#include <iostream>

Event::Event() = default;

Event::Event(const std::string & name, const Date & date, const Hall & hall)
{
	set_name(name);
	m_date = date;
	m_hall = hall;
}

Event::Event(const Event & other) : m_name{ other.m_name }, m_date{ other.m_date }, m_hall{ other.m_hall }{}

Event::~Event() = default;

Event& Event::operator=(const Event & other)
{
	if (this != &other)
	{
		m_name = other.m_name;
		m_date = other.m_date;
		m_hall = other.m_hall;
	}

	return *this;
}

bool Event::book_ticket(size_t row, size_t seat, const std::string & note)
{
	return m_hall.book_ticket(row, seat, note);
}

bool Event::unbook_ticket(size_t row, size_t seat)
{
	return m_hall.unbook_ticket(row, seat);
}

bool Event::buy_ticket(size_t row, size_t seat, const Code& code)
{
	return m_hall.buy_ticket(row, seat, code);
}

bool Event::are_overlapping(const Date & date, size_t hall_num) const
{
	return m_date == date && get_hall_num() == hall_num;
}

bool Event::are_same(const std::string & name, const Date & date) const
{
	return m_name == name && m_date == date;
}

bool Event::operator==(const Event & other) const
{
	return m_name == other.m_name && m_date == other.m_date && get_hall_num() == other.get_hall_num();
}

void Event::print_tickets_with_status(TicketStatus status) const
{
	std::cout << "Event name: " << m_name << '\n' << "Date: " << m_date << '\n' << "Hall: " << get_hall_num() << '\n';

	if (!m_hall.print_tickets_with_status(status, std::cout))
	{
		std::cout << "There are no " << status << " tickets!\n";
	}
}

bool Event::check_code(const Code& code) const
{
	return m_hall.check_code(code);
}

void Event::set_name(const std::string & name)
{
	assert(name.length());
	m_name = name;
}

const std::string& Event::get_name() const
{
	return m_name;
}

const Date& Event::get_date() const
{
	return m_date;
}

size_t Event::get_hall_num() const
{
	return m_hall.get_num();
}

size_t Event::get_sold_tickets_count() const
{
	return m_hall.get_sold_places_count();
}

std::ostream& operator<<(std::ostream& out, const Event& event)
{
	out << NAME_PREFIX << event.m_name << '\n' << DATE_PREFIX << event.m_date << '\n' << event.m_hall;

	return out;
}

std::istream& operator>>(std::istream& in, Event& event)
{
	std::string line = "";

	std::getline(in, line);
	std::string name = line.substr(NAME_PREFIX.length());

	std::getline(in, line);
	Date date = { line.substr(DATE_PREFIX.length()) };

	Hall hall{};

	in >> hall;

	event = Event(name, date, hall);

	return in;
}

