// src/ConverterJSON.cpp
#include "include/ConverterJSON.h"

ConverterJSON::ConverterJSON(const std::string& configFilePath, const std::string& requestsFilePath, const std::string& answersFilePath) {
    std::ifstream configFile(configFilePath);
    if (configFile.is_open()) {
        configFile >> config_;
        configFile.close();
    }
    else {
        throw std::runtime_error("config file is missing");
    }

    std::ifstream requestsFile(requestsFilePath);
    if (requestsFile.is_open()) {
        requestsFile >> requests_;
        requestsFile.close();
    }

    std::ifstream answersFile(answersFilePath);
    if (answersFile.is_open()) {
        answersFile >> answers_;
        answersFile.close();
    }
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> docs;
    for (const auto& filePath : config_["files"]) {
        docs.push_back(filePath.get<std::string>());
    }
    return docs;
}

int ConverterJSON::GetResponsesLimit() {
    return config_["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> requests;
    for (const auto& request : requests_["requests"]) {
        requests.push_back(request.get<std::string>());
    }
    return requests;
}

void ConverterJSON::PutAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    nlohmann::json answersJson;
    for (const auto& requestResults : answers) {
        nlohmann::json resultJson;
        for (const auto& docRank : requestResults) {
            resultJson[std::to_string(docRank.first)] = docRank.second;
        }
        answersJson[std::to_string(&requestResults - &answers[0])] = { "result", resultJson };
    }

    std::ofstream answersFile("data/answers.json");
    if (answersFile.is_open()) {
        answersFile << answersJson.dump(4);
        answersFile.close();
    }
}
