#include <iostream>
#include <limits>

int main(){
    int userIn = 0;
    std::cin >> userIn;
    std::cout << userIn << std::endl;
    while (std::cin.fail() || userIn < 1 || userIn > 10) {
        std::cin.clear(); // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        std::cout << "Invalid input. Please enter a valid integer between 1 and 10: ";
        std::cin >> userIn;
    }
}
// while (userIn < 1 or userIn > 10 or !std::cin){
//         printf("Choose a query to execute (-1 to quit): ");
//         std::cin >> userIn;
//         if (userIn == -1) return 0;
//         else if (userIn < 1 or userIn > 10 or !std::cin){
//             printf("\nYou must enter a number 1-10 inclusive or -1 to quit. Please try again :)\n");
//         }
//     }