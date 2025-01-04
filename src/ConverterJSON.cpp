#include "ConverterJSON.h"
#include <iostream>

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

        std::ifstream requestsFile(requestsFilePath);
        if (!requestsFile.is_open()) {
            throw std::runtime_error("Requests file is missing: " + requestsFilePath);
        }
        requestsFile >> requests_;
        requestsFile.close();

        if (!requests_.contains("requests")) {
            throw std::runtime_error("Missing key 'requests' in requests.json");
        }

        std::ifstream answersFile(answersFilePath);
        if (answersFile.is_open()) {
            answersFile >> answers_;
            answersFile.close();
        }
    }
    catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Initialization error: " + std::string(e.what()));
    }
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> docs;
    try {
        for (const auto& filePath : config_["files"]) {
            docs.push_back(filePath.get<std::string>());
        }
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Error reading 'files' from config.json: " + std::string(e.what()));
    }
    return docs;
}

int ConverterJSON::GetResponsesLimit() {
    try {
        return config_["config"]["max_responses"].get<int>();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Error reading 'config.max_responses' from config.json: " + std::string(e.what()));
    }
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> requests;
    try {
        for (const auto& request : requests_["requests"]) {
            requests.push_back(request.get<std::string>());
        }
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Error reading 'requests' from requests.json: " + std::string(e.what()));
    }
    return requests;
}

void ConverterJSON::PutAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    try {
        nlohmann::json answersJson;
        for (const auto& requestResults : answers) {
            nlohmann::json resultJson;
            for (const auto& docRank : requestResults) {
                resultJson[std::to_string(docRank.first)] = docRank.second;
            }
            answersJson[std::to_string(&requestResults - &answers[0])] = { { "result", resultJson } };
        }

        std::ofstream answersFile("data/answers.json");
        if (!answersFile.is_open()) {
            throw std::runtime_error("Unable to open answers file for writing: data/answers.json");
        }
        answersFile << answersJson.dump(4);
        answersFile.close();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Error writing answers to file: " + std::string(e.what()));
    }
}
