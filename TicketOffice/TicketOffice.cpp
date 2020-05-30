#include <iostream>
#include <algorithm>
#include "TicketOffice.h"

TicketOffice::TicketOffice()
{
	for (size_t i = 1; i <= HALLS_COUNT; ++i)
	{
		m_halls_sizes.emplace_back(std::pair<size_t, size_t>(ROWS_COUNT, SEATS_IN_ROW));
	}
}

TicketOffice::TicketOffice(const TicketOffice& other) : m_events{ other.m_events }, m_halls_sizes{ other.m_halls_sizes } {}

TicketOffice::~TicketOffice() = default;

TicketOffice& TicketOffice::operator=(const TicketOffice & other)
{
	if (this != &other)
	{
		m_events = other.m_events;
		m_halls_sizes = other.m_halls_sizes;
	}

	return *this;
}

void TicketOffice::set_generator(const Code & last_code)
{
	m_gen = CodeGenerator(last_code);
}

void TicketOffice::unload()
{
	m_events.clear();
}

bool TicketOffice::add_event(const Date & date, const std::string & name, size_t hall_num)
{
	for (size_t i = 0; i < m_events.size(); ++i)
	{
		if (m_events[i].are_overlapping(date, hall_num) || m_events[i].are_same(name, date))
		{
			return false;
		}
	}

	Hall hall{ hall_num, m_halls_sizes[hall_num - 1].first, m_halls_sizes[hall_num - 1].second };
	Event event{ name, date, hall };
	m_events.emplace_back(event);

	return true;
}

void TicketOffice::print_free_seats(const Date & date, const std::string & name) const
{
	bool found = false;

	for (size_t i = 0; i < m_events.size() && !found; ++i)
	{
		if (m_events[i].get_name() == name && m_events[i].get_date() == date)
		{
			m_events[i].print_tickets_with_status(TicketStatus::free);
			found = true;
		}
	}

	if (!found)
	{
		std::cout << name << " won't be held on " << date << "!\n";
	}
}

bool TicketOffice::book_ticket(const Date & date, const std::string & name, size_t row, size_t seat, const std::string& note)
{
	for (size_t i = 0; i < m_events.size(); ++i)
	{
		if (m_events[i].are_same(name, date))
		{
			return m_events[i].book_ticket(row, seat, note);
		}
	}

	return false;
}

bool TicketOffice::unbook_ticket(const Date & date, const std::string & name, size_t row, size_t seat)
{
	for (size_t i = 0; i < m_events.size(); ++i)
	{
		if (m_events[i].are_same(name, date))
		{
			return m_events[i].unbook_ticket(row, seat);
		}
	}

	return false;
}

bool TicketOffice::buy_ticket(const Date & date, const std::string & name, size_t row, size_t seat)
{
	for (size_t i = 0; i < m_events.size(); ++i)
	{
		if (m_events[i].are_same(name, date))
		{
			Code code = m_gen.generate(m_events[i].get_hall_num(), row, seat);
			return m_events[i].buy_ticket(row, seat, code);
		}
	}

	return false;
}

void TicketOffice::print_bookings(const Date & date, const std::string & name) const
{
	if (name == "" && date == Date())
	{
		for (size_t i = 0; i < m_events.size(); ++i)
		{
			m_events[i].print_tickets_with_status(TicketStatus::booked);
		}
	}
	else if (name == "")
	{
		for (size_t i = 0; i < m_events.size(); ++i)
		{
			if (m_events[i].get_date() == date)
				m_events[i].print_tickets_with_status(TicketStatus::booked);
		}
	}
	else if (date == Date())
	{
		for (size_t i = 0; i < m_events.size(); ++i)
		{
			if (m_events[i].get_name() == name)
				m_events[i].print_tickets_with_status(TicketStatus::booked);
		}
	}
	else
	{
		for (size_t i = 0; i < m_events.size(); ++i)
		{
			if (m_events[i].are_same(name, date))
			{
				m_events[i].print_tickets_with_status(TicketStatus::booked);
				return;
			}
		}
	}
}

bool TicketOffice::check_code(const Code & code) const
{
	for (size_t i = 0; i < m_events.size(); ++i)
	{
		if (m_events[i].check_code(code))
		{
			return true;
		}
	}

	return false;
}

void TicketOffice::report(const Date & from, const Date & to, size_t hall_num) const
{
	for (size_t i = 0; i < m_events.size(); ++i)
	{
		Date event_date = m_events[i].get_date();

		if (event_date >= from && event_date <= to &&
			(!hall_num || m_events[i].get_hall_num() == hall_num))
		{
			m_events[i].print_tickets_with_status(TicketStatus::sold);
		}
	}
}

void TicketOffice::print_most_watched_events()
{
	std::sort(m_events.begin(), m_events.end(), [](const Event& e1, const Event& e2) -> bool
		{return e1.get_sold_tickets_count() < e2.get_sold_tickets_count(); });

	size_t count_to_print = fmin(m_events.size(), 5);

	std::cout << "Top " << count_to_print << " most watched events:\n";

	for (size_t i = 0; i < count_to_print; ++i)
	{
		std::cout << i + 1 << ". " << m_events[i];
	}
}

void TicketOffice::worst_events(const Date& from, const Date& to)
{
	std::vector<size_t> worst_events_indexes{};
	get_worst_events_indexes(worst_events_indexes, from, to);

	std::cout << "Events with under 10% of attendance:\n";

	for (size_t index : worst_events_indexes)
	{
		std::cout << m_events[index];
	}

	std::string question = "Would you like to remove these events?(Y/N) ";	
	char answer = get_answer(question);

	if (answer == 'Y' || answer == 'y')
	{
		size_t indent = 0;

		for (size_t index : worst_events_indexes)
		{
			m_events.erase(m_events.begin() + index - indent);
			++indent;
		}

		std::cout << "Successful removal!\n";
	}
}

char TicketOffice::get_answer(const std::string& question) const
{
	std::string answer = "";
	std::cout << question;
	std::getline(std::cin, answer);

	while (answer[0] != 'Y' && answer[0] != 'N' && answer[0] != 'y' && answer[0] != 'n')
	{
		std::cout << "Invalid answer! Please answer with Yes(Y) or No(N).\n";
		std::cout << question;
		std::getline(std::cin, answer);
	}

	return answer[0];
}

void TicketOffice::get_worst_events_indexes(std::vector<size_t>& indexes, const Date& from, const Date& to) const
{
	for (size_t i = 0; i < m_events.size(); ++i)
	{
		Date date = m_events[i].get_date();

		if (m_events[i].attendance_percentage() < 10 && date >= from && date <= to)
		{
			indexes.emplace_back(i);
		}
	}
}

std::ostream& operator<<(std::ostream & out, const TicketOffice & office)
{
	out << LAST_CODE_PREFIX << office.m_gen.get_last_code() << '\n';
	size_t size = office.m_events.size();

	for (size_t i = 0; i < size - 1; ++i)
	{
		out << office.m_events[i] << '\n';
	}
	out << office.m_events[size - 1];

	return out;
}

std::istream& operator>>(std::istream & in, TicketOffice & office)
{
	std::string line = "";
	std::getline(in, line);

	if (in.eof())
	{
		return in;
	}

	Code code{ line.substr(LAST_CODE_PREFIX.length()) };
	office.set_generator(code);

	Event event{};

	while (!in.eof())
	{
		in >> event;
		office.m_events.emplace_back(event);
	}

	return in;
}