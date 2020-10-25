public class RecognizeFace {
	static {
		System.loadLibrary("recognize_face.so");
	}
	private native long setup_env();

	private native int recognize_face(long int env, byte *img_data);

	
