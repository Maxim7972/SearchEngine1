#include "InvertedIndex.h"
#include "SearchServer.h"
#include "Logger.h"
#include <iostream>
#include <vector>
#include <string>

void DisplayResults(const std::vector<std::string>& requests, const std::vector<std::vector<RelativeIndex>>& results) {
    for (size_t i = 0; i < requests.size(); ++i) {
        std::cout << "Запрос #" << i + 1 << ": \"" << requests[i] << "\"\n";
        if (results[i].empty()) {
            std::cout << "  Нет результатов.\n";
        }
        else {
            for (const auto& result : results[i]) {
                std::cout << "  Документ ID: " << result.doc_id
                    << ", Релевантность: " << result.rank << "\n";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    try {
        Logger::GetInstance().Log("Application started.");

        std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
        };

        std::vector<std::string> requests = { "milk water", "sugar" };

        InvertedIndex idx;
        idx.UpdateDocumentBase(docs);

        SearchServer srv(idx);

        auto results = srv.search(requests);

        DisplayResults(requests, results);

        Logger::GetInstance().Log("Application finished successfully.");
    }
    catch (const std::exception& e) {
        Logger::GetInstance().Log(std::string("Error: ") + e.what());
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}
