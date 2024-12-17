#include "SearchServer.h"
#include <iostream>

int main() {
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

    // Output search results
    for (const auto& query_results : results) {
        for (const auto& result : query_results) {
            std::cout << "Document ID: " << result.doc_id << ", Rank: " << result.rank << std::endl;
        }
    }

    return 0;
}
