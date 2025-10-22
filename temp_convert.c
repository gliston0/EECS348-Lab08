// EECS 348 • Lab 8 • Task 2
// temp_convert.c — convert between F/C/K, categorize, and give advisory
// Author: Gabe Liston
// Build:  gcc -Wall -Wextra -O2 -o temp_convert temp_convert.c
// Run:    ./temp_convert
#include <stdio.h>
#include <ctype.h>

static double to_c(double v, char s) {
    s = (char)toupper((unsigned char)s);
    if (s == 'C') return v;
    if (s == 'F') return (v - 32.0) * 5.0 / 9.0;
    if (s == 'K') return v - 273.15;
    return v;
}

static double from_c(double c, char t) {
    t = (char)toupper((unsigned char)t);
    if (t == 'C') return c;
    if (t == 'F') return c * 9.0 / 5.0 + 32.0;
    if (t == 'K') return c + 273.15;
    return c;
}

static const char* category_from_c(double celsius) {
    // Thresholds from the lab handout (in °C)
    if (celsius < 0.0)            return "Freezing";        // (-inf, 0)
    else if (celsius < 10.0)      return "Cold";            // [0, 10)
    else if (celsius < 25.0)      return "Comfortable";     // [10, 25)
    else if (celsius < 35.0)      return "Hot";             // [25, 35)
    else                          return "Extreme Heat";    // [35, +inf)
}

static const char* advisory_for_category(const char* cat) {
    if (cat[0] == 'F') return "Wear a warm coat.";
    if (cat[0] == 'C') {
        // Could be "Cold" or "Comfortable"
        if (cat[1] == 'o') return "Dress in layers.";
        return "Light jacket recommended.";
    }
    if (cat[0] == 'H') return "Drink lots of water!";
    return "Stay hydrated and limit outdoor activity.";
}

int main(void) {
    double value;
    char s_from, s_to;

    printf("Enter the temperature value: ");
    if (scanf("%lf", &value) != 1) {
        printf("Invalid temperature value.\n");
        return 0;
    }

    printf("Enter the original scale (C, F, or K): ");
    if (scanf(" %c", &s_from) != 1) {
        printf("Invalid scale.\n");
        return 0;
    }

    printf("Enter the scale to convert to (C, F, or K): ");
    if (scanf(" %c", &s_to) != 1) {
        printf("Invalid scale.\n");
        return 0;
    }

    s_from = (char)toupper((unsigned char)s_from);
    s_to   = (char)toupper((unsigned char)s_to);

    if ((s_from!='C'&&s_from!='F'&&s_from!='K') || (s_to!='C'&&s_to!='F'&&s_to!='K')) {
        printf("Invalid scale. Use C, F, or K.\n");
        return 0;
    }
    if (s_from == 'K' && value < 0.0) {
        printf("Invalid temperature: Kelvin cannot be negative.\n");
        return 0;
    }

    // Convert
    double c_in      = to_c(value, s_from);
    double converted = from_c(c_in, s_to);

    // Categorize based on the converted temperature using °C thresholds.
    double converted_in_c = to_c(converted, s_to);
    const char* cat = category_from_c(converted_in_c);
    const char* tip = advisory_for_category(cat);

    printf("Converted temperature: %.2f %c\n", converted, s_to);
    printf("Temperature category: %s\n", cat);
    printf("Weather advisory: %s\n", tip);
    return 0;
}
