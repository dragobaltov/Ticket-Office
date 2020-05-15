#pragma once
#include <string>
#include "Date.h"

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
	Ticket(const std::string&, const Date&, size_t, size_t, const std::string& = "");
	Ticket(const Ticket&);
	~Ticket();
	Ticket& operator=(const Ticket&);

	void set_event_name(const std::string&);
	void set_date(const Date&);
	void set_row(size_t);
	void set_seat(size_t);
	void set_code(const std::string&);
	void set_note(const std::string&);
	void set_status(TicketStatus);

	const std::string& get_event_name() const;
	const Date& get_date() const;
	size_t get_row() const;
	size_t get_seat() const;
	const std::string& get_note() const;
	const std::string& get_code() const;
	TicketStatus get_status() const;
private:
	std::string m_event_name{ "" };
	Date m_date{};
	size_t m_row{ 0 };
	size_t m_seat{ 0 };
	std::string m_note{ "" };
	std::string m_code{ "" };
	TicketStatus m_status{ TicketStatus::free };
};

std::ostream& operator<<(std::ostream&, TicketStatus);