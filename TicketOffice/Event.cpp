#include "Event.h"
#include <cassert>

Event::Event() = default;

Event::Event(const std::string& name, const Date& date, size_t hall_num)
{
	set_name(name);
	m_date = date;
	set_hall_num(hall_num);
}

Event::Event(const Event& other) : m_name{ other.m_name }, m_date{ other.m_date }, 
m_hall_num{ other.m_hall_num }, m_tickets{other.m_tickets} {}

Event::~Event() = default;

Event& Event::operator=(const Event& other)
{
	if (this != &other)
	{
		m_name = other.m_name;
		m_date = other.m_date;
		m_hall_num = other.m_hall_num;
		m_tickets = other.m_tickets;
	}

	return *this;
}

void Event::set_name(const std::string& name)
{
	assert(name.length());
	m_name = name;
}

void Event::set_hall_num(size_t hall_num)
{
	assert(hall_num >= 1 && hall_num <= HALLS_COUNT);
	m_hall_num = hall_num;
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
	return m_hall_num;
}

void Event::add_ticket(const Ticket& ticket)
{
	m_tickets.emplace_back(ticket);
}
