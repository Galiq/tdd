#ifndef __PERSON_ENTITY____
#define __PERSON_ENTITY____

#include "../thirdparty/json/json.hpp"

#include <string>
#include <ostream>

namespace crud {

/**
 * @brief Entity object
 ************/
 
struct Person {
	int id;
	std::string name;
	int yob;
};

bool operator==( const Person &p1, const Person &p2 );
std::ostream& operator << ( std::ostream& os, Person const& value );
void to_json( nlohmann::json& j, const Person& p );
void from_json( const nlohmann::json& j, Person& p );

}

#endif
