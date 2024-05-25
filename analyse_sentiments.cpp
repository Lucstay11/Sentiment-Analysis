#include "analyse_sentiments.hpp"

Sentiment::Sentiment(const std::string& language = "",const std::string& positivePath = "", const std::string& negativePath = "")
    : positivePath(positivePath), negativePath(negativePath) {
    loadSentimentDictionary(language,dictionary);
}

void Sentiment::loadSentimentDictionary(const std::string &language,SentimentDictionary &dictionary) {
    std::string path;
    path=toLowerCase(language)==""?positivePath:"languages/"+language+"/p.txt";
    if (!std::filesystem::exists("languages/"+toLowerCase(language)) && language !="") {
        std::cerr << "Language is not supported!" << std::endl;
        return;
    }

    std::ifstream positiveFile(path);
    if (positiveFile.is_open()) {
        std::string line;
        while (std::getline(positiveFile, line)) {
            dictionary.positiveWords.insert(toLowerCase(line));
        }
        positiveFile.close();
    }else{
        std::cerr << "Error importing file "+positivePath << std::endl;
        return;
    } 
    path=language==""?negativePath:"languages/"+language+"/n.txt";
    std::ifstream negativeFile(path);
    if (negativeFile.is_open()) {
        std::string line;
        while (std::getline(negativeFile, line)) {
            dictionary.negativeWords.insert(toLowerCase(line));
        }
        negativeFile.close();
    }else{
        std::cerr << "Error importing file "+negativePath << std::endl;
        return;
    }
}

std::string Sentiment::removePunctuation(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (!ispunct(c)) {
            result += c;
        }
    }
    return result;
}

std::string Sentiment::toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

Sentiment::AnalysisResult Sentiment::analyzeSentimentFile(const std::string &filePath) {
    AnalysisResult result;
    std::ifstream file(filePath);
    if (file.is_open() && dictionary.positiveWords.size()>0 && dictionary.negativeWords.size()>0) {
        std::string word;
        while (file >> word) { 
                if (dictionary.positiveWords.find(removePunctuation(toLowerCase(word))) != dictionary.positiveWords.end()) {
                    result.positiveCount++;
                }
                if (dictionary.negativeWords.find(removePunctuation(toLowerCase(word))) != dictionary.negativeWords.end()) {
                    result.negativeCount++;
                }
        }
        file.close();
    }else{
        std::cerr << "Error: file not found" << std::endl;
    }
    result.overallSentiment = (result.positiveCount > result.negativeCount) ? "Positive" :(result.positiveCount < result.negativeCount) ? "Negative" : "Neutral";

    return result;
}

Sentiment::AnalysisResult Sentiment::analyzeSentimentLine(const std::string &line) {
    std::istringstream lines(line);
    if (dictionary.positiveWords.size()>0 && dictionary.negativeWords.size()>0) {
      std::string w;
      while (lines >> w) {
        if (dictionary.positiveWords.find(removePunctuation(toLowerCase(w))) != dictionary.positiveWords.end()) {
            result.positiveCount++;
        }
        if (dictionary.negativeWords.find(removePunctuation(toLowerCase(w))) != dictionary.negativeWords.end()) {
            result.negativeCount++;
        }
      }
    }
    result.overallSentiment = (result.positiveCount > result.negativeCount) ? "Positive" :(result.positiveCount < result.negativeCount) ? "Negative" : "Neutral";
    
    return result;
}

void Sentiment::displayResult(){
    std::cout << result.overallSentiment << " (Pos word: " << result.positiveCount << " Neg word: " << result.negativeCount << ")"<< std::endl;
}

void Sentiment::getPositiveWord(){
    for (const auto& sentiment : dictionary.positiveWords) {
        std::cout << sentiment << std::endl;
    }
}

void Sentiment::getNegativeWord(){
    for (const auto& sentiment : dictionary.negativeWords) {
        std::cout << sentiment << std::endl;
    }
}

