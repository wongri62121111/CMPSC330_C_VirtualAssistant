/*
	Name : Tommy Lu, Richard Wong
	Course : CMPSC 330
	Project : Virtual Assistant 
	Date : 11/21/2024
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // For setting precision in output
#include <math.h> // For math functions 
#include <random> // For random number 
#include <cstdlib>
#include <deque>
#include <ctime>
#include <limits>
#include <cmath>
#include <algorithm>

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
        cout << "The matrix is not invertible." << endl;
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

// 3x3 linear system solver with user input 
vector<double> solveLinearSystem(double a1, double b1, double c1, double d1,
                                double a2, double b2, double c2, double d2,
                                double a3, double b3, double c3, double d3) {
    vector<double> solution;
    
    double det = a1 * (b2 * c3 - b3 * c2) -
                 b1 * (a2 * c3 - a3 * c2) +
                 c1 * (a2 * b3 - a3 * b2);
    
    if (fabs(det) < 1e-10) {
        return solution;
    }
    
    double det_x = d1 * (b2 * c3 - b3 * c2) -
                   b1 * (d2 * c3 - d3 * c2) +
                   c1 * (d2 * b3 - d3 * b2);
                   
    double det_y = a1 * (d2 * c3 - d3 * c2) -
                   d1 * (a2 * c3 - a3 * c2) +
                   c1 * (a2 * d3 - a3 * d2);
                   
    double det_z = a1 * (b2 * d3 - b3 * d2) -
                   b1 * (a2 * d3 - a3 * d2) +
                   d1 * (a2 * b3 - a3 * b2);
    
    solution.push_back(det_x / det);
    solution.push_back(det_y / det);
    solution.push_back(det_z / det);
    
    return solution;
}



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

int runLinearRegressionMenu() {
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
        return -1;
    }

    return 0;
}

// Halloween Game
class TrickOrTreat {
private:
    struct Candy {
        string name;
        int rarity;  // 1 = common, 2 = uncommon, 3 = rare, 4 = legendary
        int score;
    };

    struct House {
        string description;
        vector<Candy> candyTypes;
        bool visited;
        int difficulty;  // 1-5, affects candy rarity chances
    };

    int totalCandy;
    int score;
    int movesLeft;
    vector<Candy> inventory;
    vector<House> houses;
    mt19937 rng;

    vector<Candy> commonCandy = {
        {"Mini Chocolate Bar", 1, 10},
        {"Candy Corn", 1, 10},
        {"Bubble Gum", 1, 10},
        {"Small Lollipop", 1, 10},
        {"Hard Candy", 1, 10}
    };

    vector<Candy> uncommonCandy = {
        {"Full-size Chocolate Bar", 2, 25},
        {"Sour Gummy Worms", 2, 25},
        {"Caramel Apple", 2, 25},
        {"Candy Necklace", 2, 25},
        {"Chocolate Coins", 2, 25}
    };

    vector<Candy> rareCandy = {
        {"King-size Candy Bar", 3, 50},
        {"Premium Chocolate Box", 3, 50},
        {"Artisanal Lollipop", 3, 50},
        {"Special Halloween Mix", 3, 50},
        {"Imported Chocolate", 3, 50}
    };

    vector<Candy> legendaryCandy = {
        {"Golden Chocolate Bar", 4, 100},
        {"Mystical Halloween Treat", 4, 100},
        {"Enchanted Candy Box", 4, 100},
        {"Haunted House Special", 4, 100},
        {"Ultimate Candy Collection", 4, 100}
    };

    void initializeHouses() {
        houses = {
            {"A spooky Victorian mansion with cobwebs everywhere", {}, false, 5},
            {"A cozy cottage with jack-o'-lanterns lining the path", {}, false, 1},
            {"A modern house with elaborate Halloween decorations", {}, false, 3},
            {"A dimly lit house with creepy music playing", {}, false, 4},
            {"A friendly-looking house with a 'Happy Halloween' banner", {}, false, 2},
            {"An old cemetery keeper's house", {}, false, 5},
            {"A haunted lighthouse by the sea", {}, false, 4},
            {"A witch's cottage deep in the woods", {}, false, 5},
            {"A suburban house with animatronic decorations", {}, false, 2},
            {"A spooky treehouse with glowing windows", {}, false, 3},
            {"An abandoned school turned haunted house", {}, false, 4},
            {"A mysterious carnival trailer", {}, false, 3},
            {"A gothic church converted to a residence", {}, false, 5},
            {"A cute house with carved pumpkins everywhere", {}, false, 1},
            {"A mad scientist's laboratory", {}, false, 4}
        };

        // Populate each house with possible candy based on difficulty
        for (auto& house : houses) {
            house.candyTypes = generateCandyList(house.difficulty);
        }
    }

    vector<Candy> generateCandyList(int difficulty) {
        vector<Candy> possibleCandy;
        
        // Add candy based on house difficulty
        possibleCandy.insert(possibleCandy.end(), commonCandy.begin(), commonCandy.end());
        
        if (difficulty >= 2) {
            possibleCandy.insert(possibleCandy.end(), uncommonCandy.begin(), uncommonCandy.end());
        }
        
        if (difficulty >= 4) {
            possibleCandy.insert(possibleCandy.end(), rareCandy.begin(), rareCandy.end());
        }
        
        if (difficulty == 5) {
            possibleCandy.insert(possibleCandy.end(), legendaryCandy.begin(), legendaryCandy.end());
        }
        
        return possibleCandy;
    }

    void displayStatus() {
        cout << "\n=== Status ===";
        cout << "\nMoves remaining: " << movesLeft;
        cout << "\nCurrent Score: " << score;
        cout << "\nCandy Count: " << totalCandy;
        cout << "\nInventory:";
        if (inventory.empty()) {
            cout << " Empty";
        } else {
            for (const auto& candy : inventory) {
                string rarity;
                switch(candy.rarity) {
                    case 1: rarity = "Common"; break;
                    case 2: rarity = "Uncommon"; break;
                    case 3: rarity = "Rare"; break;
                    case 4: rarity = "Legendary"; break;
                }
                cout << "\n- " << candy.name << " (" << rarity << ", Score: " << candy.score << ")";
            }
        }
        cout << "\n\n";
    }

    void printLine(const string& text) {
        cout << text << endl;
    }

    int getValidInput(int max) {
        int choice;
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Please enter a valid number between 1 and " << max << ": ";
                continue;
            }
            
            cin.ignore(10000, '\n');
            
            if (choice >= 1 && choice <= max) {
                return choice;
            }
            
            cout << "Please enter a number between 1 and " << max << ": ";
        }
    }

    void visitHouse(int index) {
        House& house = houses[index];
        if (house.visited) {
            printLine("You've already visited this house! The lights are now off.");
            return;
        }

        printLine("\nYou approach " + house.description + "...");
        printLine("*Knock knock*");

        if (rng() % 10 < 8) { // 80% chance of success
            printLine("The door opens!");
            
            // Candy rarity chances based on house difficulty
            int randNum = rng() % 100;
            int candyIndex;
            vector<Candy>& possibleCandy = house.candyTypes;
            
            // Select candy based on rarity and house difficulty
            if (house.difficulty == 5 && randNum < 10) {  // 10% chance for legendary in difficulty 5
                candyIndex = rng() % legendaryCandy.size();
                Candy receivedCandy = legendaryCandy[candyIndex];
                printLine("WOW! You received a LEGENDARY treat: " + receivedCandy.name);
                inventory.push_back(receivedCandy);
                score += receivedCandy.score;
            } else if (house.difficulty >= 4 && randNum < 30) {  // 30% chance for rare in difficulty 4+
                candyIndex = rng() % rareCandy.size();
                Candy receivedCandy = rareCandy[candyIndex];
                printLine("Amazing! You received a RARE treat: " + receivedCandy.name);
                inventory.push_back(receivedCandy);
                score += receivedCandy.score;
            } else if (house.difficulty >= 2 && randNum < 60) {  // 60% chance for uncommon in difficulty 2+
                candyIndex = rng() % uncommonCandy.size();
                Candy receivedCandy = uncommonCandy[candyIndex];
                printLine("Nice! You received an UNCOMMON treat: " + receivedCandy.name);
                inventory.push_back(receivedCandy);
                score += receivedCandy.score;
            } else {
                candyIndex = rng() % commonCandy.size();
                Candy receivedCandy = commonCandy[candyIndex];
                printLine("You received a common treat: " + receivedCandy.name);
                inventory.push_back(receivedCandy);
                score += receivedCandy.score;
            }
            totalCandy++;
        } else {
            printLine("No one answers... Maybe they ran out of candy!");
        }

        house.visited = true;
        movesLeft--;
    }

public:
    TrickOrTreat() : totalCandy(0), score(0), movesLeft(10) {
        rng.seed(12345);
        initializeHouses();
    }

    void playGame() {
        printLine("Welcome to the Halloween Trick-or-Treating Adventure!");
        printLine("Your goal is to collect the most valuable candy possible!");
        printLine("You have 10 moves before your parents call you home!");
        printLine("\nCandy Rarity Levels:");
        printLine("Common (10 pts) - Uncommon (25 pts) - Rare (50 pts) - Legendary (100 pts)");
        printLine("Harder houses have better candy chances!\n");
        
        while (movesLeft > 0) {
            displayStatus();
            
            cout << "\nAvailable houses:\n";
            for (size_t i = 0; i < houses.size(); ++i) {
                cout << (i + 1) << ". " << houses[i].description;
                cout << " (Difficulty: " << houses[i].difficulty << "/5)";
                if (houses[i].visited) cout << " (Visited)";
                cout << endl;
            }
            cout << (houses.size() + 1) << ". End trick-or-treating early\n";
            
            cout << "\nWhich house would you like to visit? (1-" << houses.size() + 1 << "): ";
            int choice = getValidInput(houses.size() + 1);
            
            if (choice == houses.size() + 1) {
                break;
            }
            
            visitHouse(choice - 1);
        }

        printLine("\n=== Game Over ===");
        printLine("Time to head home! Here's how you did:");
        printLine("Total Candy Collected: " + to_string(totalCandy));
        printLine("Final Score: " + to_string(score));
        
        if (score >= 500) {
            printLine("AMAZING! You're the Halloween Champion!");
        } else if (score >= 300) {
            printLine("Great job! You got quite a haul!");
        } else if (score >= 100) {
            printLine("Not bad! You got some good treats!");
        } else {
            printLine("Better luck next year!");
        }
    }
};

//Point Class 
class Point {
	public:
		int x, y;
		Point(int x1, int y1) : x(x1), y(y1) {}
		// Overloading the + operator
		Point operator+(const Point &p) {
			Point point(x + p.x, y + p.y);
			return point;
	}
};

//Shape Class
class Shape {
   public:
    virtual double area() = 0;  // Pure virtual function
};
class Circle : public Shape {
   private:
    double radius;

   public:
    Circle(double r) : radius(r) {}
    double area() { return 3.14 * radius * radius; }
};

//Animal Class 
class Animal {
   public:
    virtual void speak() { cout << "Some sound" << endl; }
};
class Cat : public Animal {
   public:
    void speak() override { cout << "Meow" << endl; }
};

// Function to demonstrate Circle
void demonstrateCircle() {
    Circle circle(5);
    cout << "Area of circle: " << circle.area() << endl;
}

// Function to demonstrate Point
void demonstratePoint() {
    Point p1(10, 5), p2(2, 4);
    Point p3 = p1 + p2; // Operator overloading example
    cout << "Point p3: (" << p3.x << ", " << p3.y << ")" << endl;
}

// Function to demonstrate Animal and Cat
void demonstrateAnimal() {
    Cat myCat;
    myCat.speak();
}

// Wellness bot class 
class WellnessBot {
private:
    struct ActivityMultiplier {
        string level;
        double multiplier;
    };

    const vector<ActivityMultiplier> ACTIVITY_MULTIPLIERS = {
        {"sedentary", 1.2},
        {"lightly active", 1.375},
        {"moderately active", 1.55},
        {"very active", 1.725}
    };

    struct MacroRatio {
        double carbs = 0.5;    // 50% of calories from carbs
        double protein = 0.2;  // 20% of calories from protein
        double fats = 0.3;     // 30% of calories from fats
    };

    const double CALORIES_PER_GRAM_PROTEIN = 4.0;
    const double CALORIES_PER_GRAM_CARBS = 4.0;
    const double CALORIES_PER_GRAM_FAT = 9.0;

    const double WATER_INTAKE_MULTIPLIER = 0.033; // Liters of water per kg

    struct BMIThresholds {
        const double underweight = 18.5;
        const double normal = 24.9;
        const double overweight = 29.9;
    } bmiThresholds;

    static bool isValidGender(const string& gender) {
        string lower = gender;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return (lower == "male" || lower == "female");
    }

    static bool isValidActivityLevel(const string& level) {
        string lower = level;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return (lower == "sedentary" || lower == "lightly active" || 
                lower == "moderately active" || lower == "very active");
    }

    static bool isValidLifestyle(const string& lifestyle) {
        string lower = lifestyle;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return (lower == "smoking" || lower == "alcohol" || lower == "none");
    }

    static bool isValidDietaryPref(const string& pref) {
        string lower = pref;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return (lower == "vegetarian" || lower == "vegan" || lower == "none");
    }

    template<typename T>
    static T getValidInput(const string& prompt, T min_value, T max_value) {
        T value;
        while (true) {
            cout << prompt;
            if (cin >> value && value >= min_value && value <= max_value) {
                break;
            }
            cout << "Invalid input. Please enter a value between " 
                 << min_value << " and " << max_value << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return value;
    }

    static string getValidStringInput(const string& prompt, 
                                      bool (*validationFunc)(const string&)) {
        string input;
        while (true) {
            cout << prompt;
            getline(cin, input);
            if (validationFunc(input)) {
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                return input;
            }
            cout << "Invalid input. Please try again.\n";
        }
    }

public:
    struct UserProfile {
        int age;
        string gender;
        double height;  // in meters
        double weight;  // in kg
        string activityLevel;
        int sleepHours;
        string lifestyle;
        string dietaryPref;
        int stressLevel; // Scale of 1 to 10
        int caffeineIntake; // Cups per day

        // Calculated values
        double bmi;
        double bmr;
        double dailyCalories;
        double dailyWaterIntake; // in liters
    };
	
	void run() {
        auto profile = collectUserData();
        calculateMetrics(profile);
        displayResults(profile);
    }
	
    UserProfile collectUserData() {
        UserProfile profile;
        
        profile.age = getValidInput<int>("Enter your age: ", 1, 120);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        profile.gender = getValidStringInput("Enter your gender (male/female): ", isValidGender);
        
        profile.height = getValidInput<double>("Enter your height (in meters): ", 0.5, 2.5);
        profile.weight = getValidInput<double>("Enter your weight (in kg): ", 20.0, 300.0);
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        profile.activityLevel = getValidStringInput(
            "Enter your activity level (sedentary, lightly active, moderately active, very active): ",
            isValidActivityLevel
        );
        
        profile.sleepHours = getValidInput<int>("Enter your hours of sleep per night: ", 0, 24);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        profile.lifestyle = getValidStringInput(
            "Enter your lifestyle habits (smoking, alcohol, none): ",
            isValidLifestyle
        );
        
        profile.dietaryPref = getValidStringInput(
            "Enter your dietary preferences (vegetarian, vegan, none): ",
            isValidDietaryPref
        );

        profile.stressLevel = getValidInput<int>("Rate your stress level (1-10): ", 1, 10);
        profile.caffeineIntake = getValidInput<int>("Enter your daily caffeine intake (cups): ", 0, 20);

        return profile;
    }

    void calculateMetrics(UserProfile& profile) {
        profile.bmi = profile.weight / pow(profile.height, 2);
        
        if (profile.gender == "male") {
            profile.bmr = 88.362 + (13.397 * profile.weight) + 
                          (4.799 * profile.height * 100) - (5.677 * profile.age);
        } else {
            profile.bmr = 447.593 + (9.247 * profile.weight) + 
                          (3.098 * profile.height * 100) - (4.330 * profile.age);
        }

        for (const auto& activity : ACTIVITY_MULTIPLIERS) {
            if (activity.level == profile.activityLevel) {
                profile.dailyCalories = profile.bmr * activity.multiplier;
                break;
            }
        }

        profile.dailyWaterIntake = profile.weight * WATER_INTAKE_MULTIPLIER;
    }

    void displayResults(const UserProfile& profile) {
        cout << "\n=== Wellness Assessment Results ===\n\n";
        
        cout << "BMI: " << fixed << setprecision(2) << profile.bmi << " - ";
        if (profile.bmi < bmiThresholds.underweight)
            cout << "Category: Underweight\n";
        else if (profile.bmi < bmiThresholds.normal)
            cout << "Category: Normal weight\n";
        else if (profile.bmi < bmiThresholds.overweight)
            cout << "Category: Overweight\n";
        else
            cout << "Category: Obese\n";

        cout << "\nBMR: " << fixed << setprecision(2) 
             << profile.bmr << " calories/day\n";
        cout << "Daily Caloric Needs: " << profile.dailyCalories << " calories\n";
        cout << "Daily Water Intake: " << profile.dailyWaterIntake << " liters\n";

        MacroRatio macros;
        cout << "\nRecommended Macronutrient Distribution:";
        cout << "\n  - Carbohydrates: " 
             << (profile.dailyCalories * macros.carbs / CALORIES_PER_GRAM_CARBS) 
             << " grams";
        cout << "\n  - Protein: " 
             << (profile.dailyCalories * macros.protein / CALORIES_PER_GRAM_PROTEIN) 
             << " grams";
        cout << "\n  - Fats: " 
             << (profile.dailyCalories * macros.fats / CALORIES_PER_GRAM_FAT) 
             << " grams\n";

        provideRecommendations(profile);
    }

    void provideRecommendations(const UserProfile& profile) {
        cout << "\n=== Personalized Recommendations ===\n";

        cout << "\nExercise Recommendations:\n";
        if (profile.bmi >= bmiThresholds.normal) {
            cout << "- Focus on low-impact activities like walking or swimming\n";
            cout << "- Include strength training and flexibility exercises\n";
        } else {
            cout << "- Maintain a balanced exercise routine\n";
        }

        cout << "\nSleep Recommendations:\n";
        if (profile.sleepHours < 7) {
            cout << "- Aim to get 7-8 hours of sleep per night\n";
        }

        cout << "\nHydration Tips:\n";
        cout << "- Drink at least " << profile.dailyWaterIntake << " liters of water daily.\n";

        cout << "\nMental Health Tips:\n";
        if (profile.stressLevel >= 7) {
            cout << "- Consider relaxation techniques such as meditation or yoga.\n";
        }

        cout << "\nDietary Recommendations:\n";
        if (profile.dietaryPref == "vegetarian") {
            cout << "- Focus on protein sources like legumes and eggs.\n";
        } else if (profile.dietaryPref == "vegan") {
            cout << "- Include plant-based iron and calcium sources.\n";
        } else {
            cout << "- Opt for lean meats and whole grains.\n";
        }
    }
};


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
void tic_tac_toe();
void conways_game_of_life();
void minesweeper();
// Array
void arrayOperations();
void userInputArrayOperations();
void multiplyArrayByNumber();
void matrixOperations();
void inverseMatrixLinearEquations();
void solveLinearSystemFromInput();
// Recursive functions 
double calculateFactorial(double n);
double calculateFibonacci(double n);
double sumDigits(double n);
// Linear Regression
int runLinearRegressionMenu();
// Function to demonstrate pointers with famous U.S. buildings
void demonstratePointers();
// Various functions
void weightConversion();
void bubbleSort();
void selectionSort();
void merge();
void mergeSort();
void performMergeSort();
void mealCostCalculator();
void randomIntegerGenerator();
void randomInRange();
void timezoneConversion();
void volumeCalculator();
// Array operations with pointers
void addArraysWithPointers();
void subtractArraysWithPointers();
void multiplyArraysWithPointers();
void divideArraysWithPointers();
void moduloArraysWithPointers();

const int SIZE = 6; // Size of the arrays


// Helper functions for T-Shirt Customization
string getInput(const string& prompt);
int getChoice(const string& prompt, const string options[], int optionCount);
string getYesNo(const string& prompt);

int main() {
    int categoryChoice, functionChoice;
    double num1, num2, num3;
	TrickOrTreat game;
	WellnessBot bot;
	

    do {
        cout << "\nVirtual Assistant Operations Categories:\n";
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
                cout << "1. Basic arithmetic (+-*/) [#1-4][#39-40]\n";
                cout << "2. Average of two numbers [#5]\n";
                cout << "3. Absolute value [#9]\n";
                cout << "4. Square root [#8]\n";
                cout << "5. Sum of squares [#20]\n";
				cout << "6. Meal cost and tip calculator [#45]\n";
				cout << "7. Random number generator [#46]\n";
				cout << "8. Random number generator between two numbers [#47]\n";
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
					case 6:
						mealCostCalculator();
						break;
					case 7:
						randomIntegerGenerator();
						break;
					case 8:
						randomInRange();
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            case 2: // Number Properties
                cout << "\nNumber Properties:\n";
                cout << "1. Check even/odd [#6]\n";
                cout << "2. Check positive/negative/zero [#7]\n";
				cout << "3. Find largest of two numbers [#38]\n";
                cout << "4. Find smallest of three numbers [#18]\n";
                cout << "5. Find largest of three numbers [#19]\n";
                cout << "6. Find min and max of three numbers [#21]\n";
				cout << "7. Array addition with pointers [#66]\n";
				cout << "8. Array subtraction with pointers [#67]\n";
				cout << "9. Array multiplication with pointers [#68]\n";
				cout << "10. Array division with pointers [#69]\n";
				cout << "11. Array modulo with pointers [#70]\n";
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
					case 7:
						addArraysWithPointers();
						break;
					case 8:
						subtractArraysWithPointers();
						break;
					case 9:
						multiplyArraysWithPointers();
						break;
					case 10:
						divideArraysWithPointers();
						break;
					case 11:
						moduloArraysWithPointers();
						break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            case 3: // Geometry
                cout << "\nGeometry:\n";
                cout << "1. Calculate square perimeter and area [#10]\n";
                cout << "2. Calculate hypotenuse [#14]\n";
				cout << "3. Cube, Sphere and Cylinder volume calculator [#49]\n";
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
					case 3:
						volumeCalculator();
						break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            case 4: // Series and Sequences
                cout << "\nSeries and Sequences:\n";
                cout << "1. Multiplication table of 2 [#11-13]\n";
                cout << "2. Sum of first 100 integers [#22]\n";
                cout << "3. Sum of first 100 even integers [#23]\n";
                cout << "4. Sum of first N integers [#26]\n";
                cout << "5. Sum of first N even integers [#27]\n";
				cout << "6. Calculate Factorial [#52]\n";          
				cout << "7. Calculate Fibonacci Number [#53]\n";    
				cout << "8. Calculate Sum of Digits [#54]\n";  
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
                cout << "1. Solve first-degree equation [#24]\n";
                cout << "2. Solve second-degree equation [#25]\n";
				cout << "3. Solving a system of two linear equations with the inverse matrix method [#58]\n";
				cout << "4. Solving a system of three linear equations [#59]\n";
				cout << "5. Linear Regression example [#61-62]\n";
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
					case 4:
						solveLinearSystemFromInput();
						break;
					case 5:
						runLinearRegressionMenu();
						break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            case 6: // Miscellaneous
                cout << "\nMiscellaneous:\n";
                cout << "1. Currency exchange [#15-16]\n";
                cout << "2. Swap numbers [#17]\n";
                cout << "3. Convert distance (km to m or m to km) [#28]\n";
				cout << "4. Array Operations [#31-33]\n";
				cout << "5. User Input Array Operations [#34]\n";
				cout << "6. Multiply Array by Number [#35]\n";
				cout << "7. Matrix Operations [#37]\n";
				cout << "8. Point class [#55]\n";
				cout << "9. Shape class [#56]\n";
				cout << "10. Animal class [#57]\n";
				cout << "11. Weight conversion [#41]\n";
				cout << "12. Bubble Sort [#42]\n";
				cout << "13. Selection Sort [#43]\n";
				cout << "14. Merge Sort [#44]\n";
				cout << "15. Timezone Conversion [#48]\n";
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
						demonstratePoint();
						break;
					case 9:
						demonstrateCircle();
						break;
					case 10:
						demonstrateAnimal();
						break;		
					case 11:
						weightConversion();
						break;
					case 12:
						bubbleSort();
						break;
					case 13:
						selectionSort();
						break;
					case 14:
						performMergeSort();
						break;
					case 15:
						timezoneConversion();
						break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
			case 7: // Fun Activities
                cout << "\nFun Activities:\n";
                cout << "1. T-Shirt Customization [#30]\n";
                cout << "2. Quiz Game [#29]\n";
				cout << "3. Halloween Game [#51]\n";
				cout << "4. Tic-Tac-Toe [#63]\n";
				cout << "5. Conway's Game of Life [#64]\n";
				cout << "6. Minesweeper [#60]\n";
				cout << "7. Demonstrate pointers [#65]\n";
				cout << "8. Wellness Bot [#71]\n";
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
					case 3:
						game.playGame();
					case 4:
                        tic_tac_toe();
                        break;
					case 5:
                        conways_game_of_life();
                        break;
					case 6:
                        minesweeper();
                        break;
					case 7:
						demonstratePointers();
						break;
					case 8:
						WellnessBot().run();
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

void solveLinearSystemFromInput() {
    double a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3;
    
    cout << "Enter coefficients for three linear equations in the form: ax + by + cz = d\n\n";
    
    cout << "Enter coefficients for first equation:\n";
    cout << "a1: "; cin >> a1;
    cout << "b1: "; cin >> b1;
    cout << "c1: "; cin >> c1;
    cout << "d1: "; cin >> d1;
    
    cout << "\nEnter coefficients for second equation:\n";
    cout << "a2: "; cin >> a2;
    cout << "b2: "; cin >> b2;
    cout << "c2: "; cin >> c2;
    cout << "d2: "; cin >> d2;
    
    cout << "\nEnter coefficients for third equation:\n";
    cout << "a3: "; cin >> a3;
    cout << "b3: "; cin >> b3;
    cout << "c3: "; cin >> c3;
    cout << "d3: "; cin >> d3;
    
    cout << "\nSolving system:\n";
    cout << a1 << "x + " << b1 << "y + " << c1 << "z = " << d1 << "\n";
    cout << a2 << "x + " << b2 << "y + " << c2 << "z = " << d2 << "\n";
    cout << a3 << "x + " << b3 << "y + " << c3 << "z = " << d3 << "\n\n";
    
    vector<double> result = solveLinearSystem(a1, b1, c1, d1,
                                            a2, b2, c2, d2,
                                            a3, b3, c3, d3);
    
    cout << fixed << setprecision(4);
    
    if (!result.empty()) {
        cout << "Solution exists:\n";
        cout << "x = " << result[0] << "\n";
        cout << "y = " << result[1] << "\n";
        cout << "z = " << result[2] << "\n";
    } else {
        cout << "No unique solution exists.\n";
    }
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

// Tic-Tac-Toe Game
void tic_tac_toe() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char player = 'X';
    int moves = 0;

    auto print_board = [&]() {
        for (int i = 0; i < 3; i++) {
            cout << " --- --- ---" << endl;
            cout << "| " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " |" << endl;
        }
        cout << " --- --- ---" << endl;
    };

    auto check_win = [&]() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
                return board[i][0];
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
                return board[0][i];
        }

        // Check diagonals
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
            return board[0][0];
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
            return board[0][2];

        return ' ';
    };

    print_board();

    while (moves < 9) {
        int row, col;
        cout << "Player " << player << ", enter row and column (1-3): ";
        cin >> row >> col;
        row--, col--;

        if (board[row][col] == ' ') {
            board[row][col] = player;
            moves++;

            char winner = check_win();
            if (winner != ' ') {
                print_board();
                cout << "Player " << winner << " wins!" << endl;
                return;
            }

            if (player == 'X')
                player = 'O';
            else
                player = 'X';

            print_board();
        } else {
            cout << "That position is already taken, try again." << endl;
        }
    }

    cout << "It's a tie!" << endl;
}

