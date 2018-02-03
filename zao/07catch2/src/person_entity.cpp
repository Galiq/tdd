#include "../include/person_entity.hpp"
#include "../thirdparty/json/json.hpp"

namespace crud {


bool operator==( const Person &p1, const Person &p2 ) {
	if ( p1.id != p2.id ) return false;
	if ( p1.name != p2.name ) return false;
	if ( p1.yob != p2.yob ) return false;
	return true;
}

std::ostream& operator << ( std::ostream& os, Person const& value ) {
	os << "{ " << value.id << ", " << value.name << ", " << value.yob << " }";
	return os;
}

void to_json( nlohmann::json& j, const Person& p ) {
	j = nlohmann::json{{"id", p.id}, {"name", p.name}, {"yob", p.yob}};
}

void from_json( const nlohmann::json& j, Person& p ) {
	p.id = j.at( "id" ).get<int>();
	p.name = j.at( "name" ).get<std::string>();
	p.yob = j.at( "yob" ).get<int>();
}

}

