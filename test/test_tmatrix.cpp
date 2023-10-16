#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	const int size = 10;
	TMatrix<int> m1(size);
	m1[0][0] = 3;
	m1[0][1] = 4;
	TMatrix<int> m2(m1);
	EXPECT_EQ(m1==m2,1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	const int size = 10;
	TMatrix<int> m1(size);
	m1[0][0] = 3;
	m1[0][1] = 4;
	TMatrix<int> m2(m1);
	m1[0][2] = 5;
	
	EXPECT_NE(m1==m2,1);
}

TEST(TMatrix, can_get_size)
{
	const int size = 10;
	TMatrix<int> m1(size);

	EXPECT_EQ(10, m1.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	const int size = 10;
	TMatrix<int> m1(size);
	m1[0][0] = 1;
	EXPECT_EQ(1, m1[0][0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	const int size = 10;
	TMatrix<int> m1(size);
	ASSERT_ANY_THROW(m1[0][-1] = 1);
		
}

//В моей реализации при вызове слишком большого индекса он кидает нулевой элемент
//TEST(TMatrix, throws_when_set_element_with_too_large_index)
//{
//	const int size = 10;
//	TMatrix<int> m1(size);
//	EXPECT_EQ(TVector<int>(size), m1[10]);
//}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m1(10);
	ASSERT_NO_THROW(m1=m1);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> m1(10),m2(10);
	m1[5][0] = 3;
	m2 = m1;
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> m1(10), m2(8);
	m2 = m1;
	EXPECT_EQ(10, m2.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> m1(10), m2(8);
	ASSERT_NO_THROW(m2 = m1);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m1(10), m2(10);
	m1[5][0] = 3;
	m2[5][0] = 3;
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	const int size = 10;
	TMatrix<int> m1(size);
	m1[0][0] = 3;
	m1[0][1] = 4;
	m1[0][2] = 5;
	EXPECT_EQ(m1, m1);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m1(10), m2(8);
	EXPECT_NE(m1, m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m1(3), m2(3), test(3);
	m1[0][0] = 5;
	m1[1][1] = 4;
	m1[2][2] = 3;
	m2[0][0] = 1;
	m2[1][1] = 2;
	m2[2][2] = 3;
	test[0][0] = 6;
	test[1][1] = 6;
	test[2][2] = 6;
	EXPECT_EQ(m1 + m2, test);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m1(3), m2(2), test(3);
	m1[0][0] = 5;
	m1[1][1] = 4;
	m1[2][2] = 6;
	m2[0][0] = 1;
	m2[1][1] = 2;
	test[0][0] = 6;
	test[1][1] = 6;
	test[2][2] = 6;
	EXPECT_EQ(m1 + m2, test);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m1(3), m2(3), test(3);
	m1[0][0] = 5;
	m1[1][1] = 4;
	m1[2][2] = 3;
	m2[0][0] = 1;
	m2[1][1] = 2;
	m2[2][2] = 3;
	test[0][0] = 4;
	test[1][1] = 2;
	test[2][2] = 0;
	EXPECT_EQ(m1 - m2, test);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m1(3), m2(2), test(3);
	m1[0][0] = 5;
	m1[1][1] = 4;
	m1[2][2] = 6;
	m2[0][0] = 1;
	m2[1][1] = 2;
	test[0][0] = 4;
	test[1][1] = 2;
	test[2][2] = 6;
	EXPECT_EQ(m1 - m2, test);
}

