package pl.tau.restdemo.web;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import pl.tau.restdemo.domain.Person;
import pl.tau.restdemo.service.PersonManager;

import java.sql.SQLException;
import java.util.List;

/**
 * Simple web api demo -- try implementning post method
 * <p>
 * Created by tp on 24.04.17.
 */
@RestController
public class PersonApi {

    @Autowired
    PersonManager personManager;

    @RequestMapping("/")
    public String index() {
        return "This is non rest, just checking if everything works.";
    }

    @RequestMapping(value = "/person/{id}",
            method = RequestMethod.GET,
            produces = MediaType.APPLICATION_JSON_VALUE)
    @ResponseBody
    public Person getPerson(@PathVariable("id") int id) {
        return personManager.getPerson(id);
    }

    @RequestMapping(
            value = "/person/{id}",
            method = RequestMethod.DELETE)
    @ResponseBody
    public void deletePerson(@PathVariable("id") int id) {
        personManager.deletePerson(id);
    }

    @RequestMapping(value = "/persons",
            method = RequestMethod.GET,
            produces = MediaType.APPLICATION_JSON_VALUE)
    @ResponseBody
    public List<Person> getPersons(@RequestParam(value = "filter", defaultValue = "") String filter) {
        return personManager.getAllPersons();
    }

    @RequestMapping(value = "/person",
            consumes = MediaType.APPLICATION_JSON_VALUE,
            method = RequestMethod.POST)
    @ResponseBody
    public void putPerson(@RequestBody Person person) {
        personManager.addPerson(person);
    }

}
