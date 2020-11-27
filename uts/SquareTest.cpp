#include "../src/Square.hpp"
#include "gtest/gtest.h"
 
TEST(SquareRootTest, PositiveNos) 
    { 
    ASSERT_EQ(6, squarefun(36.0));
    ASSERT_EQ(18.0, squarefun(324.0));
    ASSERT_EQ(25.4, squarefun(645.16));
    ASSERT_EQ(0, squarefun(0.0));
    }