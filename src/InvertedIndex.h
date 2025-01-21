#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class InvertedIndex {
public:
    void UpdateDocumentBase(const std::vector<std::string>& docs);
    const std::unordered_map<std::string, std::unordered_map<int, int>>& GetIndex() const;

private:
    std::unordered_map<std::string, std::unordered_map<int, int>> index;
};
