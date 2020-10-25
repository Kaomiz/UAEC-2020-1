package com.example.uaec_2020;

import org.json.*;
import android.content.*;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;


public class UserShit {

        //define a new user, set the values of arguments provided by the filled form, return as
        //a JSON object
        public JSONObject createJSONObject(String first, String Last, String street, String city,
                                           String province, String pc, String phn, String hin,
                                           String healthConditions) throws JSONException{
                //make new json object and set values
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
        public void storeJSONObject(JSONObject user1) throws IOException, JSONException {

                //make new writer and write to json
                FileWriter writer = new FileWriter("filename.json");
                writer.write(user1.toString());
                writer.close();
        }

        //read the json from file and make it into a new JSON object
        public JSONObject readFromFile(File user) throws FileNotFoundException {

                //set up a new reader and parse the JSON file to create a new JSON object
                JsonParser parser = new JsonParser();
                JsonObject user1 = parser.parse(new FileReader("filename.json"));
        }

}
