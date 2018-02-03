package pl.tau.restdemo.domain;

public class Person {
	
	private int id;
	
	private String name;
	private int yob;
	
	public Person() {
	}

	public Person(String name, int yob) {
		super();
		this.name = name;
		this.yob = yob;
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getYob() {
		return yob;
	}
	public void setYob(int yob) {
		this.yob = yob;
	}
	
}
