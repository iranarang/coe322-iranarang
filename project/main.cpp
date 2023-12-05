// Name: Ira Narang
// UTEID: in2933
// TACC Username: iranarang

#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>
#include <random>
#include <ctime>
#include "infectious.hpp"
#include "main.h"

using namespace std;

// Exercise 49.1
void simulation_joe()
{
    Person joe;              // create a new person, joe
    Disease disease(0.5, 5); // create a new disease, disease
    for (int step = 1; step <= 10; ++step)
    { // run a simulation lasting up to 10 days
        joe.one_more_day();

        if (step == 3)
        {
            joe.infect(disease); // infect joe on the third day
        }

        cout << "On day " << step << ", Joe is "
             << joe.status_string() << endl;
        if (joe.is_recovered())
        { // if joe is recovered, stop running the simulation
            break;
        }
    }
    cout << endl;
}

// Exercise 49.4
void simulation_for_few_days()
{
    // Create a population with 10 people
    int population_count1 = 10;
    Population population1(population_count1);
    Disease disease1(0.5, 5);

    // Print the initial state of the population
    cout << "Initial State: " << endl;
    population1.print_population_state();

    population1.random_infection(disease1, 0.1);

    cout << "After Infection: " << endl;
    population1.print_population_state();

    // Run simulation for a few days
    for (int day = 1; day <= 5; ++day)
    {
        population1.original_one_more_day();
        std::cout << "Day " << day << ": ";
        population1.print_population_state();
    }
    cout << endl;
}

// Exercise 49.5 and Exercise 49.6
// Run simulations with different population sizes and contagion probabilities
void test_one_more_day(int population_size, double contagion_probability)
{
    Population population2(population_size);
    Disease disease2(contagion_probability, 5);  // Adjust days_sick as needed
    population2.random_infection(disease2, 0.1); // infect an initial set of people
    population2.random_vaccination(0.1);         // vaccinate an initial set of people, unrealistic bc the people next to the vaccinated can't get infected either

    cout << "Simulation with Population Size: " << population_size
         << ", Contagion Probability: " << contagion_probability << endl;

    // Run the simulation for a fixed number of days (e.g., 10)
    for (int day = 1; day <= 10; ++day)
    {
        population2.one_more_day(disease2);
        cout << "Day " << day << ": ";
        population2.print_population_state();
    }

    cout << "---------------------------------------------------------" << endl;
}

void test_one_more_day_with_varying_prob()
{
    for (int population_size : {10, 20, 50})
    {
        for (double contagion_probability : {0.1, 0.3, 0.5})
        {
            test_one_more_day(population_size, contagion_probability);
        }
    }
    cout << endl;
}

// 49.3.4 Spreading
void test_one_more_day_with_contacts(double probability, double vacc_rate)
{
    // Run the simulation for a fixed number of days (e.g., 10) with 6 contacts per day
    int population_count2 = 50;
    int no_of_days = 10;
    Population population3(population_count2);
    Disease disease3(probability, 5);
    population3.random_infection(disease3, 0.1); // infect an initial set of people
    population3.random_vaccination(vacc_rate);   // infect an initial set of people

    cout << "Simulation with Contagion Probability: " << probability
         << ", Vaccination Probability: " << vacc_rate << endl;

    for (int day = 1; day <= no_of_days; ++day)
    {
        population3.one_more_day_with_contacts(disease3, 6);
        cout << "Day " << day << ": ";
        population3.print_population_state();
    }
    cout << "---------------------------------------------------------" << endl;
}

void test_one_more_day_with_contacts_with_vary_prob()
{
    for (double contagion_probability : {0.1, 0.3, 0.5})
    {
        for (double vaccination_rate : {0.1, 0.3, 0.5})
        {
            test_one_more_day_with_contacts(contagion_probability, vaccination_rate);
        }
    }
    cout << endl;
}

