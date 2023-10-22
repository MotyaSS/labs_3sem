#include <string.h>
#include "l1-2.h"

int db_construct(user_db* db, size_t pref_cap) {
  if (db == NULL) {
    return 1;
  }

  db->users = (user*) malloc(sizeof(user) * pref_cap);
  if (db->users == NULL) {
    return -1;
  }
  db->cap = pref_cap;
  db->cur_size = 0;

  return 0;
}

int db_expand(user_db* db) {
  if (db == NULL) {
    return 1;
  }

  db->cap *= 2;
  user* temp = (user*) realloc(db->users, sizeof(user) * db->cap);
  if (temp == NULL) {
    return -1;
  }

  db->users = temp;
  return 0;
}

int db_add_user(user_db* db, user user_) {
  if (db == NULL) {
    return 1;
  }
  if (db->cur_size >= db->cap) {
    if (db_expand(db) != 0) {
      return -1;
    }
  }

  db->users[db->cur_size].password = user_.password;
  strncpy(db->users[db->cur_size].login, user_.login, LOGIN_LEN);
  db->users[db->cur_size].sanctions = -1;
  db->cur_size++;

  return 0;
}

int db_destruct(user_db* db) {
  free(db->users);
  db->users = NULL;
  db->cap = 0;
  db->cur_size = 0;
  return 0;
}

user* db_get_user(user_db* db, char login[LOGIN_LEN + 1]) {
  user* temp_arr = db->users;
  for (int i = 0; i < db->cur_size; i++) {
    if (compare(temp_arr[i].login, login))
      return temp_arr + i;
  }
  return NULL;
}