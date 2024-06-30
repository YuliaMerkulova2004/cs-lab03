#include "histogram.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max) {
    if (numbers.empty()) {
        return;
    }

    auto min_it = min_element(numbers.begin(), numbers.end());
    auto max_it = max_element(numbers.begin(), numbers.end());
    min = *min_it;
    max = *max_it;
}
