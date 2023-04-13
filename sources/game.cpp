#include "card.hpp"
#include "player.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include "game.hpp"

using namespace std;

namespace ariel
{
  // constructor - get two players
  Game::Game(Player &player1, Player &player2) : winner(-1), player1(player1), player2(player2)
  {

    this->turns = 0;
    this->ifStrat = false;

    // Filling cards_heap
    std::cout << "Filling cards_heap..." << std::endl;
    for (int rank = 1; rank < 14; rank++)
    {
      for (int suit = 0; suit < 4; suit++)
      {
        Suit cardSuit = static_cast<Suit>(suit);
        Rank cardRank = static_cast<Rank>(rank);
        Card card(cardRank, cardSuit);
        cards_heap.push_back(card);
      }
    }

    //  Use std::random_device to seed the random number generator
    std::random_device rd;

    // Use std::mt19937 as the generator engine for high-quality randomness
    std::mt19937 gen(rd());

    // Shuffle the cards_heap using std::shuffle with the generator engine
    std::shuffle(std::begin(cards_heap), std::end(cards_heap), gen);

    players[0] = &player1;
    players[1] = &player2;

    std::cout << "Dealing the cards to the players: each player gets 26 cards." << std::endl;
    for (size_t i = 0; i < cards_heap.size(); i += 2)
    {
      players[0]->addcardtostack(cards_heap[i]);
      players[1]->addcardtostack(cards_heap[i + 1]);
    }

    cout << "Player one: " << players[0]->getName() << ",has: " << players[0]->stacksize() << "cards in his stack." << std::endl;
    cout << "Player two: " << players[1]->getName() << ",has: " << players[1]->stacksize() << "cards in his stack." << std::endl;
  }

  // constructor - default
  Game::Game() : winner(-1), player1(*new Player("player1")), player2(*new Player("player2")) {}

  // destructor
  Game::~Game() {}

  // copy constructor
  Game::Game(const Game &other)
      : turn(other.turn),
        cards_heap(other.cards_heap),
        mainLog(other.mainLog),
        lastTurn(other.lastTurn),
        ifStrat(other.ifStrat),
        winner(other.winner),
        turns(other.turns),
        player1(*other.players[0]),
        player2(*other.players[1])
  {
    players = {&player1, &player2};
  }

  // copy assignment operator
  /*Game &Game::operator=(const Game &other)
  {
    if (this != &other)
    {
      turn = other.turn;
      cards_heap = other.cards_heap;
      mainLog = other.mainLog;
      lastTurn = other.lastTurn;
      ifStrat = other.ifStrat;
      winner = other.winner;
      turns = other.turns;
      player1 = *other.players[0];
      player2 = *other.players[1];
      players = {&player1, &player2};
    }
    return *this;
  }

  // move constructor
  Game::Game(Game &&other) noexcept
      : turn(other.turn),
        cards_heap(std::move(other.cards_heap)),
        mainLog(std::move(other.mainLog)),
        lastTurn(std::move(other.lastTurn)),
        ifStrat(other.ifStrat),
        winner(other.winner),
        turns(other.turns),
        player1(*other.players[0]),
        player2(*other.players[1])
  {
    players = {&player1, &player2};
  }

  // move assignment operator
  Game &Game::operator=(Game &&other) noexcept
  {
    if (this != &other)
    {
      turn = other.turn;
      cards_heap = std::move(other.cards_heap);
      mainLog = std::move(other.mainLog);
      lastTurn = std::move(other.lastTurn);
      ifStrat = other.ifStrat;
      winner = other.winner;
      turns = other.turns;
      player1 = *other.players[0];
      player2 = *other.players[1];
      players = {&player1, &player2};
    }
    return *this;
  }*/

  // A boolean variable that tells us if the game has started
  bool Game::getIfStart()
  {
    return this->ifStrat;
  }

  // The method prints the description of the card
  std::string printCard(const Card &card)
  {
    return card.toString();
  }

