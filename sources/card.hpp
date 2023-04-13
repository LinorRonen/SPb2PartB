#ifndef CARD_HPP
#define CARD_HPP

#include <string>

namespace ariel
{
    // Define two enums for the rank and suit of a playing card.
    enum Rank
    {
        ACE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING
    };
    enum Suit
    {
        CLUBS,
        DIAMONDS,
        HEARTS,
        SPADES
    };

    const int NUM_RANKS = 13;
    const int NUM_SUITS = 4;

    class Card
    {
    public:
        Card(Rank rank = ACE, Suit suit = SPADES);
        Card(const Card &other);                // Copy constructor
        Card &operator=(const Card &other);     // Copy assignment operator
        Card(Card &&other) noexcept;            // Move constructor
        Card &operator=(Card &&other) noexcept; // Move assignment operator
        ~Card();                                // Destructor for the Card class
        Rank getRank() const;                   // getRank() method
        Suit getSuit() const;                   // getSuit() method
        void setSuit(Suit suit);                // setSuit(Suit suit) method
        std::string toString() const;           // toString() method
        int compare(const Card &other) const;   // compare(const Card &other) const method

    private:
        Rank rank; // the rank
        Suit suit; // the suit
    };
}

#endif
