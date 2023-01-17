#include <gtest/gtest.h>
#include "../Headers/dynamic_stack.h"

TEST(TDynamicStack, CreateWithDefaultSize) {
	EXPECT_NO_THROW(TDynamicStack<int>());
}

TEST(TDynamicStack, CreateWith3SizeAndVerifyAll) {
	TDynamicStack<int> stack(3);

	EXPECT_TRUE(stack.IsEmpty());

	EXPECT_TRUE(!stack.IsFull());

	EXPECT_NO_THROW(stack.Push(5));
	EXPECT_NO_THROW(stack.Push(1));
	EXPECT_NO_THROW(stack.Push(7));

	EXPECT_TRUE(stack.IsFull());

	EXPECT_NO_THROW(stack.Push(10));

	EXPECT_TRUE(!stack.IsFull());

	EXPECT_EQ(stack.Pop(), 10);
	EXPECT_EQ(stack.Pop(), 7);
	EXPECT_EQ(stack.Pop(), 1);
	EXPECT_EQ(stack.Pop(), 5);

	EXPECT_ANY_THROW(stack.Pop());

	EXPECT_TRUE(stack.IsEmpty());


}