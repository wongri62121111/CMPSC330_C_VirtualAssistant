/*
	Name : Tommy Lu, Richard Wong
	Course : CMPSC 330
	Project : Virtual Assistant 
	Date : 10/3/2024
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // For setting precision in output
#include <math.h>

using namespace std;

// Custom math functions
double customAbs(double x) {
    return x < 0 ? -x : x;
}

double customSqrt(double x) {
    if (x < 0) return -1; // Error case
    double guess = x / 2;
    double epsilon = 1e-7;
    while (customAbs(guess * guess - x) > epsilon) {
        guess = (guess + x / guess) / 2;
    }
    return guess;
}

// Function to calculate the determinant of a 2x2 matrix
double determinant(double a, double b, double c, double d) {
    return a * d - b * c;
}

// Function to calculate the inverse of a 2x2 matrix
void inverse(double a, double b, double c, double d, double inv[2][2]) {
    double det = determinant(a, b, c, d);
    if (det == 0) {
        std::cout << "The matrix is not invertible." << std::endl;
        return;
    }
    double invDet = 1.0 / det;
    inv[0][0] = d * invDet;
    inv[0][1] = -b * invDet;
    inv[1][0] = -c * invDet;
    inv[1][1] = a * invDet;
}

// Function to multiply a 2x2 matrix with a 2x1 matrix
void matrixMultiply(double A[2][2], double B[2], double result[2]) {
    result[0] = A[0][0] * B[0] + A[0][1] * B[1];
    result[1] = A[1][0] * B[0] + A[1][1] * B[1];
}

// Function prototypes
void basicOperations(double num1, double num2);
void averageNumbers(double num1, double num2);
void checkEvenOdd(int num1, int num2);
void checkPositiveNegativeZero(double num1, double num2);
void calculateSquareRoot(double num);
void calculateAbsoluteValue(double num);
void calculateSquarePerimeterArea(double side);
void multiplicationTableTwo();
void calculateHypotenuse(double a, double b);
void currencyExchange(double amount, double rate, bool dollarsToEuros);
void swapNumbers(double &num1, double &num2);
void findLargestofTwo(double num1, double num2);
void findSmallestOfThree(double num1, double num2, double num3);
void findLargestOfThree(double num1, double num2, double num3);
void sumOfSquares(double num1, double num2);
void findMinMaxOfThree(double num1, double num2, double num3);
void sumFirstHundredIntegers();
void sumFirstHundredEvenIntegers();
void solveFirstDegreeEquation(double a, double b, double c);
void solveSecondDegreeEquation(double a, double b, double c);
void sumFirstNIntegers(int N);
void sumFirstNEvenIntegers(int N);
void convertDistance(double distance, bool kmToM);
// Games 
void tShirtCustomization();
void quizGame();
// Array
void arrayOperations();
void userInputArrayOperations();
void multiplyArrayByNumber();
void matrixOperations();
void inverseMatrixLinearEquations();
// Recursive functions 
double calculateFactorial(double n);
double calculateFibonacci(double n);
double sumDigits(double n);

// Helper functions for T-Shirt Customization
string getInput(const string& prompt);
int getChoice(const string& prompt, const string options[], int optionCount);
string getYesNo(const string& prompt);

// Linear Regression class 
class LinearRegression {
private:
    double slope;
    double intercept;
    double r_squared;

    // Helper function to calculate mean
    double calculateMean(const vector<double>& data) {
        double sum = 0;
        for (double value : data) {
            sum += value;
        }
        return sum / data.size();
    }

public:
    // Function to fit the linear regression model
    void fit(const vector<double>& x, const vector<double>& y) {
        if (x.size() != y.size() || x.size() < 2) {
            cout << "Error: Invalid data size" << endl;
            return;
        }

        double x_mean = calculateMean(x);
        double y_mean = calculateMean(y);

        double numerator = 0;
        double denominator = 0;

        // Calculate slope
        for (size_t i = 0; i < x.size(); i++) {
            numerator += (x[i] - x_mean) * (y[i] - y_mean);
            denominator += pow(x[i] - x_mean, 2);
        }

        slope = numerator / denominator;
        intercept = y_mean - (slope * x_mean);

        // Calculate R-squared
        double ss_tot = 0;
        double ss_res = 0;
        for (size_t i = 0; i < x.size(); i++) {
            double y_pred = predict(x[i]);
            ss_tot += pow(y[i] - y_mean, 2);
            ss_res += pow(y[i] - y_pred, 2);
        }
        r_squared = 1 - (ss_res / ss_tot);
    }

    // Function to make predictions
    double predict(double x_value) {
        return (slope * x_value) + intercept;
    }

    // Function to print model statistics
    void printStats() {
        cout << fixed << setprecision(4);
        cout << "\nModel Statistics:" << endl;
        cout << "Slope (b1): " << slope << endl;
        cout << "Intercept (b0): " << intercept << endl;
        cout << "R-squared: " << r_squared << endl;
        cout << "Equation: y = " << slope << "x + " << intercept << endl;
    }
};



int main() {
    int categoryChoice, functionChoice;
    double num1, num2, num3;

    do {
        cout << "\nMath Operations Categories:\n";
        cout << "1. Basic Operations\n";
        cout << "2. Number Properties\n";
        cout << "3. Geometry\n";
        cout << "4. Series and Sequences\n";
        cout << "5. Equations\n";
        cout << "6. Miscellaneous\n";
		cout << "7. Fun Activities\n";
        cout << "0. Exit\n";
        cout << "Enter your category choice: ";
        cin >> categoryChoice;

        switch(categoryChoice) {
            case 1: // Basic Operations
                cout << "\nBasic Operations:\n";
                cout << "1. Basic arithmetic (+-*/)\n";
                cout << "2. Average of two numbers\n";
                cout << "3. Absolute value\n";
                cout << "4. Square root\n";
                cout << "5. Sum of squares\n";
                cout << "Enter your function choice: ";
                cin >> functionChoice;
                switch(functionChoice) {
                    case 1:
                        cout << "Enter two numbers: ";
                        cin >> num1 >> num2;
                        basicOperations(num1, num2);
                        break;
                    case 2:
                        cout << "Enter two numbers: ";
                        cin >> num1 >> num2;
                        averageNumbers(num1, num2);
                        break;
                    case 3:
                        cout << "Enter a number: ";
                        cin >> num1;
                        calculateAbsoluteValue(num1);
                        break;
                    case 4:
                        cout << "Enter a number: ";
                        cin >> num1;
                        calculateSquareRoot(num1);
                        break;
                    case 5:
                        cout << "Enter two numbers: ";
                        cin >> num1 >> num2;
                        sumOfSquares(num1, num2);
                        break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            case 2: // Number Properties
                cout << "\nNumber Properties:\n";
                cout << "1. Check even/odd\n";
                cout << "2. Check positive/negative/zero\n";
				cout << "3. Find largest of two numbers\n";
                cout << "4. Find smallest of three numbers\n";
                cout << "5. Find largest of three numbers\n";
                cout << "6. Find min and max of three numbers\n";
                cout << "Enter your function choice: ";
                cin >> functionChoice;
                switch(functionChoice) {
                    case 1:
                        cout << "Enter two integers: ";
                        cin >> num1 >> num2;
                        checkEvenOdd(num1, num2);
                        break;
                    case 2:
                        cout << "Enter two numbers: ";
                        cin >> num1 >> num2;
                        checkPositiveNegativeZero(num1, num2);
                        break;
                    case 3:
                        cout << "Enter two numbers: ";
                        cin >> num1 >> num2;
                        findLargestofTwo(num1, num2);
                        break;
                    case 4:
                        cout << "Enter three numbers: ";
                        cin >> num1 >> num2 >> num3;
                        findSmallestOfThree(num1, num2, num3);
                        break;
                    case 5:
                        cout << "Enter three numbers: ";
                        cin >> num1 >> num2 >> num3;
                        findLargestOfThree(num1, num2, num3);
                        break;
					case 6:
						cout << "Enter three numbers: ";
                        cin >> num1 >> num2 >> num3;
                        findMinMaxOfThree(num1, num2, num3);
                        break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            case 3: // Geometry
                cout << "\nGeometry:\n";
                cout << "1. Calculate square perimeter and area\n";
                cout << "2. Calculate hypotenuse\n";
                cout << "Enter your function choice: ";
                cin >> functionChoice;
                switch(functionChoice) {
                    case 1:
                        cout << "Enter the side length of the square: ";
                        cin >> num1;
                        calculateSquarePerimeterArea(num1);
                        break;
                    case 2:
                        cout << "Enter the lengths of two sides of the right triangle: ";
                        cin >> num1 >> num2;
                        calculateHypotenuse(num1, num2);
                        break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            case 4: // Series and Sequences
                cout << "\nSeries and Sequences:\n";
                cout << "1. Multiplication table of 2\n";
                cout << "2. Sum of first 100 integers\n";
                cout << "3. Sum of first 100 even integers\n";
                cout << "4. Sum of first N integers\n";
                cout << "5. Sum of first N even integers\n";
				cout << "6. Calculate Factorial\n";          
				cout << "7. Calculate Fibonacci Number\n";    
				cout << "8. Calculate Sum of Digits\n";  
                cout << "Enter your function choice: ";
                cin >> functionChoice;
                switch(functionChoice) {
                    case 1:
                        multiplicationTableTwo();
                        break;
                    case 2:
                        sumFirstHundredIntegers();
                        break;
                    case 3:
                        sumFirstHundredEvenIntegers();
                        break;
                    case 4:
                        int N;
                        cout << "Enter N (> 0): ";
                        cin >> N;
                        sumFirstNIntegers(N);
                        break;
                    case 5:
                        cout << "Enter N (> 0): ";
                        cin >> N;
                        sumFirstNEvenIntegers(N);
                        break;
					case 6: {
						double num;
						cout << "Enter a non-negative number: ";
						cin >> num;
						if (num < 0) {
							cout << "Factorial is not defined for negative numbers." << endl;
						} else {
							cout << "Factorial of " << num << " is: " << calculateFactorial(num) << endl;
						}
						break;
						}
					case 7: {
						double num;
						cout << "Enter the position in the Fibonacci sequence (>= 0): ";
						cin >> num;
						if (num < 0) {
							cout << "Position cannot be negative." << endl;
						} else {
							cout << "Fibonacci number at position " << num << " is: " << calculateFibonacci(num) << endl;
						}
						break;
						}
					case 8: {
						double num;
						cout << "Enter a number: ";
						cin >> num;
						cout << "Sum of digits in " << num << " is: " << sumDigits(num) << endl;
						break;
						}
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            case 5: // Equations
                cout << "\nEquations:\n";
                cout << "1. Solve first-degree equation\n";
                cout << "2. Solve second-degree equation\n";
				cout << "3. Solving a system of two linear equations with the inverse matrix method\n";
                cout << "Enter your function choice: ";
                cin >> functionChoice;
                switch(functionChoice) {
                    case 1:
                        cout << "Enter coefficients a, b, and c for ax + b = c: ";
                        cin >> num1 >> num2 >> num3;
                        solveFirstDegreeEquation(num1, num2, num3);
                        break;
                    case 2:
                        cout << "Enter coefficients a, b, and c for ax^2 + bx + c = 0: ";
                        cin >> num1 >> num2 >> num3;
                        solveSecondDegreeEquation(num1, num2, num3);
                        break;
					case 3:
						inverseMatrixLinearEquations();
						break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            case 6: // Miscellaneous
                cout << "\nMiscellaneous:\n";
                cout << "1. Currency exchange\n";
                cout << "2. Swap numbers\n";
                cout << "3. Convert distance (km to m or m to km)\n";
				cout << "4. Array Operations\n";
				cout << "5. User Input Array Operations\n";
				cout << "6. Multiply Array by Number\n";
				cout << "7. Matrix Operations\n";
                cout << "8. Two Linear Regression Examples\n";
                cout << "Enter your function choice: ";
                cin >> functionChoice;
                switch(functionChoice) {
                    case 1:
                        double rate;
                        char direction;
                        cout << "Enter the amount: ";
                        cin >> num1;
                        cout << "Enter the exchange rate: ";
                        cin >> rate;
                        cout << "Convert from dollars to euros (d) or euros to dollars (e)? ";
                        cin >> direction;
                        currencyExchange(num1, rate, direction == 'd' || direction == 'D');
                        break;
                    case 2:
                        cout << "Enter two numbers: ";
                        cin >> num1 >> num2;
                        cout << "Before swap: num1 = " << num1 << ", num2 = " << num2 << endl;
                        swapNumbers(num1, num2);
                        cout << "After swap: num1 = " << num1 << ", num2 = " << num2 << endl;
                        break;
                    case 3:
                        char unit;
                        cout << "Enter distance: ";
                        cin >> num1;
                        cout << "Convert from km to m (k) or m to km (m)? ";
                        cin >> unit;
                        convertDistance(num1, unit == 'k' || unit == 'K');
                        break;
					case 4:
						arrayOperations();
						break;
					case 5:
						userInputArrayOperations();
						break;
					case 6:
						multiplyArrayByNumber();
						break;
					case 7:
						matrixOperations();
						break;	
                    case 8:
                        LinearRegression model;
                        int choice;
                        
                        cout << "Choose the example:\n";
                        cout << "1. Study Hours vs Exam Score\n";
                        cout << "2. House Size vs Price\n";
                        cout << "Enter your choice (1 or 2): ";
                        cin >> choice;

                        if (choice == 1) {
                            // Example 1: Study Hours vs Exam Score
                            vector<double> study_hours = {2, 3, 4, 5, 6, 7, 8};
                            vector<double> exam_scores = {65, 70, 75, 80, 85, 90, 95};
                            
                            model.fit(study_hours, exam_scores);
                            model.printStats();
                            
                            double study_time = 5;  // Predict score for 5 hours of study
                            cout << "\nPredicted exam score for " << study_time << " hours of study: "
                                << model.predict(study_time) << endl;
                        }
                        else if (choice == 2) {
                            // Example 2: House Size vs Price
                            vector<double> house_sizes = {1000, 1500, 1800, 2200, 2500, 3000, 3500};
                            vector<double> house_prices = {200000, 300000, 350000, 400000, 450000, 500000, 550000};
                            
                            model.fit(house_sizes, house_prices);
                            model.printStats();
                            
                            double house_size = 2000;  // Predict price for 2000 sq ft house
                            cout << "\nPredicted house price for " << house_size << " sq ft: $"
                                << model.predict(house_size) << endl;
                        }
                        else {
                            cout << "Invalid choice!" << endl;
                        }
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
			case 7: // Fun Activities
                cout << "\nFun Activities:\n";
                cout << "1. T-Shirt Customization\n";
                cout << "2. Quiz Game\n";
                cout << "Enter your function choice: ";
                cin >> functionChoice;
                switch(functionChoice) {
                    case 1:
                        cin.ignore(); // Clear the input buffer
                        tShirtCustomization();
                        break;
                    case 2:
                        quizGame();
                        break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid category choice. Please try again.\n";
        }
    } while (categoryChoice != 0);

    return 0;
}

// Function implementations

void basicOperations(double num1, double num2) {
    cout << "Addition: " << num1 + num2 << endl;
    cout << "Subtraction: " << num1 - num2 << endl;
    cout << "Multiplication: " << num1 * num2 << endl;
    if (num2 != 0) {
        cout << "Division: " << num1 / num2 << endl;
    } else {
        cout << "Division by zero is undefined." << endl;
    }
}

void averageNumbers(double num1, double num2) {
    cout << "Average: " << (num1 + num2) / 2 << endl;
}

void checkEvenOdd(int num1, int num2) {
    cout << num1 << " is " << (num1 % 2 == 0 ? "even" : "odd") << endl;
    cout << num2 << " is " << (num2 % 2 == 0 ? "even" : "odd") << endl;
}

void checkPositiveNegativeZero(double num1, double num2) {
    auto check = [](double num) {
        if (num > 0) return "positive";
        if (num < 0) return "negative";
        return "zero";
    };
    cout << num1 << " is " << check(num1) << endl;
    cout << num2 << " is " << check(num2) << endl;
}

void calculateSquareRoot(double num) {
    if (num >= 0) {
        cout << "Square root of " << num << " is " << customSqrt(num) << endl;
    } else {
        cout << "Cannot calculate square root of a negative number." << endl;
    }
}

void calculateAbsoluteValue(double num) {
    cout << "Absolute value of " << num << " is " << customAbs(num) << endl;
}

void calculateSquarePerimeterArea(double side) {
    cout << "Perimeter of the square: " << 4 * side << endl;
    cout << "Area of the square: " << side * side << endl;
}

void multiplicationTableTwo() {
    for (int i = 1; i <= 12; ++i) {
        cout << "2 x " << i << " = " << 2 * i << endl;
    }
}

void calculateHypotenuse(double a, double b) {
    double hypotenuse = customSqrt(a*a + b*b);
    cout << "Hypotenuse: " << hypotenuse << endl;
}

void currencyExchange(double amount, double rate, bool dollarsToEuros) {
    if (dollarsToEuros) {
        cout << amount << " USD = " << amount * rate << " EUR" << endl;
    } else {
        cout << amount << " EUR = " << amount * rate << " USD" << endl;
    }
}

void swapNumbers(double &num1, double &num2) {
    double temp = num1;
    num1 = num2;
    num2 = temp;
}

void findSmallestOfThree(double num1, double num2, double num3) {
    double smallest = num1;
    if (num2 < smallest) smallest = num2;
    if (num3 < smallest) smallest = num3;
    cout << "The smallest number is: " << smallest << endl;
}

void findLargestOfThree(double num1, double num2, double num3) {
    double largest = num1;
    if (num2 > largest) largest = num2;
    if (num3 > largest) largest = num3;
    cout << "The largest number is: " << largest << endl;
}

void sumOfSquares(double num1, double num2) {
    double result = num1*num1 + num2*num2;
    cout << "Sum of squares: " << result << endl;
}

void findMinMaxOfThree(double num1, double num2, double num3) {
    double smallest = num1, largest = num1;
    if (num2 < smallest) smallest = num2;
    if (num3 < smallest) smallest = num3;
    if (num2 > largest) largest = num2;
    if (num3 > largest) largest = num3;
    cout << "Smallest: " << smallest << ", Largest: " << largest << endl;
}

void findLargestofTwo(double num1, double num2) {
	double largest = num1;
	if (num2 > largest) largest = num2;
	cout << "Largest: " << largest << endl;
}

void sumFirstHundredIntegers() {
    int sum = (100 * 101) / 2;  // Using the formula n(n+1)/2
    cout << "Sum of first 100 integers: " << sum << endl;
}

void sumFirstHundredEvenIntegers() {
    int sum = 100 * (100 + 1);  // Using the formula n(n+1) for first n even numbers
    cout << "Sum of first 100 even integers: " << sum << endl;
}

void solveFirstDegreeEquation(double a, double b, double c) {
    if (a == 0) {
        if (b == c) {
            cout << "All real numbers are solutions (0x + " << b << " = " << c << ")." << endl;
        } else {
            cout << "No solution exists (" << b << " ≠ " << c << ")." << endl;
        }
    } else {
        double x = (c - b) / a;
        cout << "Solution: x = " << x << endl;
    }
}

void solveSecondDegreeEquation(double a, double b, double c) {
    if (a == 0) {
        solveFirstDegreeEquation(b, c, 0);  // Convert to first-degree equation bx + c = 0
        return;
    }

    double discriminant = b*b - 4*a*c;
    
    if (discriminant > 0) {
        double x1 = (-b + customSqrt(discriminant)) / (2*a);
        double x2 = (-b - customSqrt(discriminant)) / (2*a);
        cout << "Two real roots: x1 = " << x1 << ", x2 = " << x2 << endl;
    } else if (discriminant == 0) {
        double x = -b / (2*a);
        cout << "One real root: x = " << x << endl;
    } else {
        double realPart = -b / (2*a);
        double imaginaryPart = customSqrt(-discriminant) / (2*a);
        cout << "Complex roots: " << endl;
        cout << "x1 = " << realPart << " + " << imaginaryPart << "i" << endl;
        cout << "x2 = " << realPart << " - " << imaginaryPart << "i" << endl;
    }
}

void sumFirstNIntegers(int N) {
    if (N <= 0) {
        cout << "N must be greater than 0." << endl;
        return;
    }
    long long sum = (N * (N + 1LL)) / 2;  // Using the formula n(n+1)/2
    cout << "Sum of first " << N << " integers: " << sum << endl;
}

void sumFirstNEvenIntegers(int N) {
    if (N <= 0) {
        cout << "N must be greater than 0." << endl;
        return;
    }
    long long sum = N * (N + 1LL);  // Using the formula n(n+1) for first n even numbers
    cout << "Sum of first " << N << " even integers: " << sum << endl;
}

void convertDistance(double distance, bool kmToM) {
    if (kmToM) {
        cout << distance << " km = " << distance * 1000 << " m" << endl;
    } else {
        cout << distance << " m = " << distance / 1000 << " km" << endl;
	}
}

// New function implementation for T-Shirt Customization
void tShirtCustomization() {
    const string shirtTypes[] = {"Mens", "Womens"};
    const string sizes[] = {"XS", "S", "M", "L", "XL"};
    const string materials[] = {"Cotton", "Nylon", "Polyester", "Linen", "Wool", "Denim"};
    const string brands[] = {"Nike", "Adidas", "Puma", "Under Armour", "Reebok"};

    cout << "Welcome to the Shirt Customization Program!" << endl;
    string shirtType = shirtTypes[getChoice("Select shirt type: ", shirtTypes, 2) - 1];
    string size = sizes[getChoice("Select size: ", sizes, 5) - 1];
    string material = materials[getChoice("Select material: ", materials, 6) - 1];
    string colorChoice = getYesNo("Do you want multiple colors? ");
    string colors;
    if (colorChoice[0] == 'y' || colorChoice[0] == 'Y') {
        colors = getInput("Enter the colors you want (comma-separated): ");
    } else {
        colors = getInput("Enter the color you want: ");
    }
    string brand = brands[getChoice("Select brand: ", brands, 5) - 1];
    string pockets = getYesNo("Do you want pockets? ");
    string print = getYesNo("Do you want a print on your shirt? ");
    string printDesign;
    if (print[0] == 'y' || print[0] == 'Y') {
        printDesign = getInput("Enter the print design: ");
    }
    string hood = getYesNo("Do you want a hood? ");

    cout << "\nThis is the shirt you ordered: " << endl;
    cout << "--------------------------------" << endl;
    cout << "A " << shirtType << "'s shirt in size " << size << ", in colors " << colors
         << ", made out of " << material << ", by " << brand << ", "
         << (pockets[0] == 'y' || pockets[0] == 'Y' ? "with pockets, " : "without pockets, ")
         << (print[0] == 'y' || print[0] == 'Y' ? "with print, " : "without print, ")
         << (hood[0] == 'y' || hood[0] == 'Y' ? "and with hood. " : "and without hood. ") << endl;
    if (print[0] == 'y' || print[0] == 'Y') {
        cout << "Your shirt has the print design: " << printDesign << endl;
    }
}

// New function implementation for Quiz Game
void quizGame() {
    int score = 0;
    string answer;
    
    cout << "Welcome to the Quiz Game!\n\n";

    // Q1
    cout << "Question 1: What year was the game platform Steam released?\n";
    cout << "a) 2000\nb) 2001\nc) 2002\nd) 2003\n";
    cout << "Your answer: ";
    cin >> answer;
    if (answer == "d" || answer == "D" || answer == "4" || answer == "2003") {
        score += 100;
        cout << "Correct!\n";
    } else {
        cout << "Incorrect. Steam was released in 2003.\n";
    }

    // Q2
    cout << "\nQuestion 2: What is the capital of Canada?\n";
    cout << "a) London\nb) Vienna\nc) Ottawa\nd) Prague\n";
    cout << "Your answer: ";
    cin >> answer;
    if (answer == "c" || answer == "C" || answer == "3" || answer == "Ottawa" || answer == "ottawa") {
        score += 100;
        cout << "Correct!\n";
    } else {
        cout << "Incorrect. The capital of Canada is Ottawa.\n";
    }

    // Q3
    cout << "\nQuestion 3: In what city is the British vehicle show, Top Gear, filmed?\n";
    cout << "a) Surrey\nb) Cambridge\nc) Oxford\nd) York\n";
    cout << "Your answer: ";
    cin >> answer;
if (answer == "a" || answer == "A" || answer == "1" || answer == "Surrey" || answer == "surrey") {
        score += 100;
        cout << "Correct!\n";
    } else {
        cout << "Incorrect. Top Gear is filmed in the town of Surrey, England.\n";
    }

    // Q4
    cout << "\nQuestion 4: There is a town in Australia that is different from any other city in the world. What is it?\n";
    cout << "a) Perth\nb) 1770\nc) Cairns\nd) Geelong\n";
    cout << "Your answer: ";
    cin >> answer;
    if (answer == "b" || answer == "B" || answer == "2" || answer == "1770") {
        score += 100;
        cout << "Correct!\n";
    } else {
        cout << "Incorrect. It is 1770, a town in Queensland, Australia.\n";
    }

    // Q5
    cout << "\nQuestion 5: Was 'The Marvels' the lowest grossing film of 2023?\n";
    cout << "a) Yes\nb) No\n";
    cout << "Your answer: ";
    cin >> answer;
    if (answer == "a" || answer == "A" || answer == "yes" || answer == "Yes" || answer == "YES" || answer == "y" || answer == "Y") {
        score += 100;
        cout << "Correct!\n";
    } else {
        cout << "Incorrect. 'The Marvels' bombed quite hard, with an overall loss of 237 million dollars.\n";
    }

    cout << "\nYour total score was: " << score << " points\n";

    if (score >= 300) {
        cout << "Congratulations! Your knowledge is vast and impeccable!\n";
    } else {
        cout << "Almost there! You got this!\n";
    }
}

void arrayOperations() {
    const int size = 5;
    double a1[size] = {2.0, 4.0, 6.0, 8.0, 10.0};
    double b1[size] = {20.0, 40.0, 60.0, 80.0, 100.0};
    double c1[size];

    cout << "Array Operations:" << endl;
    cout << fixed << setprecision(2); // Set output precision to 2 decimal places

    // a1 + b1
    cout << "a1 + b1: ";
    for (int i = 0; i < size; ++i) {
        c1[i] = a1[i] + b1[i];
        cout << c1[i] << " ";
    }
    cout << endl;

    // a1 - b1
    cout << "a1 - b1: ";
    for (int i = 0; i < size; ++i) {
        c1[i] = a1[i] - b1[i];
        cout << c1[i] << " ";
    }
    cout << endl;

    // b1 - a1
    cout << "b1 - a1: ";
    for (int i = 0; i < size; ++i) {
        c1[i] = b1[i] - a1[i];
        cout << c1[i] << " ";
    }
    cout << endl;

    // a1 * b1
    cout << "a1 * b1: ";
    for (int i = 0; i < size; ++i) {
        c1[i] = a1[i] * b1[i];
        cout << c1[i] << " ";
    }
    cout << endl;

    // a1 / b1
    cout << "a1 / b1: ";
    for (int i = 0; i < size; ++i) {
        if (b1[i] != 0) {
            c1[i] = a1[i] / b1[i];
            cout << c1[i] << " ";
        } else {
            cout << "Undefined ";
        }
    }
    cout << endl;
}

void userInputArrayOperations() {
    const int size = 5;
    double a1[size], b1[size], c1[size];

    cout << "Enter 5 values for array a1:" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> a1[i];
    }

    cout << "Enter 5 values for array b1:" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> b1[i];
    }

    cout << "Array Operations:" << endl;
    cout << fixed << setprecision(2); // Set output precision to 2 decimal places

    // a1 + b1
    cout << "a1 + b1: ";
    for (int i = 0; i < size; ++i) {
        c1[i] = a1[i] + b1[i];
        cout << c1[i] << " ";
    }
    cout << endl;

    // a1 - b1
    cout << "a1 - b1: ";
    for (int i = 0; i < size; ++i) {
        c1[i] = a1[i] - b1[i];
        cout << c1[i] << " ";
    }
    cout << endl;

    // b1 - a1
    cout << "b1 - a1: ";
    for (int i = 0; i < size; ++i) {
        c1[i] = b1[i] - a1[i];
        cout << c1[i] << " ";
    }
    cout << endl;

    // a1 * b1
    cout << "a1 * b1: ";
    for (int i = 0; i < size; ++i) {
        c1[i] = a1[i] * b1[i];
        cout << c1[i] << " ";
    }
    cout << endl;

    // a1 / b1
    cout << "a1 / b1: ";
    for (int i = 0; i < size; ++i) {
        if (b1[i] != 0) {
            c1[i] = a1[i] / b1[i];
            cout << c1[i] << " ";
        } else {
            cout << "Undefined ";
        }
    }
    cout << endl;
}

void multiplyArrayByNumber() {
    const int size = 5;
    double arr[size];
    double n;

    cout << "Enter 5 values for the array:" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    cout << "Enter the number to multiply by: ";
    cin >> n;

    cout << "Result: ";
    cout << fixed << setprecision(2); // Set output precision to 2 decimal places
    for (int i = 0; i < size; ++i) {
        arr[i] *= n;
        cout << arr[i] << " ";
    }
    cout << endl;
}

void matrixOperations() {
    const int rows = 2, cols = 2;
    double matrix1[rows][cols], matrix2[rows][cols], result[rows][cols];

    cout << "Enter values for first 2x2 matrix:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix1[i][j];
        }
    }

    cout << "Enter values for second 2x2 matrix:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix2[i][j];
        }
    }

    cout << fixed << setprecision(2); // Set output precision to 2 decimal places

    // Matrix Addition
    cout << "Matrix Addition Result:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    // Matrix Multiplication
    cout << "Matrix Multiplication Result:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < cols; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}

