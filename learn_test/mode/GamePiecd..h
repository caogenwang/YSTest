#include <iostream>
#include  <utility>
#ifndef GAMEPIECE_H
#define GAMEPIECE_H
class GamePiece
{
    public:
        virtual std::unique_ptr<GamePiece> clone() const = 0;
};

class ChessPiece:public GamePiece
{
    public:
        virtual std::unique_ptr<GamePiece> clone() const override;
};

std::unique_ptr<GamePiece> ChessPiece::clone() const
{
    return std::make_unique<ChessPiece>(*this);
};

class GameBoard
{
    public:
        explicit GameBoard(size_t inWidth=0,size_t inHight = 0);
        GameBoard(const GameBoard& src);
        virtual ~GameBoard();
        GameBoard& operator=(const GameBoard& rhs);
        void setPieceAt(size_t x,size_t y,std::unique_ptr<GamePiece> inPiece);
        std::unique_ptr<GamePiece>& getPieceAt(size_t x,size_t y);
        const std::unique_ptr<GamePiece>& getPieceAt(size_t x,size_t y) const;

        size_t getHight() const {return mHeight;}
        size_t getWidth() const {return mWidth;}
    
    private:
        void copyFrom(const GameBoard& src);
        void initializeCellsContainer();
        std::vector<std::vector<std::unique_ptr<GamePiece> > > mCells;
        size_t mHeight,mWidth;
};

GameBoard::GameBoard(const GameBoard& src)
{
    copyFrom(src);
}

GameBoard::~GameBoard()
{

}

void GameBoard::copyFrom(const GameBoard &src)
{
    mHeight = src.mHeight;
    mWidth = src.mWidth;
    initializeCellsContainer();
    for(size_t i = 0;i < mWidth;i ++)
    {
        for(size_t j = 0; j < mHeight; j++)
        {
            if (src.mCells[i][j]) {
                mCells[i][j] = src.mCells[i][j]->clone;
            }
            else
            {
                mCells[i][j].reset();
            } 
        }
    }
}

GameBoard &GameBoard::operator=(const GameBoard &rhs)
{
    if (this == &rhs) {
        return *this;
    }
    copyFrom(rhs);
    return *this;
    
}

void GameBoard::setPieceAt(size_t x,size_t y,std::unique_ptr<GamePiece> inPiece)
{
    mCells[x][y] = move(inPiece);
}

std::unique_ptr<GamePiece> &GameBoard::getPieceAt(size_t x,size_t y)
{
    return mCells[x][y];
}

const std::unique_ptr<GamePiece> &GameBoard::getPieceAt(size_t x,size_t y) const
{
    return mCells[x][y];
}

template<typename T>
class Grid
{
    public: 
        explicit Grid(size_t inWidth=0,size_t inHight = 0);
        void ~Grid();
        void setElementAt(size_t x,size_t y,T inElem);
        T &getElementAt(size_t x,size_t y);
        const T& getElementAt(size_t x,size_t y) const;

        size_t getHight() const {return mHeight;}
        size_t getWidth() const {return mWidth;}
    
    private:
        void initializeCellsContainer();
        std::vector<std::vector<T>> mCells;
        size_t mHeight,mWidth;
};
#endif