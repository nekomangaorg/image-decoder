//
// Created by len on 23/12/20.
//

#include "java_objects.h"

static jclass imageDecoderCls;
static jmethodID imageDecoderCtor;
static jclass imageTypeCls;
static jmethodID imageTypeCtor;
static jmethodID createBitmapMethod;
static jmethodID bitmapRecycleMethod;

void init_java_objects(JNIEnv* env) {
  jclass tmpCls;

  tmpCls = env->FindClass("tachiyomi/decoder/ImageDecoder");
  imageDecoderCls = (jclass)env->NewGlobalRef(tmpCls);
  imageDecoderCtor = env->GetMethodID(imageDecoderCls, "<init>", "(JII)V");

  tmpCls = env->FindClass("tachiyomi/decoder/ImageType");
  imageTypeCls = (jclass)env->NewGlobalRef(tmpCls);
  imageTypeCtor = env->GetMethodID(imageTypeCls, "<init>", "(IZ)V");

  createBitmapMethod = env->GetStaticMethodID(imageDecoderCls, "createBitmap",
                                              "(II)Landroid/graphics/Bitmap;");

  env->DeleteLocalRef(tmpCls);

  tmpCls = env->FindClass("android/graphics/Bitmap");
  bitmapRecycleMethod = env->GetMethodID(tmpCls, "recycle", "()V");
  env->DeleteLocalRef(tmpCls);
}

jobject create_image_decoder(JNIEnv* env, jlong decoderPtr, jint width,
                             jint height) {
  return env->NewObject(imageDecoderCls, imageDecoderCtor, decoderPtr, width,
                        height);
}

jobject create_bitmap(JNIEnv* env, jint width, jint height) {
  return env->CallStaticObjectMethod(imageDecoderCls, createBitmapMethod, width,
                                     height);
}

void recycle_bitmap(JNIEnv* env, jobject bitmap) {
  env->CallVoidMethod(bitmap, bitmapRecycleMethod);
}

jobject create_image_type(JNIEnv* env, jint format, jboolean isAnimated) {
  return env->NewObject(imageTypeCls, imageTypeCtor, format, isAnimated);
}
