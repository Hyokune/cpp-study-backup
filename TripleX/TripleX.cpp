#include <iostream>

int main()
{
	// Print welcome messages to the terminal
	std::cout << "You are a secret agent breaking into a secure server room...\n";
	std::cout << "You need to enter the correct codes to continue...\n\n";

	// Declare 3 number code
	const int CodeA = 4;
	const int CodeB = 3;
	const int CodeC = 2;

	const int CodeSum = CodeA + CodeB + CodeC;
	const int CodeProduct = CodeA * CodeB * CodeC;

	// Print CodeSum and CodeProduct to the terminal
	std::cout << std::endl;
	std::cout << "+ There are 3 numbers in the code";
	std::cout << "\n+ The codes add-up to: "<< CodeSum;
	std::cout << "\n+ The codes multiply to give: " << CodeProduct;

	int GuessA, GuessB, GuessC;
	std::cin >> GuessA >> GuessB >> GuessC;

	const int GuessSum = GuessA + GuessB + GuessC;
	const int GuessProduct = GuessA * GuessB * GuessC;

	// Check if the players guess is correct
	if (GuessSum == CodeSum && GuessProduct == CodeProduct)
	{
		std::cout << "You win!";
	}
	else
	{
		std::cout << "You lose!";
	}
	

	return 0;
}