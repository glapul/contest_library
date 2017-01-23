#include <vector>
#include <cassert>
#include <functional>
#include <algorithm>
namespace board {
#ifndef ONLINE_JUDGE
#define SAFE
#endif

// Board is a container, T must have a 0-arg constructor;
template<typename T>
struct Board {
    struct iterator {
        iterator(int row, int column, Board<T> board)
            :row_(row), column_(column), board_(board) {}
        iterator& operator++() {
            if (column_ < board_.columns_ - 1)
                ++column_;
            else
                ++row_;
            return *this;
        }
        bool operator==(const iterator& other) const {
            return &board_ == &other.board_ &&
                row_ == other.row_ &&
                column_ == other.column_;
        }
        T& operator*() {
#ifdef SAFE
            assert(0 <= row_ && row_ <= board_.rows_);
            assert(0 <= column_ && column_ <= board_.columns_);
#endif
            return board_[row_][column_];
        }
        // members
        int row_, column_;
        Board& board_;
    };
    Board(int rows = 0, int columns = 0) : rows_(rows), columns_(columns) {
        board_.resize(rows, std::vector<T>(columns));
    }
    Board(const std::vector<std::vector<T>>& v) {
        rows_ = v.size();
#ifdef SAFE
        assert(v.size() > 0);
        for (int i = 0; i < rows_ - 1; i++)
            assert(v[i].size() == v[i + 1].size());
#endif
        columns_ = v[0].size();
        board_ = v;
    }


    Board::iterator begin() {
        return iterator(0, 0, *this);
    }
    Board::iterator end() {
        return iterator(rows_, 0, *this);
    }
    std::vector<T>& operator[] (int i) {
#ifdef SAFE
        assert(0 <= i && i <= rows_);
#endif
        return board_[i];
    }
    void ProcessByRows(std::function<void(T&)> fun) {
        std::for_each(board_.begin(), board_.end(),
                [=](std::vector<T>& v) {std::for_each(v.begin(), v.end(), fun);});
    }
    void ProcessByColumns(std::function<void(T&)> fun) {
        for (int j = 0; j < columns_; j++)
            for (int i = 0; i < rows_; i++)
                fun(board_[i][j]);
    }
    // members
    int rows_, columns_;
    std::vector<std::vector<T>> board_;
    //static functions
    static Board<T> Rotate90DegreesCCW(Board<T>& b);
    static void Iterate(const Board &b,
            std::function<void(int,int)>f);

};

Board<char> CreateBoardFromStringVector(const std::vector<std::string>& v) {
    Board<char> b(v.size(), v[0].size());
    b.rows_ = v.size();
#ifdef SAFE
    assert(v.size() > 0);
    for (int i = 0; i < b.rows_ - 1; i++)
        assert(v[i].size() == v[i + 1].size());
#endif
    b.columns_ = v[0].size();
    for (int i = 0; i < b.rows_; i++)
        std::copy(v[i].begin(), v[i].end(),
                std::back_inserter(b.board_[i]));
    return b;
}

template<typename T>
Board<T> Board<T>::Rotate90DegreesCCW(Board<T>& b) {
    Board<T> result(b.columns_, b.rows_);
    for (int i = 0; i < result.rows_; i++) {
        for (int j = 0; j < result.columns_; j++) {
            result[i][j] = b[j][result.rows_ - 1 - i];
        }
    }
    return result;
}
template<typename T>
void Board<T>::Iterate(const Board<T>& b,
        std::function<void(int,int)> f) {
    for (int i = 0; i < b.rows_; i++)
        for (int j = 0; j < b.columns_; j++)
            f(i, j);
}


}  // namespace board
