#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>

#include "database.hpp"
#include "constants.hpp"

/* Provided test cases */

TEST_CASE("Test initialize", "[database]")
{
    // create the database as a dynamic array
    // ENTRIES and COLS are defined in constants.hpp
    // as the number of rows and columns in DATA, respectively
    double *db = new double[ENTRIES * COLS];
    // use the provided initialize function to fill db with entries from DATA
    initialize(db);

    // Get each value in the dynamic array db, and confirm that it matches
    // the corresponding value in DATA.
    // This tests that the initialize function called above
    // has correctly copied all of the values from DATA into db.
    double dbval, ref, diff;
    bool db_matches_DATA = true; // define a boolean to reduce REQUIRE statements in the loop
    for (int r = 0; r < ENTRIES; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            // use the index function to get a 1D index for db from the row,column
            dbval = db[index(r, c)];
            // use double brackets to index DATA as a static 2D array
            ref = DATA[r][c];
            // these are double values, so we should check that their difference
            // is within a threshold instead of using ==
            diff = std::abs(dbval - ref);
            db_matches_DATA = (diff <= THRESHOLD);
            if (!db_matches_DATA)
            {
                // if any mismatch is detected, stop the comparisons
                break;
            }
        }
        if (!db_matches_DATA)
        {
            // need a second break to break out of the outer loop
            break;
        }
    }
    // check whether the loops completed without a mismatch
    REQUIRE(db_matches_DATA);

    // always deallocate at the end of each test case
    // when allocating with "new" in that test case
    delete[] db;
}

TEST_CASE("Test search", "[database]")
{
    double *db = new double[ENTRIES * COLS];
    initialize(db);

    // search for each DATA value in the corresponding column of db
    std::string field;
    double value;
    bool db_search = true;
    for (int r = 0; r < ENTRIES; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            // defining field and value outside of the function call
            // makes debugging easier
            field = FIELDS[c];
            value = DATA[r][c];
            db_search = search(field, value, db, ENTRIES);
            if (!db_search)
            {
                break;
            }
        }
        if (!db_search)
        {
            break;
        }
    }
    REQUIRE(db_search);

    delete[] db;
}

TEST_CASE("Search for missing field and missing value", "[database]") 
{
    double *db = new double[ENTRIES * COLS];
    initialize(db);

    // Search for a non-existent field
    REQUIRE_FALSE(search("Temperature", 300.0, db, ENTRIES));

    // Search for a non-existent value in an existing field
    REQUIRE_FALSE(search("Class", 3.1415, db, ENTRIES));

    delete[] db;
}

TEST_CASE("Add entry with new data (Moon) and verify", "[database]")
{
    int rows = ENTRIES;
    double *db = new double[rows * COLS];
    initialize(db);

    // Moon entry
    double moon[COLS] = {301, 3, 1737.4, 7.349e22, 3.3437, 27.321582};

    REQUIRE(add_entry(moon, db, rows));
    REQUIRE(rows == ENTRIES + 1);

    // Verify the new row was actually added
    REQUIRE(search("ID", 301, db, rows));
    REQUIRE(search("Class", 3, db, rows));
    REQUIRE(search("Orbit", 27.321582, db, rows));

    delete[] db;
}

TEST_CASE("Add duplicate entry (Earth) should fail", "[database]")
{
    int rows = ENTRIES;
    double *db = new double[rows * COLS];
    initialize(db);

    // Earth's row
    double earth_dup[COLS] = {399, 1, 6371.0084, 5.97217e24, 5.5134, 1.0000174};

    // Attempt to add duplicate
    REQUIRE_FALSE(add_entry(earth_dup, db, rows));

    // Rows should be unchanged
    REQUIRE(rows == ENTRIES);

    delete[] db;
}

TEST_CASE("Remove existing entry (Sun) and verify", "[database]")
{
    int rows = ENTRIES;
    double *db = new double[rows * COLS];
    initialize(db);

    // Remove the sun
    REQUIRE(remove_entry(10, db, rows));

    // Should have one less row
    REQUIRE(rows == ENTRIES - 1);

    // Searching for Sun's class should fail
    REQUIRE_FALSE(search("Class", 0, db, rows));

    delete[] db;
}

TEST_CASE("Add then remove entry and verify in-between", "[database]")
{
    int rows = ENTRIES;
    double *db = new double[rows * COLS];
    initialize(db);

    // Add Moon
    double moon[COLS] = {301, 3, 1737.4, 7.349e22, 3.3437, 27.321582};
    REQUIRE(add_entry(moon, db, rows));
    REQUIRE(search("ID", 301, db, rows));

    // Remove Moon
    REQUIRE(remove_entry(301, db, rows));

    // Verify it's gone
    REQUIRE_FALSE(search("ID", 301, db, rows));
    REQUIRE(rows == ENTRIES);

    delete[] db;
}


// Check Off One
TEST_CASE("Search, then add duplicate, and not aliases", "[database]"){
    
    double *db = new double[ENTRIES * COLS];
    initialize(db);
    REQUIRE_FALSE(search("Temperature", 300.0, db, ENTRIES));

    int rows = ENTRIES;
    double earth_dup[COLS] = {399, 1, 6371.0084, 5.97217e24, 5.5134, 1.0000174};
    REQUIRE_FALSE(add_entry(earth_dup, db, rows));

    REQUIRE(rows == ENTRIES);

    delete[] db;

    std::vector<int> static_array = {1, 4, 9, 16};
    std::vector<int> dynamic_array;

    for (int i = 0; i < 4; i++)
        dynamic_array.push_back(static_array[i]);

    for (int i = 0; i < 4; i++){
        REQUIRE_FALSE(&dynamic_array[i] == &static_array[i]);
        REQUIRE(dynamic_array[i] == static_array[i]);
    }
}