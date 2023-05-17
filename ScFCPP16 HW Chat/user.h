#pragma once

#include <string>

namespace chat {
    class User final {
        const std::string username_;
        std::string password_;
        std::string name_;
        std::string description_;

    public:
        User(const std::string& username, const std::string& password, const std::string& name)
            : username_(username)
            , password_(password)
            , name_(name)
        {
        }
        // getters
        const std::string& getName() const noexcept;
        const std::string& getUsername() const noexcept;
        const std::string& getPassword() const noexcept;
        const std::string& getDescription() const noexcept;
        // setters
        void setName(const std::string& name) noexcept;
        void setPassword(const std::string& pass) noexcept;
        void setDescription(const std::string& description) noexcept;
    };
} // namespace chat
