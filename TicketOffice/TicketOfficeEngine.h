#pragma once
#include "Engine.h"
#include "TicketOffice.h"

const std::string WRONG_INPUT_MSG = "Invalid input!\n";
const size_t COUNT_COMMANDS = 16;
const std::string VALID_COMMANDS[COUNT_COMMANDS] = { "open", "save", "saveas", "close", "exit", "help", "addevent", 
"freeseats", "book", "unbook", "buy", "bookings", "check", "report", "best", "worst" };

std::string get_name(const std::vector<std::string>&, size_t);

/*! \brief The class deals with user input and generates data for TicketOffice methods.*/
class TicketOfficeEngine : public Engine
{
public:
	TicketOfficeEngine();
private:
	TicketOffice m_office{};

	void load(std::istream&) override;
	void unload() override;
	void save_data(std::ostream&) const override;
	void help() const override;
	void execute_command(const std::string&, const std::string&) override;
	bool is_valid_command(const std::string&) const override;

	void add_event(const std::string&);
	void print_freeseats(const std::string&) const;
	void book(size_t, size_t, const Date&, const std::string&);
	void unbook(size_t, size_t, const Date&, const std::string&);
	void buy(size_t, size_t, const Date&, const std::string&);
	void print_bookings(const std::string&) const;
	void check_code(const std::string&) const;
	void report(const std::string&) const;
	void print_best();
	void print_worst(const std::string&);
};
