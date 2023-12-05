#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>
#include <random>
#include <ctime>

using namespace std;

#ifndef INFECTIOUS_HPP
#define INFECTIOUS_HPP

class Disease
{
private:
    double transmission_chance;
    int days_sick;

public:
    Disease(double transmission, int days) : transmission_chance(transmission), days_sick(days) {}

    double get_transmission_chance() const
    {
        return transmission_chance;
    }

    int get_days_sick() const
    {
        return days_sick;
    }
};

class Person
{
private:
    string status;
    int days_to_recover;

public:
    Person() : status("susceptible"), days_to_recover(0) {}

    string status_string() const
    {
        return status;
    }

    void one_more_day()
    {
        if (status == "infected")
        {
            days_to_recover--;
            if (days_to_recover <= 0)
            {
                status = "recovered";
            }
        }
    }

    void infect(const Disease &disease)
    {
        // srand(time(0));
        if (status == "susceptible")
        {
            double my_roll = ((double)rand() / (RAND_MAX));
            // cout << my_roll << endl;
            if (my_roll < disease.get_transmission_chance())
            {
                status = "infected";
                days_to_recover = disease.get_days_sick();
            }
        }
    }

    void touch(const Person &other, const Disease &disease)
    {
        if (status == "susceptible" && other.status_string() == "infected")
        {
            double my_roll = ((double)rand() / (RAND_MAX));
            if (my_roll < disease.get_transmission_chance())
            {
                status = "infected";
                days_to_recover = disease.get_days_sick();
            }
        }
    }

    bool is_recovered() const
    {
        if (status == "recovered")
        {
            return true;
        }
        return false;
    }

    int get_days_to_recover()
    {
        return days_to_recover;
    }

    void get_vaccinated()
    {
        status = "vaccinated";
        days_to_recover = 0;
    }
    void get_recovered()
    {
        status = "recovered";
        days_to_recover = 0;
    }
    void get_infected(const Disease &disease)
    {
        status = "infected";
        days_to_recover = disease.get_days_sick();
    }
};

class Population //
{
private:
    vector<Person> people;
    int population_count;

public:
    Population(double num_people) : population_count(num_people)
    {

        for (int i = 1; i <= num_people; i++)
        {
            people.emplace_back(); // Adds a new Person to the vector
        }
    }
    void random_infection(const Disease &disease, double initial_infect)
    {
        int num_to_infect = (people.size() * initial_infect);
        for (int i = 0; i < num_to_infect; ++i)
        {
            int index = rand() % people.size();
            if (people[index].status_string() == "infected")
            {
                while (people[index].status_string() == "infected")
                {
                    index = rand() % people.size();
                }
                // index = rand() % people.size();
                people[index].get_infected(disease);
            }
            else
            {
                people[index].get_infected(disease);
            }
        }
    }

    int count_infected() const
    {
        return count_if(people.begin(), people.end(), [](const Person &person)
                        { return person.status_string() == "infected"; });
    }

    bool has_infected() const
    {
        return any_of(people.begin(), people.end(), [](const Person &person)
                      { return person.status_string() == "infected"; });
    }

    void random_vaccination(double vaccination_rate)
    {
        int num_to_vaccinate = (people.size() * vaccination_rate);
        for (int i = 0; i < num_to_vaccinate; ++i)
        {
            int index = rand() % people.size();
            if (people[index].status_string() == "vaccinated")
            {
                while (people[index].status_string() == "vaccinated")
                {
                    index = rand() % people.size();
                }
                people[index].get_vaccinated();
            }
            else
            {
                people[index].get_vaccinated();
            }
        }
    }

    int count_vaccinated() const
    {
        return count_if(people.begin(), people.end(), [](const Person &person)
                        { return person.status_string() == "vaccinated"; });
    }
    void original_one_more_day()
    {
        for (auto &person : people)
        {
            person.one_more_day();
        }
    }

    void one_more_day(const Disease &disease)
    {
        // Create a copy of the current state to avoid simultaneous updates
        vector<Person> new_people = people;

        for (size_t i = 0; i < people.size(); ++i)
        {
            // If the person is infected, try to infect their neighbors
            if (people[i].status_string() == "infected")
            {
                // Assuming a linear arrangement

                // Infect left neighbor if not at the 0th index
                if (i > 0 && new_people[i - 1].status_string() == "susceptible")
                {
                    new_people[i - 1].touch(people[i], disease); // Adjust transmission chance and days_sick as needed
                }

                // Infect right neighbor if not at the last index
                if (i < people.size() - 1 && new_people[i + 1].status_string() == "susceptible")
                {
                    new_people[i + 1].touch(people[i], disease); // Adjust transmission chance and days_sick as needed
                }
            }
        }

        // Update the population state
        people = new_people;

        // Update the remaining logic for one more day
        for (auto &person : people)
        {
            person.one_more_day();
        }
    }

    void one_more_day_with_contacts(const Disease &disease, int contacts_per_day)
    {
        // Create a copy of the current state to avoid simultaneous updates
        vector<Person> new_people = people;

        // Iterate through each person in the population
        for (size_t i = 0; i < people.size(); ++i)
        {
            // If the person is infected, make contacts
            if (people[i].status_string() == "infected")
            {
                // Make contacts with a fixed number of random people
                for (int contact = 0; contact < contacts_per_day; ++contact)
                {
                    // Generate a random index to represent a random person in the population
                    int contact_index = rand() % people.size();

                    // Infect the contacted person
                    new_people[contact_index].touch(people[i], disease); // Adjust transmission chance and days_sick as needed
                }
            }
        }

        // Update the population state
        people = new_people;

        // Update the remaining logic for one more day
        for (auto &person : people)
        {
            person.one_more_day();
        }
    }

    const vector<Person> &get_people() const
    {
        return people;
    }

    void print_population_state() const
    {
        for (const auto &person : people)
        {
            char symbol;
            if (person.status_string() == "susceptible")
            {
                symbol = '?';
            }
            else if (person.status_string() == "infected")
            {
                symbol = '+';
            }
            else if (person.status_string() == "vaccinated")
            {
                symbol = 'x';
            }
            else
            {
                symbol = '-';
            }

            cout << symbol << " ";
        }
        cout << endl;
    }
    void infect_person(int index, const Disease &disease)
    {
        if (index >= 0 && index < people.size() && people[index].status_string() == "susceptible")
        {
            people[index].get_infected(disease);
        }
    }
    bool isPersonRecovered(int index) const
    {
        if (index >= 0 && index < people.size())
        {
            return people[index].is_recovered();
        }
        return false; // Return false for invalid index
    }
    void print_population_data() const
    {
        int num_susceptible = 0;
        int num_infected = 0;
        int num_recovered = 0;
        int num_vaccinated = 0;
        for (const auto &person : people)
        {

            if (person.status_string() == "susceptible")
            {
                num_susceptible++;
            }
            else if (person.status_string() == "infected")
            {
                num_infected++;
            }
            else if (person.status_string() == "vaccinated")
            {
                num_vaccinated++;
            }
            else
            {
                num_recovered++;
            }
        }
        cout << "number of infected: " << num_infected << " "
             << "number of recovered: " << num_recovered << " "
             << "number of vaccinated: "
             << num_vaccinated << " "
             << "number of susceptible: " << num_susceptible;
    }
};

#endif