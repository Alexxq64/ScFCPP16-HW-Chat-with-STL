#pragma once

#include <string>

namespace chat {
    class mUser final {
    private:
        std::size_t hashedPassword_;
        std::string name_;
        std::string description_;

    public:
        mUser(const std::string& password, const std::string& name):
            name_(name)
        {
            hashedPassword_ = std::hash<std::string>{}(password);

        }
        // getters
        const std::string& getName() const noexcept;
        const std::size_t getHashedPassword() const noexcept;
        const std::string& getDescription() const noexcept;
        // setters
        void setName(const std::string& name) noexcept;
        //void setName(const std::string& name) const noexcept {
        //    name_ = name;
        //}
        //void setName(std::string& name) noexcept;
        void setPassword(const std::string& pass) noexcept;
        void setDescription(const std::string& description) noexcept;
    };
} // namespace chat
