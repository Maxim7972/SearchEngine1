#ifndef RELATIVEINDEX_H
#define RELATIVEINDEX_H

#include <cstddef> // for size_t

struct RelativeIndex {
    size_t doc_id;
    double rank;
};

#endif // RELATIVEINDEX_H
