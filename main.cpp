#include <iostream>
#include <map>
#include "analyse_sentiments.cpp"

 // You can directly import the class to instance it elsewhere

 // Sentiment analyse1("en");
 // analyse1.analyzeSentimentLine("Fuck you,I am afraid and I love the abomination");
 // analyse1.displayResult();

 // Sentiment analyse2("","data/Positive.txt","data/Negative.txt");
 // analyse2.analyzeSentimentFile("data/Newspaper.txt");
 // analyse2.displayResult();
    
 // Or use the parameters of the main.cpp program to analyze

 // Usage: 
 // [-lang <language>] -f <file_to_analyze> or -l <line_to_analyse>
 //   Or directly import your positive/negative files:
 // -f <file_to_analyze> -pos <positive_words_file> -neg <negative_words_file>



std::map<std::string, std::string> parseArguments(int argc, char *argv[]) {
    std::map<std::string, std::string> arguments;
    for (int i = 1; i < argc; i += 2) {
        if (i + 1 < argc) {
            arguments[argv[i]] = argv[i + 1];
        }
    }
    return arguments;
}

int main(int argc, char *argv[]){
    auto args = parseArguments(argc, argv);

    std::string fileToAnalyze = args["-f"];
    std::string lineToAnalyze = args["-l"];
    std::string positiveWordsFile = args["-pos"];
    std::string negativeWordsFile = args["-neg"];
    std::string language = args["-lang"];

    if (!language.empty() && (!fileToAnalyze.empty() || !lineToAnalyze.empty())) {
        Sentiment analyse(language);
        lineToAnalyze.empty()?analyse.analyzeSentimentFile(fileToAnalyze):analyse.analyzeSentimentLine(lineToAnalyze);
        analyse.displayResult();

    }else if(!fileToAnalyze.empty() && !positiveWordsFile.empty() && !negativeWordsFile.empty()){
        Sentiment analyse("",positiveWordsFile,negativeWordsFile);
        analyse.analyzeSentimentFile(fileToAnalyze);
        analyse.displayResult();
        
    }else{
        std::cerr << "Usage: " << std::endl << argv[0] << " [-lang <language>] -f <file_to_analyze> or -l <line_to_analyse>" << std::endl;
        std::cerr << "  Or directly import your positive/negative files:" << std::endl;
        std::cerr << argv[0] << " -f <file_to_analyze> -pos <positive_words_file> -neg <negative_words_file>" << std::endl;
        return 1;
    }

    return 0;
 } 