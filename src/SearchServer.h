#ifndef SEARCHSERVER_H
#define SEARCHSERVER_H

#include "InvertedIndex.h"
#include "RelativeIndex.h"
#include <vector>
#include <string>

class SearchServer {
public:
    SearchServer(const InvertedIndex& idx);
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex index;
};

#endif // SEARCHSERVER_H
