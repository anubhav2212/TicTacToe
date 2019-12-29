#include<bits/stdc++.h>
using namespace std;

class Player {
    string name;
    char symbol;
    int id;
    bool hasWon;
public:
    Player(int idd, char sym, string nam) {
        id = idd;
        symbol = sym;
        name = nam;
        hasWon = false;
    }
    string getName() {
        return name;
    }
    int getId() {
        return id;
    }
    char getSymbol() {
        return symbol;
    }
    bool hasWonGame() {
        return hasWon;
    }
    void setHasWon(bool hasW) {
        hasWon = hasW;
    }
};

class Cell {
    int row;
    int col;
    bool isMarked;
    char symbol;
    vector<int> arrX;
    vector<int> arrO;
public:
    Cell(int r, int c) {
        row = r;
        col = c;
        isMarked = false;
        arrX.assign(4, 0);
        arrO.assign(4, 0);
    }
    int getRow() {
        return row;
    }
    int getCol() {
        return col;
    }
    char getSym() {
        return symbol;
    }
    void setSym(char s) {
        symbol = s;
    }
    bool getIsMarked() {
        return isMarked;
    }
    void setIsMarked(bool isM) {
        isMarked = isM;
    }
    int getArrX(int pos) {
        return arrX[pos];
    }
    int getArrO(int pos) {
        return arrO[pos];
    }
    void setArrX(int pos, int val) {
        arrX[pos] = val;
    }
    void setArrO(int pos, int val) {
        arrO[pos] = val;
    }
};

class Board {
    int size;
    vector<vector<Cell>> cells;

public:
    Board(int siz) {
        size = siz;
        for(int i=0;i<size;i++) {
                vector<Cell> temp;
            for(int j=0;j<size;j++) {
                Cell c(i, j);
                temp.push_back(c);
            }
            cells.push_back(temp);
        }
    }
    int getSize() {
     return size;
    }
    bool isValidCell(int r, int c) {
        return (r>=0 && c>=0 && r<size && c<size);
    }
    Cell* getCell(int r, int c) {
        return &cells[r][c];
    }
};

