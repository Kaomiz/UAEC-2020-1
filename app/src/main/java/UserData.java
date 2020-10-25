import org.json.*;

public class UserData {
    public static void main (String[] args) throws JSONException {

            JSONObject user1 = new JSONObject();
            user1.put("first name", "user");
            user1.put("last name", "last");
            user1.put("street address", "yeet street");
            user1.put("city","yaw");
            user1.put("province","rednecksville:");
            user1.put("postal code","1337");
            user1.put("personal health number","69420");
            user1.put("Health insurance number","42069");
            user1.put("current and previous health condiditons","large pee pee syndrome");


            System.out.println(user1);
        }
}
