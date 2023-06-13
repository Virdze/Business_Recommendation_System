import java.time.LocalDateTime;

public class Review {
    private String review_id;
    private String user_id;
    private String business_id;
    private float stars;
    private int useful;
    private int funny;
    private int cool;
    private LocalDateTime date;
    private String text;

    public Review(){
        this.review_id = "";
        this.user_id = "";
        this.business_id = "";
        this.stars = 0;
        this.useful = 0;
        this.funny = 0;
        this.cool = 0;
        this.text = "";
    }

    public Review(String review_id, String user_id, String business_id, float stars, int useful,
                int funny, int cool, LocalDateTime date, String text){
        this.review_id = review_id;
        this.user_id = user_id;
        this.business_id = business_id;
        this.stars = stars;
        this.useful = useful;
        this.funny = funny;
        this.cool = cool;
        this.date = date;
        this.text = text;
    }

    public Review(Review r){
        this.review_id = r.getReview_ID();
        this.user_id = r.getUser_ID();
        this.business_id = r.getBusiness_ID();
        this.stars = r.getStars();
        this.useful = r.getUseful();
        this.funny = r.getFunny();
        this.cool = r.getCool();
        this.date = r.getDate();
        this.text = r.getText();
    }

    public String getReview_ID() { return this.review_id; }
    public String getUser_ID() { return this.user_id; }
    public String getBusiness_ID() { return this.business_id; }
    public float getStars() { return this.stars; }
    public int getUseful() { return this.useful; }
    public int getFunny() { return this.funny; }
    public int getCool() { return this.cool; }
    public LocalDateTime getDate() { return this.date; }
    public String getText() { return text; }

    public Review clone(){ return new Review(this); }
    
}
