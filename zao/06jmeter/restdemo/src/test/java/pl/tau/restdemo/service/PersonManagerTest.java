package pl.tau.restdemo.service;
// przyklad na podstawie przykladow J. Neumanna
import static org.junit.Assert.*;

import java.sql.SQLException;
import java.util.List;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import pl.tau.restdemo.domain.Person;

public class PersonManagerTest {

	PersonManager personManager = new PersonManagerImpl();
	
	private final static String NAME_1 = "Janek";
	private final static int YOB_1 = 1939;

	public PersonManagerTest() throws SQLException {
	}

	@After
    public void cleanup() throws SQLException {
	    personManager.getConnection().close();
//        personManager.clearPersons();
    }

	@Test
	public void checkConnection() throws SQLException {
	    assertNotNull(personManager.getConnection());
	    personManager.getConnection().close();
	}

	@Test
	public void checkAdding() throws SQLException{
		Person person = new Person();
		person.setName(NAME_1);
		person.setYob(YOB_1);
		
//		personManager.clearPersons();
		assertEquals(1,personManager.addPerson(person));
		
		List<Person> persons = personManager.getAllPersons();
		Person personRetrieved = persons.get(0);
		
		assertEquals(NAME_1, personRetrieved.getName());
		assertEquals(YOB_1, personRetrieved.getYob());
	}

    @Test
	public void checkAddingMultipleData() throws SQLException {
		personManager.clearPersons();
		assertEquals(1,personManager.addPerson(new Person("Damian", 1992)));
		assertEquals(1,personManager.addPerson(new Person("Michal", 1991)));
		assertEquals(1,personManager.addPerson(new Person("Pawel", 1994)));
		assertEquals(1,personManager.addPerson(new Person("Marcin", 1988)));
		assertEquals(1,personManager.addPerson(new Person("Mateusz", 1993)));
		assertEquals(1,personManager.addPerson(new Person("Mariusz", 1986)));
		List<Person> persons = personManager.getAllPersons();
		assertEquals(6, persons.size());
		personManager.getConnection().close();
	}

}
