#include <iostream>
#include <thread> // for std::this_thread::sleep_for()

#include "chatroom.h"
#include "exceptions.h"

namespace chat {

	namespace {
		static const std::string BLACK = "\u001B[30m";
		static const std::string GREEN = "\u001B[32m";
		static const std::string YELLOW = "\u001B[33m";
		static const std::string BLUE = "\u001B[34m";
		static const std::string CYAN = "\u001B[36m";
		static const std::string WHITE = "\u001B[37m";
		static const std::string GREEN_BG = "\u001B[42m";
		static const std::string BLUE_BG = "\u001B[44m";
		static const std::string CYAN_BG = "\u001B[46m";
		static const std::string WHITE_BG = "\u001B[47m";
		static const std::string RESET = "\u001B[0m";
	}

	enum ActionsMenu {
		Logout,
		DisplayMsgAll,
		SendMessage,
		ViewAccount
	};

	void menuPrompt(const std::string& name, const std::vector<std::string>& actions, const std::string& color, const std::string& background)
	{
		int i = 0;
		std::cout << std::endl
			<< color << background << " " << name << " " << RESET << "    ";
		for (const auto& a : actions) {
			std::cout << color << background << " " << i++ << " " << RESET << a << "  ";
		}
		std::cout << "\nChoose the action: ";
	}

	void printMessage(const std::string& from, const std::string& to, const std::string& text)
	{
		std::string color = CYAN;
		std::cout << "from: " << color << from << RESET
			<< " to: " << color << to << RESET << std::endl
			<< "     " << color << text << RESET << std::endl;
	}

