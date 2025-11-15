#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include <string>
#include <vector>

struct Entry
{
    int id;
    std::string name;
    int units, pins, transistors;
    double max_delay, power_per_unit, bulk_price;
};

// Database class declaration below
class Database
{
private:
    int num_entries;
    std::vector<Entry> data;

public:
    // A: Default Constructor
    Database();

    // B: Constructor takes Entry
    Database(Entry entry);

    // C: Constructor takes vector
    Database(std::vector<Entry> entries);

    // D: Add method
    bool add(Entry entry);

    // E: Remove method
    bool remove(int id);

    // F: Size method
    int size() const;

    // G: Is_Empty method
    bool is_empty() const;

    // H: Search method
    bool search(int id) const;

    // I: Get_All_Entries method
    std::vector<Entry> get_all_entries() const;

    // J: Sort_By_ID method
    void sort_by_id(bool ascending = true);

    // K: Sort_By_Name method
    void sort_by_name();

    // L: Search_Criteria method
    int search_criteria(double upper[3]) const;
};

#endif
