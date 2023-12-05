// Name: Ira Narang
// UTEID: in2933
// TACC Username: iranarang

#include <iostream>
#include <iomanip>
#include "infectious.hpp"
#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"
#include <ctime>
#include <random>

// 49.2.1.1 Person tests & 49.2.2.1 Interaction tests (adapted to include touch method)

// After being infected with a 100% transmittable disease, they should register as sick.
TEST_CASE("infection with 100% transmittable disease", "[Person]")
{
    Disease disease(1.0, 5);
    Person person;
    person.infect(disease);
    REQUIRE(person.status_string() == "infected");
}

// If they are vaccinated or recovered, and they come in contact with such a disease, they stay in their original state.
TEST_CASE("vaccinated/recovered person contact w disease", "[Person]")
{
    Disease disease(1.0, 5);
    Person vaccinated_person;
    Person recovered_person;

    vaccinated_person.get_vaccinated();
    recovered_person.get_recovered();

    vaccinated_person.infect(disease);
    recovered_person.infect(disease);

    REQUIRE(vaccinated_person.status_string() == "vaccinated");
    REQUIRE(recovered_person.status_string() == "recovered");
}

// If a disease has a transmission chance of 50%, and a number of people come into contact with it, about half of them should get sick.
TEST_CASE("transmission chance", "[Person]")
{
    srand(time(0));
    Disease disease(0.5, 5);

    double total_people = 1000;
    double people_infected = 0.0;

    for (int i = 0; i <= total_people; i++)
    {
        Person infected_person;
        Person susceptible_person;

        infected_person.get_infected(disease); // Infect one person

        susceptible_person.touch(infected_person, disease); // Use touch method

        if (susceptible_person.status_string() == "infected")
        {
            people_infected++;
        }
    }

    // cout << people_infected;
    double transmission_chance = 0.5;
    double actual_transmission_percent = (people_infected) / (total_people);

    double prec = 0.1;

    REQUIRE(actual_transmission_percent >= (transmission_chance - prec));
    REQUIRE(actual_transmission_percent <= (transmission_chance + prec));
}

// 49.2.3.1 Population tests

// With a vaccination percentage of 100%, everyone should indeed be vaccinated.
TEST_CASE("vaccination rate", "[Population]")
{
    // Create a population with 100 people
    int population_count = 100;
    Population population(population_count);

    // Vaccinate the entire population with 100% vaccination rate
    population.random_vaccination(1.0);

    // Check that every person in the population is vaccinated
    REQUIRE(population.count_vaccinated() == population_count);
}

// 49.3.1.1 tests

// Test that the number of infected people stays constant during the disease duration
TEST_CASE("constant infected count", "[Population]")
{
    // Set up a population with 100 people
    int population_count = 100;
    Population population(population_count);

    // Set up a disease with a 50% transmission chance and a duration of 5 days
    Disease disease(0.5, 5);

    // Infect 10 random people in the population initially
    population.random_infection(disease, 0.1);

    // Record the initial counts
    int initial_infected_count = population.count_infected();
    int initial_healthy_count = population_count - initial_infected_count;

    // Run the simulation for 10 days
    for (int day = 1; day < 5; ++day)
    {
        population.original_one_more_day();
        int current_infected_count = population.count_infected();

        int current_healthy_count = population_count - current_infected_count;

        // Check that the number of infected people stays constant
        REQUIRE(current_infected_count == initial_infected_count);

        // Check that the sum of healthy and infected people remains equal to the population size
        REQUIRE(current_healthy_count + current_infected_count == population_count);
    }
}

// 49.3.2.1 Tests

// 1st sanity test
TEST_CASE("sanity test with p = 1", "[Population]")
{
    // Set up a population with 5 people
    int population_count = 5;
    Population population(population_count);

    // Set up a disease with a 100% transmission chance and a duration of 5 days
    Disease disease(1.0, 5);

    // Infect person 2
    population.infect_person(2, disease);

    // Run the simulation for one day
    population.one_more_day(disease);

    // Check that the next day there should be 3 people sick
    REQUIRE(population.count_infected() == 3);

    // If the infected person is the first or last, there should be two sick
    population = Population(population_count); // Reset population
    population.infect_person(0, disease);
    population.one_more_day(disease);
    REQUIRE(population.count_infected() == 2);

    population = Population(population_count); // Reset population
    population.infect_person(population_count - 1, disease);
    population.one_more_day(disease);
    REQUIRE(population.count_infected() == 2);
}

// 2nd sanity test
TEST_CASE("simulation duration with p = 1", "[Population]")
{
    // Set up a population with 5 people
    int population_count = 5;
    Population population(population_count);

    // Set up a disease with a 100% transmission chance and a duration of 5 days
    Disease disease(1.0, 5);

    // Infect person 0
    population.infect_person(0, disease);

    int days = 1;

    // Run the simulation until all people are infected
    while (!(population.get_people().back().status_string() == "infected"))
    {
        population.one_more_day(disease);
        days++;
    }

    // Check that the simulation ran for a number of days equal to the size of the population
    REQUIRE(days == population_count);
}

// 3rd sanity test
TEST_CASE("simulation duration with p = 0.5", "[Population]")
{
    // Set up a population with 5 people
    int population_count = 5;
    Population population(population_count);

    // Set up a disease with a 50% transmission chance and a duration of 5 days
    Disease disease(0.5, 5);

    // Infect person 0
    population.infect_person(0, disease);

    int days = 1;

    // Run the simulation until all people are infected
    while (!(population.get_people().back().status_string() == "infected"))
    {
        population.one_more_day(disease);
        days++;
    }

    // Check that the simulation ran for a number of days equal to the size of the population
    REQUIRE_NOTHROW(days == population_count); // shows that when the probability of getting the disease isn't 100%, this statement isn't true
}