#include "InvertedIndex.h"
#include "Logger.h"
#include <sstream>

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& docs) {
    Logger::GetInstance().Log("Updating document base.");
    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id) {
        std::istringstream stream(docs[doc_id]);
        std::string word;
        while (stream >> word) {
            index[word].push_back(doc_id);
        }
    }
    Logger::GetInstance().Log("Document base updated.");
}

const std::unordered_map<std::string, std::vector<size_t>>& InvertedIndex::GetIndex() const {
    return index;
}
