#pragma once
#include <iostream>
#include <vector>
using namespace std;

void svg_begin(double width, double height);

void svg_end();

void svg_text(double left, double baseline, string text);

void svg_rect(double x, double y, double width, double height, string stroke, string fill);

size_t max_count(const vector<size_t>& bins);

void draw_histogram_bar(double x, double y, double width, double height, size_t bin_value, size_t average_height, string& stroke, string& fill);

void show_histogram_svg(const vector<size_t>& bins);

