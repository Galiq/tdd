package pl.tau.restdemo.service;

// w oparciu o przyklad J Neumanna, przerobiony przez T Puzniakowskiego

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;

import pl.tau.restdemo.domain.Person;

public interface PersonManager {
	public Connection getConnection() throws SQLException;
	public void deletePerson(int id);
	public void clearPersons() throws SQLException;
	public int addPerson(Person person);
	public Person getPerson(int personId);
	public List<Person> getAllPersons();
}
