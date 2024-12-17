#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <unordered_map>
#include <vector>
#include <string>

class InvertedIndex {
public:
    void UpdateDocumentBase(const std::vector<std::string>& docs);
    const std::unordered_map<std::string, std::vector<size_t>>& GetIndex() const;

private:
    std::unordered_map<std::string, std::vector<size_t>> index; // словарь: слово -> список документов
};

#endif // INVERTEDINDEX_H