// Conway's Game of Life 
void conways_game_of_life() {
    const int rows = 10, cols = 10;
    vector<vector<bool>> grid(rows, vector<bool>(cols, false));

    // Randomly initialize the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = rand() % 2;
        }
    }

    auto print_grid = [&]() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << (grid[i][j] ? "#" : ".") << " ";
            }
            cout << endl;
        }
        cout << endl;
    };

    auto get_neighbors = [&](int i, int j) {
        int count = 0;
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (di == 0 && dj == 0)
                    continue;
                int ni = i + di, nj = j + dj;
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && grid[ni][nj])
                    count++;
            }
        }
        return count;
    };

    auto update_grid = [&]() {
        vector<vector<bool>> new_grid = grid;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int neighbors = get_neighbors(i, j);
                if (grid[i][j]) {
                    if (neighbors < 2 || neighbors > 3)
                        new_grid[i][j] = false;
                } else {
                    if (neighbors == 3)
                        new_grid[i][j] = true;
                }
            }
        }
        grid = move(new_grid);
    };

    print_grid();

    for (int i = 0; i < 10; i++) {
        cout << "Generation " << i + 1 << ":" << endl;
        update_grid();
        print_grid();
    }
}

// Minesweeper game 
void minesweeper() {
    const int rows = 8, cols = 8;
    const int num_mines = 10;
    vector<vector<int>> board(rows, vector<int>(cols, 0));
    vector<vector<bool>> revealed(rows, vector<bool>(cols, false));

    // Place mines
    for (int i = 0; i < num_mines; i++) {
        int r, c;
        do {
            r = rand() % rows;
            c = rand() % cols;
        } while (board[r][c] == -1);
        board[r][c] = -1;
    }

    // Calculate neighboring mine counts
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] != -1) {
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && board[ni][nj] == -1) {
                            board[i][j]++;
                        }
                    }
                }
            }
        }
    }

    auto print_board = [&]() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (!revealed[i][j]) {
                    cout << "□ ";
                } else if (board[i][j] == -1) {
                    cout << "X ";
                } else {
                    cout << board[i][j] << " ";
                }
            }
            cout << endl;
        }
    };

    int revealed_cells = 0;
    while (revealed_cells < rows * cols - num_mines) {
        print_board();
        int row, col;
        cout << "Enter row and column to reveal (1-8): ";
        cin >> row >> col;
        row--, col--;

        if (revealed[row][col])
            continue;

        revealed[row][col] = true;
        revealed_cells++;

        if (board[row][col] == -1) {
            cout << "You hit a mine! Game over." << endl;
            print_board();
            return;
        }

        if (board[row][col] == 0) {
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = row + di, nj = col + dj;
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && !revealed[ni][nj]) {
                        revealed[ni][nj] = true;
                        revealed_cells++;
                    }
                }
            }
        }
    }

    cout << "Congratulations, you win!" << endl;
    print_board();
}

