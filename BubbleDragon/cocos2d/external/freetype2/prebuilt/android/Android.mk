LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_freetype2_static
LOCAL_MODULE_FILENAME := freetype2
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_freetype2_static
$(call import-module,external/freetype2/prebuilt/android)
$(call import-add-path, $(LOCAL_PATH)/../../cocos2d/external)
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libfreetype.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/android $(LOCAL_PATH)/../../include/android/freetype2
include $(PREBUILT_STATIC_LIBRARY)
