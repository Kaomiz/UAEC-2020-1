package com.example.uaec_2020;
import android.graphics.Bitmap;


public class Pixel {
    //converts raw bitmaps from the camera into greyscale byte arrays to be used by facial recognition
    public byte[] greyscale(Bitmap in){
        //scales picture to the size use by image recognition algorithm
        Bitmap img = Bitmap.createScaledBitmap(in,256,256,true);
        byte[] greyscale = new byte[img.getWidth()*img.getHeight()];
        //looping through all pixels
        for (int x = 0; x < img.getWidth(); x++) {
            for (int y = 0; y < img.getHeight(); y++) {
                //retrieving colour data from pixels
                int colour=img.getPixel(x,y);
                int A = (colour >> 24) & 0xff; // or color >>> 24
                int R = (colour >> 16) & 0xff;
                int G = (colour >>  8) & 0xff;
                int B = (colour      ) & 0xff;

                //converting colour data to greyscale byte array
                byte grey = (byte)((R+G+B)/3);
                greyscale[y*img.getWidth()+x]=grey;
            }
        }
        return greyscale;
    }
}
