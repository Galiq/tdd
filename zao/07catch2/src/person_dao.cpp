#include "../include/person_dao.hpp"
#include "../thirdparty/json/json.hpp"
#include "../include/person_entity.hpp"
#include "../include/db_interface.hpp"

#include <iostream>

// for convenience
using json = nlohmann::json;

namespace crud {

std::list<Person> Person_dao::get() {
	std::list<Person> ret;
    auto keys = _data_source->get_keys(std::regex(_index_prefix + ".*"));
    for (const auto &k:keys) {
        json j = json::parse( _data_source->get( k ) );
	    Person r = j;
        ret.push_back(r);
    }
	return ret;
}

Person Person_dao::get( int key ) {
    std::string k = _index_prefix + std::to_string( key );
    std::string jstring = _data_source->get( k );
	json j = json::parse( jstring );
	Person ret = j;
	return ret;
}

void Person_dao::put( Person &p ) {
    std::string k = _index_prefix + std::to_string( p.id );
	json j = p;
	_data_source->put( k, j.dump() );
}

void Person_dao::del( Person &p ) {
	_data_source->del( _index_prefix + std::to_string( p.id ) );
}

Person_dao::Person_dao( db::Database_i *data_source, const std::string &index_prefix ) {
	_data_source = data_source;
    _index_prefix = index_prefix;
}

}
