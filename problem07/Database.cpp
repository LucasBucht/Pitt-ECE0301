#include "Database.hpp"

// initialize empty data
Database::Database() : num_entries(0){
}

// initialize with one row of Entry
Database::Database(Entry entry){
  data.push_back(entry);
  num_entries = 1;
}

// initialize with vector
Database::Database(std::vector<Entry> entries){
  data = entries;
  num_entries = entries.size();
}

// add function
bool Database::add(Entry entry){
  for (const Entry &e : data){
    if (e.id == entry.id)
      return false;
  }

  data.push_back(entry);
  num_entries++;
  return true;
}

// remove function
bool Database::remove(int id){
  for (int i = 0; i < num_entries; i++){
    if (data[i].id == id){
      data.erase(data.begin() + i);
      num_entries--;
      return true;
    }
  }
  return false;
}

// size function
int Database::size() const{
  return num_entries;
}

// is_empty function
bool Database::is_empty() const{
  return num_entries == 0;
}

// search function
bool Database::search(int id) const{
  for (const Entry &e : data){
    if (e.id == id){
      return true;
    }
  }
  return false;
}

// get_all_entries function
std::vector<Entry> Database::get_all_entries() const{
  return data;
}

// sort_by_id function
void Database::sort_by_id(bool ascending){
  if (num_entries < 2)
    return;
  for (int i = 0; i < num_entries - 1; i++){
    for (int j = 0; j < num_entries - 1; j++){
      bool swap = false;
      if (ascending){
        if (data[j].id > data[j + 1].id)
          swap = true;
      }
      else{
        if (data[j].id < data[j + 1].id)
          swap = true;
      }

      if (swap){
        Entry temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }
}

// sort_by_name function
void Database::sort_by_name()
{
  if (num_entries < 2)
    return;
  for (int i = 0; i < num_entries - 1; ++i){
    for (int j = 0; j < num_entries - i - 1; ++j){
      if (data[j].name > data[j + 1].name){
        Entry temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }
}

// search_criteria function
int Database::search_criteria(double upper[3]) const {
  for (const Entry &e : data){
    if (e.max_delay <= upper[0] && e.power_per_unit <= upper[1] && e.bulk_price <= upper[2]){
      return e.id;
    }
  }
  return -1;
}
