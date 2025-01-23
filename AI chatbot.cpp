#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Predefined responses for simple queries
map<string, string> predefinedResponses;

// Function to initialize the predefined responses
void initializeResponses() {
    predefinedResponses.insert(make_pair("hello", "Hi there! How can I help you?"));
    predefinedResponses.insert(make_pair("how are you", "I'm just a chatbot, but I'm functioning perfectly! How about you?"));
    predefinedResponses.insert(make_pair("what is your name", "I'm your friendly chatbot! What's yours?"));
    predefinedResponses.insert(make_pair("bye", "Goodbye! Have a great day!"));
    predefinedResponses.insert(make_pair("thank you", "You're welcome! Let me know if there's anything else I can help with."));
}

// Function to convert a string to lowercase
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Simple sentiment analysis function
string analyzeSentiment(const string& input) {
    // Initialize positive and negative words (C++98 compatible)
    vector<string> positiveWords;
    positiveWords.push_back("good");
    positiveWords.push_back("great");
    positiveWords.push_back("awesome");
    positiveWords.push_back("happy");
    positiveWords.push_back("fantastic");
    positiveWords.push_back("amazing");

    vector<string> negativeWords;
    negativeWords.push_back("bad");
    negativeWords.push_back("sad");
    negativeWords.push_back("terrible");
    negativeWords.push_back("horrible");
    negativeWords.push_back("angry");
    negativeWords.push_back("upset");

    int sentimentScore = 0;
    istringstream iss(input);
    string word;

    while (iss >> word) {
        word = toLowerCase(word);
        if (find(positiveWords.begin(), positiveWords.end(), word) != positiveWords.end()) {
            sentimentScore++;
        } else if (find(negativeWords.begin(), negativeWords.end(), word) != negativeWords.end()) {
            sentimentScore--;
        }
    }

    if (sentimentScore > 0) {
        return "It sounds like you're feeling positive!";
    } else if (sentimentScore < 0) {
        return "I'm sorry to hear that. Is there something I can do to help?";
    } else {
        return "I'm not sure how you're feeling. Could you tell me more?";
    }
}

// Chatbot response function
string getResponse(const string& userInput) {
    string lowerInput = toLowerCase(userInput);

    // Check for predefined responses
    for (map<string, string>::const_iterator it = predefinedResponses.begin(); it != predefinedResponses.end(); ++it) {
        if (lowerInput.find(it->first) != string::npos) {
            return it->second;
        }
    }

    // Perform sentiment analysis for unsupported queries
    return analyzeSentiment(userInput);
}


// Main chatbot function
void chatbot() {
    cout << "Chatbot: Hi! I'm your chatbot. Ask me anything, or type 'bye' to exit." << endl;

    string userInput;
    while (true) {
        cout << "You: ";
        getline(cin, userInput);

        if (toLowerCase(userInput) == "bye") {
            cout << "Chatbot: Goodbye! Take care!" << endl;
            break;
        }

        string response = getResponse(userInput);
        cout << "Chatbot: " << response << endl;
    }
}

int main() {
    // Initialize predefined responses
    initializeResponses();

    // Start the chatbot
    chatbot();
    return 0;
}

