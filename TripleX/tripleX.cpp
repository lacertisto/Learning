#include <iostream>
#include <ctime>
//preprocessor statement gives compiler a directive to add code from the file\files stated in include directive to our solution

void PrintLogo()
{
    std::cout << std::endl;
    std::cout << " _____    _       _                __   __     \n";
    std::cout << "|_   _|  (_)     | |               \\ \\ / /     \n";
    std::cout << "  | |_ __ _ _ __ | | ___   ______   \\ V /      \n";
    std::cout << "  | | '__| | '_ \\| |/ _ \\ |______|  /   \\      \n";
    std::cout << "  | | |  | | |_) | |  __/          / /^\\ \\     \n";
    std::cout << "  \\_/_|  |_| .__/|_|\\___|          \\/   \\/     \n";
    std::cout << "           | |                                 \n";
    std::cout << "           |_|                                 \n";
    std::cout << " _____ _            _____                      \n";
    std::cout << "|_   _| |          |  __ \\                     \n";
    std::cout << "  | | | |__   ___  | |  \\/ __ _ _ __ ___   ___ \n";
    std::cout << "  | | | '_ \\ / _ \\ | | __ / _` | '_ ` _ \\ / _ \\ \n";
    std::cout << "  | | | | | |  __/ | |_\\ \\ (_| | | | | | |  __/ \n";
    std::cout << "  \\_/ |_| |_|\\___|  \\____/\\__,_|_| |_| |_|\\___| \n";
    std::cout << std::endl;
}

void PrintIntroduction(int CodeMul, int CodeSum, int Difficulty)
{
//expresiion statement is a piece of code which tells what we want the pc to do and how it should do it
    std::cout << "You are an Anonymous team member cracking the Facebook backdoor server level "<< Difficulty <<" password hash for recursive console call" << std::endl;
    std::cout << "You need to enter the correct codes to achieve your goal..." << std::endl;

    std::cout << "The intel you already have states the following:" << std::endl;
    std::cout << "\t + There is a three digit numeric code.\n\t + CodeMultiplication of thoose numbers gives you " << CodeMul << "." << std::endl;
    std::cout << "\t + Addition of thoose numbers gives you " << CodeSum << "." << std::endl;

    std::cout << "Enter your code below:" << std::endl;    
}

bool PlayGame(int Difficulty)
{  
    srand(time(NULL)); //initialize random number generator based on PC time
    int CodeA(rand() % Difficulty + Difficulty),CodeB(rand() % Difficulty + Difficulty),CodeC(rand() % Difficulty + Difficulty);
    int GuessSum, GuessMul, GuessA, GuessB, GuessC;
    int CodeMul(CodeA * CodeB * CodeC); // CodeMultiplication of a three digits
    int CodeSum(CodeA + CodeB + CodeC); // addition of three numbers

    PrintIntroduction(CodeMul, CodeSum, Difficulty);

//store the players input    
    std::cin >> GuessA >> GuessB >> GuessC;
    GuessMul = GuessA * GuessB * GuessC;
    GuessSum = GuessA + GuessB + GuessC;

//check if the players guess is correct
    if(GuessSum == CodeSum && GuessMul == CodeMul)
    {
        std::cout << "\n!!! Nicely done, fellow hacker! You have successfully cracked theese hash! Keep up the good work... !!!\n";
        return true;
    }
    else
    {
        std::cout << "\n!!! You have passed the wrong salt to crack the hash! Try again with another one and try to not being spotted! !!!\n";
        return false;
    }
}


int main() //main function is the body of the program which will be an entry point and the finishing point of it
{
    /*
        int c = 4; //copy initialization - taking the literal 4 and assigning it to c variable
        int a(4);//construct (direct) initialization - a bit more efficient than copy initialization
        int b{4}; //disallow "narrowing" conversions - uniform initialization 
    */
    // const prevents variable changes after being initialized
    //declaration statement is a place where all variables and structures we needed will be initialized. Usually it located first in the program
    bool bLevelComplete(false);
    int LevelDifficulty(1);
    const int MaxDifficulty(5);
    PrintLogo();
    while(LevelDifficulty <= MaxDifficulty)
    {
        bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear(); //clears input errors
        std::cin.ignore(); //discards the buffer
        if (bLevelComplete)
        {
            LevelDifficulty++;
        }
        
    }   
    //return statement tells the program what it should return in the end. 0 for example states for no problems during execution and successfully exiting the program.
    std::cout << "-------- Well Done! You have cracked the whle hash and now you are waiting for the console to reach you! Nice work! --------" << std::endl;
    return 0;
}