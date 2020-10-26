package com.example.uaec_2020;

import static java.lang.System.loadLibrary;

public class recognize_face
{
    static {
        loadLibrary("recognize_face.so");
    }
    public native long alloc_nn();
    public native long run_data(long nn_ptr, byte data[]);
}
