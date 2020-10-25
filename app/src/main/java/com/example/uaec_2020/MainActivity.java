package com.example.uaec_2020;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.media.Image;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import com.google.android.material.snackbar.Snackbar;

public class MainActivity extends AppCompatActivity {

	@Override
	protected void onCreate (Bundle savedInstanceState) {
		super.onCreate (savedInstanceState);
		setContentView (R.layout.activity_main);
	}

	public void testImage (View view) {
		Camera c = new Camera ();
		Bitmap image = c.GetImage ();
		ImageView imageView = new ImageView (null);
		imageView.setImageBitmap (image);
	}
}