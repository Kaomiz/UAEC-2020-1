import android.graphics.Bitmap;


public class Pixel {
Bitmap img;

    public Pixel(Bitmap img) {
        this.img = img;
    }
    public byte[] greyscale(){
        byte[] greyscale = new byte[img.getWidth()*img.getHeight()];
        for (int x = 0; x < img.getWidth(); x++) {
            for (int y = 0; y < img.getHeight(); y++) {
                int colour=img.getPixel(x,y);
                int A = (colour >> 24) & 0xff; // or color >>> 24
                int R = (colour >> 16) & 0xff;
                int G = (colour >>  8) & 0xff;
                int B = (colour      ) & 0xff;

                byte grey = (byte)((R+G+B)/3);
                greyscale[y*img.getWidth()+x]=grey;
            }
        }
        return greyscale;
    }
}
