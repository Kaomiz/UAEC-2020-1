LOCAL_PATH := $(call my-dir)
# APP_CFLAGS += -fopenmp
APP_PLATFORM := android-21
APP_ABI	:= arm64-v8a

include $(CLEAR_VARS)
LOCAL_MODULE	:= fann
LOCAL_SRC_FILES	:= fann_src/fann.c fann_src/fann_error.c fann_src/fann_train.c \
	fann_src/fann_cascade.c fann_src/fann_train_data.c fann_src/fann_io.c
LOCAL_EXPORT_C_INCLUDES := fann_src/include/
# LOCAL_SHARED_LIBRARIES	:= fann_error parallel_fann
include $(BUILD_SHARED_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_MODULE	:= floatfann
#LOCAL_CFLAGS += -fopenmp
#LOCAL_LDFLAGS += -fopenmp
#LOCAL_SRC_FILES	:= fann_src/floatfann.c
#LOCAL_SHARED_LIBRARIES := fann
#LOCAL_EXPORT_C_INCLUDES := fann_src/include/
#include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := nn_shizzle
LOCAL_SRC_FILES := recognize_face.c
LOCAL_SHARED_LIBRARIES := fann
include $(BUILD_SHARED_LIBRARY)
