package com.example.uaec_2020;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.media.Image;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.service.autofill.UserData;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.google.android.material.snackbar.Snackbar;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

import pub.devrel.easypermissions.AfterPermissionGranted;
import pub.devrel.easypermissions.EasyPermissions;

public class MainActivity extends AppCompatActivity {

	static final int REQUEST_IMAGE_CAPTURE = 1;
	ImageView view1;
	Button create;
	Bitmap image;
	recognize_face face;
	long alloc;
	byte pixel_data[];
	@Override
	protected void onCreate (Bundle savedInstanceState) {
		super.onCreate (savedInstanceState);
		setContentView (R.layout.activity_main);
		RequestPerms ();
		face = new recognize_face();
		alloc = face.alloc_nn();
		view1 = findViewById (R.id.imageView);
		create = findViewById (R.id.button2);
		create.setOnClickListener (new View.OnClickListener () {
			@Override
			public void onClick (View v) {
				Intent intent = new Intent (getApplicationContext (), CreateProfile.class);
				startActivity (intent);
				finish();
			}
		});
	}

	//Take the emergency picture
	public void testImage (View view) {
		dispatchTakePictureIntent ();
		//email ();
	}

	private void call () {
		Intent callIntent = new Intent (Intent.ACTION_CALL);
		callIntent.setData (Uri.parse("tel:7806048907"));
		if (ActivityCompat.checkSelfPermission(MainActivity.this, Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
			return;
		}
		startActivity(callIntent);
	}

	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults){
		super.onRequestPermissionsResult(requestCode, permissions, grantResults);

		//Forward results to EasyPermissions
		EasyPermissions.onRequestPermissionsResult(requestCode, permissions, grantResults, this);
	}
	@AfterPermissionGranted (2)
	public void RequestPerms () {
		String[] perms = {Manifest.permission.CALL_PHONE};
		if (EasyPermissions.hasPermissions(this, perms)) {
		}
		else {
			EasyPermissions.requestPermissions(this, "Please grant the phone permission", 2, perms);
		}
	}

	//Run the intent for picture
	private void dispatchTakePictureIntent () {
		Intent takePictureIntent = new Intent (MediaStore.ACTION_IMAGE_CAPTURE);
		try {
			startActivityForResult (takePictureIntent, REQUEST_IMAGE_CAPTURE);
		} catch (ActivityNotFoundException e) {
			// display error state to the user
		}
	}

	//Get the view picture up
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult (requestCode, resultCode, data);
		if (requestCode == REQUEST_IMAGE_CAPTURE && resultCode == RESULT_OK) {
			Bundle extras = data.getExtras ();
			image = (Bitmap) extras.get ("data");
			view1.setImageBitmap (image);
			Pixel p = new Pixel ();
			pixel_data = p.greyscale (image);
			System.out.println(face.run_data(alloc, pixel_data));
			call ();
		}
	}
}