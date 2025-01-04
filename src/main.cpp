#include "SearchServer.h"
#include <iostream>

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
        // Заданные документы
        std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
        };

        // Запросы для поиска
        std::vector<std::string> requests = { "milk water", "sugar" };

        // Создание инвертированного индекса и обновление базы документов
        InvertedIndex idx;
        idx.UpdateDocumentBase(docs);

        // Создание поискового сервера
        SearchServer srv(idx);

        // Выполнение поиска по запросам
        auto results = srv.search(requests);

        // Вывод результатов на экран
        DisplayResults(requests, results);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}
