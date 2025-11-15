// I looked up better ways to organize my test cases, since they were getting very crowded and confusing. 
// Using: https://android.googlesource.com/platform/external/catch2/+/e7c3bdb3/docs/test-cases-and-sections.md
// This website showed me how to implement sections and better organization in my test cases.

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>

#include "Database.hpp"

const double THRESHOLD = 1e-9;

/* Provided test cases */

TEST_CASE("Test default construction", "[database]")
{
    Database db;
    REQUIRE(db.is_empty());
    REQUIRE(db.size() == 0);

    std::vector<Entry> test = db.get_all_entries();
    REQUIRE(test.size() == 0);
}

TEST_CASE("Test construction with one Entry", "[database]")
{
    // 7400 NAND data
    // id  name  units  pins  transistors  max_delay[ns]  power_per_unit[mW]  bulk_price[$]
    Entry test_entry = {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30};
    Database db(test_entry);
    REQUIRE_FALSE(db.is_empty());
    REQUIRE(db.size() == 1);

    std::vector<Entry> test = db.get_all_entries();
    REQUIRE(test.size() == 1);
    REQUIRE(test[0].id == test_entry.id);
    REQUIRE(test[0].name == test_entry.name);
    REQUIRE(test[0].units == test_entry.units);
    REQUIRE(test[0].pins == test_entry.pins);
    REQUIRE(test[0].transistors == test_entry.transistors);
    REQUIRE(std::abs(test[0].max_delay - test_entry.max_delay) <= THRESHOLD);
    REQUIRE(std::abs(test[0].power_per_unit - test_entry.power_per_unit) <= THRESHOLD);
    REQUIRE(std::abs(test[0].bulk_price - test_entry.bulk_price) <= THRESHOLD);
}

TEST_CASE("Test construction with vector", "[database]")
{
    // id  name  units  pins  transistors  max_delay[ns]  power_per_unit[mW]  bulk_price[$]
    std::vector<Entry> entries = {
        // quad 2-input NAND gates
        {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30},
        // quad 2-input AND gates
        {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30},
        // single 8-input NAND gate
        {7430, "nand8", 1, 14, 50, 22.0, 2.0, 0.40},
        // single BCD to 7-segment display
        {7447, "seven_seg", 2, 16, 80, 35.0, 30.0, 0.60},
        // dual JK Flip-Flops
        {7473, "jk_ff", 2, 14, 90, 20.0, 15.0, 0.50},
        // single 4-bit Adder with carry
        {7483, "adder_4", 1, 16, 100, 22.0, 24.0, 0.70},
        // single 8-bit Shift Register
        {7491, "shift_8", 1, 16, 120, 20.0, 20.0, 0.60}
    };
    Database db(entries);
    REQUIRE_FALSE(db.is_empty());
    REQUIRE(db.size() == entries.size());

    std::vector<Entry> test = db.get_all_entries();
    REQUIRE(test.size() == entries.size());
    for (int i = 0; i < entries.size(); i++)
    {
        REQUIRE(test[i].id == entries[i].id);
        REQUIRE(test[i].name == entries[i].name);
        REQUIRE(test[i].units == entries[i].units);
        REQUIRE(test[i].pins == entries[i].pins);
        REQUIRE(test[i].transistors == entries[i].transistors);
        REQUIRE(std::abs(test[i].max_delay - entries[i].max_delay) <= THRESHOLD);
        REQUIRE(std::abs(test[i].power_per_unit - entries[i].power_per_unit) <= THRESHOLD);
        REQUIRE(std::abs(test[i].bulk_price - entries[i].bulk_price) <= THRESHOLD);
    }
}

TEST_CASE("Test search", "[database]")
{
    // id  name  units  pins  transistors  max_delay[ns]  power_per_unit[mW]  bulk_price[$]
    std::vector<Entry> entries = {
        {7400, "nand2", 4, 14, 40, 22.0, 2.0, 0.30},
        {7408, "and2", 4, 14, 40, 15.0, 2.0, 0.30},
        {7430, "nand8", 1, 14, 50, 22.0, 2.0, 0.40},
        {7447, "seven_seg", 2, 16, 80, 35.0, 30.0, 0.60},
        {7473, "jk_ff", 2, 14, 90, 20.0, 15.0, 0.50},
        {7483, "adder_4", 1, 16, 100, 22.0, 24.0, 0.70},
        {7491, "shift_8", 1, 16, 120, 20.0, 20.0, 0.60}
    };

    Database dbdefault;
    for (int i = 0; i < entries.size(); i++)
    {
        REQUIRE_FALSE(dbdefault.search(entries[i].id));
    }

    Database dbentry(entries[0]);
    REQUIRE(dbentry.search(entries[0].id));

    Database db(entries);
    for (int i = 0; i < entries.size(); i++)
    {
        REQUIRE(db.search(entries[i].id));
    }
}


