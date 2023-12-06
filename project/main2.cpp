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
#include "infectious_with_mutation.hpp"
#include "main.h"
#include "main2.h"

using namespace std;

void mutation_simulation(int mutation_threshold, double vaccination_rate)
{
    //mutation thershold = number of transmissions before mutating, so the higher it is, the slower the disease mutates
    // Set up the initial parameters
    double initial_infection_rate = 0.005; // Initial percentage of infected people
    int contacts_per_day = 3;             // Number of contacts per day
    int variant_limit = 20;

    // Create a population
    Population1 population(10000);

    // Create a disease with initial parameters
    Disease1 disease(0.2, 7, mutation_threshold, variant_limit);

    // Introduce initial infection to the population
    population.random_infection(disease, initial_infection_rate);

    // Vaccinate a percentage of the population
    population.random_vaccination(vaccination_rate);

    cout << endl << "Simulation with Mutation Threshold: " << mutation_threshold
         << ", Vaccination Rate: " << vaccination_rate << endl;

    int day = 0;

    while (population.has_infected())
    {
        day++;
        cout << "Day: " << day << " ";
        population.one_more_day_with_contacts(disease, contacts_per_day);
        population.print_population_data();
        cout << endl;
    }
    cout << "Disease ran through the population in " << day << " days." << endl;
    cout << "---------------------------------------------------------" << endl;
    disease.reset_transmission_counter();
    disease.reset_variants_counter();
}
void mutation_simulation_with_vary_prob()
{
    for (int mutation_transmission = 0; mutation_transmission<=30; mutation_transmission++) //can be adjusted, created a lot of outputs for the graphs
    {
        mutation_simulation(mutation_transmission, 0.3);
    }
    
    for (double vaccination_rate = 0; vaccination_rate<=1; vaccination_rate+=0.01)
    {
        mutation_simulation(5, vaccination_rate);
    }

    cout << endl;
}

int main()
{
    // Seed the random number generator
    srand(std::time(0));

    //mutation_simulation(5,0.3);
    mutation_simulation_with_vary_prob();

}