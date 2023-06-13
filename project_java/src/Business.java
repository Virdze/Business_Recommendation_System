import java.util.Comparator;
import java.util.Set;
import java.util.TreeSet;

public class Business {
    private String business_id;
    private String name;
    private String city;
    private String state;
    private Set<String> categories;

    public Business(){
        this.business_id = "";
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = new TreeSet<>();
    }

    public Business(String business_id, String name, String city, String state, Set<String> categories){
        this.business_id = business_id;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = new TreeSet<>(categories);
    }

    public Business(Business b){
        this.business_id = b.getBusiness_ID();
        this.name = b.getName();
        this.city = b.getCity();
        this.state = b.getState();
        this.categories = b.getCategories();
    }

    public String getBusiness_ID() { return this.business_id; }
    public String getName() { return this.name; }
    public String getCity() { return this.city; }
    public String getState() { return this.state; }
    public Set<String> getCategories() { return categories; }

    public void setBusiness_ID(String business_id) { this.business_id = business_id; }
    public void setName(String name) { this.name = name; }
    public void setCity(String city) { this.city = city; }
    public void setState(String state) { this.state = state; }
    public void setCategories(Set<String> categories) { this.categories = new TreeSet<>(categories); }

    public Business clone() { return new Business(this); }


}
