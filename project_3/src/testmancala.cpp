#include <gtest/gtest.h>
#include "MancalaBoard.h"
//#include "MancalaBoard.cpp"

TEST(MancalaBoardTest, DefaultBoardTest){
    // Needs to test that default board is correct
    
//    // test if it's start with pits start with 4 and score with 0 as default
//    int def_Pits [] = {4,4,4,4,4,4,4,4,4,4}; // the selection for each pits
//    int def_Stores [] = {0,0}; // player scored
//
    CMancalaBoard cmb;// initialize the class

    for(int player = 0; player < MANCALA_PLAYERS; player++) //check each player's slot
    {
        for(int pit = 0; pit < MANCALA_PIT_SLOTS; pit++)
        {
            EXPECT_EQ(cmb.PitStoneCount(player,pit),4); //check if every pit slot is 4
        }
        EXPECT_EQ(cmb.PlayerScore(player),0); // check the initialized score is 0
        
    }
    EXPECT_EQ(cmb.PlayerTurn(),0); // check the initialized turn
    EXPECT_EQ(cmb.ToString(),
                            "P1          PITS\n"
                            "      5   4   3   2   1\n"
                            "/---------------------------\\\n"
                            "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
                            "| 0 |-------------------| 0 |\n"
                            "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
                            "\\---------------------------/\n"
                            "      1   2   3   4   5\n"
                            "             PITS          P2\n"); // print board
    
    EXPECT_FALSE(cmb.GameOver()); // check the game winning conditions
    EXPECT_EQ(cmb.ToString(),std::string(cmb)); // check ToSting == string
}

