#include <ctime>
#include <iostream>

void PrintIntroduction(int Difficulty)
{
	std::cout << "\n\nYou are a secret agent breaking into a level " << Difficulty << " secure server room...\n";
	std::cout << "You need to enter the correct codes to continue...\n\n";
}

bool PlayGame(int Difficulty)
{
	PrintIntroduction(Difficulty);

	const int CodeA = rand() % Difficulty + Difficulty;
	const int CodeB = rand() % Difficulty + Difficulty;
	const int CodeC = rand() % Difficulty + Difficulty;

	const int CodeSum = CodeA + CodeB + CodeC;
	const int CodeProduct = CodeA * CodeB * CodeC;

	// Print CodeSum and CodeProduct to the terminal
	std::cout << "+ There are 3 numbers in the code";
	std::cout << "\n+ The codes add-up to: "<< CodeSum;
	std::cout << "\n+ The codes multiply to give: " << CodeProduct << std::endl;

	int GuessA, GuessB, GuessC;
	std::cin >> GuessA >> GuessB >> GuessC;

	const int GuessSum = GuessA + GuessB + GuessC;
	const int GuessProduct = GuessA * GuessB * GuessC;

	// Check if the players guess is correct
	if (GuessSum == CodeSum && GuessProduct == CodeProduct)
	{
		std::cout << "\n*** Well done agent! You have extracted a file! Keep going! ***";
		return true;
	}
	else
	{
		std::cout << "\n*** You entered the wrong code! Careful agent! Try again! ***";
		return false;
	}
}

int main()
{
	srand(time(NULL)); // Create new random sequence based on time of day

	int LevelDifficulty = 1;
	const int MaxDifficulty = 5;

	while (LevelDifficulty <= MaxDifficulty)
	{
		bool bLevelComplete = PlayGame(LevelDifficulty);
		std::cin.clear(); // Clears any errors
		std::cin.ignore(); // Discards the buffer

		if (bLevelComplete)
		{
			LevelDifficulty++;
		}
	}

	std::cout << "\n*** Great work agent! You got all the files! Now get out of there! ***\n";

	return 0;
}