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
#include "../thirdparty/json/json.hpp"
#include "../thirdparty/fakeit/fakeit.hpp"
#include "../thirdparty/catch/catch.hpp"
#include "../include/person_dao.hpp"
#include "../include/db_memory.hpp"

using json = nlohmann::json;
using namespace fakeit;
using namespace Catch::Matchers;

using namespace db;
using namespace crud;


TEST_CASE("simple crud test", "[crud][inmemory]") {
    Person p = {.id = 1, .name = "Janusz", .yob = 1955};

    Database_in_memory datasource;
    Person_dao dao(&datasource, "Person_");

    SECTION("write and read database record") {
        dao.put(p);
        Person v = dao.get(1);
        REQUIRE(v == p);
    }
}

TEST_CASE("delete from db", "[crud][inmemory]") {
    Person p = {.id = 1, .name = "Janusz", .yob = 1955};

    Database_in_memory datasource;
    Person_dao dao(&datasource, "Person_");

    SECTION("write and read database record") {
        dao.put(p);
        std::list<Person> ret = dao.get();
        REQUIRE(ret.size() == 1);
    }

    SECTION("delete database record") {
        dao.del(p);
        std::list<Person> ret = dao.get();
        REQUIRE(ret.size() == 0);
    }
}

TEST_CASE("update record in db", "[crud][inmemory]") {
    Person p = {.id = 1, .name = "Janusz", .yob = 1955};

    Database_in_memory datasource;
    Person_dao dao(&datasource, "Person_");

    SECTION("write and read database record") {
        dao.put(p);
        Person v = dao.get(1);
        REQUIRE(v == p);
    }

    SECTION("write and read database record") {
        dao.put(p);
        Person v = dao.get(1);
        REQUIRE(v == p);
    }

    SECTION("update database record") {
        p.name = "Grazyna";
        dao.put(p);
        Person v = dao.get(1);
        REQUIRE(v.name == "Grazyna");
    }
}

TEST_CASE("getting non-existing record", "[crud][inmemory]") {
    Database_in_memory datasource;
    Person_dao dao(&datasource, "Person_");

    SECTION("write and read database record") {
        CHECK_THROWS(dao.get(1));
    }
}

