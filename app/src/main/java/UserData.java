import org.json.*;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;


public class UserData {

        //define a new user, set the values of arguments provided by the filled form, return as
        //a JSON object
        public JSONObject createJSONObject(String first, String Last, String street, String city,
                                           String province, String pc, String phn, String hin,
                                           String healthConditions) throws JSONException{

                JSONObject user1 =  new JSONObject();
                user1.put("first name", first);
                user1.put("last name", Last);
                user1.put("street address", street);
                user1.put("city",city);
                user1.put("province",province);
                user1.put("postal code",pc);
                user1.put("personal health number",phn);
                user1.put("Health insurance number",hin);
                user1.put("current and previous health conditions",healthConditions);

                return user1;
        }

        //stores the JSONObject in a text file
        public void storeJSONObject(JSONObject user1) throws IOException {
                FileWriter writer = new FileWriter("user1.json");
                writer.write(user1.toString());
                writer.close();
        }
}
