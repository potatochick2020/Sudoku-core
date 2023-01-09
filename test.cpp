#include <gtest/gtest.h> 
#include "Sudoku.hpp"
#include "DataBase.hpp"

Sudoku generate_and_return_a_sudoku(){
    Sudoku sudoku;
    sudoku.initialize(); 
    return sudoku;
}

Sudoku set_board_using_board_and_return_a_sudoku(const std::vector<std::vector<int>>& board){
    Sudoku sudoku;
    sudoku.setBoard(board);
    return sudoku;
}

Sudoku set_board_using_index_and_return_a_sudoku(const int& x_index, const int& y_index, const int& value){
    Sudoku sudoku;
    sudoku.setBoard(x_index,y_index,value);
    return sudoku;
}

bool connect_to_db(const char* dir){ 
    auto DB = DatabaseConnection(dir);
    if (DB.getDBstatus() == SQLITE_OK){
        return true;
    } else {
        return false;
    }
}

TEST(database, ConnectToDB) {
    ASSERT_EQ(true, connect_to_db(R"(../Database/SudokuDatabase.db)")); 
    ASSERT_EQ(false, connect_to_db("12345")); 
}

TEST(sudoku, GenerateValidSudoku) {
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid()); 
    ASSERT_EQ(true, generate_and_return_a_sudoku().isValid());  
}
 
TEST(sudoku, SetBoardUsing2dVector) {
    ASSERT_EQ(true, set_board_using_board_and_return_a_sudoku({{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}}).isValid());
    ASSERT_EQ(false, set_board_using_board_and_return_a_sudoku({{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1}}).isValid()); 
    ASSERT_EQ(false, set_board_using_board_and_return_a_sudoku({{1,0,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}}).isValid()); 
    ASSERT_EQ(false, set_board_using_board_and_return_a_sudoku({{1,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}}).isValid()); 
    ASSERT_EQ(true, set_board_using_board_and_return_a_sudoku({{1,0,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}}).isValid()); 
}

TEST(sudoku, SetBoardUsingINT) {
    ASSERT_EQ(true, set_board_using_index_and_return_a_sudoku(1,2,3).isValid());  
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}