// Exercise 49.7
void test_realistic_population(double probability, double vacc_rate)
{
    int population_count3 = 40000;
    Population population3(population_count3);
    Disease disease4(probability, 5);
    population3.random_infection(disease4, 0.000025); // infect an initial set of people
    population3.random_vaccination(vacc_rate);        // infect an initial set of people

    cout << "Simulation with Contagion Probability: " << probability
         << ", Vaccination Rate: " << vacc_rate << endl;

    int day = 0;
    while (population3.has_infected())
    {

        day++;
        population3.one_more_day_with_contacts(disease4, 6);
        cout << "Day " << day << ": ";
        population3.print_population_data();
        cout << '\n';
    }
    cout << "Disease ran through the population in " << day << " days." << endl;
    cout << "---------------------------------------------------------" << endl;
}

void test_realistic_population_with_vary_prob()
{

    for (double vaccination_rate : {0.2, 0.4, 0.6})
    {
        test_realistic_population(0.5, vaccination_rate);
    }
    cout << endl;
}

// Exercise 49.8 herd immunity
void herd_immunity(double probability)
{
    int population_count = 10000;
    Population population(population_count);
    Disease disease(probability, 5);
    double vaccination_rate = 0.0;
    int day = 0;

    cout << "Investigating Herd Immunity for Contagion Probability: " << probability << endl;

    while (vaccination_rate <= 1.0)
    {
        population.random_infection(disease, 0.0001);    // infect an initial set of people
        population.random_vaccination(vaccination_rate); // vaccinate the population

        int num_susceptible_before = 0;
        int num_infected_before = 0;
        for (const auto &person : population.get_people())
        {
            if (person.status_string() == "susceptible")
            {
                num_susceptible_before++;
            }
            else if (person.status_string() == "infected")
            {
                num_infected_before++;
            }
        }

        while (population.has_infected())
        {
            day++;
            population.one_more_day_with_contacts(disease, 6);
        }

        int num_susceptible = 0;
        int num_infected = 0;
        for (const auto &person : population.get_people())
        {
            if (person.status_string() == "susceptible")
            {
                num_susceptible++;
            }
            else if (person.status_string() == "infected")
            {
                num_infected++;
            }
        }

        double immunity_percentage = static_cast<double>(num_susceptible) / static_cast<double>(num_susceptible_before);
        // cout << "Vaccination Rate: " << vaccination_rate << ", Immunity Percentage: " << immunity_percentage << endl;

        if (immunity_percentage > 0.95)
        {
            break;
        }

        // Reset for the next iteration
        day = 0;
        vaccination_rate += 0.01;
        population = Population(population_count); // Reset the population
    }
    if (vaccination_rate > 0.99)
    {
        cout << "Herd immunity was not achieved." << endl;
        cout << '\n';
    }
    else
    {
        cout << "Required Vaccination Rate to Achieve 95% Immunity: " << vaccination_rate << endl;
        cout << '\n';
    }
    cout << endl;
}

void herd_immunity_with_vary_prob()
{

    for (double contagion_probability = 0; contagion_probability < 1.0; contagion_probability += 0.01)
    {

        herd_immunity(contagion_probability);
    }
    cout << endl;
}

int main()
{
    srand(time(0));

    cout << "Exercise 49.1: " << endl;
    simulation_joe();

    cout << "Exercise 49.4: " << endl;
    simulation_for_few_days();

    cout << "Exercise 49.5 and 49.6: " << endl;
    test_one_more_day(10, 0.5);
    cout << endl
         << "With varying probability: " << endl;
    test_one_more_day_with_varying_prob();

    cout << "49.3.4: " << endl;
    test_one_more_day_with_contacts(0.5, 0);
    cout << endl
         << "With varying probability: " << endl;
    test_one_more_day_with_contacts_with_vary_prob();

    cout << "Exercise 49.7: " << endl;
    test_realistic_population(0.4, 0.2);
    cout << endl
         << "With varying probability: " << endl;
    test_realistic_population_with_vary_prob();

    cout << "Exercise 49.8: " << endl;
    herd_immunity(0.1);
    cout << endl
         << "With varying probability: " << endl;
    herd_immunity_with_vary_prob();
}