#include "histogram.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <numeric>

using namespace std;

// ������� ��� ����� �����
vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}
/*
// ������� ��� ������ �������� � ���������
void find_minmax(const vector<double>& numbers, double& min, double& max) {
    auto min_it = min_element(numbers.begin(), numbers.end());
    auto max_it = max_element(numbers.begin(), numbers.end());
    min = *min_it;
    max = *max_it;
}
*/
// ������� ��� �������� �����������
vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count) {
    vector<size_t> bins(bin_count, 0);
    double min, max;
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;

    for (double x : numbers) {
        size_t bin_index = static_cast<size_t>((x - min) / bin_size);
        if (bin_index == bin_count) {
            bin_index--;
        }
        bins[bin_index]++;
    }

    return bins;
}

// ������� ��� ������ ������������� �������� � ������� bins
size_t max_count(const vector<size_t>& bins) {
    return *max_element(bins.begin(), bins.end());
}

// ������� ��� ����������� ����������� � ��������� ����
void show_histogram_text(const vector<size_t>& bins) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t number_count = accumulate(bins.begin(), bins.end(), 0);
    size_t bin_count = bins.size();
    size_t average_height = static_cast<size_t>(round(static_cast<double>(number_count) / bin_count));
    size_t max_value = max_count(bins);

    if (max_value <= MAX_ASTERISK) {
        for (size_t count : bins) {
            cout << setw(3) << count << "|";
            if (count <= average_height) {
                for (size_t j = 0; j < count; j++) {
                    cout << "*";
                }
                if (count < average_height) {
                    for (size_t j = count; j < average_height; j++) {
                        cout << "-";
                    }
                }
            } else {
                for (size_t j = 0; j < average_height; j++) {
                    cout << "*";
                }
                for (size_t j = average_height; j < count; j++) {
                    cout << "+";
                }
            }
            cout << endl;
        }
    } else {
        for (size_t count : bins) {
            cout << setw(3) << count << "|";
            size_t height = static_cast<size_t>(MAX_ASTERISK * static_cast<double>(count) / max_value);
            size_t average_height_m = static_cast<size_t>(MAX_ASTERISK * static_cast<double>(average_height) / max_value);

            if (height <= average_height_m) {
                for (size_t j = 0; j < height; j++) {
                    std::cout << "*";
                }
            }
            if (height < average_height_m) {
                for (size_t j = height; j < average_height_m; j++) {
                    cout << "-";
                }
            }
            if (height > average_height_m) {
                for (size_t j = 0; j < average_height_m; j++) {
                    cout << "*";
                }
                for (size_t j = average_height_m; j < height; j++) {
                    cout << "+";
                }
            }
            cout << endl;
        }
    }
}

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

int main() {
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);

    show_histogram_svg(bins);

    return 0;
}
