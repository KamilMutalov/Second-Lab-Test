#include "defines.h"
#include "constructors.h"
#include "math_ops.h"

void overflow_error()
{
	printf("---------------------\n");
	printf("Error: overflow error\a\n");
	printf("---------------------\n");
	exit(-1);
}

void invalid_number_error()
{
	printf("---------------------\n");
	printf("Error: invalid number\a\n");
	printf("---------------------\n");
	exit(-1);
}

void printf_value(const uint1024_t big_num)
{
	int count_zeros_prev = 0;
	int count_zeros_curr;
	int delta_curr_prev;
	
	for (int i = big_num.count_digits - 1; i >= 0; --i)
	{
		count_zeros_curr = GRADES_OF_HEX_IN_U1024 * i;

		delta_curr_prev = count_zeros_prev - count_zeros_curr - snprintf(NULL, 0, "%X", big_num.coeffs[i]);

		for (int j = 0; j < delta_curr_prev; ++j)
		{
			printf("%X", 0);
		}
		printf("%X", big_num.coeffs[i]);
		count_zeros_prev = count_zeros_curr;
	}
	
}

void scanf_value(uint1024_t* big_num)
{
	*big_num = from_uint32_t(0);
	char buffer[257];
	if (!scanf("%s", buffer))
	{
		invalid_number_error();
	}

	int buff_length = strlen(buffer);
	big_num->count_digits = buff_length / GRADES_OF_HEX_IN_U1024;

	if (strlen(buffer) % GRADES_OF_HEX_IN_U1024)
	{
		big_num->count_digits += 1;
	}

	for (int i = 0; i < big_num->count_digits; ++i)
	{
		buff_length = strlen(buffer);
		if (buff_length <= GRADES_OF_HEX_IN_U1024)
		{
			big_num->coeffs[i] = hex_to_int(buffer);
			return;
		}

		char hex_digit[9];
		int position_digit = buff_length - GRADES_OF_HEX_IN_U1024;
		sprintf(hex_digit, "%s", buffer + position_digit);
		buffer[position_digit] = '\0';
		
		big_num->coeffs[i] = hex_to_int(hex_digit);
	}
	

}

int main(int argc, char** argv)
{
	
	uint1024_t x;
	uint1024_t y;
	printf("Set first number\n");
	scanf_value(&x);
	
	printf_value(pow_op(x, 5));
	return 0;
}