// Function to demonstrate pointers with famous U.S. buildings
void demonstratePointers() {
    // Step 1: Declare variables representing famous U.S. buildings
    string building1 = "Statue of Liberty";
    string building2 = "Empire State Building";
    string building3 = "White House";

    // Step 2: Declare pointers to these variables
    string* ptr1 = &building1; // Pointer to the address of building1
    string* ptr2 = &building2; // Pointer to the address of building2
    string* ptr3 = &building3; // Pointer to the address of building3

    // Step 3: Print the values and addresses with improved formatting
    cout << left << setw(25) << "Original Buildings:" << "Value" << setw(30) << "\tMemory Address" << '\n';
    cout << left << setw(25) << "Building 1:" << building1 << "\t" << &building1 << '\n';
    cout << left << setw(25) << "Building 2:" << building2 << "\t" << &building2 << '\n';
    cout << left << setw(25) << "Building 3:" << building3 << "\t" << &building3 << '\n';

    // Step 4: Use pointers to print the values and their addresses
    cout << "\n" << left << setw(25) << "Pointer Demonstration:" << "Value" << setw(30) << "\tPointer Address" << '\n';
    cout << left << setw(25) << "Pointer to Building 1:" << *ptr1 << "\t" << ptr1 << '\n';
    cout << left << setw(25) << "Pointer to Building 2:" << *ptr2 << "\t" << ptr2 << '\n';
    cout << left << setw(25) << "Pointer to Building 3:" << *ptr3 << "\t" << ptr3 << '\n';

    // Step 5: Modify one variable through its pointer
    *ptr3 = "Lincoln Memorial"; // Modify the value of building3 using its pointer
    cout << "\nAfter modification through pointer:\n";
    cout << left << setw(25) << "Building 3:" << building3 << '\n';

    // Bonus: Demonstrate pointer arithmetic (optional learning)
    string buildings[] = {building1, building2, building3};
    string* ptrArray = buildings;
    cout << "\nPointer Arithmetic Demonstration:\n";
    cout << "First building using array pointer: " << *ptrArray << '\n';
    cout << "Second building using pointer + 1: " << *(ptrArray + 1) << '\n';
}

