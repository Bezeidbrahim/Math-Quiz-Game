#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Enums
enum enLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

// Struct Question
struct stQuestion {
    int num1 = 0;
    int num2 = 0;
    enOperationType op;
    int correctAnswer = 0;
    int userAnswer = 0;
};

// Struct Quiz
struct stQuiz {
    stQuestion questions[100];
    int totalQuestions = 0;
    int correctCount = 0;
    int wrongCount = 0;
    enLevel level;
    enOperationType opType;
};

// Random
int RandomNumber(int from, int to) {
    return rand() % (to - from + 1) + from;
}

// Operation Symbol
string GetOpSymbol(enOperationType op) {
    switch (op) {
    case Add: return "+";
    case Sub: return "-";
    case Mul: return "*";
    case Div: return "/";
    default: return "?";
    }
}

// Random Operation
enOperationType GetRandomOperation() {
    return (enOperationType)RandomNumber(1, 4);
}

// Generate Number
int GenerateNumber(enLevel level) {
    switch (level) {
    case Easy: return RandomNumber(1, 10);
    case Med: return RandomNumber(10, 50);
    case Hard: return RandomNumber(50, 100);
    case Mix: return RandomNumber(1, 100);
    }
    return 1;
}

// Calculate
int Calculate(int a, int b, enOperationType op) {
    switch (op) {
    case Add: return a + b;
    case Sub: return a - b;
    case Mul: return a * b;
    case Div: return b != 0 ? a / b : 0;
    }
    return 0;
}

// Generate Question
stQuestion GenerateQuestion(enLevel level, enOperationType opType) {
    stQuestion q;

    if (level == Mix)
        level = (enLevel)RandomNumber(1, 3);

    if (opType == MixOp)
        opType = GetRandomOperation();

    q.num1 = GenerateNumber(level);
    q.num2 = GenerateNumber(level);
    q.op = opType;
    q.correctAnswer = Calculate(q.num1, q.num2, q.op);

    return q;
}

// Generate All Questions
void GenerateQuiz(stQuiz& quiz) {
    for (int i = 0; i < quiz.totalQuestions; i++) {
        quiz.questions[i] = GenerateQuestion(quiz.level, quiz.opType);
    }
}

// Ask Questions
void AskQuestions(stQuiz& quiz) {
    for (int i = 0; i < quiz.totalQuestions; i++) {

        cout << "\nQuestion [" << i + 1 << "/" << quiz.totalQuestions << "]\n";
        cout << quiz.questions[i].num1 << " "
             << GetOpSymbol(quiz.questions[i].op) << " "
             << quiz.questions[i].num2 << " = ";

        cin >> quiz.questions[i].userAnswer;

        if (quiz.questions[i].userAnswer == quiz.questions[i].correctAnswer) {
            cout << "Correct!\n";
            quiz.correctCount++;
        }
        else {
            cout << "Wrong! Correct Answer: "
                 << quiz.questions[i].correctAnswer << endl;
            quiz.wrongCount++;
        }
    }
}

// Show Result
void ShowResult(stQuiz quiz) {
    cout << "\n=========================\n";
    cout << "Total Questions: " << quiz.totalQuestions << endl;
    cout << "Right Answers : " << quiz.correctCount << endl;
    cout << "Wrong Answers : " << quiz.wrongCount << endl;

    if (quiz.correctCount >= quiz.wrongCount)
        cout << "Result: PASS\n";
    else
        cout << "Result: FAIL\n";

    cout << "=========================\n";
}

// Start Game
void StartGame() {
    stQuiz quiz;

    cout << "How many questions? ";
    cin >> quiz.totalQuestions;

    cout << "Level [1 Easy, 2 Med, 3 Hard, 4 Mix]: ";
    cin >> quiz.level;

    cout << "Operation [1 +, 2 -, 3 *, 4 /, 5 Mix]: ";
    cin >> quiz.opType;

    GenerateQuiz(quiz);
    AskQuestions(quiz);
    ShowResult(quiz);
}

// Main
int main() {
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
