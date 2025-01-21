#include "SearchServer.h"
#include "Logger.h"
#include <algorithm>
#include <sstream>

SearchServer::SearchServer(const InvertedIndex& idx) : index(idx) {}

std::vector<std::vector<RelativeIndex>> SearchServer::Search(const std::vector<std::string>& queries) {
    std::vector<std::vector<RelativeIndex>> results;

    for (const auto& query : queries) {
        std::unordered_map<int, float> docScores;
        std::istringstream stream(query);
        std::string word;

        while (stream >> word) {
            if (index.GetIndex().count(word)) {
                for (const auto& [docId, count] : index.GetIndex().at(word)) {
                    docScores[docId] += count;
                }
            }
        }

        std::vector<RelativeIndex> queryResult;
        float maxScore = 0;
        for (const auto& [docId, score] : docScores) {
            maxScore = std::max(maxScore, score);
        }
        for (const auto& [docId, score] : docScores) {
            queryResult.push_back({ docId, score / maxScore });
        }

        std::sort(queryResult.begin(), queryResult.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
            return a.rank > b.rank;
            });

        results.push_back(queryResult);
    }

    return results;
}