// Converting weight from lb to kg or vice versa 
void weightConversion() {
    double weight;
    char unit;
    cout << "Enter weight (append 'k' for kg or 'l' for lb): ";
    cin >> weight >> unit;
    if (unit == 'k') {
        cout << weight << " kg = " << weight * 2.20462 << " lb\n";
    } else if (unit == 'l') {
        cout << weight << " lb = " << weight / 2.20462 << " kg\n";
    } else {
        cout << "Invalid input.\n";
    }
}

// Bubble Sort 
void bubbleSort() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int &x : arr) cin >> x;

    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);

    cout << "Sorted array:\n";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// Selection Sort 
void selectionSort() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int &x : arr) cin >> x;

    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[minIdx])
                minIdx = j;
        swap(arr[i], arr[minIdx]);
    }

    cout << "Sorted array:\n";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// Merge process for merge sort 
void merge(vector<int> &arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(arr.begin() + l, arr.begin() + m + 1);
    vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Main mergesort function 
void mergeSort(vector<int> &arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void performMergeSort() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int &x : arr) cin >> x;

    mergeSort(arr, 0, n - 1);

    cout << "Sorted array:\n";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// Meal and Tip calculator
void mealCostCalculator() {
    double mealCost, tipPercentage;
    cout << "Enter meal cost: ";
    cin >> mealCost;
    cout << "Enter tip percentage: ";
    cin >> tipPercentage;
    double totalCost = mealCost + (mealCost * tipPercentage / 100.0);
    cout << "Total cost including tip: $" << totalCost << endl;
}

// Random integer generator
void randomIntegerGenerator() {
    srand(time(0));
    cout << "Random integer: " << rand() << endl;
}

// Random integer in range generator 
void randomInRange() {
    srand(time(0));
    int min, max;
    cout << "Enter min and max values: ";
    cin >> min >> max;
    cout << "Random number between " << min << " and " << max << ": "
         << min + rand() % (max - min + 1) << endl;
}

// Timezone converter between EST and PST 
void timezoneConversion() {
    int originalHour, offset;
    cout << "Enter original hour (24-hour format): ";
    cin >> originalHour;
    cout << "Enter timezone offset (e.g., -5 for EST): ";
    cin >> offset;

    int convertedHour = (originalHour + offset + 24) % 24;
    cout << "Original hour: " << originalHour << "h, Converted hour: " << convertedHour << "h\n";
}

// Volume calculator for cube, sphere, cylinder
void volumeCalculator() {
    char shape;
    cout << "Enter shape (c for cube, s for sphere, y for cylinder): ";
    cin >> shape;

    if (shape == 'c') {
        double side;
        cout << "Enter side length: ";
        cin >> side;
        cout << "Cube volume: " << pow(side, 3) << endl;
    } else if (shape == 's') {
        double radius;
        cout << "Enter radius: ";
        cin >> radius;
        cout << "Sphere volume: " << (4.0 / 3.0) * M_PI * pow(radius, 3) << endl;
    } else if (shape == 'y') {
        double radius, height;
        cout << "Enter radius and height: ";
        cin >> radius >> height;
        cout << "Cylinder volume: " << M_PI * pow(radius, 2) * height << endl;
    } else {
        cout << "Invalid shape.\n";
    }
}

// Function for array addition using pointers
void addArraysWithPointers() {
    int arr1[SIZE], arr2[SIZE], arr3[SIZE];
    int *ptr1 = arr1, *ptr2 = arr2, *ptr3 = arr3;

    // Input elements for the first array
    cout << "Enter 6 elements for the first array (for addition):" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> *(ptr1 + i);
    }

    // Input elements for the second array
    cout << "Enter 6 elements for the second array (for addition):" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> *(ptr2 + i);
    }

    // Perform addition
    for (int i = 0; i < SIZE; i++) {
        *(ptr3 + i) = *(ptr1 + i) + *(ptr2 + i);
    }

    // Display the resulting array
    cout << "The resulting array after addition is:" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << *(ptr3 + i) << " ";
    }
    cout << endl;
}

