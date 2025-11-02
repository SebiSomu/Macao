#include "Player.h"

Player::Player(int playerid, const std::string& playerm_name)
    : m_id(playerid), m_name(playerm_name) {
}

void Player::addCard(const Card& card)
{
    m_hand.push_back(card);
}

bool Player::removeCard(const Card& card)
{
    for (auto it = m_hand.begin(); it != m_hand.end(); ++it)
    {
        if (*it == card)
        {
            m_hand.erase(it);
            return true;
        }
    }
    return false;
}

Card* Player::findCard(const Card& card)
{
    for (auto& c : m_hand)
        if (c == card)
            return &c;
    return nullptr;
}

std::uint8_t Player::getId() const
{
    return m_id;
}

std::string Player::getName() const
{
    return m_name;
}

const std::vector<Card>& Player::getHand() const
{
    return m_hand;
}

std::vector<Card>& Player::getHandRef()
{
    return m_hand;
}

std::uint8_t Player::getHandSize() const
{
    return m_hand.size();
}

bool Player::hasWon() const
{
    return m_hand.empty();
}

void Player::displayHand() const
{
    if (m_name == "You")
        std::cout << "Your cards:\n";
    else
        std::cout << m_name << "'s cards:\n";
    for (const auto& card : m_hand)
        std::cout << card;
    std::cout << "\n";
}

bool Player::hasCardWithValue(const std::string& m_value) const
{
    for (const auto& card : m_hand)
        if (card.getValue() == m_value)
            return true;
    return false;
}

std::vector<int> Player::getIndicesOfValue(const std::string& m_value) const
{
    std::vector<int> indices;
    for (int i = 0; i < m_hand.size(); i++)
        if (m_hand[i].getValue() == m_value)
            indices.push_back(i);
    return indices;
}
