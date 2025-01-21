#pragma once
#include "InvertedIndex.h"
#include <vector>
#include <string>

struct RelativeIndex {
    int docId;
    float rank;
};

class SearchServer {
public:
    SearchServer(const InvertedIndex& idx);
    std::vector<std::vector<RelativeIndex>> Search(const std::vector<std::string>& queries);

private:
    InvertedIndex index;
};
