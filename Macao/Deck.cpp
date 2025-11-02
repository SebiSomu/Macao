#include "Deck.h"
#include <vector>

Deck::Deck()
{
    loadFromFile();
    shuffleArray();
    cut();

    for (const auto& card : m_cards)
        m_drawPile.push(card);
}

bool Deck::isEmpty() const
{
    return m_drawPile.empty();
}

void Deck::loadFromFile(const std::string& fileName)
{
    std::ifstream fin(fileName);
    std::string m_cardstring;
    int i = 0;

    while (fin >> m_cardstring && i < 54)
    {
        m_cards[i] = Card(m_cardstring);
        i++;
    }
}

void Deck::shuffleArray()
{
    for (int i = m_cards.size() - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::swap(m_cards[i], m_cards[j]); 
    }
}

void Deck::shuffle()
{
    std::vector<Card> temp;
    while (!m_drawPile.empty())
    {
        temp.push_back(m_drawPile.top());
        m_drawPile.pop();
    }
    
    for (int i = temp.size() - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::swap(temp[i], temp[j]);
    }
    
    for (const auto& card : temp)
        m_drawPile.push(card);
}

void Deck::cut()
{
    int cutPoint = rand() % m_cards.size();
    std::rotate(m_cards.begin(), m_cards.begin() + cutPoint, m_cards.end());
}

Card Deck::drawCard()
{
    if (m_drawPile.empty())
        throw std::runtime_error("Draw pile is empty!");

    Card drawn = m_drawPile.top();
    m_drawPile.pop();
    return drawn;
}

void Deck::addCard(const Card& card)
{
    m_drawPile.push(card);
}

std::uint8_t Deck::size() const
{
    return m_drawPile.size();
}