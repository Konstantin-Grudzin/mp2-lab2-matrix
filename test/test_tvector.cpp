#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> t1(5);
	t1[1] = 3; t1[2] = 3;
	TVector<int> t2(t1);
	EXPECT_EQ(t1, t2);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> t1(5);
	t1[1] = 3; t1[2] = 3;
	TVector<int> t2(t1);
	t1[0] = 2;
	EXPECT_NE(t1, t2);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> t1(3);
  ASSERT_ANY_THROW(t1[-1]);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> t1(3);
	ASSERT_ANY_THROW(t1[100000000]);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> t1(3);
	ASSERT_NO_THROW(t1 = t1);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> t1(3),t2(3);
	t1[0] = 2;
	t1[1] = 3;
	t2 = t1;
	EXPECT_EQ(t1, t2);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> t1(3), t2(2);
	t1[0] = 2;
	t1[1] = 3;
	t2 = t1;
	EXPECT_EQ(3, t2.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> t1(3), t2(2);
	t1[0] = 2;
	t1[1] = 3;
	ASSERT_NO_THROW(t2 = t1);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> t1(3), t2(3);
	t1[0] = 2;
	t1[1] = 3;
	t2[0] = 2;
	t2[1] = 3;
	EXPECT_EQ(t1, t2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> t1(3);
	t1[0] = 2;
	t1[1] = 3;
	EXPECT_EQ(t1, t1);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> t1(3),t2(2);
	t1[0] = 2;
	t1[1] = 3;
	t2[0] = 2;
	t2[1] = 3;
	EXPECT_NE(t1, t2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> t1(3), t2(3);
	t1[0] = 1;
	t1[1] = 2;
	t2[0] = 2;
	t2[1] = 3;
	t2[2] = 1;
	t1 = t1 + 1;
	EXPECT_EQ(t1, t2);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> t1(3), t2(3);
	t1[0] = 3;
	t1[1] = 4;
	t1[2] = 2;
	t2[0] = 2;
	t2[1] = 3;
	t2[2] = 1;
	t1 = t1 - 1;
	EXPECT_EQ(t1, t2);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> t1(3), t2(3);
	t1[0] = 2;
	t1[1] = 3;
	t1[2] = 1;
	t2[0] = 4;
	t2[1] = 6;
	t2[2] = 2;
	t1 = t1 * 2;
	EXPECT_EQ(t1, t2);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> t1(3), t2(3);
	t1[0] = 2;
	t1[1] = 3;
	t1[2] = 1;
	t2[0] = 4;
	t2[1] = 6;
	t2[2] = 2;
	t1 = t1 + t1;
	EXPECT_EQ(t1, t2);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> t1(3), t2(2),t3(3);
	t1[0] = 2;
	t1[1] = 3;
	t1[2] = 1;
	t2[0] = 4;
	t2[1] = 6;

	t3[0] = 6;
	t3[1] = 9;
	t3[2] = 1;

	t1 = t1 + t2;
	EXPECT_EQ(t1, t3);
}


TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> t1(3), t2(3);
	t1[0] = 2;
	t1[1] = 3;
	t1[2] = 1;
	t2[0] = 0;
	t2[1] = 0;
	t2[2] = 0;
	t1 = t1 - t1;
	EXPECT_EQ(t1, t2);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> t1(3), t2(3);
	t1[0] = 2;
	t1[1] = 3;
	t1[2] = 1;
	t2[0] = 0;
	t2[1] = 0;
	t1 = t1 - t2;
	EXPECT_EQ(t1, t1);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> t1(3);
	t1[0] = 2;
	t1[1] = 3;
	t1[2] = 1;
	int ans = t1*t1;
	EXPECT_EQ(ans, 14);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> t1(3),t2(2);
	t1[0] = 2;
	t1[1] = 3;
	t1[2] = 1;
	t2[0] = 2;
	t2[1] = 3;
	int ans = t1 * t2;
	EXPECT_EQ(ans, 13);
}


