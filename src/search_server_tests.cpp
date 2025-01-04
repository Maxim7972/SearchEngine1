#include <gtest/gtest.h>
#include "InvertedIndex.h"
#include "SearchServer.h"

// Тест на обработку пустой базы документов
TEST(InvertedIndexTest, EmptyDocumentBase) {
    InvertedIndex idx;
    idx.UpdateDocumentBase({}); // Обновление базы пустым списком документов

    const auto& index = idx.GetIndex();
    ASSERT_TRUE(index.empty()); // Индекс должен быть пустым
}

// Тест на обработку пустых запросов
TEST(InvertedIndexTest, EmptyRequest) {
    InvertedIndex idx;
    idx.UpdateDocumentBase({ "word1 word2", "word2 word3" });

    const auto& result = idx.GetWordCount("");
    ASSERT_TRUE(result.empty()); // Для пустого запроса результат должен быть пустым
}

// Тест на отсутствие файлов конфигурации
TEST(SearchServerTest, MissingConfigurationFiles) {
    try {
        ConverterJSON converter("missing_config.json", "missing_requests.json", "missing_answers.json");
        FAIL() << "Expected std::runtime_error due to missing configuration files.";
    }
    catch (const std::runtime_error& e) {
        ASSERT_STREQ(e.what(), "Config file is missing: missing_config.json");
    }
    catch (...) {
        FAIL() << "Expected std::runtime_error, but got a different exception.";
    }
}

// Тест на редкие слова
TEST(SearchServerTest, RareWords) {
    InvertedIndex idx;
    std::vector<std::string> docs = { "common word", "rareword only", "common rareword" };
    idx.UpdateDocumentBase(docs);

    SearchServer srv(idx);
    std::vector<std::string> queries = { "rareword" };

    auto results = srv.search(queries);

    ASSERT_EQ(results.size(), 1); // Одна строка результата
    ASSERT_EQ(results[0].size(), 2); // "rareword" встречается в двух документах
    ASSERT_EQ(results[0][0].doc_id, 1);
    ASSERT_EQ(results[0][1].doc_id, 2);
}

// Тест на большое количество документов
TEST(SearchServerTest, LargeDocumentBase) {
    InvertedIndex idx;
    std::vector<std::string> docs(1000, "word1 word2"); // 1000 одинаковых документов
    idx.UpdateDocumentBase(docs);

    SearchServer srv(idx);
    std::vector<std::string> queries = { "word1" };

    auto results = srv.search(queries);

    ASSERT_EQ(results.size(), 1); // Один запрос
    ASSERT_EQ(results[0].size(), 1000); // Все 1000 документов должны быть в результатах
}

// Тест на большое количество запросов
TEST(SearchServerTest, LargeQuerySet) {
    InvertedIndex idx;
    idx.UpdateDocumentBase({ "word1 word2", "word2 word3", "word3 word4" });

    SearchServer srv(idx);
    std::vector<std::string> queries(1000, "word2"); // 1000 одинаковых запросов

    auto results = srv.search(queries);

    ASSERT_EQ(results.size(), 1000); // 1000 строк результатов
    for (const auto& result : results) {
        ASSERT_EQ(result.size(), 2); // "word2" встречается в двух документах
        ASSERT_EQ(result[0].doc_id, 0);
        ASSERT_EQ(result[1].doc_id, 1);
    }
}