// Function for array subtraction using pointers
void subtractArraysWithPointers() {
    int arr1[SIZE], arr2[SIZE], arr3[SIZE];
    int *ptr1 = arr1, *ptr2 = arr2, *ptr3 = arr3;

    // Input elements for the first array
    cout << "Enter 6 elements for the first array (for subtraction):" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> *(ptr1 + i);
    }

    // Input elements for the second array
    cout << "Enter 6 elements for the second array (for subtraction):" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> *(ptr2 + i);
    }

    // Perform subtraction
    for (int i = 0; i < SIZE; i++) {
        *(ptr3 + i) = *(ptr1 + i) - *(ptr2 + i);
    }

    // Display the resulting array
    cout << "The resulting array after subtraction is:" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << *(ptr3 + i) << " ";
    }
    cout << endl;
}

// Function for array multiplication using pointers
void multiplyArraysWithPointers() {
    int arr1[SIZE], arr2[SIZE], arr3[SIZE];
    int *ptr1 = arr1, *ptr2 = arr2, *ptr3 = arr3;

    // Input elements for the first array
    cout << "Enter 6 elements for the first array (for multiplication):" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> *(ptr1 + i);
    }

    // Input elements for the second array
    cout << "Enter 6 elements for the second array (for multiplication):" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> *(ptr2 + i);
    }

    // Perform multiplication
    for (int i = 0; i < SIZE; i++) {
        *(ptr3 + i) = *(ptr1 + i) * *(ptr2 + i);
    }

    // Display the resulting array
    cout << "The resulting array after multiplication is:" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << *(ptr3 + i) << " ";
    }
    cout << endl;
}

