#ifndef ANALYSE_SENTIMENT_HPP
#define ANALYSE_SENTIMENT_HPP

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <sstream>
namespace fs = std::filesystem;

class Sentiment {
private:
    struct SentimentDictionary {
        std::unordered_set<std::string> positiveWords;
        std::unordered_set<std::string> negativeWords;
    };

    struct AnalysisResult {
        int positiveCount = 0;
        int negativeCount = 0;
        std::string overallSentiment;
    };

    AnalysisResult result;
    SentimentDictionary dictionary;
    std::string language;
    std::string positivePath;
    std::string negativePath;


    void loadSentimentDictionary(const std::string &language,SentimentDictionary &dictionary);
    std::string removePunctuation(const std::string& str);
    std::string toLowerCase(const std::string& str);

public:
     Sentiment(const std::string& language,const std::string& positivePath, const std::string& negativePath);
    ~Sentiment() = default;

    AnalysisResult analyzeSentimentFile(const std::string &filePath);
    AnalysisResult analyzeSentimentLine(const std::string &line);
    void displayResult();
    void getPositiveWord();
    void getNegativeWord();
};

#endif
