package com.example.uaec_2020;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.provider.MediaStore;
import android.widget.ImageView;

import static android.app.Activity.RESULT_OK;


public class Camera extends Activity {
	static final int REQUEST_IMAGE_CAPTURE = 1;
	private Bitmap image;

	private void dispatchTakePictureIntent () {
		Intent takePictureIntent = new Intent (MediaStore.ACTION_IMAGE_CAPTURE);
		try {
			onActivityResult (REQUEST_IMAGE_CAPTURE, RESULT_OK, takePictureIntent);
		} catch (ActivityNotFoundException e) {
			// display error state to the user
		}
	}
	
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == REQUEST_IMAGE_CAPTURE && resultCode == RESULT_OK) {
			Bundle extras = data.getExtras();
			image = (Bitmap) extras.get("data");
			ImageView imageView = new ImageView (null);
			imageView.setImageBitmap(image);
		}
	}

	public Bitmap GetImage () {
		dispatchTakePictureIntent ();
		return (image);
	}
}