TEST(MancalaBoardTest, SetBoardTest){
    // Needs to test that setting up an initial board is correct

    // case 1: initial board / default board / player doesn't scored
    int def_Pits [] = {4,4,4,4,4,4,4,4,4,4}; // the selection for each pits
    int def_Stores [] = {0,0}; // player scored

    CMancalaBoard cmb(0, def_Pits, def_Stores); // initialize the class

    for(int player = 0; player < MANCALA_PLAYERS; player++) //check each player's slot
    {
        for(int pit = 0; pit < MANCALA_PIT_SLOTS; pit++)
        {
            EXPECT_EQ(cmb.PitStoneCount(player,pit),4); //check if every pit slot is 4
        }
        EXPECT_EQ(cmb.PlayerScore(player),0); // check the initialized score is 0

    }
    EXPECT_EQ(cmb.PlayerTurn(),0); // check the initialized turn
    EXPECT_EQ(cmb.ToString(),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
              "| 0 |-------------------| 0 |\n"
              "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    
    EXPECT_FALSE(cmb.GameOver()); // check the game winning conditions
    EXPECT_EQ(cmb.ToString(),std::string(cmb)); // check ToSting == string

    //case 2 player scored
    // Discussion Section Professor Nitta give us
    int Pits[] = {1,2,3,4,5,1,2,3,4,5}; // the selection for each pits
    int Scores[] = {5,5}; // player scored
    CMancalaBoard TheBoard(0, Pits, Scores); // initialize the class

    for(int Player = 0; Player < MANCALA_PLAYERS; Player++) //check each player's slot
    {
        for (int Pit = 0; Pit < MANCALA_PIT_SLOTS; Pit++)
        {
            EXPECT_EQ(TheBoard.PitStoneCount(Player, Pit), Pit+1);
        }
        EXPECT_EQ(TheBoard.PlayerScore(Player), 5);
    }
    EXPECT_EQ(TheBoard.PlayerTurn(), 0);// check the initialized score is 0

    EXPECT_EQ(TheBoard.ToString(),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 5 | 4 | 3 | 2 | 1 |   |\n"
              "| 5 |-------------------| 5 |\n"
              "|   | 1 | 2 | 3 | 4 | 5 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");

    EXPECT_FALSE(TheBoard.GameOver());
    EXPECT_EQ(TheBoard.ToString(), std::string(TheBoard));

}

TEST(MancalaBoardTest, ResetBoardTest){
    // Needs to test that resetting a board is correct
    
    // initial board / default board
    // case 1:
    CMancalaBoard cmb;
    cmb.ResetBoard();
    
    for(int player = 0; player < MANCALA_PLAYERS; player++) //check each player's slot
    {
        for(int pit = 0; pit < MANCALA_PIT_SLOTS; pit++)
        {
            EXPECT_EQ(cmb.PitStoneCount(player,pit),4); //check if every pit slot is 4
        }
        EXPECT_EQ(cmb.PlayerScore(player),0); // check the initialized score is 0
        
    }
    EXPECT_EQ(cmb.PlayerTurn(),0); // check the initialized turn
    EXPECT_EQ(cmb.ToString(),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
              "| 0 |-------------------| 0 |\n"
              "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(cmb.GameOver()); // check the game winning conditions
    EXPECT_EQ(cmb.ToString(),std::string(cmb)); // check ToSting == string
    // case 2
    int Pits[] = {1,2,3,4,5,1,2,3,4,5}; // the selection for each pits
    int Scores[] = {5,5}; // player scored
    CMancalaBoard TheBoard(0, Pits, Scores); // initialize the class
    
    TheBoard.ResetBoard();
    
    for(int Player = 0; Player < MANCALA_PLAYERS; Player++) //check each player's slot
    {
        for (int Pit = 0; Pit < MANCALA_PIT_SLOTS; Pit++)
        {
            EXPECT_EQ(TheBoard.PitStoneCount(Player, Pit), 4);
        }
        EXPECT_EQ(TheBoard.PlayerScore(Player), 0);
    }
    EXPECT_EQ(TheBoard.PlayerTurn(), 0);// check the initialized score is 0
    
    EXPECT_EQ(TheBoard.ToString(),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
              "| 0 |-------------------| 0 |\n"
              "|   | 4 | 4 | 4 | 4 | 4 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(TheBoard.GameOver());
    EXPECT_EQ(TheBoard.ToString(), std::string(TheBoard));
}

TEST(MancalaBoardTest, BasicMoveTest){
    
    // Needs to test that basic non-scoring moves are correct

    // Test if the input is valid which = the can/cant move
    // case 1
//    int def_Pits [] = {4,4,4,4,4,4,4,4,4,4}; // the selection for each pits
//    int def_Stores [] = {0,0}; // player scored

    CMancalaBoard cmb; // initialize the class
    
    EXPECT_TRUE(cmb.Move(0,0));
    EXPECT_EQ(cmb.PlayerTurn(),1);
    EXPECT_EQ(cmb.PlayerScore(0),0);
    EXPECT_EQ(cmb.PitStoneCount(0,0),0);
    EXPECT_TRUE(cmb.Move(1,0));
    EXPECT_EQ(cmb.PlayerTurn(),0);
    EXPECT_FALSE(cmb.Move(0,0));
    EXPECT_FALSE(cmb.Move(1,0));
    EXPECT_EQ(cmb.PlayerScore(1),0);
    EXPECT_EQ(cmb.PitStoneCount(1,0),0);
    EXPECT_FALSE(cmb.Move(2,1));
    EXPECT_FALSE(cmb.Move(0,-1));
    EXPECT_EQ(std::string(cmb),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 5 | 5 | 5 | 5 | 0 |   |\n"
              "| 0 |-------------------| 0 |\n"
              "|   | 0 | 5 | 5 | 5 | 5 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(cmb.GameOver());
    EXPECT_EQ(cmb.ToString(), std::string(cmb));
    
    // case 2
    int Pits[] = {1,2,3,4,5,1,2,3,4,5}; // the selection for each pits
    int Scores[] = {5,5}; // player scored
    CMancalaBoard TheBoard(0, Pits, Scores); // initialize the class
    
    EXPECT_TRUE(TheBoard.Move(0,0));
    EXPECT_EQ(TheBoard.PlayerTurn(),1);
    EXPECT_EQ(TheBoard.PlayerScore(0),5);
    EXPECT_EQ(TheBoard.PitStoneCount(0,3),4);
    EXPECT_TRUE(TheBoard.Move(1,0));
    EXPECT_EQ(TheBoard.PlayerTurn(),0);
    EXPECT_FALSE(TheBoard.Move(0,0));
    EXPECT_FALSE(TheBoard.Move(1,0));
    EXPECT_EQ(TheBoard.PlayerScore(1),5);
    EXPECT_EQ(TheBoard.PitStoneCount(1,2),3);
    
    
    EXPECT_EQ(TheBoard.ToString(),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 5 | 4 | 3 | 3 | 0 |   |\n"
              "| 5 |-------------------| 5 |\n"
              "|   | 0 | 3 | 3 | 4 | 5 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(TheBoard.GameOver());
    EXPECT_EQ(TheBoard.ToString(), std::string(TheBoard));
    
}

TEST(MancalaBoardTest, ScoringMoveTest){
    // Needs to test that basic scoring, non double moves, non steals are correct
    // case 1
//    int def_Pits [] = {4,4,4,4,4,4,4,4,4,4}; // the selection for each pits
//    int def_Stores [] = {0,0}; // player scored
    
    CMancalaBoard cmb; // initialize the class
    
    EXPECT_TRUE(cmb.Move(0,2));
    EXPECT_EQ(cmb.PlayerTurn(),1);
    EXPECT_EQ(cmb.PlayerScore(0),1);
    EXPECT_EQ(cmb.PitStoneCount(0,2),0);
    EXPECT_TRUE(cmb.Move(1,4));
    EXPECT_EQ(cmb.PlayerTurn(),0);
//    EXPECT_TRUE(cmb.Move(0,1));
//    EXPECT_TRUE(cmb.Move(1,1));
    EXPECT_EQ(cmb.PlayerScore(1),1);
    EXPECT_EQ(cmb.PitStoneCount(1,2),4);
    EXPECT_EQ(std::string(cmb),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 5 | 5 | 1 | 5 | 5 |   |\n"
              "| 1 |-------------------| 1 |\n"
              "|   | 5 | 4 | 4 | 4 | 0 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(cmb.GameOver());
    EXPECT_EQ(cmb.ToString(), std::string(cmb));
    
    // case 2
    int Pits[] = {1,2,3,4,5,1,2,3,4,5}; // the selection for each pits
    int Scores[] = {5,5}; // player scored
    CMancalaBoard TheBoard(0, Pits, Scores); // initialize the class
    
    EXPECT_TRUE(TheBoard.Move(0,4));
    EXPECT_EQ(TheBoard.PlayerTurn(),1);
    EXPECT_EQ(TheBoard.PlayerScore(0),6);
    EXPECT_EQ(TheBoard.PitStoneCount(0,3),4);
    EXPECT_TRUE(TheBoard.Move(1,3));
    EXPECT_EQ(TheBoard.PlayerTurn(),0);
//    EXPECT_FALSE(TheBoard.Move(0,1));
//    EXPECT_FALSE(TheBoard.Move(1,1));
    EXPECT_EQ(TheBoard.PlayerScore(1),6);
    EXPECT_EQ(TheBoard.PitStoneCount(1,3),0);
    
    EXPECT_EQ(TheBoard.ToString(),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 0 | 4 | 4 | 3 | 2 |   |\n"
              "| 6 |-------------------| 6 |\n"
              "|   | 2 | 3 | 4 | 0 | 6 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(TheBoard.GameOver());
    EXPECT_EQ(TheBoard.ToString(), std::string(TheBoard));
}

TEST(MancalaBoardTest, DoubleMoveTest){
    // Needs to test that double move is correct
    
    CMancalaBoard cmb; // initialize the class
    
    EXPECT_TRUE(cmb.Move(0,1));
    EXPECT_EQ(cmb.PlayerScore(0),1);
    EXPECT_EQ(cmb.PitStoneCount(0,1),0);
    EXPECT_EQ(cmb.PlayerTurn(),0);
    EXPECT_TRUE(cmb.Move(0,2));
    EXPECT_EQ(cmb.PlayerScore(0),2);
    EXPECT_EQ(cmb.PitStoneCount(0,2),0);
    EXPECT_EQ(cmb.PlayerTurn(),1);
    EXPECT_TRUE(cmb.Move(1,0));
    EXPECT_EQ(cmb.PlayerScore(1),1);
    EXPECT_EQ(cmb.PitStoneCount(1,0),0);
    EXPECT_EQ(cmb.PlayerTurn(),1);
    EXPECT_TRUE(cmb.Move(1,2));
    EXPECT_EQ(cmb.PlayerScore(1),2);
    EXPECT_EQ(cmb.PitStoneCount(1,2),0);
    EXPECT_EQ(cmb.PlayerTurn(),0);
    //    EXPECT_TRUE(cmb.Move(0,1));
    //    EXPECT_TRUE(cmb.Move(1,1));

    EXPECT_EQ(std::string(cmb),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 6 | 6 | 0 | 1 | 5 |   |\n"
              "| 2 |-------------------| 2 |\n"
              "|   | 0 | 6 | 0 | 6 | 6 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(cmb.GameOver());
    EXPECT_EQ(cmb.ToString(), std::string(cmb));
    
    // case 2
    int Pits[] = {1,2,3,4,5,1,2,3,4,5}; // the selection for each pits
    int Scores[] = {5,5}; // player scored
    CMancalaBoard TheBoard(0, Pits, Scores); // initialize the class
    
    EXPECT_TRUE(TheBoard.Move(0,2));
    EXPECT_EQ(TheBoard.PlayerScore(0),6);
    EXPECT_EQ(TheBoard.PitStoneCount(0,2),0);
    EXPECT_EQ(TheBoard.PlayerTurn(),0);
    EXPECT_TRUE(TheBoard.Move(0,1));
    EXPECT_EQ(TheBoard.PlayerTurn(),1);
    
    EXPECT_TRUE(TheBoard.Move(1,2));
    EXPECT_EQ(TheBoard.PlayerScore(1),6);
    EXPECT_EQ(TheBoard.PitStoneCount(1,2),0);
    EXPECT_EQ(TheBoard.PlayerTurn(),1);
    EXPECT_TRUE(TheBoard.Move(1,1));
    EXPECT_EQ(TheBoard.PlayerTurn(),0);
    
    EXPECT_EQ(TheBoard.ToString(),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 6 | 6 | 1 | 0 | 1 |   |\n"
              "| 6 |-------------------| 6 |\n"
              "|   | 1 | 0 | 1 | 6 | 6 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(TheBoard.GameOver());
    EXPECT_EQ(TheBoard.ToString(), std::string(TheBoard));
    
    // case 3
    int Pits_1[] = {0,0,0,0,0,1,2,3,4,5}; // the selection for each pits
    int Scores_1[] = {12,13}; // player scored
    CMancalaBoard TheBoard_1(0, Pits_1, Scores_1); // initialize the class
    
    EXPECT_FALSE(TheBoard_1.Move(0,2));
    EXPECT_EQ(TheBoard_1.PlayerScore(0),12);
    EXPECT_EQ(TheBoard_1.PitStoneCount(0,2),0);
    EXPECT_EQ(TheBoard_1.PlayerTurn(),0);
    EXPECT_TRUE(TheBoard_1.Move(1,0));
    EXPECT_EQ(TheBoard_1.PlayerTurn(),1);
    
    EXPECT_EQ(TheBoard_1.ToString(),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 0 | 0 | 0 | 0 | 0 |   |\n"
              "|12 |-------------------|13 |\n"
              "|   | 0 | 3 | 3 | 4 | 5 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(TheBoard_1.GameOver());
    EXPECT_EQ(TheBoard_1.ToString(), std::string(TheBoard_1));
}

TEST(MancalaBoardTest, StealMoveTest){
    // Needs to test that stealing move works correctly
    
    // case 1 can steal
    int def_Pits [] = {3,1,5,0,1,3,6,1,0,6}; // the selection for each pits
    int def_Stores [] = {7,6}; // player scored

    CMancalaBoard cmb(0, def_Pits, def_Stores); // initialize the class

    EXPECT_TRUE(cmb.Move(0,0));
    EXPECT_EQ(cmb.PlayerScore(0),14);
    EXPECT_EQ(cmb.PitStoneCount(0,3),0);
    EXPECT_EQ(cmb.PlayerTurn(),1);
    
    EXPECT_TRUE(cmb.Move(1,2));
    EXPECT_EQ(cmb.PlayerScore(1),9);
    EXPECT_EQ(cmb.PitStoneCount(1,3),0);
    EXPECT_EQ(cmb.PlayerTurn(),0);

    EXPECT_EQ(std::string(cmb),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 1 | 0 | 6 | 0 | 0 |   |\n"
              "|14 |-------------------| 9 |\n"
              "|   | 3 | 0 | 0 | 0 | 6 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(cmb.GameOver()); // check the game winning conditions
    EXPECT_EQ(cmb.ToString(),std::string(cmb)); // check ToSting == string
    
    // case 2 cant steal
    int Pits[] = {1,0,1,4,6,1,0,1,4,6}; // the selection for each pits
    int Scores[] = {7,6}; // player scored
    CMancalaBoard TheBoard(0, Pits, Scores); // initialize the class
    
    EXPECT_FALSE(TheBoard.Move(0,5));
    EXPECT_EQ(TheBoard.PlayerScore(0),7);
    EXPECT_EQ(TheBoard.PitStoneCount(0,3),4);
    EXPECT_EQ(TheBoard.PlayerTurn(),0);
    
    EXPECT_TRUE(TheBoard.Move(1,3));
    EXPECT_EQ(TheBoard.PlayerScore(1),7);
    EXPECT_EQ(TheBoard.PitStoneCount(1,3),0);
    EXPECT_EQ(TheBoard.PlayerTurn(),1);
    
    EXPECT_EQ(TheBoard.ToString(),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 6 | 4 | 1 | 1 | 2 |   |\n"
              "| 7 |-------------------| 7 |\n"
              "|   | 1 | 0 | 1 | 0 | 7 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(TheBoard.GameOver());
    EXPECT_EQ(TheBoard.ToString(), std::string(TheBoard));


}

TEST(MancalaBoardTest, CantMoveTest){
    // Needs to test when player can't move correctly
    
    int Pits_1[] = {0,0,0,0,0,1,2,3,4,5}; // the selection for each pits
    int Scores_1[] = {12,13}; // player scored
    CMancalaBoard TheBoard_1(1, Pits_1, Scores_1); // initialize the class
    
    EXPECT_TRUE(TheBoard_1.Move(1,0));
    EXPECT_EQ(TheBoard_1.PlayerScore(1),13);
    EXPECT_EQ(TheBoard_1.PitStoneCount(1,0),0);
    EXPECT_EQ(TheBoard_1.PlayerTurn(),1);
    
    EXPECT_EQ(TheBoard_1.ToString(),
              "P1          PITS\n"
              "      5   4   3   2   1\n"
              "/---------------------------\\\n"
              "|   | 0 | 0 | 0 | 0 | 0 |   |\n"
              "|12 |-------------------|13 |\n"
              "|   | 0 | 3 | 3 | 4 | 5 |   |\n"
              "\\---------------------------/\n"
              "      1   2   3   4   5\n"
              "             PITS          P2\n");
    EXPECT_FALSE(TheBoard_1.GameOver());
    EXPECT_EQ(TheBoard_1.ToString(), std::string(TheBoard_1));
}

TEST(MancalaBoardTest, BadParametersTest){
    // Needs to check that bad parameters are handled correctly
    
    CMancalaBoard cmb;
    
    EXPECT_EQ(cmb.PitStoneCount(3,2),-1);
    EXPECT_EQ(cmb.PitStoneCount(0,100),-1);
    EXPECT_EQ(cmb.PitStoneCount(0,-100),-1);
    EXPECT_EQ(cmb.PitStoneCount(1,100),-1);
    EXPECT_EQ(cmb.PitStoneCount(1,-100),-1);
    EXPECT_EQ(cmb.PitStoneCount(-1,100),-1);
    EXPECT_EQ(cmb.PlayerScore(3),-1);
    EXPECT_EQ(cmb.PlayerScore(-1),-1);
    
}

