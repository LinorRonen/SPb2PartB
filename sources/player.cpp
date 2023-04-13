#include <stdexcept>
#include "player.hpp"
#include "card.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using namespace ariel;

// Constructor that sets the player's name
Player::Player(std::string name)
{
    this->name = name;
}

// Add a card to the player's taken stack
void Player::add_Card_to_taken(const Card &card)
{
    taken_stack.push_back(card);
}

// Remove and return the top card from the player's stack
Card Player::playCard()
{
    if (stack.empty())
    {
        throw runtime_error("Player has no cards left!");
    }
    Card card = stack.front();
    stack.erase(stack.begin());
    return card;
}

// Increment the player's turnsWon counter and turnsPlayed counter.
void Player::addTurnWon()
{
    stats.turnsPlayed++;
    stats.turnsWon++;
}

// Add a card to the player's stack
void Player::addcardtostack(const Card &card)
{
    stack.push_back(card);
}

// Increment the player's turnsLost counter and turnsPlayed counter.
void Player::addTurnLost()
{
    stats.turnsPlayed++;
    stats.turnsLost++;
}

// Increment the player's turnsDraw counter and turnsPlayed counter.
void Player::addTurnDraw()
{
    stats.turnsPlayed++;
    stats.turnsDraw++;
}

// Get the player's name.
string Player::getName() const
{
    return name;
}

// Return the number of turns the player has played.
int Player::getturnsPlayed() const
{
    return stats.turnsPlayed;
}

vector<Card> Player::getCards() const
{
    return stack;
}

// Get the size of the player's stack.
int Player::stacksize() const
{
    return this->stack.size();
}

// Get the number of turns the player has won.
int Player::getTurnsWon() const
{
    return stats.turnsWon;
}

int Player::getTurnsLost() const
{
    return stats.turnsLost;
}

// Get the number of times that ended in a draw.
int Player::getTurnsDraw() const
{
    return stats.turnsDraw;
}

// Return the number of cards the player has obtained so far in the game.
int Player::cardesTaken() const
{
    return this->taken_stack.size();
}