  // playTurn() method
  void Game::playTurn()
  {
    if (&player1 == &player2)
    {
      throw std::invalid_argument("Both players cannot be the same object.");
    }
    if (players[0]->stacksize() == 0 || players[1]->stacksize() == 0)
    {
      throw logic_error("The game over!");
    }
    if (!this->ifStrat)
    {
      this->ifStrat = true;
    }

    // The number of the turn
    this->turns++;
    std::cout << "Turn: " << this->turns << std::endl;

    bool ContinueTheGame = true;
    lastTurn = "";

    std::vector<Card> drawCards;

    while (ContinueTheGame != false)
    {
      if (players[0]->stacksize() == 0 || players[1]->stacksize() == 0)
      {
        return;
      }

      Card card1 = players[0]->playCard();
      Card card2 = players[1]->playCard();

      lastTurn += players[0]->getName() + " played: " + printCard(card1) + ". ";
      lastTurn += players[1]->getName() + " played: " + printCard(card2) + ".\n";

      int result = card1.compare(card2);

      // print the cards and players
      std::cout << players[0]->getName() << " played: " << printCard(card1) << std::endl;
      std::cout << players[1]->getName() << " played: " << printCard(card2) << std::endl;

      if (result > 0)
      {
        players[0]->addTurnWon();
        players[1]->addTurnLost();
        players[0]->add_Card_to_taken(card1);
        players[0]->add_Card_to_taken(card2);
        lastTurn += players[0]->getName() + " won the turn.\n";
        winner = 0;
        cout << players[0]->getName() << " won the turn." << endl;
        ContinueTheGame = false;
        if (drawCards.size() > 0)
        {
          while (drawCards.size() > 0)
          {
            Card card = drawCards.front();
            drawCards.erase(drawCards.begin());
            players[0]->add_Card_to_taken(card);
          }
        }
      }
      else if (result < 0)
      {
        players[1]->addTurnWon();
        players[0]->addTurnLost();
        players[1]->add_Card_to_taken(card1);
        players[1]->add_Card_to_taken(card2);
        lastTurn += players[1]->getName() + " won the turn.\n";
        winner = 1;
        cout << players[1]->getName() << " won the turn." << endl;
        ContinueTheGame = false;
        if (drawCards.size() > 0)
        {
          while (drawCards.size() > 0)
          {
            Card card = drawCards.front();
            drawCards.erase(drawCards.begin());
            players[1]->add_Card_to_taken(card);
          }
        }
      }
      else
      {
        players[1]->addTurnDraw();
        players[0]->addTurnDraw();
        drawCards.push_back(card1);
        drawCards.push_back(card2);

        lastTurn += "Draw! no winner to this turn.\n";
        winner = -1;
        cout << "Draw!" << endl;

        if (players[0]->stacksize() <= 1 || players[1]->stacksize() <= 1)
        {
          lastTurn += "It is impossible to continue the draw!\n";
          cout << "It is impossible to continue the draw!" << endl;
          if (players[0]->stacksize() == 1 && players[1]->stacksize() == 1)
          {
            Card card1 = players[0]->playCard();
            Card card2 = players[1]->playCard();
            players[0]->add_Card_to_taken(card1);
            players[1]->add_Card_to_taken(card2);
          }
          while (!drawCards.empty())
          {
            int choice = (int)drawCards.size() % 2;

            if (choice == 0)
              players[0]->add_Card_to_taken(drawCards.back());

            else
              players[1]->add_Card_to_taken(drawCards.back());

            drawCards.pop_back();
          }
          ContinueTheGame = false;
          break;
        }

        else
        {
          lastTurn += "Each player draws another card and puts it aside. After that, another card, according to its result, we continue.\n";
          cout << "Each player draws another card and puts it aside." << endl
               << "After that, another card, according to its result, we continue." << endl;
          Card cardone = players[0]->playCard();
          drawCards.push_back(cardone);
          Card cardtwo = players[1]->playCard();
          drawCards.push_back(cardtwo);
        }
      }
    }

    mainLog += lastTurn;
  }