void inverseMatrixLinearEquations() {
	double A[2][2], B[2], X[2];
    double invA[2][2];

    cout << "Enter the coefficients of the system of linear equations:" << endl;
    cout << "Enter a11, a12, b1 for the first equation: ";
    cin >> A[0][0] >> A[0][1] >> B[0];
    cout << "Enter a21, a22, b2 for the second equation: ";
    cin >> A[1][0] >> A[1][1] >> B[1];

    // Calculate the inverse of matrix A
    inverse(A[0][0], A[0][1], A[1][0], A[1][1], invA);

    // Multiply invA with B to get X
    matrixMultiply(invA, B, X);

    // Output the result
    cout << fixed << setprecision(4);
    cout << "The solution is:" << endl;
    cout << "x = " << X[0] << endl;
    cout << "y = " << X[1] << endl;
}


// Recursive function to calculate factorial
double calculateFactorial(double n) {
    // Base cases
    if (n <= 0) return 1;  // 0! = 1
    if (n == 1) return 1;
    
    // Recursive case
    return n * calculateFactorial(n - 1);
}

// Recursive function to calculate Fibonacci number
double calculateFibonacci(double n) {
    // Base cases
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    // Recursive case
    return calculateFibonacci(n - 1) + calculateFibonacci(n - 2);
}

