/*
	Name : Tommy Lu, Richard Wong
	Course : CMPSC 330
	Project : Virtual Assistant 
	Date : 12/5/2024
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
#include <fstream>
#include <sstream>
#include <map>
#include <chrono>
#include <thread>




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

class EnhancedWellnessBot {
private:
    // Research-Based Mental Health Scoring Mechanisms
    const map<int, string> DEPRESSION_LEVELS = {
        {0, "Minimal Depression"},
        {5, "Mild Depression"},
        {10, "Moderate Depression"},
        {15, "Moderately Severe Depression"},
        {20, "Severe Depression"}
    };

    const map<int, string> ANXIETY_LEVELS = {
        {0, "Minimal Anxiety"},
        {5, "Mild Anxiety"},
        {10, "Moderate Anxiety"},
        {15, "Severe Anxiety"}
    };

    // References to research-based screening tools
    // Inspired by PHQ-9 and GAD-7 methodologies
    vector<pair<string, int>> DEPRESSION_QUESTIONS = {
        {"Feeling down, depressed, or hopeless", 0},
        {"Little interest or pleasure in doing things", 0},
        {"Trouble sleeping or sleeping too much", 0},
        {"Feeling tired or having little energy", 0},
        {"Poor appetite or overeating", 0},
        {"Feeling bad about yourself", 0},
        {"Trouble concentrating", 0},
        {"Moving or speaking slowly, or being restless", 0},
        {"Thoughts of self-harm", 0}
    };

    vector<pair<string, int>> ANXIETY_QUESTIONS = {
        {"Feeling nervous, anxious, or on edge", 0},
        {"Not being able to stop worrying", 0},
        {"Worrying too much about different things", 0},
        {"Trouble relaxing", 0},
        {"Being so restless it's hard to sit still", 0},
        {"Becoming easily annoyed or irritable", 0},
        {"Feeling afraid something awful might happen", 0}
    };

    int assessMentalHealthSection(const vector<pair<string, int>>& questions, const string& category) {
        int totalScore = 0;
        for (auto& question : const_cast<vector<pair<string, int>>&>(questions)) {
            cout << question.first << " \n\t(0-3 scale: 0=Not at all, 1=Occasionally, 2=Sometimes, 3=Nearly every day): ";
            cin >> question.second;
            totalScore += question.second;
        }
        return totalScore;
    }

    // Comprehensive list of recommendations
    vector<string> coping_strategies = {
        "Allow yourself to feel what you're feeling",
        "Do something you have control over",
        "Maintain a routine",
        "Aim to get a good night's sleep",
        "Try to eat balanced meals",
        "Try a walk around the block",
        "Make time for rest and relaxation",
        "Reach out to loved ones"
    };

    vector<string> therapy_options = {
        "Cognitive Behavioral Therapy (CBT)",
        "Interpersonal Therapy",
        "Mindfulness-based Cognitive Therapy",
        "Acceptance and Commitment Therapy",
        "Problem-solving Therapy",
        "Exposure Therapy"
    };

    vector<string> alternative_treatments = {
        "Hypnotherapy",
        "Acupuncture",
        "Nutritional supplements",
        "Regular exercise",
        "Meditation and mindfulness practices",
        "Yoga",
        "Stress reduction techniques"
    };

    vector<string> medication_options = {
        "Consult about Antidepressants (SSRIs/SNRIs)",
        "Explore Mood stabilizers",
        "Discuss Anti-anxiety medications",
        "Consider Beta-blockers for symptom management",
        "Personalized medication consultation"
    };

    // Random selection method
    vector<string> getRandomRecommendations(vector<string>& source, int count) {
        // Use a random device to seed the random number generator
        random_device rd;
        mt19937 g(rd());

        // Shuffle the source vector
        shuffle(source.begin(), source.end(), g);

        // Return the first 'count' recommendations
        return vector<string>(source.begin(), source.begin() + min(count, static_cast<int>(source.size())));
    }

    void provideDepessionRecommendations(int score) {
        cout << "\n=== Depression Recommendations ===\n";
        
        // Dynamic recommendation system
        if (score <= 4) {
            cout << "Your depression level is minimal. Continue maintaining good mental health practices.\n";
            return;
        }

        // Combine all recommendation types
        vector<string> allRecommendations;
        allRecommendations.insert(allRecommendations.end(), 
            coping_strategies.begin(), coping_strategies.end());
        allRecommendations.insert(allRecommendations.end(), 
            therapy_options.begin(), therapy_options.end());
        allRecommendations.insert(allRecommendations.end(), 
            alternative_treatments.begin(), alternative_treatments.end());
        allRecommendations.insert(allRecommendations.end(), 
            medication_options.begin(), medication_options.end());

        vector<string> selectedRecommendations;
        if (score > 4 && score <= 9) {
            cout << "Mild Depression: One recommended approach:\n";
            selectedRecommendations = getRandomRecommendations(allRecommendations, 1);
        } else if (score > 9 && score <= 14) {
            cout << "Moderate Depression: Two recommended approaches:\n";
            selectedRecommendations = getRandomRecommendations(allRecommendations, 2);
        } else if (score > 14 && score <= 19) {
            cout << "Moderately Severe Depression: Three recommended approaches:\n";
            selectedRecommendations = getRandomRecommendations(allRecommendations, 3);
        } else {
            cout << "!!! SEVERE DEPRESSION DETECTED !!!\n";
            selectedRecommendations = getRandomRecommendations(allRecommendations, 4);
            cout << "IMMEDIATE professional psychiatric evaluation is CRITICAL.\n";
            cout << "Emergency contact numbers:\n";
            cout << "National Suicide Prevention Lifeline: 988\n";
            cout << "Crisis Text Line: Text HOME to 741741\n\n";
        }

        // Print selected recommendations
        for (size_t i = 0; i < selectedRecommendations.size(); ++i) {
            cout << i + 1 << ". " << selectedRecommendations[i] << endl;
        }
    }

    void provideAnxietyRecommendations(int score) {
        cout << "\n=== Anxiety Recommendations ===\n";
        
        // Dynamic recommendation system
        if (score <= 4) {
            cout << "Your anxiety level is minimal. Continue maintaining good mental health practices.\n";
            return;
        }

        // Combine all recommendation types
        vector<string> allRecommendations;
        allRecommendations.insert(allRecommendations.end(), 
            coping_strategies.begin(), coping_strategies.end());
        allRecommendations.insert(allRecommendations.end(), 
            therapy_options.begin(), therapy_options.end());
        allRecommendations.insert(allRecommendations.end(), 
            alternative_treatments.begin(), alternative_treatments.end());
        allRecommendations.insert(allRecommendations.end(), 
            medication_options.begin(), medication_options.end());

        vector<string> selectedRecommendations;
        if (score > 4 && score <= 9) {
            cout << "Mild Anxiety: One recommended approach:\n";
            selectedRecommendations = getRandomRecommendations(allRecommendations, 1);
        } else if (score > 9 && score <= 14) {
            cout << "Moderate Anxiety: Two recommended approaches:\n";
            selectedRecommendations = getRandomRecommendations(allRecommendations, 2);
        } else if (score > 14 && score < 20) {
            cout << "Severe Anxiety: Three recommended approaches:\n";
            selectedRecommendations = getRandomRecommendations(allRecommendations, 3);
        } else {
            cout << "!!! SEVERE ANXIETY DETECTED !!!\n";
            selectedRecommendations = getRandomRecommendations(allRecommendations, 4);
            cout << "URGENT professional mental health intervention required.\n";
            cout << "Emergency support:\n";
            cout << "Anxiety and Depression Association of America: 240-485-1001\n";
            cout << "Crisis Text Line: Text HOME to 741741\n\n";
        }

        // Print selected recommendations
        for (size_t i = 0; i < selectedRecommendations.size(); ++i) {
            cout << i + 1 << ". " << selectedRecommendations[i] << endl;
        }
    }

public:
    void mentalHealthAssessment() {
        cout << "=== Comprehensive Mental Health Screening ===\n";
        cout << "Research-Based Assessment Inspired by PHQ-9 and GAD-7 Methodologies\n\n";

        cout << "DEPRESSION SCREENING:\n";
        int depressionScore = assessMentalHealthSection(DEPRESSION_QUESTIONS, "Depression");
        cout << "\nDepression Level: " << DEPRESSION_LEVELS.lower_bound(depressionScore)->second 
             << " (Score: " << depressionScore << ")\n";
        provideDepessionRecommendations(depressionScore);

        cout << "\nANXIETY SCREENING:\n";
        int anxietyScore = assessMentalHealthSection(ANXIETY_QUESTIONS, "Anxiety");
        cout << "\nAnxiety Level: " << ANXIETY_LEVELS.lower_bound(anxietyScore)->second 
             << " (Score: " << anxietyScore << ")\n";
        provideAnxietyRecommendations(anxietyScore);
    }

    void run() {
        cout << "Wellness and Mental Health Virtual Assistant V7\n";
        cout << "Disclaimer: This is a screening tool. Not a substitute for professional medical diagnosis.\n\n";
        
        mentalHealthAssessment();
    }
};

// Student Grade analyzer
class Student {
public:
    string name;
    int age;
    float finalGrade;

    // Constructor
    Student(const string& n, int a, float grade) 
        : name(n), age(a), finalGrade(grade) {}
};

class StudentManagementSystem {
private:
    vector<Student> students;

public:
    // Function to add students and perform analysis in one call
    void processStudentData() {
        // Clear any existing students
        students.clear();

        // Input and process 5 students
        for (int i = 0; i < 5; ++i) {
            string name, ageStr, gradeStr;
            int age = 0;
            float grade = 0.0f;

            cout << "Enter details for student " << (i+1) << ":\n";
            
            // Get name with clear buffer
            cout << "Name: ";
            getline(cin >> ws, name);

            // Get age with input validation
            while (true) {
                cout << "Age: ";
                getline(cin >> ws, ageStr);
                istringstream ageStream(ageStr);
                if (ageStream >> age && ageStream.eof()) {
                    break;
                }
                cout << "Invalid input. Please enter a valid integer for age.\n";
            }

            // Get grade with input validation
            while (true) {
                cout << "Final Grade: ";
                getline(cin >> ws, gradeStr);
                istringstream gradeStream(gradeStr);
                if (gradeStream >> grade && gradeStream.eof()) {
                    break;
                }
                cout << "Invalid input. Please enter a valid number for grade.\n";
            }

            // Add student to vector
            students.emplace_back(name, age, grade);
        }

        // Display student information
        displayStudentInfo();

        // Perform grade analysis
        performGradeAnalysis();
    }

private:
    void displayStudentInfo() {
        cout << "\n--- Student Information ---\n";
        for (const auto& student : students) {
            cout << "Name: " << student.name 
                      << ", Age: " << student.age 
                      << ", Final Grade: " << fixed << setprecision(2) << student.finalGrade << endl;
        }
    }

    void performGradeAnalysis() {
        if (students.empty()) {
            cout << "No students to analyze.\n";
            return;
        }

        // Calculate average grade
        float totalGrade = 0.0f;
        for (const auto& student : students) {
            totalGrade += student.finalGrade;
        }
        float averageGrade = totalGrade / students.size();

        cout << "\n--- Grade Analysis ---\n";
        cout << "Average Grade: " << fixed << setprecision(2) << averageGrade << endl;

        // Find highest and lowest grades
        auto highestGradeStudent = max_element(students.begin(), students.end(), 
            [](const Student& a, const Student& b) { return a.finalGrade < b.finalGrade; });

        auto lowestGradeStudent = min_element(students.begin(), students.end(), 
            [](const Student& a, const Student& b) { return a.finalGrade < b.finalGrade; });

        cout << "Highest Grade: " << highestGradeStudent->name 
                  << " (Grade: " << fixed << setprecision(2) << highestGradeStudent->finalGrade << ")" << endl;
        
        cout << "Lowest Grade: " << lowestGradeStudent->name 
                  << " (Grade: " << fixed << setprecision(2) << lowestGradeStudent->finalGrade << ")" << endl;
    }
};

// Product inventory management system
class Product {
public:
    string name;
    int quantity;
    float price;

    // Constructor
    Product(const string& n, int qty, float p) 
        : name(n), quantity(qty), price(p) {}
};

class InventoryManagementSystem {
private:
    vector<Product> inventory;

public:
    // Comprehensive method to manage inventory in one call
    void manageInventory() {
        // Clear existing inventory
        inventory.clear();

        char continueAdding;
        do {
            // Input product details with validation
            string name, quantityStr, priceStr;

            // Get product name
            cout << "Enter product name: ";
            getline(cin >> ws, name);

            // Get quantity with input validation
            int quantity = 0;
            while (true) {
                cout << "Enter quantity: ";
                getline(cin >> ws, quantityStr);
                istringstream quantityStream(quantityStr);
                if (quantityStream >> quantity && quantityStream.eof() && quantity >= 0) {
                    break;
                }
                cout << "Invalid input. Please enter a non-negative integer.\n";
            }

            // Get price with input validation
            float price = 0.0f;
            while (true) {
                cout << "Enter price: ";
                getline(cin >> ws, priceStr);
                istringstream priceStream(priceStr);
                if (priceStream >> price && priceStream.eof() && price >= 0) {
                    break;
                }
                cout << "Invalid input. Please enter a non-negative number.\n";
            }

            // Add product to inventory
            inventory.emplace_back(name, quantity, price);

            // Ask if user wants to add more products
            cout << "Add another product? (y/n): ";
            cin >> continueAdding;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (continueAdding == 'y' || continueAdding == 'Y');

        // Display inventory and calculate total value
        displayInventory();
    }

private:
    void displayInventory() {
        if (inventory.empty()) {
            cout << "Inventory is empty.\n";
            return;
        }

        // Display product details
        cout << "\n--- Current Inventory ---\n";
        cout << left << setw(20) << "Product Name" 
                  << setw(10) << "Quantity" 
                  << setw(10) << "Price" 
                  << "Total Value\n";
        cout << string(40, '-') << endl;

        // Calculate and display total inventory value
        float totalInventoryValue = 0.0f;
        for (const auto& product : inventory) {
            float productValue = product.quantity * product.price;
            totalInventoryValue += productValue;

            cout << left << setw(20) << product.name 
                      << setw(10) << product.quantity 
                      << fixed << setprecision(2) 
                      << setw(10) << product.price 
                      << productValue << endl;
        }

        // Display total inventory value
        cout << "\nTotal Inventory Value: $" 
                  << fixed << setprecision(2) 
                  << totalInventoryValue << endl;
    }
};


// Library Management System
class Book {
public:
    string title;
    string author;
    int publicationYear;

    // Constructor
    Book(const string& t, const string& a, int year) 
        : title(t), author(a), publicationYear(year) {}
};

class LibraryManagementSystem {
private:
    vector<Book> library;

public:
    // Comprehensive method to manage library in one call
    void managLibrary() {
        // Clear existing library
        library.clear();

        char continueAdding;
        do {
            // Input book details with validation
            string title, author, yearStr;

            // Get book title
            cout << "Enter book title: ";
            getline(cin >> ws, title);

            // Get book author
            cout << "Enter book author: ";
            getline(cin >> ws, author);

            // Get publication year with input validation
            int publicationYear = 0;
            while (true) {
                cout << "Enter publication year: ";
                getline(cin >> ws, yearStr);
                istringstream yearStream(yearStr);
                if (yearStream >> publicationYear && yearStream.eof()) {
                    break;
                }
                cout << "Invalid input. Please enter a valid year.\n";
            }

            // Add book to library
            library.emplace_back(title, author, publicationYear);

            // Ask if user wants to add more books
            cout << "Add another book? (y/n): ";
            cin >> continueAdding;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (continueAdding == 'y' || continueAdding == 'Y');

        // Display books published after 2000
        displayBooksAfter2000();

        // Search for a book
        searchBookByTitle();
    }

private:
    void displayBooksAfter2000() {
        vector<Book> modernBooks;
        
        // Filter books published after 2000
        copy_if(library.begin(), library.end(), back_inserter(modernBooks), 
            [](const Book& book) { return book.publicationYear > 2000; });

        if (modernBooks.empty()) {
            cout << "\nNo books published after 2000 found.\n";
            return;
        }

        cout << "\n--- Books Published After 2000 ---\n";
        cout << left 
                  << setw(30) << "Title" 
                  << setw(25) << "Author" 
                  << "Publication Year\n";
        cout << string(60, '-') << endl;

        for (const auto& book : modernBooks) {
            cout << left 
                      << setw(30) << book.title 
                      << setw(25) << book.author 
                      << book.publicationYear << endl;
        }
    }

    void searchBookByTitle() {
        if (library.empty()) {
            cout << "\nLibrary is empty.\n";
            return;
        }

        // Get search title
        string searchTitle;
        cout << "\nEnter a book title to search: ";
        getline(cin >> ws, searchTitle);

        // Convert search title to lowercase for case-insensitive search
        transform(searchTitle.begin(), searchTitle.end(), searchTitle.begin(), 
            [](unsigned char c){ return tolower(c); });

        // Search for the book
        auto it = find_if(library.begin(), library.end(), 
            [&searchTitle](const Book& book) {
                string lowercaseTitle = book.title;
                transform(lowercaseTitle.begin(), lowercaseTitle.end(), lowercaseTitle.begin(), 
                    [](unsigned char c){ return tolower(c); });
                return lowercaseTitle.find(searchTitle) != string::npos;
            });

        // Display search result
        if (it != library.end()) {
            cout << "Book Found:\n";
            cout << "Title: " << it->title << "\n";
            cout << "Author: " << it->author << "\n";
            cout << "Publication Year: " << it->publicationYear << endl;
        } else {
            cout << "Book not found in the library." << endl;
        }
    }
};

// Employee Management System
class Employee {
public:
    string name;
    string position;
    float salary;

    // Constructor
    Employee(const string& n, const string& pos, float sal) 
        : name(n), position(pos), salary(sal) {}
};

class EmployeeManagementSystem {
private:
    vector<Employee> employees;

public:
    // Comprehensive method to manage employees in one call
    void manageEmployees() {
        // Clear existing employees
        employees.clear();

        char continueAdding;
        do {
            // Input employee details with validation
            string name, position, salaryStr;

            // Get employee name
            cout << "Enter employee name: ";
            getline(cin >> ws, name);

            // Get employee position
            cout << "Enter employee position: ";
            getline(cin >> ws, position);

            // Get salary with input validation
            float salary = 0.0f;
            while (true) {
                cout << "Enter employee salary: $";
                getline(cin >> ws, salaryStr);
                istringstream salaryStream(salaryStr);
                if (salaryStream >> salary && salaryStream.eof() && salary >= 0) {
                    break;
                }
                cout << "Invalid input. Please enter a non-negative number.\n";
            }

            // Add employee to vector
            employees.emplace_back(name, position, salary);

            // Ask if user wants to add more employees
            cout << "Add another employee? (y/n): ";
            cin >> continueAdding;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (continueAdding == 'y' || continueAdding == 'Y');

        // Display all employees
        displayEmployees();

        // Calculate and display average salary
        calculateAverageSalary();

        // Display employees earning above average
        displayHighEarners();

        // Option to remove an employee
        removeEmployee();
    }

private:
    void displayEmployees() {
        if (employees.empty()) {
            cout << "\nNo employees in the system.\n";
            return;
        }

        cout << "\n--- Current Employees ---\n";
        cout << left 
                  << setw(25) << "Name" 
                  << setw(20) << "Position" 
                  << "Salary\n";
        cout << string(50, '-') << endl;

        for (const auto& employee : employees) {
            cout << left 
                      << setw(25) << employee.name 
                      << setw(20) << employee.position 
                      << "$" << fixed << setprecision(2) << employee.salary << endl;
        }
    }

    void calculateAverageSalary() {
        if (employees.empty()) return;

        // Calculate total salary
        float totalSalary = accumulate(employees.begin(), employees.end(), 0.0f, 
            [](float sum, const Employee& emp) { return sum + emp.salary; });

        // Calculate average salary
        float averageSalary = totalSalary / employees.size();

        cout << "\nAverage Salary: $" 
                  << fixed << setprecision(2) << averageSalary << endl;
    }

    void displayHighEarners() {
        if (employees.empty()) return;

        // Calculate average salary
        float totalSalary = accumulate(employees.begin(), employees.end(), 0.0f, 
            [](float sum, const Employee& emp) { return sum + emp.salary; });
        float averageSalary = totalSalary / employees.size();

        // Filter and display high earners
        vector<Employee> highEarners;
        copy_if(employees.begin(), employees.end(), back_inserter(highEarners), 
            [averageSalary](const Employee& emp) { return emp.salary > averageSalary; });

        if (highEarners.empty()) {
            cout << "No employees earning above average salary.\n";
            return;
        }

        cout << "\n--- Employees Earning Above Average ---\n";
        cout << left 
                  << setw(25) << "Name" 
                  << setw(20) << "Position" 
                  << "Salary\n";
        cout << string(50, '-') << endl;

        for (const auto& employee : highEarners) {
            cout << left 
                      << setw(25) << employee.name 
                      << setw(20) << employee.position 
                      << "$" << fixed << setprecision(2) << employee.salary << endl;
        }
    }

    void removeEmployee() {
        if (employees.empty()) return;

        // Get employee name to remove
        string nameToRemove;
        cout << "\nEnter the name of the employee to remove: ";
        getline(cin >> ws, nameToRemove);

        // Convert search name to lowercase for case-insensitive search
        transform(nameToRemove.begin(), nameToRemove.end(), nameToRemove.begin(), 
            [](unsigned char c){ return tolower(c); });

        // Find and remove the employee
        auto it = find_if(employees.begin(), employees.end(), 
            [&nameToRemove](const Employee& emp) {
                string lowercaseName = emp.name;
                transform(lowercaseName.begin(), lowercaseName.end(), lowercaseName.begin(), 
                    [](unsigned char c){ return tolower(c); });
                return lowercaseName.find(nameToRemove) != string::npos;
            });

        // Display removal result
        if (it != employees.end()) {
            cout << "Removed employee: " << it->name << endl;
            employees.erase(it);
        } else {
            cout << "Employee not found." << endl;
        }
    }
};

// Silly Adventure Game
class SillyAdventureGame {
private:
    // Randomness generator
    mt19937 rng;

    // Player stats with a comedic twist
    struct Player {
        string name;
        int silliness = 0;
        int weirdness = 0;
        int randomJokePoints = 0;
        vector<string> exploredAreas;
    };

    Player player;

    // Collection of absolutely absurd jokes and responses
    vector<string> jokes = {
        "Why don't scientists trust atoms? Because they make up everything!",
        "I told my wife she was drawing her eyebrows too high. She looked surprised.",
        "Why did the scarecrow win an award? Because he was outstanding in his field!",
        "What do you call a bear with no teeth? A gummy bear!",
        "Why don't eggs tell jokes? They'd crack each other up!",
        "I'm afraid for the calendar. Its days are numbered.",
        "What do you call a fake noodle? An impasta!",
        "Why did the math book look so sad? Because it had too many problems.",
        "What do you call a boomerang that doesn't come back? A stick.",
        "Why did the cookie go to the doctor? Because it was feeling crumbly!",
        "Why don't skeletons fight each other? They don't have the guts!",
        "What did the grape do when it got stepped on? Nothing but let out a little wine!",
        "Why did the coffee file a police report? It got mugged!",
        "How do you organize a space party? You planet!",
        "What's orange and sounds like a parrot? A carrot!",
        "What did the ocean say to the beach? Nothing, it just waved!",
        "Why don't oysters share their pearls? Because they're shellfish!",
        "What did the duck say when it bought lipstick? Put it on my bill!",
        "Why do cows wear bells? Because their horns don't work!",
        "What do you call fake spaghetti? An impasta!",
        "I couldn't figure out how to put my seatbelt on. Then it clicked!",
        "What did one hat say to the other? Stay here, I'm going on ahead!",
        "Why don't some couples go to the gym? Because some relationships don't work out!",
        "What's brown and sticky? A stick!",
        "Why did the bicycle fall over? It was two-tired!",
        "I'm reading a book about anti-gravity. It's impossible to put down!",
        "Why was the math book sad? It had too many problems!",
        "What's a skeleton's least favorite room? The living room!",
        "Why was the computer cold? It left its Windows open!",
        "Why don't scientists trust stairs? Because they're always up to something!"
    };

    vector<string> easterEggs = {
        "You found a rubber chicken wearing sunglasses!",
        "A wild meme appears and dabs at you!",
        "You discover a talking potato chip.",
        "A wild dad joke generator activates!",
        "You've unlocked the secret realm of maximum goofiness!"
        "You found a rubber duck that quacks riddles!",
        "A random potato appears and asks for your help!",
        "You discover a secret dance party hosted by flamingos!",
        "You find a treasure chest full of invisible coins!",
        "A magical unicorn gives you a high-five!",
        "A glowing jellyfish offers you a ride through the clouds!",
        "You stumble upon a giant pancake floating in the air!",
        "A frog hands you a map to the 'Cave of Unusual Snacks'!",
        "You find a time-traveling toaster that makes breakfast for the past!",
        "A mysterious portal opens to a world made entirely of cheese!",
        "A rainbow-colored squirrel offers you a snack!",
        "You find a book titled 'How to Speak to Inanimate Objects'!",
        "You discover a secret room full of dancing tacos!",
        "A cactus in a top hat challenges you to a staring contest!",
        "A penguin wearing a bowtie asks if you want to go ice fishing!",
        "You meet a wizard who only speaks in puns!",
        "A cloud with a face challenges you to a joke-off!",
        "You encounter a flying rubber chicken with sunglasses!",
        "A fortune cookie offers you a life-changing riddle!",
        "A frog starts singing opera in a pond!"
    };


public:
    // Constructor to seed random number generator
    SillyAdventureGame() : rng(chrono::steady_clock::now().time_since_epoch().count()) {}

    // Main game method
    void playAbsurdGame() {
        // Clear previous game state
        player = Player();

        // Dramatic game introduction
        cout << "🎉 WELCOME TO THE MOST RIDICULOUS ADVENTURE EVER! 🎉\n";
        cout << "Prepare for maximum silliness and unexpected randomness!\n\n";

        // Get player name with a twist
        getPlayerName();
        

        // Start the silly adventure
        beginAdventure();

        // Final score and ridiculous conclusion
        concludeAdventure();
    }

private:
    void getPlayerName() {
        string input;
        cout << "Enter your name (or a silly nickname): ";
        getline(cin >> ws, input);

        // Transform name for extra comedy
        if (input.length() > 3) {
            input = "Sir/Lady " + input + " the Magnificent";
        }

        player.name = input;
        cout << "Greetings, " << player.name << "! Your adventure of absurdity begins!\n";
    }

    

    void exploreArea() {
        vector<string> areas = {
            "Enchanted Forest of Giggles",
            "Valley of Infinite Puns",
            "Mountain of Mischief",
            "Swamp of Quirky Critters",
            "Castle of Comic Chaos",
            "The Forest of Foolishness",
            "The Beach of Bizarre",
            "The Desert of Dad Jokes",
            "The Mountain of Madness",
            "The Cavern of Comedy"
        };

        cout << "\n📍 Where would you like to explore?\n";
        for (size_t i = 0; i < areas.size(); ++i) {
            cout << i + 1 << ". " << areas[i] << endl;
        }
        cout << "Enter the number of your choice: ";
        
        int choice;
        cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(areas.size())) {
            cout << "\n🚶 Heading to the " << areas[choice - 1] << "...\n";
            performRandomEventsInArea(areas[choice - 1]);
        } else {
            cout << "Invalid choice! A random area will be chosen for you.\n";
            uniform_int_distribution<int> areaDist(0, areas.size() - 1);
            performRandomEventsInArea(areas[areaDist(rng)]);
        }
    }

     void performRandomEventsInArea(const string& areaName) {
        cout << "🌟 Welcome to the " << areaName << "!\n";

        // Avoid duplicate entries in the explored list
        if (find(player.exploredAreas.begin(), player.exploredAreas.end(), areaName) == player.exploredAreas.end()) {
            player.exploredAreas.push_back(areaName);
        }
        
        // Determine the number of events (0–2)
        uniform_int_distribution<int> eventCountDist(0, 2);
        int eventCount = eventCountDist(rng);

        cout << "🌀 You will experience " << eventCount << " random event(s) here.\n";


        for (int i = 0; i < eventCount; ++i) {
            performRandomEvent();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }

    void quizEvent() {
        vector<pair<string, int>> quizzes = {
            {"What is 5 + 3?", 8},
            {"How many legs does a spider have?", 8},
            {"What is 7 * 6?", 42},
            {"What is the square root of 49?", 7},
            {"How many planets are in our solar system? (as of 2023)", 8},
            {"What is 2 + 2?", 4},
            {"How many sides does a triangle have?", 3},
            {"What is the square of 5?", 25},
            {"What is 9 divided by 3?", 3},
            {"How many hours are in a day?", 24},
            {"What is 100 minus 40?", 60},
            {"What is 3 * 3?", 9},
            {"How many continents are there?", 7},
            {"What is the capital of France?", 1}, // Answering with number of options
            {"What is 10 - 2?", 8},
            {"What is 8 + 4?", 12},
            {"What is 6 * 7?", 42},
            {"How many days are in a leap year?", 366},
            {"How many weeks are in a year?", 52},
            {"How many legs does an octopus have?", 8},
            {"What is the square root of 64?", 8},
            {"What is 20 + 30?", 50},
            {"What is the number of hours in a week?", 168},
            {"What is 15 divided by 5?", 3},
            {"What is 4 * 4?", 16}
        };

        uniform_int_distribution<int> quizDist(0, quizzes.size() - 1);
        int quizIndex = quizDist(rng);

        cout << "🧠 QUIZ TIME! 🧠\n";
        cout << quizzes[quizIndex].first << endl;
        cout << "Enter your answer: ";

        int playerAnswer;
        cin >> playerAnswer;

        if (playerAnswer == quizzes[quizIndex].second) {
            cout << "🎉 Correct! You've earned some brainy points!\n";
            player.randomJokePoints += 15; // Reward with points
        } else {
            cout << "❌ Oops! The correct answer was " << quizzes[quizIndex].second << ".\n";
            player.silliness += 5; // Small penalty or consolation reward
        }
    }

    void beginAdventure() {
        cout << "\n🌈 Chapter 1: Choose Your Path 🌈\n";

        char userChoice;
        bool continueExploring = true;

        while (continueExploring) {
            cout << "\nWould you like to explore an area? (y/n): ";
            cin >> userChoice;

            if (tolower(userChoice) == 'y') {
                exploreArea();
            } else {
                cout << "\n🎲 Let randomness guide your fate!\n";
                for (int i = 0; i < 5; ++i) {
                    performRandomEvent();
                    this_thread::sleep_for(chrono::milliseconds(500));
                }
            }

            // Ask the player if they want to continue
            cout << "\nWould you like to continue exploring? (y/n): ";
            cin >> userChoice;
            continueExploring = (tolower(userChoice) == 'y');
        }

        cout << "\n🏁 You've chosen to end your adventure. On to the final chapter...\n";
    }

    

    void performRandomEvent() {
        uniform_int_distribution<int> eventDist(1, 6); // Add 6 for the new quiz event
        int event = eventDist(rng);

        cout << "\n🎭 A random event occurs:\n";
        switch (event) {
            case 1:
                telljoke();
                break;
            case 2:
                discoverEasterEgg();
                break;
            case 3:
                randomChallenge();
                break;
            case 4:
                magicalTransformation();
                break;
            case 5:
                encounterWeirdCreature();
                break;
            case 6:
                quizEvent();
                break;
        }
    }

    void telljoke() {
        uniform_int_distribution<int> jokeDist(0, jokes.size() - 1);
        int jokeIndex = jokeDist(rng);

        cout << "🤡 JOKE TIME! 🤡\n";
        cout << jokes[jokeIndex] << endl;
        player.randomJokePoints += 10;
        player.silliness += 5;
    }

    void discoverEasterEgg() {
        uniform_int_distribution<int> eggDist(0, easterEggs.size() - 1);
        int eggIndex = eggDist(rng);

        cout << "🥚 EASTER EGG DISCOVERED! 🥚\n";
        cout << easterEggs[eggIndex] << endl;
        player.weirdness += 15;
    }

    void randomChallenge() {
        vector<string> challenges = {
            "Do your best impression of a confused penguin!",
            "Sing the alphabet backwards while hopping!",
            "Tell a story using only movie quotes!",
            "Dance like nobody's watching (but everyone is)!",
            "Convince an imaginary friend to do your homework!"
            "Do 10 jumping jacks while making animal noises!",
            "Pretend to be a pirate and shout 'Arr!' for 30 seconds!",
            "Describe your day using only emojis!",
            "Talk like a robot for the next 2 minutes!",
            "Draw a picture of your favorite fruit with your non-dominant hand!",
            "Make up a short song about socks!",
            "Act like a sloth for the next 1 minute!",
            "Give your best impression of a chicken crossing the road!",
            "Pretend you're an astronaut and explain how to make pizza in space!",
            "Do an impression of your favorite superhero!",
            "Pretend you are a teacher and give a lecture on the importance of naps!",
            "Explain how to do your favorite dance move in the most complicated way possible!",
            "Pretend you're a famous movie director and tell a short story about a banana!",
            "Dance like you're in a music video for the next 30 seconds!",
            "Do your best impression of a robot malfunctioning!",
            "Create a funny story about a talking spoon!",
            "Pretend you're a mime trapped in a box for 1 minute!",
            "Act like a cat for the next 2 minutes!",
            "Do your best impression of a wizard casting a spell!",
            "Explain how to do a cartwheel, but only use song lyrics!"
        };

        uniform_int_distribution<int> challengeDist(0, challenges.size() - 1);
        int challengeIndex = challengeDist(rng);

        cout << "🏆 RANDOM CHALLENGE ACTIVATED! 🏆\n";
        cout << challenges[challengeIndex] << endl;
        player.silliness += 20;
    }

    void magicalTransformation() {
        vector<string> transformations = {
            "You've been transformed into a tap-dancing potato!",
            "Congratulations! You're now a talking traffic cone!",
            "You're temporarily a wizard who can only cast dad jokes!",
            "You've become a motivational speaker for houseplants!",
            "You are now fluent in the language of rubber chickens!",
            "You've been transformed into a dancing taco!",
            "You are now a magical potato with wizard powers!",
            "You've become a living balloon animal!",
            "You are now a famous rock star with a crowd of adoring fans!",
            "You've turned into a balloon animal with a top hat!",
            "Congratulations! You are now a superhero who can only speak in puns!",
            "You've turned into a talking sandwich who loves to sing!",
            "You are now a walking dictionary who loves to define words!",
            "You've become a donut with sprinkles and a serious attitude!",
            "You are now a circus acrobat who can do backflips!",
            "You've turned into a disco ball that can only play funky music!",
            "Congratulations! You're a talking plant with all the wisdom of the earth!",
            "You're now a time-traveling ice cream cone!",
            "You've become a high-speed race car with a personality of a turtle!",
            "You are now a superhero who can only solve problems using dad jokes!",
            "You're now a professional juggler with invisible balls!",
            "You've transformed into a giant rubber band who bounces everywhere!",
            "Congratulations! You're a sentient cloud who loves to rain on parades!",
            "You are now a disco-dancing robot with a heart of gold!",
            "You've turned into a robot chef who makes gourmet meals!"
        };

        uniform_int_distribution<int> transformDist(0, transformations.size() - 1);
        int transformIndex = transformDist(rng);

        cout << "✨ MAGICAL TRANSFORMATION! ✨\n";
        cout << transformations[transformIndex] << endl;
        player.weirdness += 25;
    }

    void encounterWeirdCreature() {
        vector<string> creatures = {
            "A quantum physics-studying platypus!",
            "A philosophical sock puppet!",
            "A stand-up comedian squirrel!",
            "A time-traveling garden gnome!",
            "A motivational speaking cactus!",
            "A dancing llama who speaks fluent Spanish!",
            "A robot unicorn who can do backflips!",
            "A dragon who only breathes confetti!",
            "A giraffe who is also a master of yoga!",
            "A singing octopus that loves karaoke!",
            "A ninja hamster who knows kung fu!",
            "A dancing pineapple who loves to cook!",
            "A bear who can solve riddles in Morse code!",
            "A magical koala who can juggle pinecones!",
            "A flamingo who only speaks in rhymes!",
            "A cat that can play the piano while wearing sunglasses!",
            "A bear who does stand-up comedy!",
            "A chameleon that changes colors based on your mood!",
            "A magical sloth who can read minds!",
            "A hedgehog who can do a perfect moonwalk!",
            "A rhinoceros who is a professional breakdancer!",
            "A raccoon who loves to bake cookies and sing opera!",
            "A giraffe who wears a monocle and loves tea parties!",
            "A zebra who can tell jokes about stripes!",
            "A talking hedgehog who gives advice on relationships!"
        };

        uniform_int_distribution<int> creatureDist(0, creatures.size() - 1);
        int creatureIndex = creatureDist(rng);

        cout << "👾 WEIRD CREATURE ENCOUNTER! 👾\n";
        cout << "You've met: " << creatures[creatureIndex] << endl;
        player.silliness += 15;
    }

    void concludeAdventure() {
        cout << "\n🎊 ADVENTURE COMPLETE! 🎊\n";
        cout << "Congratulations, " << player.name << "!\n\n";

        cout << "\n🌍 Areas Explored:\n";
        if (player.exploredAreas.empty()) {
            cout << "None! Were you avoiding fun?\n";
        } else {
            for (const auto& area : player.exploredAreas) {
                cout << "- " << area << endl;
            }
        }

        // Silly score calculation
        int totalScore = player.silliness + player.weirdness + player.randomJokePoints;

        cout << "🏅 SILLINESS REPORT 🏅\n";
        cout << "Silliness Level: " << player.silliness << endl;
        cout << "Weirdness Meter: " << player.weirdness << endl;
        cout << "Random Joke Points: " << player.randomJokePoints << endl;
        cout << "Total Absurdity Score: " << totalScore << endl;
        
        // Humorous awards based on score
        if (totalScore < 50) 
            cout << "Award: Rookie Goofball 🧀\n";
        else if (totalScore < 100)
            cout << "Award: Master of Mild Madness 🤪\n";
        else if (totalScore < 150)
            cout << "Award: Supreme Silly Sovereign 🤡\n";
        else
            cout << "Award: ULTIMATE CHAOS COMMANDER OF THE UNIVERSE! 🌈🚀\n";
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
// CSV file reading and operation
void processCsvData(bool fromFile);
void processSalesData(bool fromFile);

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
    string filename;
    char choice;
    EnhancedWellnessBot bot2;
    StudentManagementSystem sms;
    InventoryManagementSystem ims;
    LibraryManagementSystem lms;
    EmployeeManagementSystem ems;
    SillyAdventureGame game2;
	

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
                cout << "16. CSV Age Adder [#72]\n";
                cout << "17. CSV Sales Calculator [#73]\n";
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
                    case 16:
                        // Ask user whether they want to input data manually or use a file
                        cout << "Do you want to (M)anually enter CSV data or (F)ill from a (F)ile? (M/F): ";
                        cin >> choice;
                        cin.ignore();  // Ignore leftover newline after the character input

                        if (choice == 'M' || choice == 'm') {
                            processCsvData(false);  // Call function with `false` to enter data manually
                        } else if (choice == 'F' || choice == 'f') {
                            processCsvData(true);   // Call function with `true` to load data from file
                        } else {
                            cout << "Invalid option. Please choose 'M' or 'F'.\n";
                        }
                        break;
                    case 17:
                        // Ask user whether they want to input data manually or use a file
                        cout << "Do you want to (M)anually enter CSV data or (F)ill from a (F)ile? (M/F): ";
                        cin >> choice;
                        cin.ignore();  // Ignore leftover newline after the character input

                        if (choice == 'M' || choice == 'm') {
                            processSalesData(false);  // Call function with `false` to enter data manually
                        } else if (choice == 'F' || choice == 'f') {
                            processSalesData(true);   // Call function with `true` to load data from file
                        } else {
                            cout << "Invalid option. Please choose 'M' or 'F'.\n";
                        }
                        break;
                    default:
                        cout << "Invalid choice.\n" ;
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
                cout << "9. Mental Wellness Bot [#80]\n";
                cout << "10. Student Management System [#74-75]\n";
                cout << "11. Product Inventory Management System [#76]\n";
                cout << "12. Library Management System [#77]\n";
                cout << "13. Employee Management System [#78]\n";
                cout << "14. Silly Adventure Game [#79]\n";
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
                    case 9:
                        bot2.run();
                        break;
                    case 10:
                        sms.processStudentData();
                        break;
                    case 11:
                        ims.manageInventory();
                        break;
                    case 12:
                        lms.managLibrary();
                        break;
                    case 13:
                        ems.manageEmployees();
                        break;
                    case 14:
                        game2.playAbsurdGame();
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

// Function to process CSV data entered via cin or from an external file
void processCsvData(bool fromFile) {
    string csvInput, line;
    vector<string> rows;
    vector<pair<string, int>> validEntries;  // Stores valid entries (name, age)

    if (fromFile) {
        // User provides file name to read from
        string filename;
        cout << "Enter the CSV file name: ";
        cin >> filename;
        cin.ignore();  // To ignore the leftover newline character from previous input

        ifstream inputFile(filename);

        // Check if the file opened successfully
        if (!inputFile.is_open()) {
            cout << "Error: Could not open the file " << filename << endl;
            return;
        }

        // Read the file line by line
        while (getline(inputFile, line)) {
            rows.push_back(line);
        }

        inputFile.close();

        if (rows.empty()) {
            cout << "The file is empty or contains no data.\n";
            return;
        }
    } else {
        // User manually enters CSV data via cin
        cout << "Enter CSV data like so [Name, Age] (end with an empty line):\n";
        while (true) {
            getline(cin, line);
            if (line.empty()) break;
            rows.push_back(line);
        }

        if (rows.empty()) {
            cout << "No data provided.\n";
            return;
        }
    }

    // Process the CSV data
    int totalAge = 0, validEntriesCount = 0;

    for (size_t i = 0; i < rows.size(); ++i) {
        stringstream ss(rows[i]);
        string name, ageStr;

        // Extract name and age from the current row
        if (getline(ss, name, ',') && getline(ss, ageStr)) {
            try {
                int age = stoi(ageStr);
                totalAge += age;
                validEntries.push_back(make_pair(name, age));
                validEntriesCount++;
            } catch (invalid_argument&) {
                cout << "Invalid age value in row " << i + 1 << ": " << rows[i] << "\n";
            } catch (out_of_range&) {
                cout << "Age out of range in row " << i + 1 << ": " << rows[i] << "\n";
            }
        } else {
            cout << "Malformed row " << i + 1 << ": " << rows[i] << "\n";
        }
    }

    // Print the summary
    cout << "Total sum of ages: " << totalAge << "\n";
    cout << "Number of valid entries processed: " << validEntriesCount << "\n";

    // Print the valid entries
    if (validEntriesCount > 0) {
        cout << "\nValid entries:\n";
        for (const auto& entry : validEntries) {
            cout << entry.first << ", " << entry.second << endl;
        }
    } else {
        cout << "No valid entries found.\n";
    }
}

// Function to process sales data entered via cin or from an external file
void processSalesData(bool fromFile) {
    string line;
    vector<string> rows;
    vector<pair<string, vector<int>>> validEntries;  // Stores valid entries (product name, sales for 12 months)

    if (fromFile) {
        // User provides file name to read from
        string filename;
        cout << "Enter the CSV file name: ";
        cin >> filename;
        cin.ignore();  // To ignore the leftover newline character from previous input

        ifstream inputFile(filename);

        // Check if the file opened successfully
        if (!inputFile.is_open()) {
            cout << "Error: Could not open the file " << filename << endl;
            return;
        }

        // Read the file line by line
        while (getline(inputFile, line)) {
            rows.push_back(line);
        }

        inputFile.close();

        if (rows.empty()) {
            cout << "The file is empty or contains no data.\n";
            return;
        }
    } else {
        // User manually enters CSV data via cin
        cout << "Enter CSV data like so [Product X, Jan Sales, Feb Sales, Mar sales, Apr sales,\n\tMay sales, June sales, July sales, August sales,\n\tSeptember sales, October sales, November sales, December sales](end with an empty line):\n";
        while (true) {
            getline(cin, line);
            if (line.empty()) break;
            rows.push_back(line);
        }

        if (rows.empty()) {
            cout << "No data provided.\n";
            return;
        }
    }

    // Process the sales data
    int validEntriesCount = 0;
    vector<string> months = {
        "January", "February", "March", "April", "May", "June", "July", "August", 
        "September", "October", "November", "December"
    };

    // Process each row (skip the first line if it's a header)
    for (size_t i = 0; i < rows.size(); ++i) {
        stringstream ss(rows[i]);
        string product;
        string salesStr;
        vector<int> sales;

        // Extract product name from the current row
        if (getline(ss, product, ',')) {
            bool valid = true;

            // Extract sales for each month and check validity
            for (size_t j = 0; j < 12; ++j) {
                if (getline(ss, salesStr, ',')) {
                    try {
                        int salesValue = stoi(salesStr);
                        sales.push_back(salesValue);
                    } catch (invalid_argument&) {
                        cout << "Invalid sales value for " << product << " in month " << months[j] << " (row " << i + 1 << ").\n";
                        valid = false;
                        break;
                    } catch (out_of_range&) {
                        cout << "Sales value out of range for " << product << " in month " << months[j] << " (row " << i + 1 << ").\n";
                        valid = false;
                        break;
                    }
                } else {
                    cout << "Missing sales data for " << product << " in month " << months[j] << " (row " << i + 1 << ").\n";
                    valid = false;
                    break;
                }
            }

            if (valid) {
                validEntries.push_back(make_pair(product, sales));
                validEntriesCount++;
            }
        } else {
            cout << "Malformed row " << i + 1 << ": " << rows[i] << "\n";
        }
    }

    // Print the summary
    cout << "\nAverage sales for each product:\n";
    for (const auto& entry : validEntries) {
        const string& productName = entry.first;
        const vector<int>& sales = entry.second;
        int totalSales = 0;

        for (int sale : sales) {
            totalSales += sale;
        }

        double averageSales = static_cast<double>(totalSales) / sales.size();
        cout << "Average sales for " << productName << ": " << averageSales << endl;
    }

    // Print the summary of how many valid entries were processed
    cout << "\nNumber of valid products processed: " << validEntriesCount << endl;
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