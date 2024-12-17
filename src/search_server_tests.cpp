#include <gtest/gtest.h>
#include "InvertedIndex.h"
#include "SearchServer.h"

TEST(InvertedIndexTest, UpdateDocumentBase) {
    InvertedIndex idx;
    std::vector<std::string> docs = { "word1 word2", "word2 word3" };

    idx.UpdateDocumentBase(docs);

    const auto& index = idx.GetIndex();
    ASSERT_EQ(index.size(), 3);
    ASSERT_EQ(index.at("word1").size(), 1);
    ASSERT_EQ(index.at("word2").size(), 2);
    ASSERT_EQ(index.at("word3").size(), 1);
}

TEST(SearchServerTest, Search) {
    InvertedIndex idx;
    std::vector<std::string> docs = { "word1 word2", "word2 word3" };
    idx.UpdateDocumentBase(docs);

    SearchServer srv(idx);
    std::vector<std::string> queries = { "word2" };

    auto results = srv.search(queries);

    ASSERT_EQ(results.size(), 1);
    ASSERT_EQ(results[0].size(), 2);
    ASSERT_EQ(results[0][0].doc_id, 0);
    ASSERT_EQ(results[0][1].doc_id, 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
