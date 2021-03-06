#include <Display/Window.hpp>
#include <EAI.hpp>
#include <Heuristic.hpp>
#include <Minimax.hpp>
#include <Mcts.hpp>
#include <EngineGlobals.hpp>

#include <vector>
using std::vector;


class Board
{

public:
    enum kindStone
    {
        EMPTY, X, O, XW, OW, BLOCKED
    };

    enum role
    {
        PLAYER_1, PLAYER_2, BOT
    };
    struct infoBoard
    {
        int x;
        int y;
        kindStone kind;
    } stone;

    int width;
    int height;
    int style;

    int currentX;
    int currentY;
    int lastX;
    int lastY;

    Board();
    ~Board();

    void setType(EngineGlobals::Board::Style _style);
    void setBoard(bool willLoad);
    void draw(Window* win, role currentPlayer);

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    bool undo();
    void goRandom();
    void makeMove();

    bool isOutOfBoard(int x, int y);
    void searchForStone(kindStone currentStone, int& count, int& toHead, int x, int y, int direction);
    void markStateWin(kindStone currentStone, int& count, int x, int y, int direction);
    int isCheckedForWin(int x, int y);
    int isCheckCapture(int x, int y);
    void animationWin(int directionWin);

    int getSize();
    vector< std::pair<int, int> > getLastBoard();
    bool update(role currentPlayer);
    vector< vector<kindStone> > board;
    vector< infoBoard > contains;

    EAI* lokiAi;
    Heuristic* heuristic;
    Minimax* minimax;
    Mcts* mcts;
}
;
