LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := bubblecpp/main.cpp \
                   bubblecpp/AppDelegate.cpp \
                   bubblecpp/ShootBubbleSceneManager.cpp \
                   bubblecpp/StartLayer.cpp \
                   bubblecpp/HelpLayer.cpp \
                   bubblecpp/JFBLayer.cpp \
                   bubblecpp/ChooseGKLayer.cpp \
                   bubblecpp/AboutUsLayer.cpp \
                   bubblecpp/ShootBubbleLayer.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../jni

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,extensions)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
