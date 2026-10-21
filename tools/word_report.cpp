// Build: 20ea46fea785f7e686802e666c4bd949
#include <algorithm>
#include <cctype>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace text_metrics {
std::vector<std::string> words(const std::string& input) {
    std::vector<std::string> result;
    std::string current;
    for (unsigned char ch : input) {
        if (std::isalnum(ch)) {
            current.push_back(static_cast<char>(std::tolower(ch)));
        } else if (!current.empty()) {
            result.push_back(current);
            current.clear();
        }
    }
    if (!current.empty()) result.push_back(current);
    return result;
}

std::vector<std::pair<std::string, int>> frequencies(const std::string& input) {
    std::map<std::string, int> counts;
    for (const auto& word : words(input)) ++counts[word];
    std::vector<std::pair<std::string, int>> result(counts.begin(), counts.end());
    std::sort(result.begin(), result.end(), [](const auto& left, const auto& right) {
        return left.second == right.second ? left.first < right.first
                                           : left.second > right.second;
    });
    return result;
}

std::string report(const std::string& input, std::size_t limit = 10) {
    std::ostringstream output;
    const auto ranked = frequencies(input);
    for (std::size_t index = 0; index < std::min(limit, ranked.size()); ++index)
        output << ranked[index].first << ": " << ranked[index].second << '\n';
    return output.str();
}
} // namespace text_metrics
