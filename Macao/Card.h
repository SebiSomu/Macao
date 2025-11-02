#pragma once
#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>

class Card
{
public:
    Card();
    Card(const std::string& m_cardstring);
    bool isJoker() const;
    const std::string& getValue() const;
    char getSuit() const;
    void setSuit(char s);
    bool isValidCard(const Card& lastCard, int m_cardsToDraw) const;
    bool operator==(const Card& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Card& c);
    friend std::istream& operator>>(std::istream& in, Card& c);

private:
    std::string m_value;
    char m_suit;
    bool m_joker;
    void parseCardstring(const std::string& s);
};