  // playAll() method - playes the game untill the end.
  void Game::playAll()
  {
    if (this->ifStrat != true)
    {
      cout << "Before the game starts:" << std::endl;
      cout << "Player one: " << players[0]->getName() << ", has:" << players[0]->stacksize() << "cards in his stack." << std::endl;
      cout << "Player one:" << players[1]->getName() << ", has:" << players[1]->stacksize() << "cards in his stack." << std::endl;
    }

    while (players[0]->stacksize() != 0 && players[1]->stacksize() != 0)
    {
      playTurn();
    }

    cout << "playAll() end......................................" << std::endl;
  }

  // printLastTurn() method- print the last turn stats.
  void Game::printLastTurn()
  {
    if (!this->ifStrat)
    {
      throw logic_error("The game hasn't strated yet.");
    }
    cout << lastTurn << std::endl;
    cout << "printLastTurnend() end............................." << std::endl;
  }

  // printWiner() method - prints the name of the winning player.
  void Game::printWiner()
  {
    if (!this->ifStrat)
    {
      throw std::logic_error("The game hasn't strated yet.");
    }
    else
    {
      checkWin();
    }
    cout << "printwiner() end............................." << std::endl;
    cout << std::endl;
  }

  // printLog() method - prints all the turns played one line per turn.
  void Game::printLog()
  {
    if (this->ifStrat)
    {
      std::cout << mainLog << std::endl;
    }
    cout << "printLog() end............................" << std::endl;
    cout << std::endl;
    cout << std::endl;
  }

  // printStats() method- for each player prints basic statistics.
  void Game::printStats()
  {
    if (this->ifStrat)
    {
      cout << "Player 1:" << endl;
      cout << "Name: " << players[0]->getName() << endl;
      cout << "Number of cards in his stack: " << players[0]->stacksize() << endl;
      cout << "Number of cards obtained in the game: " << players[0]->cardesTaken() << endl;
      cout << "Number of turns won in the game: " << players[0]->getTurnsWon() << endl;
      cout << "Number of turns lost in the game: " << players[0]->getTurnsLost() << endl;
      cout << "Win rate: " << (((float)players[0]->getTurnsWon() / this->turns) * 100) << "%" << endl;
      cout << std::endl;
      cout << "Player 2:" << endl;
      cout << "Name: " << players[1]->getName() << endl;
      cout << "Number of cards in his stack: " << players[1]->stacksize() << endl;
      cout << "Number of cards obtained in the game: " << players[1]->cardesTaken() << endl;
      cout << "Number of turns won in the game: " << players[1]->getTurnsWon() << endl;
      cout << "Number of turns lost in the game: " << players[1]->getTurnsLost() << endl;
      cout << "Win rate: " << (((float)players[1]->getTurnsWon() / this->turns) * 100) << "%" << endl;
      cout << std::endl;
      cout << "Additional information about the game: " << endl;
      cout << "The number of turns in which they drew:" << players[1]->getTurnsDraw() << endl;
      cout << "The game ended in " << turns << " turns" << endl;
      cout << "Draw rate: " << (((float)players[1]->getTurnsDraw() / this->turns) * 100) << "%" << endl;
      cout << "The winner is: ";
      checkWin();
    }
    cout << "printStats() end............................" << endl;
    cout << endl;
  }

  // getLog() method
  std::string Game::getLog()
  {
    return mainLog;
    cout << endl;
  }

  // checkWin() method
  // An method that prints the name of the winner and in case of a draw prints: "Draw!".
  void Game::checkWin()
  {
    if (players[0]->cardesTaken() > players[1]->cardesTaken())
    {
      winner = 0;
      cout << players[0]->getName() << " won the game!" << std::endl;
      return;
    }
    else if (players[0]->cardesTaken() < players[1]->cardesTaken())
    {
      winner = 1;
      cout << players[1]->getName() << " won the game!" << std::endl;
      return;
    }
    else if (players[0]->cardesTaken() == players[1]->cardesTaken())
    {
      winner = -1;
      cout << "Draw!" << endl;
      return;
    }
  }

} // namespace ariel
