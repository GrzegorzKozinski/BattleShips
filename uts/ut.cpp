#include <gtest/gtest.h> 
#include "TestBoard.cpp" 
#include "TestPlayer.cpp" 
 
int main(int argc, char **argv)  
{
    ::testing::InitGoogleTest(&argc, argv);    
    return RUN_ALL_TESTS();     
}      