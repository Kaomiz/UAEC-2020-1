public class recognize_face
{
    static {
        System.loadLibrary("recognize_face.so");
    }
    public native long alloc_nn();
    public native long run_data(long nn_ptr, byte data[]);
}
