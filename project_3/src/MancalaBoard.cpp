#include "MancalaBoard.h"
#include <iostream>

CMancalaBoard::CMancalaBoard(){
    DTurn = 0;
    for(int Index = 0; Index < MANCALA_TOTAL_PITS; Index++){
        DPits[Index] = 4;
    }
    for(int Index = 0; Index < MANCALA_PLAYERS; Index++){
        DStores[Index] = 0;
    }
}

CMancalaBoard::CMancalaBoard(int turn, const int pits[MANCALA_TOTAL_PITS], const int stores[MANCALA_PLAYERS]){
    DTurn = turn;
    for(int Index = 0; Index < MANCALA_TOTAL_PITS; Index++){
        DPits[Index] = pits[Index];
    }
    for(int Index = 0; Index < MANCALA_PLAYERS; Index++){
        DStores[Index] = stores[Index];
    }
}

void CMancalaBoard::ResetBoard(){
    DTurn = 0;
    for(int Index = 0; Index < MANCALA_TOTAL_PITS; Index++){
        DPits[Index] = 4;
    }
    for(int Index = 0; Index < MANCALA_PLAYERS; Index++){
        DStores[Index] = 0;
    }
}

int CMancalaBoard::PlayerTurn() const{
    return DTurn;
}

int CMancalaBoard::PlayerScore(int player) const{
    if( (player < 0) or (player >= MANCALA_PLAYERS))
    { // bad parameter of players
        return -1;
    }
    else{
        return DStores[player];
    }
}

int CMancalaBoard::PitStoneCount(int player, int pit){
    if(((pit < 0) or (pit >= MANCALA_PIT_SLOTS) or (player < 0)) or ((player >= MANCALA_PLAYERS)))
    { // bad parameter of players
        return -1;
    }
    else{
         return DPits[player * MANCALA_PIT_SLOTS + pit]; //what is stored in dpit in pit index
    }
}

bool CMancalaBoard::GameOver() const{
    for(int Index = 0; Index < MANCALA_TOTAL_PITS; Index++){
        if(DPits[Index]){
            return false;
        }
    }
    return true;
}

std::string CMancalaBoard::ToString() const{
    std::string ReturnString  = "P1          PITS\n";
    ReturnString += "      5   4   3   2   1\n";
    ReturnString += "/---------------------------\\\n";
    ReturnString += "|   |";
    for(int Index = MANCALA_PIT_SLOTS-1; Index >= 0; Index--){
        if(DPits[Index] >= 10){
            ReturnString += std::to_string(DPits[Index]) + " |";
        }
        else{
            ReturnString += std::string(" ") + std::to_string(DPits[Index]) + " |";
        }
    }
    ReturnString += "   |\n|";
    
    if(DStores[0] >= 10){
        ReturnString += std::to_string(DStores[0]);
    }
    else{
        ReturnString += std::string(" ") + std::to_string(DStores[0]);
    }
    ReturnString += " |-------------------|";
    if(DStores[1] >= 10){
        ReturnString += std::to_string(DStores[1]);
    }
    else{
        ReturnString += std::string(" ") + std::to_string(DStores[1]);
    }
    ReturnString += " |\n|   |";
    for(int Index = 0; Index < MANCALA_PIT_SLOTS; Index++){
        if(DPits[MANCALA_PIT_SLOTS + Index] >= 10){
            ReturnString += std::to_string(DPits[MANCALA_PIT_SLOTS + Index]) + " |";
        }
        else{
            ReturnString += std::string(" ") + std::to_string(DPits[MANCALA_PIT_SLOTS + Index]) + " |";
        }
    }
    ReturnString += "   |\n";
    ReturnString += "\\---------------------------/\n";
    ReturnString += "      1   2   3   4   5\n";
    ReturnString += "             PITS          P2\n";
    
    return ReturnString;
    
    //    std::string ReturnString  = "P1          PITS\n";
    //    ReturnString += "      5   4   3   2   1\n";
    //    ReturnString += "/---------------------------\\\n";
    //    ReturnString += "|   |";
    //    for(int Index = 0; Index < MANCALA_PIT_SLOTS; Index++){
    //        if(DPits[Index] >= 10){
    //            ReturnString += std::to_string(DPits[Index]) + " |";
    //        }
    //        else{
    //            ReturnString += std::string(" ") + std::to_string(DPits[Index]) + " |";
    //        }
    //    }
    //    ReturnString += "   |\n|";
    //
    //    if(DStores[0] > 10){
    //        ReturnString += std::to_string(DStores[0]);
    //    }
    //    else{
    //        ReturnString += std::string(" ") + std::to_string(DStores[0]);
    //    }
    //    ReturnString += " |-------------------|";
    //    if(DStores[1] >= 10){
    //        ReturnString += std::to_string(DStores[1]);
    //    }
    //    else{
    //        ReturnString += std::string(" ") + std::to_string(DStores[1]);
    //    }
    //    ReturnString += " |\n|   |";
    //    for(int Index = 0; Index < MANCALA_PIT_SLOTS; Index++){
    //        if(DPits[MANCALA_PIT_SLOTS + Index] >= 10){
    //            ReturnString += std::to_string(DPits[MANCALA_PIT_SLOTS + Index]) + " |";
    //        }
    //        else{
    //            ReturnString += std::string(" ") + std::to_string(DPits[MANCALA_PIT_SLOTS + Index]) + " |";
    //        }
    //    }
    //    ReturnString += "   |\n";
    //    ReturnString += "\\---------------------------/\n";
    //    ReturnString += "      1   2   3   4   5\n";
    //    ReturnString += "             PITS          P2\n";
    //
    //    return ReturnString;
}

