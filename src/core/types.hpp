#include <cstdint>

#define MAX_PLAYERS 6
#define MAX_TERRITORIES 64
#define MAX_CONTINENTS 64

const struct MapData{
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

struct MapState{
    // Current Game Flow
    uint8_t currPlayer;
    GamePhase phase = GamePhase::SETUP;
    bool hasConqueredThisTurn;
    int globalSetBonus;

    //Player Data
    int aliveFlags = 0x3F;
    int troopsToPlace[MAX_PLAYERS] = {0};
    uint64_t ownedMasks[MAX_PLAYERS] = {0};
    int playerCards[MAX_PLAYERS] = {0};

    //Territory Data
    uint16_t territoryState[MAX_TERRITORIES] = {0};
};

struct Action{
    ActionType type;
    int SourceID;
    int TargetID;
    int Amount;
};

struct Result{
    bool moveRequired;
    bool territoryTaken;
    int aLosses;
    int dLosses;
    int playerEliminated;
};

enum class GamePhase{
    MOVE,
    SETUP,
    DRAFT,
    ATTACK,
    FORTIFY
};

enum class ActionType{
    END_PHASE,
    TRADE,
    STANDARD
};