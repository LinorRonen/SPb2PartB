#ifndef WAR_PLAYER_H
#define WAR_PLAYER_H
#include <string>
#include <vector>
#include "card.hpp"

namespace ariel
{
    // struct - PlayerStats
    struct PlayerStats
    {
        int turnsPlayed = 0; // The number of turns the player played.
        int turnsWon = 0;    // The number of turns the player won.
        int turnsLost = 0;   // The number of turns the player lost.
        int turnsDraw = 0;   // The number  of turns that was a draw.
    };

    class Player
    {
        std::vector<Card> stack;       // The player's deck of cards.
        std::vector<Card> taken_stack; // The cards that the player obtained during the game.
        PlayerStats stats;             // struct - PlayerStats - holds data about the player.
        std::string name;              // The name of the player.

    public:
        Player(std::string name);                 // Constructor to create a player with a given name.
        Card playCard();                          // playCard() method.
        void add_Card_to_taken(const Card &card); // Adds a card to the player's taken stack.
        std::string getName() const;              // Returns the player's name.
        std::vector<Card> getCards() const;       // Prints the cards this player has left.
        void addTurnWon();                        // addTurnWon() method.
        void addTurnLost();                       // addTurnLost() method.
        void addTurnDraw();                       // addTurnDraw() method.
        int stacksize() const;                    // return amount of cards left in the player's stack.
        int getTurnsWon() const;                  // getTurnsWon() method.
        int getTurnsLost() const;                 // getTurnsLost() method.
        int getTurnsDraw() const;                 // getTurnsDraw() method.
        int cardesTaken() const;                  // Prints the amount of cards this player has won.
        int getturnsPlayed() const;               // getturnsPlayed() method.
        void addcardtostack(const Card &card);    // Adds a card to the player's stack.
    };
} // namespace ariel
#endif // WAR_PLAYER_H
