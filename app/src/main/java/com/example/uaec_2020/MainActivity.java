package com.example.uaec_2020;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.graphics.Bitmap;
import android.media.Image;
import android.os.Bundle;
import android.provider.MediaStore;
import android.service.autofill.UserData;
import android.view.View;
import android.widget.ImageView;

import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {

	static final int REQUEST_IMAGE_CAPTURE = 1;
	ImageView view1;
	@Override
	protected void onCreate (Bundle savedInstanceState) {
		super.onCreate (savedInstanceState);
		setContentView (R.layout.activity_main);
		view1 = findViewById (R.id.imageView);
	}

	public void testImage (View view) {
		dispatchTakePictureIntent ();
		//Camera c = new Camera ();
		//Bitmap image = c.GetImage ();
		//ImageView imageView = new ImageView (null);
		//imageView.setImageBitmap (image);
		/*UserShit user = new UserShit ();
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
		}*/
	}

	private void dispatchTakePictureIntent () {
		Intent takePictureIntent = new Intent (MediaStore.ACTION_IMAGE_CAPTURE);
		try {
			startActivityForResult (takePictureIntent, REQUEST_IMAGE_CAPTURE);
		} catch (ActivityNotFoundException e) {
			// display error state to the user
		}
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult (requestCode, resultCode, data);
		if (requestCode == REQUEST_IMAGE_CAPTURE && resultCode == RESULT_OK) {
			Bundle extras = data.getExtras ();
			Bitmap image = (Bitmap) extras.get ("data");
			view1.setImageBitmap (image);
		}
	}
}