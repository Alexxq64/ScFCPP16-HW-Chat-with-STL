#pragma once
#define DEBUG


#include <memory>
#include <string>
#include <vector>
#include <deque>
#include <functional>

#include "mMessage.h"
#include "mUser.h"
#include <unordered_map>

namespace chat {

	class mChatRoom {
		std::string current_user_ID;
		bool isAuthorized_ = false;
		std::deque<mMessage> msgs_;
		std::unordered_map<std::string, mUser> mUsers_;

	public:
		void showMenu();

	private:
		void showAuthMenu();

		void displayAllMessages(const std::string& whoseMessages = "allUsers") const;
		void sendMessage();
		void selectAction(unsigned int action);
		// login in an account previously created by signUp()
		void signIn();
		// creating a new account in mUsers_
		void signUp();

		void viewAccount() const;
	};

}