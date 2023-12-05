#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>
#include <random>
#include <ctime>

using namespace std;

#ifndef INFECTIOUS_WITH_MUTATION_HPP
#define INFECTIOUS_WITH_MUTATION_HPP

int transmissions_counter = 0; 
int global_variants_counter = 0; 


class Disease1
{
private:
    double transmission_chance;
    int days_sick;
    int transmissions_until_mutation; // New parameter to determine after how many transmissions the disease mutates
    int variant;                      // Variant of the disease
    int variant_limit;
public:
    Disease1(double transmission, int days, int mutations_threshold, int limit)
        : transmission_chance(transmission), days_sick(days), transmissions_until_mutation(mutations_threshold), variant_limit(limit), variant(0) {}

    double get_transmission_chance() const
    {
        return transmission_chance;
    }

    int get_days_sick() const
    {
        return days_sick;
    }

    int get_variant() const
    {
        return variant;
    }
    
    static void increment_transmissions_counter()
    {
        transmissions_counter++;
    }

    void mutate_variant()
    {
        global_variants_counter++;
        variant = global_variants_counter; // Update the global variants counter
    }

    bool should_mutate() 
    {
        if ((transmissions_counter % transmissions_until_mutation == 0) && (check_variant_limit()))
        {
            //increment_transmissions_counter();
            return true;
        }
        return false;
        
    }

    static int get_transmissions_counter()
    {
        return transmissions_counter;
    }

    static int get_global_variants_counter()
    {
        return global_variants_counter;
    }
    bool check_variant_limit()
    {
        if (global_variants_counter >= variant_limit){
            return false;
        }
        else {
            return true;
        }
    }
    void reset_transmission_counter()
    {
        transmissions_counter = 0;
    }
    void reset_variants_counter()
    {
        global_variants_counter = 0;
    }
};


class Person1
{
private:
    string status;
    int days_to_recover;
    vector<int> recovered_variants;

public:
    Person1() : status("susceptible"), days_to_recover(0) {}

    string status_string() const
    {
        return status;
    }

    bool contains_value(const vector<int>& vec, int value)
    {
        return find(vec.begin(), vec.end(), value) != vec.end();
    }

    void one_more_day(const Disease1 &disease)
    {
        if (status == "infected" )
        {
            days_to_recover--;
            if (days_to_recover <= 0 && !contains_value(recovered_variants, disease.get_variant()))
            {
                status = "susceptible"; 
                recovered_variants.push_back(disease.get_variant());
            }
        }
        //cout << "variant number: " << disease.get_variant() << endl;
    }

    void infect(const Disease1 &disease)
    {
        if (status == "susceptible" && !contains_value(recovered_variants, disease.get_variant())) //cannot infect someone while theyre already infected
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

    void touch(const Person1 &other, const Disease1 &disease)
    {
        if ((status == "susceptible") && (other.status_string() == "infected") && (!contains_value(recovered_variants, disease.get_variant())))
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
    void get_infected(const Disease1 &disease)
    {
        status = "infected";
        days_to_recover = disease.get_days_sick();
    }

    void get_variant_num(Disease1 &disease) {
        cout << "variant number: " << disease.get_variant() << endl;
    }
    vector<int> get_recovered_variants(){
        return recovered_variants;
    }


};

class Population1
{
private:
    vector<Person1> people;
    int population_count;

public:
    Population1(double num_people) : population_count(num_people)
    {

        for (int i = 1; i <= num_people; i++)
        {
            people.emplace_back(); // Adds a new Person1 to the vector
        }
    }
    void random_infection(const Disease1 &disease, double initial_infect)
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
        return count_if(people.begin(), people.end(), [](const Person1 &person)
                        { return person.status_string() == "infected"; });
    }

    bool has_infected() const
    {
        return any_of(people.begin(), people.end(), [](const Person1 &person)
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
        return count_if(people.begin(), people.end(), [](const Person1 &person)
                        { return person.status_string() == "vaccinated"; });
    }
    void original_one_more_day(Disease1 &disease)
    {
        for (auto &person : people)
        {
            person.one_more_day(disease);
        }
        //disease.increment_transmissions_counter();

    }

    void one_more_day(Disease1 &disease)
    {
        // Create a copy of the current state to avoid simultaneous updates
        vector<Person1> new_people = people;

        for (size_t i = 0; i < people.size(); ++i)
        {
            // If the person is infected, try to infect their neighbors
            if ((people[i].status_string() == "infected") && !(people[i].contains_value(people[i].get_recovered_variants(), disease.get_variant())))
            {
                if (disease.should_mutate())
                {
                    disease.mutate_variant();
                }
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
            person.one_more_day(disease);
        }
    }
    void one_more_day_with_contacts(Disease1 &disease, int contacts_per_day)
    {
        // Create a copy of the current state to avoid simultaneous updates
        vector<Person1> new_people = people;

        // Iterate through each person in the population
        for (size_t i = 0; i < people.size(); ++i)
        {
            // If the person is infected, make contacts
            if (people[i].status_string() == "infected")
            {
 
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
            person.one_more_day(disease);
        }

        disease.increment_transmissions_counter();

        if (disease.should_mutate())
        {
            //cout << "should mutate" << endl;
            disease.mutate_variant();
        }
        else {
            //cout << "no";
        }
        
    }

    const vector<Person1> &get_people() const
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
    void infect_person(int index, const Disease1 &disease)
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
        return false; // Return false for an invalid index
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
             << "number of vaccinated: " << num_vaccinated << " "
             << "number of susceptible: " << num_susceptible;
    }
};

#endif
