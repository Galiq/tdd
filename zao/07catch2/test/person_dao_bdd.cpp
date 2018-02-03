/*
    Example tests
    Copyright (C) 2017 Tadeusz Puźniakowski

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "../include/db_memory.hpp"
#include "../include/person_entity.hpp"
#include "../thirdparty/catch/catch.hpp"
#include "../thirdparty/fakeit/fakeit.hpp"
#include "../include/person_dao.hpp"

using json = nlohmann::json;
using namespace fakeit;
using namespace Catch::Matchers;

using namespace db;
using namespace crud;

std::string random_string(size_t length) {
    auto randchar = []() -> char {
        const char charset[] =
                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

bool compare_id(const Person &first, const Person &second) {
    unsigned int i = 0;
    while ((i < first.id) && (i < second.id)) {
        if (first.id < second.id) return true;
        else if ((first.id) > (second.id)) return false;
        ++i;
    }
    return (first.id < second.id);
}

SCENARIO("working on filled database", "[crud][bdd]") {

    Database_in_memory datasource;
    Person_dao dao(&datasource, "Person_");

    GIVEN("the database is empty") {
        REQUIRE(dao.get().size() == 0);

        WHEN("there is added one person") {
            Person p = {.id = 1, .name = "Janusz", .yob = 1955};
            dao.put(p);

            THEN("there is one item in database") {
                CAPTURE(dao.get());
                REQUIRE(dao.get().size() == 1);
            }

            THEN("the item is the same as added") {
                REQUIRE(dao.get(1) == p);
            }

            THEN("it is impossible to get element that has not been added") {
                CAPTURE(dao.get());
                REQUIRE_THROWS_WITH(dao.get(3), Contains("not found") && Contains("3"));
            }
        }
    }
}

SCENARIO("delete elements from database", "[crud][bdd]") {

    Database_in_memory datasource;
    Person_dao dao(&datasource, "Person_");
    std::list<Person> recordsAfterDeletion;

    for (int i = 1; i <= 100; i++) {
        Person p = {.id = i, .name = random_string(6), .yob = 1900 + rand() % 69 + 20};
        if (!(i == 1 || i == 50 || i == 99)) {
            recordsAfterDeletion.push_back(p);
        }
        dao.put(p);
    }

    GIVEN("the database has 100 records") {
        REQUIRE(dao.get().size() == 100);

        WHEN("there are 3 elements deleted") {
            Person p1 = dao.get(1);
            dao.del(p1);
            Person p50 = dao.get(50);
            dao.del(p50);
            Person p99 = dao.get(99);
            dao.del(p99);

            THEN("the database has 97 elements") {
                CAPTURE(dao.get());
                REQUIRE(dao.get().size() == 97);
            }

            THEN("the 97 items are in database") {
                std::list<Person> allElementsSorted = dao.get();
                allElementsSorted.sort(compare_id);
                recordsAfterDeletion.sort(compare_id);
                REQUIRE(allElementsSorted == recordsAfterDeletion);
            }

            THEN("it is impossible to get element that was deleted") {
                REQUIRE_THROWS_WITH(dao.get(1), Contains("not found"));
                REQUIRE_THROWS_WITH(dao.get(50), Contains("not found"));
                REQUIRE_THROWS_WITH(dao.get(99), Contains("not found"));
            }
        }
    }
}

SCENARIO("add elements to database", "[crud][bdd]") {

    Database_in_memory datasource;
    Person_dao dao(&datasource, "Person_");
    std::list<Person> recordsAfterDeletion;

    for (int i = 1; i <= 100; i++) {
        Person p = {.id = i, .name = random_string(6), .yob = 1900 + rand() % 69 + 20};
        dao.put(p);
    }

    GIVEN("the database has 100 records") {
        REQUIRE(dao.get().size() == 100);

        WHEN("there are 3 elements added") {
            Person p1 = {.id = 101, .name = random_string(6), .yob = 1900 + rand() % 69 + 20};
            dao.put(p1);
            Person p111 = {.id = 111, .name = random_string(6), .yob = 1900 + rand() % 69 + 20};
            dao.put(p111);
            Person p199 = {.id = 199, .name = random_string(6), .yob = 1900 + rand() % 69 + 20};
            dao.put(p199);

            THEN("the database has 103 elements") {
                CAPTURE(dao.get());
                REQUIRE(dao.get().size() == 103);
            }

            THEN("it is possible to get element that was addes") {
                REQUIRE(dao.get(101).id == 101);
                REQUIRE(dao.get(111).id == 111);
                REQUIRE(dao.get(199).id == 199);
            }
        }
    }
}