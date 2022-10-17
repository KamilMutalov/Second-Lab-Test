#include <stdio.h>

// Discount coefficients and price for discount
double _discount_3_coef = 0.97;
double _discount_3_price = 500.0;
double _discount_5_coef = 0.95;
double _discount_5_price = 1000.0;
double _discount_8_coef = 0.92;
double _discount_8_price = 1500.0;

int main()
{
    double _purchase_price, _result;
    int _discount;

    printf("Enter the purchase price\n");
    scanf("%lf", &_purchase_price);

    // -1 because the inequality ( > 500, > 1000, > 1500) is strict
    int _discount_type = (_purchase_price -1) / 500;

    switch (_discount_type)
    {
        case 0:
            _discount = 0;
            _result = _purchase_price;
            break;
        
        case 1:
            _discount = 3;
            _result = _purchase_price * _discount_3_coef;
            break;
            
        case 2:
            _discount = 5;
            _result = _purchase_price * _discount_5_coef;
            break;
            
        default:
            _discount = 8;
            _result = _purchase_price * _discount_8_coef;
            break;
    }

    printf("Your discount is %d\n", _discount);
    printf("Total price after discount is %.2lf\n", _result);

    return 0;
}
