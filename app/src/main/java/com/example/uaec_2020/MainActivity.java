package com.example.uaec_2020;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.media.Image;
import android.os.Bundle;
import android.service.autofill.UserData;
import android.view.View;
import android.widget.ImageView;

import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {

	@Override
	protected void onCreate (Bundle savedInstanceState) {
		super.onCreate (savedInstanceState);
		setContentView (R.layout.activity_main);
	}

	public void testImage (View view) {
		/*Camera c = new Camera ();
		Bitmap image = c.GetImage ();
		ImageView imageView = new ImageView (null);
		imageView.setImageBitmap (image);*/
		UserShit user = new UserShit ();
		JSONObject person = new JSONObject ();
		try {
			person = user.createJSONObject ("Sam", "Tait", "Yeety", "Yoink","yikes","T6A3C9","78069696969","42069","Death");
		} catch (JSONException e) {
			e.printStackTrace ();
		}
		try {
			user.storeJSONObject (person);
		} catch (IOException e) {
			e.printStackTrace ();
		}
	}
}