	int getInt()
	{
		int input = 0;
		while (true) {
			std::cin >> input;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
				std::cerr << YELLOW << "Wrong input. Try again \n"
					<< RESET;
			}
			else {
				std::cin.ignore();
				return input;
			}
		}
	}

	void ChatRoom::showMenu()
	{
		showAuthMenu();
		std::vector<std::string> actions = {
			"log out",
			"display all messages",
			"send a message",
			"view profile"
		};
		// int action = -1;
		int action = 0;
		while (true) {
			menuPrompt("User's menu", actions, WHITE, CYAN_BG);
			action = getInt();
			selectAction(action);
		}
	}

	void ChatRoom::showAuthMenu()
	{
		int action = 0;
		std::vector<std::string> actions = {
			"exit",
			"sign in",
			"sign up",
		};
		while (!isAuthorized_) {
			menuPrompt("Main menu", actions, WHITE, GREEN_BG);
			action = getInt();
			try {
				switch (action) {
				case 0:
					exit(0);
				case 1:
					signIn();
					break;
				case 2:
					signUp();
					break;
				case 290664:
					std::cout << "Secret item in the menu" << std::endl;
					break;
				default:
					std::cout << YELLOW << "There is no such item in the menu" << RESET << std::endl;
				}
			}
			catch (std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}

	void ChatRoom::selectAction(unsigned int action)
		try {
		switch (action) {
		case Logout:
			isAuthorized_ = false;
			showAuthMenu();
			break;
		case DisplayMsgAll:
			displayAllMessages("currentUser");
			break;
		case SendMessage:
			sendMessage();
			break;
		case ViewAccount:
			viewAccount();
			break;
		case 999:
			std::cout << "Secret item in the menu" << std::endl;
			displayAllMessages();
			break;
		default:
			std::cout << YELLOW << "There is no such item in the menu" << RESET << std::endl;
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	// really all messages or only messages of the current user
	void ChatRoom::displayAllMessages(const std::string& whoseMessages) const
	{
		if (msgs_.empty()) {
			std::cerr << "  there are no messages yet.\n\n";
			return;
		}
		int count = 0;
		std::cout << "messages =>" << std::endl;
		for (const auto& m : msgs_) {
			// if (((ChatRoom::current_user_->getUsername() == m.getSender() || ChatRoom::current_user_->getUsername() == m.getReceiver()) && whoseMessages == "currentUser")
			//     || whoseMessages == "allUsers") {
			//     printMessage(m.getSender(), m.getReceiver(), m.getContent());
			//     ++count;
			// }
			if (((ChatRoom::current_user_->getUsername() == m.getSender() || ChatRoom::current_user_->getUsername() == m.getReceiver())
				|| (whoseMessages == "currentUser" && m.getReceiver() == "all"))
				|| whoseMessages == "allUsers") {
				printMessage(m.getSender(), m.getReceiver(), m.getContent());
				++count;
			}
		}
		if (count == 0)
			std::cerr << YELLOW << "  there are no messages for or from this user.\n\n"
			<< RESET;
		std::cout << std::endl;
	}

	void ChatRoom::sendMessage()
	{
		// don't show in the final release
#ifdef NDEBUG
		if (msgs_.empty()) {
			msgs_.emplace_back(Message("text1", "u1", "r1"));
			msgs_.emplace_back(Message("text2", "r1", "t1"));
			msgs_.emplace_back(Message("text3", "t1", "u1"));
			msgs_.emplace_back(Message("text4", "u1", "all"));
		}
#endif

		std::string receiver, text;
		std::cout << "use \"all\" to send a message to all users" << std::endl;
		std::cout << "who will be the receiver: ";
		std::cin >> receiver;
		if (!isUserExisted(receiver) && receiver != "all") {
			std::cerr << YELLOW << "There is no such receiver\n\n"
				<< RESET;
			return;
		}
		if (receiver == chat::ChatRoom::current_user_->getUsername()) {
			std::cout << YELLOW << "You can't send a message to yourself\n\n"
				<< RESET;
			return;
		}
		std::cin.ignore();
		std::cout << "enter text: ";
		std::getline(std::cin, text);
		Message m(text, ChatRoom::current_user_->getUsername(), receiver);
		msgs_.emplace_back(m);
		if (receiver.compare("all") == 0) {
			for (const auto& r : users_) {
				// don't send to yourself
				if (m.getSender().compare(r.getUsername()) == 0)
					continue;
				printMessage(m.getSender(), r.getUsername(), text);
			}
		}
		else {
			printMessage(m.getSender(), m.getReceiver(), text);
		}
	}

	void ChatRoom::signUp()
	{
#ifdef NDEBUG
		if (users_.empty()) {
			users_.emplace_back(User("u1", "u", "u"));
			users_.emplace_back(User("r1", "r", "r"));
			users_.emplace_back(User("t1", "t", "t"));
			users_.emplace_back(User("w1", "w", "w"));
		}
#endif
		std::string name, username, password;
		std::cout << "Enter the name: ";
		std::cin >> name;
		std::cout << "Enter the username: ";
		std::cin >> username;
		if (isUserExisted(username))
			throw busy_login_error();
		std::cout << "Enter the password: ";
		std::cin >> password;
		User client(username, password, name);
		users_.emplace_back(client);

		std::cout << GREEN << "Account was created" << RESET << std::endl;
	}

	void ChatRoom::signIn()
	{
		static int attempts_num;
		std::string username, password;
		std::cout << "Enter the username: ";
		std::cin >> username;
		if (!isUserExisted(username))
			throw user_not_existed_error();
		std::cout << "Enter the password: ";
		std::cin >> password;
		current_user_ = lookUpUserByUsername(username);
		if (!current_user_ || (password != current_user_->getPassword())) {
			current_user_ = nullptr;
			if (attempts_num == 3) {
				std::cerr << "Password was entered 3 times wrong. Wait 20 seconds" << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(20));
				attempts_num = 0;
			}
			++attempts_num;
			throw pass_or_login_not_correct_error();
		}
		isAuthorized_ = true;
		// tell the new user if there are any users in the chatroom
		std::cout << GREEN << "Hi, " << current_user_->getName() << ". ";
		if (users_.size() == 1)
			std::cout << "You are the only user in the chat";
		else if (users_.size() == 2) {
			std::cout << "In the chat there are you and ";
			for (auto& u : users_)
				if (current_user_->getUsername() != u.getUsername())
					std::cout << u.getUsername();
		}
		else {
			std::cout << "In the chat there are besides you: ";
			int count = 0;
			// appropriate placement "," , "and" and "."
			std::string delimiter;
			for (auto& u : users_)
				if (current_user_->getUsername() != u.getUsername()) {
					std::cout << u.getUsername();
					count++;
					switch (users_.size() - count) {
					case 1:
						delimiter = ".";
						break;
					case 2:
						delimiter = " and ";
						break;
					default:
						delimiter = ", ";
					}
					std::cout << delimiter;
				}
		}
		std::cout << RESET << std::endl;
	}

	void ChatRoom::viewAccount() const
	{
		std::string username;
		std::shared_ptr<User> profile;

		std::cout << "User 'my' to view your profile" << std::endl
			<< "Which profile do you want to view?" << std::endl;

		std::cin >> username;
		if (username == "my") {
			char answer;
			std::cout << "Your profile is " << current_user_->getUsername() << std::endl
				<< "Name: " << current_user_->getName() << std::endl
				<< "Description: " << (current_user_->getDescription().empty() ? "not set" : current_user_->getDescription()) << std::endl;

			std::cout << "Do you want to change your profile? y/N" << std::endl;
			std::cin >> answer;
			if (answer == 'y') {
				std::string new_value;
				std::vector<std::string> actions = {
					"cancel",
					"change name",
					"change description",
					"change password"
				};
				menuPrompt("profile editor", actions, WHITE, BLUE_BG);
				int action = getInt();
				if (action == 0)
					return;
				if (action >= actions.size() || action < 0) {
					std::cout << YELLOW << "No such item in the menu" << RESET << std::endl;
					return;
				}
				std::cout << "enter the new value: ";
				std::getline(std::cin, new_value);
				switch (action) {
				case 1:
					current_user_->setName(new_value);
					break;
				case 2:
					current_user_->setDescription(new_value);
					break;
				case 3:
					current_user_->setPassword(new_value);
					break;
				}
			}
			return;
		}
		profile = lookUpUserByUsername(username);
		if (!profile)
			throw user_not_existed_error();

		std::cout << "Info about: " << profile->getUsername() << std::endl
			<< "Name: " << profile->getName() << std::endl
			<< "Description: " << (profile->getDescription().empty() ? "not set" : profile->getDescription()) << std::endl;
	}

	bool ChatRoom::isUserExisted(const std::string& username) const
	{
		return lookUpUserByUsername(username) ? true : false;
	}

	std::shared_ptr<chat::User> ChatRoom::lookUpUserByUsername(const std::string& username) const
	{
		for (const auto& user : users_) {
			if (user.getUsername() == username) {
				return std::make_shared<User>(user);
			}
		}
		return nullptr;
	}

} // namespace chat