CMancalaBoard::operator std::string() const{
    std::string ReturnString  = "P1          PITS\n";
    ReturnString += "      5   4   3   2   1\n";
    ReturnString += "/---------------------------\\\n";
    ReturnString += "|   |";
    for(int Index = MANCALA_PIT_SLOTS-1; Index >= 0; Index--){
        if(DPits[Index] >= 10){
            ReturnString += std::to_string(DPits[Index]) + " |";
        }
        else{
            ReturnString += std::string(" ") + std::to_string(DPits[Index]) + " |";
        }
    }
    ReturnString += "   |\n|";
    
    if(DStores[0] >= 10){
        ReturnString += std::to_string(DStores[0]);
    }
    else{
        ReturnString += std::string(" ") + std::to_string(DStores[0]);
    }
    ReturnString += " |-------------------|";
    if(DStores[1] >= 10){
        ReturnString += std::to_string(DStores[1]);
    }
    else{
        ReturnString += std::string(" ") + std::to_string(DStores[1]);
    }
    ReturnString += " |\n|   |";
    for(int Index = 0; Index < MANCALA_PIT_SLOTS; Index++){
        if(DPits[MANCALA_PIT_SLOTS + Index] >= 10){
            ReturnString += std::to_string(DPits[MANCALA_PIT_SLOTS + Index]) + " |";
        }
        else{
            ReturnString += std::string(" ") + std::to_string(DPits[MANCALA_PIT_SLOTS + Index]) + " |";
        }
    }
    ReturnString += "   |\n";
    ReturnString += "\\---------------------------/\n";
    ReturnString += "      1   2   3   4   5\n";
    ReturnString += "             PITS          P2\n";
    
    return ReturnString;
}