// Function for array division using pointers
void divideArraysWithPointers() {
    int arr1[SIZE], arr2[SIZE], arr3[SIZE];
    int *ptr1 = arr1, *ptr2 = arr2, *ptr3 = arr3;

    // Input elements for the first array
    cout << "Enter 6 elements for the first array (for division):" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> *(ptr1 + i);
    }

    // Input elements for the second array
    cout << "Enter 6 elements for the second array (for division):" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> *(ptr2 + i);
    }

    // Perform division
    for (int i = 0; i < SIZE; i++) {
        if (*(ptr2 + i) != 0) { // Check for division by zero
            *(ptr3 + i) = *(ptr1 + i) / *(ptr2 + i);
        } else {
            cout << "Error: Division by zero at element " << i + 1 << endl;
            *(ptr3 + i) = 0; // Set result to 0 for invalid division
        }
    }

    // Display the resulting array
    cout << "The resulting array after division is:" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << *(ptr3 + i) << " ";
    }
    cout << endl;
}

// Function for array modulo using pointers
void moduloArraysWithPointers() {
    int arr1[SIZE], arr2[SIZE], arr3[SIZE];
    int *ptr1 = arr1, *ptr2 = arr2, *ptr3 = arr3;

    // Input elements for the first array
    cout << "Enter 6 elements for the first array (for modulo):" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> *(ptr1 + i);
    }

    // Input elements for the second array
    cout << "Enter 6 elements for the second array (for modulo):" << endl;
    for (int i = 0; i < SIZE; i++) {
        cin >> *(ptr2 + i);
    }

    // Perform modulo
    for (int i = 0; i < SIZE; i++) {
        if (*(ptr2 + i) != 0) { // Check for division by zero
            *(ptr3 + i) = *(ptr1 + i) % *(ptr2 + i);
        } else {
            cout << "Error: Modulo by zero at element " << i + 1 << endl;
            *(ptr3 + i) = 0; // Set result to 0 for invalid modulo
        }
    }

    // Display the resulting array
    cout << "The resulting array after modulo is:" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << *(ptr3 + i) << " ";
    }
    cout << endl;
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