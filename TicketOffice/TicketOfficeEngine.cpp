#include "TicketOfficeEngine.h"
#include <iostream>
#include <regex>

const std::regex DATE_FORMAT("^20[0-9]{2}-((0?[1-9])|(1[0-2]))-(([12][0-9])|(3[01])|(0?[1-9])|)$");
const std::regex CODE_FORMAT("^[A-Z][1-9][0-9]*[A-Z][1-9][0-9]*[A-Z][1-9][0-9]*[A-Z]$");

TicketOfficeEngine::TicketOfficeEngine() = default;

void TicketOfficeEngine::load(std::istream & in)
{
	in >> m_office;
}

void TicketOfficeEngine::unload()
{
	m_office.unload();
}

void TicketOfficeEngine::save_data(std::ostream & out) const
{
	out << m_office;
}

void TicketOfficeEngine::execute_command(const std::string & command, const std::string & additional)
{
	if (command == "open")
	{
		open(additional);
	}
	else if (command == "help")
	{
		help();
	}
	else if (command == "exit")
	{
		exit();
	}
	else
	{
		if (m_status != Status::open)
		{
			std::cout << INVALID_ACTION_MSG;
			return;
		}

		if (command == "save")
		{
			save_as(m_current_file);
		}
		else if (command == "saveas")
		{
			save_as(additional);
		}
		else if (command == "close")
		{
			close();
		}
		else if (command == "addevent")
		{
			add_event(additional);
		}
		else if (command == "book" || command == "unbook" || command == "buy")
		{
			std::vector<std::string> tokens{};
			split(additional, tokens, ' ');

			if (tokens.size() < 4)
			{
				std::cout << WRONG_INPUT_MSG;
			}
			else
			{
				size_t row = num_parse(tokens[0]);
				size_t seat = num_parse(tokens[1]);

				if (!std::regex_match(tokens[2], DATE_FORMAT))
				{
					std::cout << "Invalid date!";
					return;
				}

				Date date = { tokens[2] };
				std::string name = get_name(tokens, 3);

				if (command == "book")
				{
					book(row, seat, date, name);
				}
				else if (command == "unbook")
				{
					unbook(row, seat, date, name);
				}
				else
				{
					buy(row, seat, date, name);
				}
			}
		}
		else if (command == "freeseats")
		{
			print_freeseats(additional);
		}
		else if (command == "bookings")
		{
			print_bookings(additional);
		}
		else if (command == "check")
		{
			check_code(additional);
		}
		else if (command == "report")
		{
			report(additional);
		}
		else if (command == "best")
		{
			print_best();
		}
	}
}

bool TicketOfficeEngine::is_valid_command(const std::string & command) const
{
	for (size_t i = 0; i < COUNT_COMMANDS; ++i)
	{
		if (command == VALID_COMMANDS[i])
		{
			return true;
		}
	}

	return false;
}

void TicketOfficeEngine::help() const
{
	Engine::help();

	std::cout << "addevent <date> <hall> <name> - Adds new event. Gives an error if the event already exists.\n"
		<< "freeseats <date> <name> - Prints all free seats for the event.\n"
		<< "book <row> <seat> <date> <name> - Books the ticket if it's not already taken.\n"
		<< "unbook <row> <seat> <date> <name> - Unbooks the ticket if it's not already sold.\n"
		<< "buy <row> <seat> <date> <name> - Buys the ticket if it's not already sold.\n"
		<< "bookings [<date>] [<name>] - Prints all booked tickets for the event <name> on <date>.\n"
		<< "check <code> - Checks if there is a ticket with code <code>.\n"
		<< "report <from> <to> [<hall>] - Prints report for the period <from> - <to> for hall #<hall>.\n"
		<< "best - Prints 5 most watched events.\n"
		<< "worst <from> <to> - 1. Prints all events under 10% attendance for the period <from> - <to>\n"
		<< "                    2. Gives a choice wheater or not to remove those events.\n";
}