bool CMancalaBoard::Move(int player, int pit){
    
    
    if((pit < 0) or (pit >= MANCALA_PIT_SLOTS))
    { // bad parameter of pits
        return false;
    }
    if( (player < 0) or (player >= MANCALA_PLAYERS))
    { // bad parameter of players
        return false;
    }
    
    int PitIndex = player * MANCALA_PIT_SLOTS + pit; // what pit you choose
    
    if(DPits[PitIndex] == 0) // if the player choose a empty pit slot
    {
        return false;
    }
    
    int Stones = DPits[PitIndex];// how many stones in that slot temp store the stones
    int LastPitDrop = PitIndex; // last time u played is this pit
    DPits[PitIndex] = 0; // pit slot is empty
    
    //std::cout<<"@ line "<<__LINE__<<" "<<Stones<<std::endl;
    bool isScored = false; // did u last put it in the score board
    bool isTurned = true; // it's your not turn anymore because it change the player
    
    while(Stones > 1) // exit when you have 1 stone left or 0 stone
    {
        PitIndex++;
        // 7 / 5 = 2 != 0
        // 10
        if((PitIndex % MANCALA_PIT_SLOTS) == 0) // check if it's got to score board
        {
            // 0 == 10/5 - 1 = 1 false
            // 1 == 10/5 -1 =1 true
            // check the right player's score board
            if(player == (PitIndex / MANCALA_PIT_SLOTS) - 1)
            {
                DStores[player]++;
                Stones--;
                isScored = true;
            }
        }
        // 7 / 10 = 7
        // 8
        // 9
        // 10 / 10 = 0
        // index = 0
        PitIndex %= MANCALA_TOTAL_PITS; // 7 only use when u above 10
        if(Stones > 1) // if(stone is not 0) we need to put stone in the pit
        {
            isScored = false;
            DPits[PitIndex]++; // increasing the value of the pit
            Stones--;// losing 1 stone
            LastPitDrop = PitIndex; // what u drop last time
        }
        else
        {
            PitIndex--;
        }
        
    }// exit when you have 1 stone left or 0 stone
    
    
    // statring check special cases
    PitIndex++;
    
    // 7/10 = 7
    
    // PitIndex %= MANCALA_TOTAL_PITS;// it won't do anything check if u go above 10 set it to 0
    // double move
    if(Stones == 1)
    {
        // checking if we got to store board
        if((PitIndex % MANCALA_PIT_SLOTS) == 0){
            // 0 == 5/5-1 = 0
            if((player == (PitIndex / MANCALA_PIT_SLOTS) - 1) and !isScored){
                DStores[player]++;
                Stones--;
                isTurned = false;
                // 1 - 1 = 0
                // change the player
                //DTurn = 1 - DTurn;
            }
        }
        PitIndex %= MANCALA_TOTAL_PITS;
    }
    
    // steal move
    if(DPits[PitIndex] == 0)// check if the last pit slot is empty
    {
        // doesnt check for how many stones
        //std::cout<<"@ line "<<__LINE__<<std::endl;
        if((PitIndex >= 0 and PitIndex <= 4 and player == 0) or (PitIndex >= 5 and PitIndex <= 9 and player == 1)) // check if it's in player side of the pit slot
        {
            int OppositeSide = MANCALA_TOTAL_PITS - 1  - PitIndex;// opposite index
            DStores[player] += DPits[OppositeSide] + 1; // it steals all from the opposite index and 1 we dropped
            DPits[OppositeSide] = 0; // pit slot is 0 only opposited 1
            Stones = 0;
        }
        else if(Stones)
        {
            DPits[PitIndex]++;
            Stones--;
            LastPitDrop = PitIndex;
        }
    }
    if(Stones) // if stone != 0
    {
        DPits[PitIndex]++; // drop 1
        Stones--;// stone - 1
        LastPitDrop = PitIndex;// Last pit = what we dropped we dont have any stones
    }
    // 5 = 5 or 6!= 5
    // 1 = 1 - 1 = 0 ;
    // turn = 0 change player
    // DTurn = 1 - DTurn; // change player turn it your turn here
    
    // test if 1 player gets all 0 in every pit slot
    int pits = 0;
    int total = 0;
    int modifier = 0;
    // if it's player 1 start with index 5
    // check my self
    if(DTurn == 1)// player 2
    {
        modifier = 5;
    }
    // check every pits slots for the player
    for(pits; pits + modifier < MANCALA_PIT_SLOTS + modifier; pits++)
    {
        total += DPits[pits + modifier]; // add to total
    }
    if(total == 0)
    {
        isTurned = true;
    }
    // check the other player
    total = 0;
    modifier = 5;
    // if it's player 1 start with index 5
    if(DTurn == 1)// player 2
    {
        modifier = 0;
    }
    // check every pits slots for the player
    for(pits = 0; pits + modifier < MANCALA_PIT_SLOTS + modifier; pits++)
    {
        total += DPits[pits + modifier]; // add to total
    }
    if(total == 0)
    {
        isTurned = false;
    }
    
    if(isTurned == true)
    {
        DTurn = 1 - DTurn;
    }
    return true;
}