// Test Cases Added by Me

// Sample Entries
Entry e1 = {7408, "and2", 3, 14, 120, 0.4, 0.9, 2.5};
Entry e2 = {7430, "nand8", 5, 16, 300, 0.6, 1.2, 3.8};
Entry e3 = {7400, "nand2", 2, 12, 90, 0.35, 0.8, 2.1};
Entry e4 = {7473, "jk_ff", 4, 14, 150, 0.5, 1.0, 3.0};
Entry e5 = {7483, "add4", 6, 16, 350, 0.7, 1.5, 4.2};
Entry e6 = {7491, "shift_8", 7, 18, 420, 0.8, 1.6, 4.5};
Entry e7 = {7447, "seven_seg", 9, 20, 450, 1.1, 1.7, 4.8};

// Test Add and Size
TEST_CASE("Add entries and test size function", "[add][size]") {
    Database db;

    REQUIRE(db.add(e1) == true);
    REQUIRE(db.add(e2) == true);
    REQUIRE(db.add(e3) == true);
    REQUIRE(db.size() == 3);

    SECTION("Duplicate add should fail") {
        REQUIRE(db.add(e1) == false);
        REQUIRE(db.size() == 3);
    }
}

// Test Remove, Search, and Is_Empty
TEST_CASE("Remove entries and test search/empty/size", "[remove][search][is_empty]") {
    Database db;
    db.add(e1);
    db.add(e2);
    db.add(e3);

    REQUIRE(db.size() == 3);
    REQUIRE(db.search(7430) == true);

    SECTION("Remove an existing entry") {
        REQUIRE(db.remove(7430) == true);
        REQUIRE(db.search(7430) == false);
        REQUIRE(db.size() == 2);
    }

    SECTION("Remove non-existing entry should fail") {
        REQUIRE(db.remove(7402) == false);
        REQUIRE(db.size() == 3);
    }

    SECTION("Remove all entries and test is_empty()") {
        db.remove(7408);
        db.remove(7430);
        db.remove(7400);
        REQUIRE(db.is_empty() == true);
        REQUIRE(db.size() == 0);
    }
}

// Test Sort_By_ID
TEST_CASE("Sort database by ID ascending and descending", "[sort_by_id]") {
    Database db;
    db.add(e6); 
    db.add(e3); 
    db.add(e5); 
    db.add(e1);
    db.add(e7); 
    db.add(e2); 
    db.add(e4);

    SECTION("Ascending sort") {
        db.sort_by_id(true);
        std::vector<Entry> data = db.get_all_entries();

        REQUIRE(data[0].id == 7400);
        REQUIRE(data[1].id == 7408);
        REQUIRE(data[2].id == 7430);
        REQUIRE(data[3].id == 7447);
        REQUIRE(data[4].id == 7473);
        REQUIRE(data[5].id == 7483);
        REQUIRE(data[6].id == 7491);
    }

    SECTION("Descending sort") {
        db.sort_by_id(false);
        std::vector<Entry> data = db.get_all_entries();

        REQUIRE(data[0].id == 7491);
        REQUIRE(data[1].id == 7483);
        REQUIRE(data[2].id == 7473);
        REQUIRE(data[3].id == 7447);
        REQUIRE(data[4].id == 7430);
        REQUIRE(data[5].id == 7408);
        REQUIRE(data[6].id == 7400);
    }
}

// Test Sort_By_Name
TEST_CASE("Sort database by name alphabetically", "[sort_by_name]") {
    Database db;
    db.add(e1); 
    db.add(e2); 
    db.add(e3);
    db.add(e4); 
    db.add(e5); 
    db.add(e6); 
    db.add(e7);

    db.sort_by_name();
    std::vector<Entry> data = db.get_all_entries();

    std::vector<std::string> expected_names = {
        "add4", "and2", "jk_ff", "nand2", "nand8", "seven_seg", "shift_8"
    };

    for (size_t i = 0; i < data.size(); ++i) {
        REQUIRE(data[i].name == expected_names[i]);
    }
}

// Test Search_Criteria
TEST_CASE("Search entries by criteria", "[search_criteria]") {
    Database db;
    db.add(e1);
    db.add(e2);
    db.add(e3);

    double upper1[3] = {0.5, 1.0, 3.0};
    double upper2[3] = {0.2, 0.5, 1.0};

    SECTION("Criteria that matches entries") {
        int id = db.search_criteria(upper1);
        REQUIRE((id == 7408 || id == 7400));  // either matches
    }

    SECTION("Criteria that matches no entries") {
        int id = db.search_criteria(upper2);
        REQUIRE(id == -1);
    }
}