void TicketOfficeEngine::add_event(const std::string& input)
{
	std::vector<std::string> tokens{};
	split(input, tokens, ' ');

	if (tokens.size() < 3)
	{
		std::cout << WRONG_INPUT_MSG;
	}
	else
	{
		if (!std::regex_match(tokens[0], DATE_FORMAT))
		{
			std::cout << "Invalid date!\n";
			return;
		}

		Date date = { tokens[0] };
		size_t hall_num = num_parse(tokens[1]);

		if (hall_num < 1 || hall_num > HALLS_COUNT)
		{
			std::cout << "Invalid hall number!\n";
			return;
		}

		std::string name = get_name(tokens, 2);

		bool is_successful = m_office.add_event(date, name, hall_num);

		if (is_successful)
		{
			std::cout << "Successfully added event " << name << '\n';
		}
		else
		{
			std::cout << "The hall is taken or the event has already been scheduled for " << date << '\n';
		}
	}
}

void TicketOfficeEngine::book(size_t row, size_t seat, const Date& date, const std::string& event_name)
{
	std::string note = "";
	std::cout << "Note: ";
	std::getline(std::cin, note);

	bool is_successful = m_office.book_ticket(date, event_name, row, seat, note);

	if (is_successful)
	{
		std::cout << "Successfully booked ticket for " << event_name << "!\n";
	}
	else
	{
		std::cout << "Unsuccessful booking!\n";
	}
}

void TicketOfficeEngine::unbook(size_t row, size_t seat, const Date & date, const std::string & event_name)
{
	bool is_successful = m_office.unbook_ticket(date, event_name, row, seat);

	if (is_successful)
	{
		std::cout << "Successfully unbooked the ticket!\n";
	}
	else
	{
		std::cout << "Unsuccessful unbooking!\n";
	}
}

void TicketOfficeEngine::buy(size_t row, size_t seat, const Date & date, const std::string & event_name)
{
	bool is_successful = m_office.buy_ticket(date, event_name, row, seat);

	if (is_successful)
	{
		std::cout << "Successfully bought ticket for " << event_name << "!\n";
	}
	else
	{
		std::cout << "Unsuccessful purchase!\n";
	}
}

void TicketOfficeEngine::print_freeseats(const std::string& input) const
{
	std::vector<std::string> tokens{};
	split(input, tokens, ' ');

	if (tokens.size() < 2)
	{
		std::cout << WRONG_INPUT_MSG;
	}
	else
	{
		if (!std::regex_match(tokens[0], DATE_FORMAT))
		{
			std::cout << "Invalid date!\n";
			return;
		}

		Date date = { tokens[0] };
		std::string name = get_name(tokens, 1);

		m_office.print_free_seats(date, name);
	}
}

void TicketOfficeEngine::print_bookings(const std::string& input) const
{
	if (input == "")
	{
		m_office.print_bookings();
	}
	else
	{
		std::vector<std::string> tokens{};
		split(input, tokens, ' ');
		
		Date date{};
		std::string name = "";

		if (std::regex_match(tokens[0], DATE_FORMAT))
		{
			date = { tokens[0] };

			if (tokens.size() > 1)
			{
				name = get_name(tokens, 1);
			}
		}
		else
		{
			name = get_name(tokens, 0);
		}

		m_office.print_bookings(date, name);
	}
}

void TicketOfficeEngine::check_code(const std::string& code_str) const
{
	if (!std::regex_match(code_str, CODE_FORMAT))
	{
		std::cout << "Invalid code!\n";
		return;
	}

	Code code = { code_str };

	bool is_valid = m_office.check_code(code);

	if (!is_valid)
	{
		std::cout << "There is no ticket with code " << code_str << "!\n";
	}
	else
	{
		code.print_place();
	}
}

void TicketOfficeEngine::report(const std::string& input) const
{
	std::vector<std::string> tokens{};
	split(input, tokens, ' ');

	if (tokens.size() < 2 || tokens.size() > 3)
	{
		std::cout << WRONG_INPUT_MSG;
	}
	else
	{
		if (!std::regex_match(tokens[0], DATE_FORMAT) || !std::regex_match(tokens[1], DATE_FORMAT))
		{
			std::cout << "Invalid date!\n";
			return;
		}

		Date from = { tokens[0] };
		Date to = { tokens[1] };
		size_t hall_num = 0;

		if (tokens.size() == 3)
		{
			hall_num = num_parse(tokens[2]);
		}

		m_office.report(from, to, hall_num);
	}
}

void TicketOfficeEngine::print_best()
{
	m_office.print_most_watched_events();
}

std::string get_name(const std::vector<std::string> & tokens, size_t start)
{
	std::string name = "";
	size_t size = tokens.size();

	for (size_t i = start; i < size - 1; ++i)
	{
		name += tokens[i] + ' ';
	}
	name += tokens[size - 1];

	return name;
}
