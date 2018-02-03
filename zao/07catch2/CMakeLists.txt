cmake_minimum_required(VERSION 3.9)
project(07catch2)

set(CMAKE_CXX_STANDARD 11)

add_executable(07catch2
        build/test/.placeholder
        build/.placeholder
        include/db_interface.hpp
        include/db_memory.hpp
        include/person_dao.hpp
        include/person_entity.hpp
        src/db_memory.cpp
        src/person_dao.cpp
        src/person_entity.cpp
        test/person_dao_bdd.cpp
        test/person_dao_mock.cpp
        test/person_dao_unittest.cpp
        test/unit.cpp
        thirdparty/catch/catch.hpp
        thirdparty/fakeit/fakeit.hpp
        thirdparty/json/json.hpp
        bitbucket-pipelines.yml
        LICENSE
        Makefile)
