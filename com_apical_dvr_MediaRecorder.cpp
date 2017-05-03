#define LOG_TAG "ffrecorder_jni"

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <android_runtime/AndroidRuntime.h>
#include <android_runtime/android_graphics_SurfaceTexture.h>
#include <android_runtime/android_view_Surface.h>
#include <utils/Log.h>
#include "com_apical_dvr_MediaRecorder.h"
#include "ffrecorder.h"
/* Header for class com_apical_dvr_MediaRecorder */

JavaVM* g_jvm = NULL;
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        ALOGE("ERROR: GetEnv failed\n");
        return -1;
    }
    assert(env != NULL);

    // for g_jvm
    g_jvm = vm;

    return JNI_VERSION_1_4;
}

JNIEXPORT JNIEnv* get_jni_env(void)
{
    JNIEnv *env;
    int status;
    if (NULL == g_jvm)
    {
        ALOGE("g_jvm == NULL !\n");
        return NULL;
    }
    status = g_jvm->GetEnv((void **)&env, JNI_VERSION_1_4);
    if (status < 0) {
//      ALOGD("failed to get JNI environment assuming native thread !\n");
        status = g_jvm->AttachCurrentThread(&env, NULL);
        if (status < 0) {
            ALOGE("failed to attach current thread !\n");
            return NULL;
        }
    }
    return env;
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeInitCallback
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeInitCallback
  (JNIEnv *env, jobject obj, jlong ctxt)
{
    ffrecorder_init_jni_callback((void*)ctxt, env, obj);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeInit
 * Signature: (IIII)J
 */
JNIEXPORT jlong JNICALL Java_com_apical_dvr_MediaRecorder_nativeInit
  (JNIEnv *env, jclass clazz, jint cam_main_w, jint cam_main_h, jint cam_usb_w, jint cam_usb_h)
{
    FFRECORDER_PARAMS params;
    memset(&params, 0, sizeof(params));
    params.cam_frame_width_0  = cam_main_w;
    params.cam_frame_height_0 = cam_main_h;
    params.cam_frame_width_1  = cam_usb_w;
    params.cam_frame_height_1 = cam_usb_h;
    return (jlong)ffrecorder_init(&params, env);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeFree
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeFree
  (JNIEnv *env, jclass clazz, jlong ctxt)
{
    ffrecorder_free((void*)ctxt);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeGetMicMute
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_com_apical_dvr_MediaRecorder_nativeGetMicMute
  (JNIEnv *env, jclass clazz, jlong ctxt, jint micidx)
{
    return ffrecorder_get_mic_mute((void*)ctxt, micidx);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeSetMicMute
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeSetMicMute
  (JNIEnv *env, jclass clazz, jlong ctxt, jint micidx, jint mute)
{
    ffrecorder_set_mic_mute((void*)ctxt, micidx, mute);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeResetCamera
 * Signature: (JIIII)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeResetCamera
  (JNIEnv *env, jclass clazz, jlong ctxt, jint camidx, jint w, jint h, jint frate)
{
    ffrecorder_reset_camdev((void*)ctxt, camidx, w, h, frate);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeSetPreviewWindow
 * Signature: (JILjava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeSetPreviewWindow
  (JNIEnv *env, jclass clazz, jlong ctxt, jint camidx, jobject jsurface)
{
    sp<IGraphicBufferProducer> gbp;
    sp<Surface> surface;
    if (jsurface) {
        surface = android_view_Surface_getSurface(env, jsurface);
        if (surface != NULL) {
            gbp = surface->getIGraphicBufferProducer();
        }
    }
    ffrecorder_preview_target((void*)ctxt, camidx, gbp);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeSetPreviewTarget
 * Signature: (JILjava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeSetPreviewTarget
  (JNIEnv *env, jclass clazz, jlong ctxt, jint camidx, jobject jtexture)
{
    sp<IGraphicBufferProducer> gbp = NULL;
    if (jtexture != NULL) {
        gbp = SurfaceTexture_getProducer(env, jtexture);
        if (gbp == NULL) {
            ALOGW("SurfaceTexture already released in setPreviewTexture !");
            return;
        }
    }
    ffrecorder_preview_target((void*)ctxt, camidx, gbp);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeStartPreview
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeStartPreview
  (JNIEnv *env, jclass clazz, jlong ctxt, jint camidx)
{
    ffrecorder_preview_start((void*)ctxt, camidx);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeStopPreview
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeStopPreview
  (JNIEnv *env, jclass clazz, jlong ctxt, jint camidx)
{
    ffrecorder_preview_stop((void*)ctxt, camidx);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeStartRecording
 * Signature: (JILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeStartRecording
  (JNIEnv *env, jclass clazz, jlong ctxt, jint encidx, jstring filename)
{
    const char *str = env->GetStringUTFChars(filename, NULL);
    ffrecorder_record_start((void*)ctxt, encidx, (char*)str);
    env->ReleaseStringUTFChars(filename, str);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeStopRecording
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeStopRecording
  (JNIEnv *env, jclass clazz, jlong ctxt, jint encidx)
{
    ffrecorder_record_stop((void*)ctxt, encidx);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeSetAudioSource
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeSetAudioSource
  (JNIEnv *env, jclass clazz, jlong ctxt, jint encidx, jint source)
{
    ffrecorder_record_audio_source((void*)ctxt, encidx, source);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeSetVideoSource
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeSetVideoSource
  (JNIEnv *env, jclass clazz, jlong ctxt, jint encidx, jint source)
{
    ffrecorder_record_video_source((void*)ctxt, encidx, source);
}

/*
 * Class:     com_apical_dvr_MediaRecorder
 * Method:    nativeTakePhoto
 * Signature: (JILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_apical_dvr_MediaRecorder_nativeTakePhoto
  (JNIEnv *env, jclass clazz, jlong ctxt, jint camidx, jstring filename)
{
    const char *str = env->GetStringUTFChars(filename, NULL);
    ffrecorder_take_photo((void*)ctxt, camidx, (char*)str);
    env->ReleaseStringUTFChars(filename, str);
}
