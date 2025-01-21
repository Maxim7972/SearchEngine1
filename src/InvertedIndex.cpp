#include "InvertedIndex.h"
#include "Logger.h"
#include <sstream>

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& docs) {
    Logger::GetInstance().Log("Updating document base.");
    for (size_t docId = 0; docId < docs.size(); ++docId) {
        std::istringstream stream(docs[docId]);
        std::string word;
        while (stream >> word) {
            index[word][docId]++;
        }
    }
    Logger::GetInstance().Log("Document base updated.");
}

const std::unordered_map<std::string, std::unordered_map<int, int>>& InvertedIndex::GetIndex() const {
    return index;
}
