#pragma once
#include <string>
#include <vector>
#include "Date.h"
#include "Ticket.h";

const size_t HALLS_COUNT = 10;

class Event
{
public:
	Event();
	Event(const std::string&, const Date&, size_t);
	Event(const Event&);
	~Event();
	Event& operator=(const Event&);

	void set_name(const std::string&);
	void set_date(const Date&);
	void set_hall_num(size_t);

	const std::string& get_name() const;
	const Date& get_date() const;
	size_t get_hall_num() const;

	void add_ticket(const Ticket&);
private:
	std::string m_name{""};
	Date m_date{};
	size_t m_hall_num{ 0 };
	std::vector<Ticket> m_tickets{};
};