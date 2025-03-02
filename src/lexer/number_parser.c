#include "baa/lexer/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Forward declaration for baa_is_arabic_digit
bool baa_is_arabic_digit(wchar_t c);

// Arabic-Indic digits (٠١٢٣٤٥٦٧٨٩)
static const wchar_t ARABIC_DIGITS[] = {0x0660, 0x0661, 0x0662, 0x0663, 0x0664,
                                        0x0665, 0x0666, 0x0667, 0x0668, 0x0669};

// Convert Arabic-Indic digit to decimal value
static int arabic_to_decimal(wchar_t c)
{
    for (int i = 0; i < 10; i++)
    {
        if (c == ARABIC_DIGITS[i])
        {
            return i;
        }
    }
    return -1; // Not an Arabic digit
}

bool baa_is_digit(wchar_t c)
{
    return (c >= '0' && c <= '9') || baa_is_arabic_digit(c);
}

bool baa_is_decimal_digit(wchar_t c)
{
    return baa_is_digit(c) || c == '.' || c == L'٫'; // Support both . and Arabic decimal separator
}

bool baa_is_arabic_digit(wchar_t c)
{
    return (c >= 0x0660 && c <= 0x0669); // Arabic-Indic digits range
}

bool baa_is_number_start(wchar_t c)
{
    return baa_is_digit(c) || c == '.' || c == L'٫';
}

static BaaNumberError parse_integer_part(const wchar_t *text, size_t *pos, size_t length, long long *value)
{
    long long result = 0;
    bool has_digits = false;

    while (*pos < length && baa_is_digit(text[*pos]))
    {
        has_digits = true;
        int digit;

        if (baa_is_arabic_digit(text[*pos]))
        {
            digit = arabic_to_decimal(text[*pos]);
        }
        else
        {
            digit = text[*pos] - '0';
        }

        // Check for overflow
        if (result > (LLONG_MAX - digit) / 10)
        {
            return BAA_NUM_OVERFLOW;
        }

        result = result * 10 + digit;
        (*pos)++;
    }

    if (!has_digits)
    {
        return BAA_NUM_INVALID_FORMAT;
    }

    *value = result;
    return BAA_NUM_SUCCESS;
}

static BaaNumberError parse_decimal_part(const wchar_t *text, size_t *pos, size_t length, double *value)
{
    double result = 0;
    double place = 0.1;
    bool has_digits = false;

    while (*pos < length && baa_is_digit(text[*pos]))
    {
        has_digits = true;
        int digit;

        if (baa_is_arabic_digit(text[*pos]))
        {
            digit = arabic_to_decimal(text[*pos]);
        }
        else
        {
            digit = text[*pos] - '0';
        }

        result += digit * place;
        place /= 10;
        (*pos)++;
    }

    if (!has_digits)
    {
        return BAA_NUM_INVALID_FORMAT;
    }

    *value = result;
    return BAA_NUM_SUCCESS;
}

BaaNumber *baa_parse_number(const wchar_t *text, size_t length, BaaNumberError *error)
{
    if (!text || length == 0)
    {
        if (error)
            *error = BAA_NUM_INVALID_FORMAT;
        return NULL;
    }

    BaaNumber *number = (BaaNumber *)malloc(sizeof(BaaNumber));
    if (!number)
    {
        if (error)
            *error = BAA_NUM_MEMORY_ERROR;
        return NULL;
    }

    // Copy the raw text
    wchar_t *raw_text = (wchar_t *)malloc((length + 1) * sizeof(wchar_t));
    if (!raw_text)
    {
        free(number);
        if (error)
            *error = BAA_NUM_MEMORY_ERROR;
        return NULL;
    }
    wcsncpy(raw_text, text, length);
    raw_text[length] = L'\0';

    number->raw_text = raw_text;
    number->text_length = length;

    size_t pos = 0;
    bool is_decimal = false;
    BaaNumberError parse_error;

    // Check for decimal point
    for (size_t i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == L'٫')
        {
            if (is_decimal)
            {
                free(raw_text);
                free(number);
                if (error)
                    *error = BAA_NUM_MULTIPLE_DOTS;
                return NULL;
            }
            is_decimal = true;
        }
    }

    if (!is_decimal)
    {
        // Parse integer
        long long int_value;
        parse_error = parse_integer_part(text, &pos, length, &int_value);

        if (parse_error == BAA_NUM_SUCCESS)
        {
            number->type = BAA_NUM_INTEGER;
            number->int_value = int_value;
        }
    }
    else
    {
        // Parse decimal number
        long long int_part = 0;
        double dec_part = 0.0;

        // Parse integer part
        parse_error = parse_integer_part(text, &pos, length, &int_part);
        if (parse_error == BAA_NUM_SUCCESS)
        {
            // Skip decimal point
            pos++;

            // Parse decimal part
            parse_error = parse_decimal_part(text, &pos, length, &dec_part);
            if (parse_error == BAA_NUM_SUCCESS)
            {
                number->type = BAA_NUM_DECIMAL;
                number->decimal_value = (double)int_part + dec_part;
            }
        }
    }

    if (parse_error != BAA_NUM_SUCCESS)
    {
        free(raw_text);
        free(number);
        if (error)
            *error = parse_error;
        return NULL;
    }

    if (error)
        *error = BAA_NUM_SUCCESS;
    return number;
}

void baa_free_number(BaaNumber *number)
{
    if (number)
    {
        if (number->raw_text)
        {
            free((void *)number->raw_text);
        }
        free(number);
    }
}

const wchar_t *baa_number_error_message(BaaNumberError error)
{
    switch (error)
    {
    case BAA_NUM_SUCCESS:
        return L"نجاح"; // Success
    case BAA_NUM_OVERFLOW:
        return L"الرقم كبير جداً"; // Number too large
    case BAA_NUM_INVALID_CHAR:
        return L"حرف غير صالح في الرقم"; // Invalid character in number
    case BAA_NUM_MULTIPLE_DOTS:
        return L"نقاط عشرية متعددة"; // Multiple decimal points
    case BAA_NUM_INVALID_FORMAT:
        return L"تنسيق رقم غير صالح"; // Invalid number format
    case BAA_NUM_MEMORY_ERROR:
        return L"خطأ في الذاكرة"; // Memory error
    default:
        return L"خطأ غير معروف"; // Unknown error
    }
}
