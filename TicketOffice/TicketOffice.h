#pragma once
#include "Event.h"
#include "Hall.h"
#include <vector>
#include <memory>
#include <utility>
#include "CodeGenerator.h"
#include <string>

const std::string LAST_CODE_PREFIX = "Last code: ";

class TicketOffice
{
	friend std::ostream& operator<<(std::ostream&, const TicketOffice&);
	friend std::istream& operator>>(std::istream&, TicketOffice&);
public:
	TicketOffice();
	TicketOffice(const TicketOffice&);
	~TicketOffice();
	TicketOffice& operator=(const TicketOffice&);

	void set_generator(const Code&);

	bool add_event(const Date&, const std::string&, size_t);
	void print_free_seats(const Date&, const std::string&) const;
	bool book_ticket(const Date&, const std::string&, size_t, size_t, const std::string&);
	bool unbook_ticket(const Date&, const std::string&, size_t, size_t);
	bool buy_ticket(const Date&, const std::string&, size_t, size_t);
	void print_bookings(const Date & = {}, const std::string & = "") const;
	bool check_code(const Code&) const;
	void report(const Date&, const Date&, size_t = 0) const;
	void print_most_watched_events();
	void unload();
private:
	std::vector<Event> m_events{};
	std::vector<std::pair<size_t, size_t>> m_halls_sizes{};
	CodeGenerator m_gen{};
};