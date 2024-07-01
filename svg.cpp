#include "svg.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke = "green", string fill = "green") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />";
}

size_t max_count(const vector<size_t>& bins) {
    return *max_element(bins.begin(), bins.end());
}

void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 1000;
    const auto IMAGE_HEIGHT = 200;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    const size_t MAX_LEN = 76;
    size_t number_count = accumulate(bins.begin(), bins.end(), 0);
    size_t bin_count = bins.size();
    size_t average_height = static_cast<size_t>(round(static_cast<double>(number_count) / bin_count));
    size_t max_value = max_count(bins);

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    if (max_value > MAX_LEN) {
        for (size_t bin : bins) {
            const double bin_width = BLOCK_WIDTH * static_cast<double>(bin) * MAX_LEN / max_value;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            if (bin > average_height) {
                svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "red");
            } else {
                svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            }
            top += BIN_HEIGHT;
        }
    } else {
        for (size_t bin : bins) {
            const double bin_width = BLOCK_WIDTH * bin;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            if (bin > average_height) {
                svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "red");
            } else {
                svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            }
            top += BIN_HEIGHT;
        }
    }
    svg_end();
}