class GameService {
    vector<Player> players;
    Board* board;
    bool isGameComplete;
    int winningLength;
public:
    GameService(int s, int wL) {
    board = new Board(s);
    isGameComplete = false;
    winningLength = wL;
    }
    void setPlayers(vector<Player> ps) {
        players = ps;
    }
    void startGame() {
        int chance = 0, row, col, moves = 0;
        while(!isGameCompleted() || moves == pow(board->getSize(), 2)) {
            cin>>row;
            cin>>col;
            if(!isValidCell(row, col)) {
                cout<<"wrong move! retry\n";
                continue;
            }
            playerMarks(row, col, chance);
            moves++;
            if(hasPlayerWon(players[chance])) {
                isGameComplete = true;
                cout<<players[chance].getName()<<" wins the game\n";
            }
            chance = (chance + 1)%players.size();
        }
        if(!isGameComplete) {
            cout<<"draw\n";
        }
    }
    bool isGameCompleted() {
        return isGameComplete;
    }
    bool hasPlayerWon(Player player) {
        return player.hasWonGame();
    }
    void playerMarks(int row, int col, int pos) {
        Cell *c = board->getCell(row, col);
        c->setIsMarked(true);
        c->setSym(players[pos].getSymbol());
        if(players[pos].getSymbol() == 'X' || players[pos].getSymbol() == 'x') {
            int q=0,w=0;
            if(isValidMarkedCell(row-1, col-1)) {
                q = board->getCell(row-1, col-1)->getArrX(0);
            }
            if(isValidMarkedCell(row+1, col+1)) {
                w = board->getCell(row+1, col+1)->getArrX(0);
            }
            if(q+w+1 >= winningLength) {
                players[pos].setHasWon(true);
            }
            else {
                board->getCell(row, col)->setArrX(0, q+w+1);
            }
            q=0,w=0;
            if(isValidMarkedCell(row-1, col)) {
                q = board->getCell(row-1, col)->getArrX(1);
            }
            if(isValidMarkedCell(row+1, col)) {
                w = board->getCell(row+1, col)->getArrX(1);
            }
            if(q+w+1 >= winningLength) {
                players[pos].setHasWon(true);
            }
            else {
                board->getCell(row, col)->setArrX(1, q+w+1);
            }
            q=0,w=0;
            if(isValidMarkedCell(row-1, col+1)) {
                q = board->getCell(row-1, col+1)->getArrX(2);
            }
            if(isValidMarkedCell(row+1, col-1)) {
                w = board->getCell(row+1, col-1)->getArrX(2);
            }
            if(q+w+1 >= winningLength) {
                players[pos].setHasWon(true);
            }
            else {
                board->getCell(row, col)->setArrX(2, q+w+1);
            }
            q=0,w=0;
            if(isValidMarkedCell(row, col+1)) {
                q = board->getCell(row, col+1)->getArrX(3);
            }
            if(isValidMarkedCell(row, col-1)) {
                w = board->getCell(row, col-1)->getArrX(3);
            }
            if(q+w+1 >= winningLength) {
                players[pos].setHasWon(true);
            }
            else {
                board->getCell(row, col)->setArrX(3, q+w+1);
            }
        }
        else if(players[pos].getSymbol() == 'O' || players[pos].getSymbol() == 'o') {
            int q=0,w=0;
            if(isValidMarkedCell(row-1, col-1)) {
                q = board->getCell(row-1, col-1)->getArrO(0);
            }
            if(isValidMarkedCell(row+1, col+1)) {
                w = board->getCell(row+1, col+1)->getArrO(0);
            }
            if(q+w+1 >= winningLength) {
                players[pos].setHasWon(true);
            }
            else {
                board->getCell(row, col)->setArrO(0, q+w+1);
            }
            q=0,w=0;
            if(isValidMarkedCell(row-1, col)) {
                q = board->getCell(row-1, col)->getArrO(1);
            }
            if(isValidMarkedCell(row+1, col)) {
                w = board->getCell(row+1, col)->getArrO(1);
            }
            if(q+w+1 >= winningLength) {
                players[pos].setHasWon(true);
            }
            else {
                board->getCell(row, col)->setArrO(1, q+w+1);
            }
            q=0,w=0;
            if(isValidMarkedCell(row-1, col+1)) {
                q = board->getCell(row-1, col+1)->getArrO(2);
            }
            if(isValidMarkedCell(row+1, col-1)) {
                w = board->getCell(row+1, col-1)->getArrO(2);
            }
            if(q+w+1 >= winningLength) {
                players[pos].setHasWon(true);
            }
            else {
                board->getCell(row, col)->setArrO(2, q+w+1);
            }
            q=0,w=0;
            if(isValidMarkedCell(row, col+1)) {
                q = board->getCell(row, col+1)->getArrO(3);
            }
            if(isValidMarkedCell(row, col-1)) {
                w = board->getCell(row, col-1)->getArrO(3);
            }
            if(q+w+1 >= winningLength) {
                players[pos].setHasWon(true);
            }
            else {
                board->getCell(row, col)->setArrO(3, q+w+1);
            }
        }
    }
    bool isValidMarkedCell(int row, int col) {
        return (board->isValidCell(row, col));
    }
    bool isValidCell(int row, int col) {
        return (board->isValidCell(row, col)) && !(board->getCell(row, col)->getIsMarked());
    }
};
int main() {
    int numOfPlayers;
    int idCounter = 1;
    int wL;
    int size;
    string name;
    char symb;
    cin>>wL;
    cin>>size;
    cin>>numOfPlayers;
    vector<Player> players;
    for(int i=0;i<numOfPlayers;i++) {
        cin>>name;
        cin>>symb;
        Player p(idCounter, symb, name);
        idCounter++;
        players.push_back(p);
    }
    GameService *game = new GameService(size, wL);
    game->setPlayers(players);
    game->startGame();
    return 0;
}

/*
Input
3
3
2
a
x
b
o
*/
