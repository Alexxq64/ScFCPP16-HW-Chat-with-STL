#include "mMessage.h"

const std::string& chat::mMessage::getContent() const noexcept
{
    return content_;
}

const std::string& chat::mMessage::getSender() const noexcept
{
    return sender_;
}

const std::string& chat::mMessage::getReceiver() const noexcept
{
    return receiver_;
}

