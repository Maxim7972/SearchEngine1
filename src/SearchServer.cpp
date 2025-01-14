#include "SearchServer.h"
#include "Logger.h"
#include <algorithm>
#include <sstream>

SearchServer::SearchServer(const InvertedIndex& idx) : index(idx) {
    Logger::GetInstance().Log("SearchServer initialized.");
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    Logger::GetInstance().Log("Search started.");
    std::vector<std::vector<RelativeIndex>> result;

    for (const auto& query : queries_input) {
        Logger::GetInstance().Log("Processing query: " + query);
        std::vector<RelativeIndex> query_results;

        std::istringstream stream(query);
        std::string word;
        while (stream >> word) {
            if (index.GetIndex().count(word)) {
                for (const auto& doc_id : index.GetIndex().at(word)) {
                    query_results.push_back({ doc_id, 1.0 });
                }
            }
        }

        std::sort(query_results.begin(), query_results.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
            return a.rank > b.rank;
            });

        result.push_back(query_results);
    }

    Logger::GetInstance().Log("Search completed.");
    return result;
}
