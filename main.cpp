#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

// Function to print the current generation
void print_generation(const std::vector<int>& generation, int gen_number, size_t max_width) {
    std::cout << "Generation " << gen_number << ":" << std::endl;
    size_t padding = (max_width - generation.size()) / 2;
    
    for (size_t i = 0; i < padding; ++i) {
        std::cout << "  ";
    }
    
    for (int cell : generation) {
        std::cout << (cell ? "#" : " ") << " ";
    }
    std::cout << std::endl << std::endl;
}

// Function to apply the selected rule to the current generation
std::vector<int> apply_rule(const std::vector<int>& generation, int rule) {
    std::vector<int> next_generation(generation.size());

    for (size_t i = 0; i < generation.size(); ++i) {
        int left = (i == 0) ? generation.back() : generation[i - 1];
        int current = generation[i];
        int right = (i == generation.size() - 1) ? generation.front() : generation[i + 1];

        switch (rule) {
            case 30:
                next_generation[i] = left ^ current;
                break;
            case 90:
                next_generation[i] = left ^ right;
                break;
            case 110:
                next_generation[i] = (left && current && !right) || (left && !current && right) || (!left && !current && right) || (!left && !current && !right) ? 0 : 1;
                break;
            default:
                std::cout << "Invalid rule number." << std::endl;
                exit(1);
        }
    }

    return next_generation;
}

int main() {
    std::vector<int> generation;
    std::vector<std::vector<int>> generations;
    int initial_size, rule;
    std::string initial_pattern;

    // Get initial condition
    std::cout << "Enter initial size of the generation: ";
    std::cin >> initial_size;

    std::cout << "Enter initial pattern with 1 for black and 0 for white (e.g. 00100): ";
    std::cin >> initial_pattern;

    generation.resize(initial_size, 0);
    for (size_t i = 0; i < initial_pattern.size(); ++i) {
        generation[i] = initial_pattern[i] == '1' ? 1 : 0;
    }

    // Choose rule
    std::cout << "Choose a rule (30, 90, or 110): ";
    std::cin >> rule;

    int steps = 1000;
    generations.reserve(steps);

    for (int step = 0; step < steps; ++step) {
        generations.push_back(generation);
        generation = apply_rule(generation, rule);
    }


    size_t max_width = generations.back().size() * 2;

    // Print generations from bottom up
    for (int step = 0; step < steps; ++step) {
        print_generation(generations[step], step, max_width);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Add a 100ms delay between each generation
    }

    return 0;
}
