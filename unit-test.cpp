#include "svg.h"
#include <cassert>
#include <string>

using namespace std;

void test_draw_histogram_bar_max_average() {
    double x = 10.0, y = 20.0, width = 50.0, height = 30.0;
    size_t bin_value = 15, average_height = 10;
    string one, two;
    draw_histogram_bar(x, y, width, height, bin_value, average_height, one, two);
    assert(one == "red");
    assert(two == "red");
}

void test_draw_histogram_bar_min_average() {
    double x = 20.0, y = 30.0, width = 60.0, height = 40.0;
    size_t bin_value = 5, average_height = 10;
    string one, two;
    draw_histogram_bar(x, y, width, height, bin_value, average_height, one, two);
    assert(one == "green");
    assert(two == "green");
}

void test_draw_histogram_bar_equal_average() {
    double x = 7.0, y = 15.0, width = 34.0, height = 18.0;
    size_t bin_value = 10, average_height = 10;
    string one, two;
    draw_histogram_bar(x, y, width, height, bin_value, average_height, one, two);
    assert(one == "green");
    assert(two == "green");
}

int main() {
    test_draw_histogram_bar_max_average();
    test_draw_histogram_bar_min_average();
    test_draw_histogram_bar_equal_average();
    return 0;
}
