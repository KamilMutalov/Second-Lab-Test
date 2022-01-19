#include "Lab2.h"
#include <gtest/gtest.h>

TEST(IO, min_val)
{
	uint1024_t number;
	char* expected = "0";
	scanf_value(&number, expected);
	char* result = printf_value(number);
	EXPECT_STREQ(expected, result);
}

TEST(IO, rand_val)
{
	uint1024_t number;
	char* expected = "123456789112233445566778899111222333444555666777888999";
	scanf_value(&number, expected);
	char* result = printf_value(number);
	EXPECT_STREQ(expected, result);
}

TEST(IO, max_val)
{
	uint1024_t number;
	char* expected = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	// 256 * 'F'
	scanf_value(&number, expected);
	char* result = printf_value(number);
	EXPECT_STREQ(expected, result);
}


TEST(CONSTR, min_val)
{
	uint1024_t number;
	int value = 0;
	number = from_uint32_t(value);
	char* expected = "0";
	char* result = printf_value(number);
	EXPECT_STREQ(expected, result);
}

TEST(CONSTR, rand_val)
{
	uint1024_t number;
	int value = 123456789;
	number = from_uint32_t(value);
	char* expected = "75BCD15";
	char* result = printf_value(number);
	EXPECT_STREQ(expected, result);
}

TEST(CONSTR, max_val)
{
	uint1024_t number;
	int value = INT_MAX;
	number = from_uint32_t(value);
	char* expected = "7FFFFFFF";
	char* result = printf_value(number);
	EXPECT_STREQ(expected, result);
}


TEST(ADD, min_val)
{
	uint1024_t first, second;
	char* input_first = "0";
	char* input_second = "0";
	scanf_value(&first, input_first);
	scanf_value(&second, input_second);
	char* expected = "0";
	char* result = printf_value(add_op(first, second));
	EXPECT_STREQ(expected, result);
}

TEST(ADD, rand_val)
{
	uint1024_t first, second;
	char* input_first = "123456789112233445566778899111222333444555666777888999";
	char* input_second = "987654321998877665544332211999888777666555444333222111";
	scanf_value(&first, input_first);
	scanf_value(&second, input_second);
	char* expected = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	char* result = printf_value(add_op(first, second));
	EXPECT_STREQ(expected, result);
}

TEST(ADD, max_val)
{
	uint1024_t first, second;
	char* input_first = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	char* input_second = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	// Both are 128 * 'F'
	scanf_value(&first, input_first);
	scanf_value(&second, input_second);
	char* expected = "1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE";
	char* result = printf_value(add_op(first, second));
	EXPECT_STREQ(expected, result);
}


TEST(SUB, min_val)
{
	uint1024_t first, second;
	char* input_first = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	char* input_second = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	// Both are 128 * 'F'
	scanf_value(&first, input_first);
	scanf_value(&second, input_second);
	char* expected = "0";
	char* result = printf_value(subtr_op(first, second));
	EXPECT_STREQ(expected, result);
}

TEST(SUB, rand_val)
{
	uint1024_t first, second;
	char* input_first = "123456789112233445566778899111222333444555666777888999";
	char* input_second = "987654321998877665544332211999888777666555444333222111";
	scanf_value(&first, input_first);
	scanf_value(&second, input_second);
	char* expected = "8641FDB9888664421FFDDBB9978888666444221FFFDDDBBB999778";
	char* result = printf_value(subtr_op(first, second));
	EXPECT_STREQ(expected, result);
}

TEST(SUB, max_val)
{
	uint1024_t first, second;
	char* input_first = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	// 128 * 'F'
	char* input_second = "0";
	scanf_value(&first, input_first);
	scanf_value(&second, input_second);
	char* expected = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	// 128 * 'F'
	char* result = printf_value(subtr_op(first, second));
	EXPECT_STREQ(expected, result);
}


TEST(MULT, min_val)
{
	uint1024_t first, second;
	char* input_first = "0";
	char* input_second = "0";
	scanf_value(&first, input_first);
	scanf_value(&second, input_second);
	char* expected = "0";
	char* result = printf_value(mult_op(first, second));
	EXPECT_STREQ(expected, result);
}

TEST(MULT, rand_val)
{
	uint1024_t first, second;
	char* input_first = "123456789112233445566778899111222333444555666777888999";
	char* input_second = "987654321998877665544332211999888777666555444333222111";
	scanf_value(&first, input_first);
	scanf_value(&second, input_second);
	char* expected = "AD77D742E200B90AF0A4692CCCD785198D74E1954E66C404822277E26D3C86288DBDCDAEBF158384CCCCDF036A06D82DDDE4B1FDC29";
	char* result = printf_value(mult_op(first, second));
	EXPECT_STREQ(expected, result);
}

TEST(MULT, max_val)
{
	uint1024_t first, second;
	char* input_first = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	char* input_second = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	// Both are 128 * 'F'
	scanf_value(&first, input_first);
	scanf_value(&second, input_second);
	char* expected = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
	char* result = printf_value(mult_op(first, second));
	EXPECT_STREQ(expected, result);
}


TEST(POW, min_val)
{
	uint1024_t number;
	int grade = 0;
	char* input = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	// 256 * 'F'
	scanf_value(&number, input);
	char* expected = "1";
	char* result = printf_value(pow_op(number, grade));
	EXPECT_STREQ(expected, result);
}

TEST(POW, rand_val)
{
	uint1024_t number;
	int grade = 3;
	char* input = "123456789112233445566778899111222333444555666777888999";
	scanf_value(&number, input);
	char* expected = "1790FC50EADC673B7A30F836754F89730693D96AA0764E1D2E107E558B15F2DB08EC788EFD8ABE5CA46239E59C1EDC92E40B5F657E2D7A4798230AB217D9164B52EE73F5672909368A438E9AE1581189";
	char* result = printf_value(pow_op(number, grade));
	EXPECT_STREQ(expected, result);
}

TEST(POW, max_val)
{
	uint1024_t number;
	int grade = 2;
	char* input = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	// 128 * 'F'
	scanf_value(&number, input);
	char* expected = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
	char* result = printf_value(pow_op(number, grade));
	EXPECT_STREQ(expected, result);
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}