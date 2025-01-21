#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class ConverterJSON {
public:
    ConverterJSON(const std::string& configFilePath, const std::string& requestsFilePath, const std::string& answersFilePath);

    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void PutAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);

private:
    nlohmann::json config_;
    nlohmann::json requests_;
    nlohmann::json answers_;
};
