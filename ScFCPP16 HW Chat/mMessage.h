#pragma once

#include <string>

namespace chat {
    class mMessage final {
        const std::string content_;
        const std::string sender_;
        const std::string receiver_;

    public:
        mMessage(const std::string& content, const std::string& sender, const std::string& receiver)
            : content_(content)
            , sender_(sender)
            , receiver_(receiver)
        {
        }
        // getters
        const std::string& getSender() const noexcept;
        const std::string& getContent() const noexcept;
        const std::string& getReceiver() const noexcept;
    };

} // namespace chat
