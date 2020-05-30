#pragma once
#include <string>
#include <vector>
#include "Date.h"
#include "Ticket.h"
#include "Hall.h"
#include <memory>

const std::string NAME_PREFIX = "Name: ";
const std::string DATE_PREFIX = "Date: ";

class Event
{
	friend std::ostream& operator<<(std::ostream&, const Event&);
	friend std::istream& operator>>(std::istream&, Event&);
public:
	Event();
	Event(const std::string&, const Date&, const Hall&);
	Event(const Event&);
	~Event();
	Event& operator=(const Event&);

	void set_name(const std::string&);
	void set_date(const Date&);

	const std::string& get_name() const;
	const Date& get_date() const;
	size_t get_hall_num() const;
	size_t get_sold_tickets_count() const;
	double attendance_percentage() const;

	bool book_ticket(size_t, size_t, const std::string&);
	bool unbook_ticket(size_t, size_t);
	bool buy_ticket(size_t, size_t, const Code&);
	bool are_overlapping(const Date&, size_t) const;
	bool are_same(const std::string&, const Date&) const;
	bool operator==(const Event&) const;
	void print_tickets_with_status(TicketStatus) const;
	bool check_code(const Code&) const;
private:
	std::string m_name{""};
	Date m_date{};
	Hall m_hall{};
};