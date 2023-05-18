#include "mUser.h"

// getters
const std::string& chat::mUser::getName() const noexcept
{
    return name_;
}

//const std::string& chat::User::getUsername() const noexcept
//{
//    return username_;
//}

//const std::string& chat::User::getPassword() const noexcept
//{
//    return password_;
//}

const std::size_t chat::mUser::getHashedPassword() const noexcept
{
    return hashedPassword_;
}

const std::string& chat::mUser::getDescription() const noexcept
{
    return description_;
}

// setters
void chat::mUser::setName(const std::string& name) noexcept
{
    name_ = name;
}

void chat::mUser::setPassword(const std::string& password) noexcept
{
    //password_ = password;
    hashedPassword_ = std::hash<std::string>{}(password);
}

void chat::mUser::setDescription(const std::string& description) noexcept
{
    description_ = description;
}
