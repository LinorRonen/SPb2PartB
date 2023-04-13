#include "card.hpp"

namespace ariel
{
  Card::Card(Rank rank, Suit suit) : rank(rank), suit(suit)
  {
    this->rank = rank;
    this->suit = suit;
  }

  // Copy Constructor
  Card::Card(const Card &other)
  {
    this->rank = other.rank;
    this->suit = other.suit;
  }

  // Copy Assignment Operator
  Card &Card::operator=(const Card &other)
  {
    if (this != &other)
    {
      rank = other.rank;
      suit = other.suit;
    }
    return *this;
  }

  // Move Constructor
  Card::Card(Card &&other) noexcept
  {
    rank = std::move(other.rank);
    suit = std::move(other.suit);
  }

  // Move Assignment Operator
  Card &Card::operator=(Card &&other) noexcept
  {
    if (this != &other)
    {
      rank = std::move(other.rank);
      suit = std::move(other.suit);
    }
    return *this;
  }

  // destructor
  Card::~Card() {}

  // getRank() method
  Rank Card::getRank() const
  {
    return rank;
  }

  // getSuit() method
  Suit Card::getSuit() const
  {
    return suit;
  }

  // setSuit(Suit suit) method
  void Card::setSuit(Suit suit)
  {
    this->suit = suit;
  }

  // toString() method - return the description of the card.
  std::string Card::toString() const
  {
    std::string rankStr;
    std::string suitStr;

    switch (rank)
    {
    case ACE:
      rankStr = "Ace";
      break;
    case TWO:
      rankStr = "2";
      break;
    case THREE:
      rankStr = "3";
      break;
    case FOUR:
      rankStr = "4";
      break;
    case FIVE:
      rankStr = "5";
      break;
    case SIX:
      rankStr = "6";
      break;
    case SEVEN:
      rankStr = "7";
      break;
    case EIGHT:
      rankStr = "8";
      break;
    case NINE:
      rankStr = "9";
      break;
    case TEN:
      rankStr = "10";
      break;
    case JACK:
      rankStr = "Jack";
      break;
    case QUEEN:
      rankStr = "Queen";
      break;
    case KING:
      rankStr = "King";
      break;
    default:
      rankStr = "Ace";
    }

    switch (suit)
    {
    case CLUBS:
      suitStr = "Clubs";
      break;
    case DIAMONDS:
      suitStr = "Diamonds";
      break;
    case HEARTS:
      suitStr = "Hearts";
      break;
    case SPADES:
      suitStr = "Spades";
      break;
    default:
      suitStr = "Spades";
    }

    return rankStr + " of " + suitStr;
  }

  // compare(const Card &other) const method- compare the cards by their rank.
  int Card::compare(const Card &other) const
  {
    if (this->rank == TWO && other.rank == ACE)
    {
      return 1;
    }
    else if (this->rank == ACE && other.rank == TWO)
    {
      return -1;
    }
    else if (this->rank == ACE && other.rank != ACE)
    {
      return 1;
    }
    else if (this->rank != ACE && other.rank == ACE)
    {
      return -1;
    }
    else if (this->rank > other.rank)
    {
      return 1;
    }
    else if (this->rank < other.rank)
    {
      return -1;
    }
    else
    {
      return 0;
    }
  }
}