// Recursive function to calculate sum of digits
double sumDigits(double n) {
    // Convert to positive number if negative
    n = customAbs(n);
    
    // Base case
    if (n < 10) return n;
    
    // Extract the last digit using modulo and division
    // We need to handle floating point numbers
    double intPart;
    double fractPart = modf(n / 10, &intPart);
    
    // Recursive case
    // Add the last digit (n % 10) to the sum of the remaining digits
    return (n - intPart * 10) + sumDigits(intPart);
}


// Helper functions for T-Shirt Customization
string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int getChoice(const string& prompt, const string options[], int optionCount) {
    cout << prompt << endl;
    for (int i = 0; i < optionCount; i++) {
        cout << i + 1 << ". " << options[i] << endl;
    }
    int choice;
    while (true) {
        cout << "Enter your choice (1 - " << optionCount << "): ";
        if (cin >> choice && choice >= 1 && choice <= optionCount) {
            cin.ignore(10000, '\n');
            return choice;
        }
        cout << "Invalid choice. Please try again." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

string getYesNo(const string& prompt) {
    while (true) {
        string input = getInput(prompt + " (yes/no): ");
        if (input == "yes" || input == "Yes" || input == "YES" || input == "y" || input == "Y" ||
            input == "no" || input == "No" || input == "NO" || input == "n" || input == "N") {
            return input;
        }
        cout << "Invalid input. Please enter 'yes' or 'no'." << endl;
    }
}