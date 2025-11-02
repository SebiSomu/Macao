#pragma once
#include "Card.h"
#include <vector>
#include <cstdint>

class Player
{
private:
    std::vector<Card> m_hand;
    std::uint8_t m_id;
    std::string m_name;

public:
    Player(int playerid, const std::string& playerm_name);
    void addCard(const Card& card);
    bool removeCard(const Card& card);
    Card* findCard(const Card& card);
    std::uint8_t getId() const;
    std::string getName() const;
    const std::vector<Card>& getHand() const;
    std::vector<Card>& getHandRef();
    std::uint8_t getHandSize() const;
    bool hasWon() const;
    void displayHand() const;
    bool hasCardWithValue(const std::string& m_value) const;
    std::vector<int> getIndicesOfValue(const std::string& m_value) const;
};

