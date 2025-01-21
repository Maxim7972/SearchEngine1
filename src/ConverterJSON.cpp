#include "ConverterJSON.h"
#include <fstream>
#include <stdexcept>
#include "Logger.h"

ConverterJSON::ConverterJSON(const std::string& configFilePath, const std::string& requestsFilePath, const std::string& answersFilePath) {
    try {
        std::ifstream configFile(configFilePath);
        if (!configFile.is_open()) {
            throw std::runtime_error("Config file is missing: " + configFilePath);
        }
        configFile >> config_;
        configFile.close();

        if (!config_.contains("config") || !config_["config"].contains("max_responses")) {
            throw std::runtime_error("Missing key 'config.max_responses' in config.json");
        }
        if (!config_.contains("files")) {
            throw std::runtime_error("Missing key 'files' in config.json");
        }
        if (config_["config"]["max_responses"].get<int>() < 1) {
            throw std::runtime_error("Invalid value for 'max_responses': must be >= 1");
        }

        std::ifstream requestsFile(requestsFilePath);
        if (!requestsFile.is_open()) {
            throw std::runtime_error("Requests file is missing: " + requestsFilePath);
        }
        requestsFile >> requests_;
        requestsFile.close();

        if (!requests_.contains("requests")) {
            throw std::runtime_error("Missing key 'requests' in requests.json");
        }
    }
    catch (const std::exception& e) {
        Logger::GetInstance().Log(e.what(), "ERROR");
        throw;
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
    return config_["config"]["max_responses"].get<int>();
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
        answersJson.push_back(resultJson);
    }

    std::ofstream answersFile("answers.json");
    if (!answersFile.is_open()) {
        throw std::runtime_error("Unable to open answers.json for writing");
    }
    answersFile << answersJson.dump(4);
}
