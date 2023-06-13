import java.util.ArrayList;
import java.util.List;

public class User {
    private String user_id;
    private String name;
    private List<String> friends;

    // Constructors

    public User(){
        this.user_id = "";
        this.name = "";
        this.friends = new ArrayList<>();
    }

    public User(String user_id, String name, ArrayList<String> friends){
        this.user_id = user_id;
        this.name = name;
        this.friends = friends;
    }

    public User(User u){
        this.user_id = u.getUser_ID();
        this.name = u.getName();
        this.friends = u.getFriends();
    }

    // Gets e Sets

    public String getUser_ID() { return this.user_id; }
    public String getName() { return this.name; }
    public List<String> getFriends() { return friends; }

    public void setUser_id(String user_id) { this.user_id = user_id; }
    public void setName(String name) { this.name = name; }
    public void setFriends(List<String> friends) { this.friends = friends; }

    public User clone(){ return new User(this);}

}
