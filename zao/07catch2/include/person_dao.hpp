#ifndef __PERSON_DAO_INTERFACE___
#define  __PERSON_DAO_INTERFACE___

#include <list>
#include "db_interface.hpp"
#include "person_entity.hpp"

namespace crud {

/**
 * @brief Simple CRUD for person
 ************/

class Person_dao {
private:
	db::Database_i *_data_source;
   	std::string _index_prefix;

public:
	std::list<Person> get();
	Person get( int key );
	void put( Person &p );
	void del( Person &p );
	Person_dao( db::Database_i *data_source, const std::string &index_prefix );
};


}
#endif
