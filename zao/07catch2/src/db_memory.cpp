
#include "../include/db_memory.hpp"
#include "../include/db_interface.hpp"


namespace db {


std::string Database_in_memory::get( const std::string &key ) const {
	// does the element exists in a map?
	if ( _data.count( key ) ) {
		// return the element
		return _data.at( key );
	} else {
		// element not found
		throw std::domain_error ( key + " not found." );
	}
}

std::list<std::string> Database_in_memory::get_keys( const std::regex &matching ) const {
	std::list<std::string> keys;
	for ( const auto &kv : _data ) {
		// check if current key matches regex
		if ( std::regex_match( kv.first, matching ) ) {
			// push found key to list
			keys.push_back( kv.first );
		}
	}
	return keys;
}

int Database_in_memory::put( const std::string &key, const std::string &value ) {
	// add element to map
	_data[key] = value;
}

int Database_in_memory::del( const std::string &key ) {
	// remove element from map
	_data.erase( key );
}


}
