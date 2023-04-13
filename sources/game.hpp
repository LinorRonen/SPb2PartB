#ifndef GAME_HPP
#define GAME_HPP

#include "card.hpp"
#include "player.hpp"
#include <vector>
#include <string>
#include <array>

namespace ariel
{
    class Game
    {

        int turn = 0;

    private:
        std::vector<Card> cards_heap; // cards_heap -  the deck of the game.
        std::array<Player *, 2> players;
        Player &player1;
        Player &player2;
        std::string mainLog;  // The mainLog string.
        std::string lastTurn; // Astring representing the last turn.
        bool ifStrat;         // A boolean variable that indicates whether the gaame has started or not.
        int winner;           // players[0] - winner=0 , players[1]- winner=1 and if it's a draw - winner = -1.
        int turns;            // The number of the turn
        void checkWin();

    public:
        Game(Player &player1, Player &player2); // constructor - get two players
        Game();                                 // constructor - default
        ~Game();                                // destructor
        Game(const Game &other);                // copy constructor
        Game &operator=(const Game &other);     // copy assignment operator
        Game(Game &&other) noexcept;            // move constructor
        Game &operator=(Game &&other) noexcept; // move assignment operator
        void playTurn();                        // playTurn() method
        void playAll();                         // playAll() method
        void printLastTurn();                   // printLastTurn() method
        void printWiner();                      // printWiner() method
        void printLog();                        // printLog() method
        void printStats();                      // printStats() method
        std::string getLog();                   // getLog() method
        bool getIfStart();                      // getIfStart() method
    };
}

#endif // GAME_HPP
