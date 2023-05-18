//#include "mUser.h"
//
//// getters
//const std::string& chat::mUser::getName() const noexcept
//{
//    return name_;
//}
//
//const std::size_t chat::mUser::getHashedPassword() const noexcept
//{
//    return hashedPassword_;
//}
//
//const std::string& chat::mUser::getDescription() const noexcept
//{
//    return description_;
//}
//
//// setters
////void setName(std::string& name) noexcept {
////    name_ = name;
////}
//void mUser::setName(const std::string& name) noexcept {
//    name_ = name;
//}
////
////void chat::mUser::setName(std::string& name) noexcept
////{
////    name_ = name;
////}
////
//void chat::mUser::setPassword(const std::string& password) noexcept
//{
//    hashedPassword_ = std::hash<std::string>{}(password);
//}
//
//void chat::mUser::setDescription(const std::string& description) noexcept
//{
//    description_ = description;
//}


#include "mUser.h"

namespace chat {

    // getters
    const std::string& mUser::getName() const noexcept {
        return name_;
    }

    const std::size_t mUser::getHashedPassword() const noexcept {
        return hashedPassword_;
    }

    const std::string& mUser::getDescription() const noexcept {
        return description_;
    }

    // setters
    void mUser::setName(const std::string& name) noexcept {
        name_ = name;
    }

    void mUser::setPassword(const std::string& password) noexcept {
        hashedPassword_ = std::hash<std::string>{}(password);
    }

    void mUser::setDescription(const std::string& description) noexcept {
        description_ = description;
    }

} // namespace chat
