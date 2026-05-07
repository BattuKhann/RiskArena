#include <cstdint>

#define MAX_PLAYERS 6
#define MAX_TERRITORIES 64
#define MAX_CONTINENTS 64

enum ActionType : uint8_t{
    END_PHASE,
    TRADE,
    STANDARD
};

enum GamePhase : uint8_t{
    MOVE,
    SETUP,
    DRAFT,
    ATTACK,
    FORTIFY
};

struct Action{
    ActionType type;
    uint64_t SourceID; //Doubles as # of Infantry Cards
    uint64_t TargetID; //Doubles as # of Cavalry Cards
    uint64_t Amount; //Doubles as # of Artillery Cards
};

struct Result{
    bool moveRequired;
    bool territoryTaken;
    int aLosses;
    int dLosses;
    int playerEliminated;
};

struct MapData{
    uint64_t adjacency[MAX_TERRITORIES] = {0};
    uint64_t continents[MAX_CONTINENTS] = {0};
    int bonuses[MAX_CONTINENTS] = {0};
    int numTerritorries;
    int numContinents;
};

struct GameData{
    int numPlayers = 2;
    bool balancedBlitz;
    bool fixed;
    bool fow;
    bool capitals;
};

struct Card {
    uint64_t territoryID;
    uint8_t type;
};

struct MapState{
    uint64_t ownedMasks[MAX_PLAYERS];
    uint64_t playerCards[MAX_PLAYERS];
    uint64_t drawDeckMask; //Available cards to draw

    uint16_t territoryTroops[MAX_TERRITORIES];
    uint16_t troopsToPlace;

    uint8_t aliveFlags = 0x3F;
    uint8_t currPlayer;
    GamePhase phase = GamePhase::SETUP;
    bool hasConqueredThisTurn;
    int globalSetBonus;
    int turn;

    Card gameDeck[MAX_TERRITORIES];
};