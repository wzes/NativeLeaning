#include "com_xuantang_nativelearning_JNIDemo.h"
#include <string>
#include <jni.h>
#include "NativeObj.cpp"

#define  LOG_TAG    "jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ENV_CLASSPATH "com/xuantang/nativelearning/Env"

using namespace std;

jclass jEnvClass;

jfieldID jEnvFieldId;

jmethodID jEnvConstructor;

jmethodID jEnvMethod;

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    LOGI("JNI_OnLoad called");
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGI("Failed to get the environment using GetEnv()");
        return -1;
    }
    jclass nativeJEnvClass = env->FindClass(ENV_CLASSPATH);
    jEnvClass = (jclass) env->NewGlobalRef(nativeJEnvClass);
    if (jEnvClass == NULL) {
        LOGI("Failed to find JEnvClass class");
    } else {
        jEnvFieldId = env->GetFieldID(jEnvClass, "ptr", "J");
        if (jEnvFieldId == NULL) {
            LOGI("Failed to get JEnv field");
        }
        jEnvConstructor = env->GetMethodID(jEnvClass, "<init>", "()V");
        jEnvMethod = env->GetMethodID(jEnvClass, "changeName", "(Ljava/lang/String;)V");
        if (jEnvMethod == NULL) {
            LOGI("Failed to get JEnv jEnvMethod");
        }
    }
    LOGI("JNI_OnLoad return");
    return JNI_VERSION_1_6;
}

JNIEXPORT jstring JNICALL Java_com_xuantang_nativelearning_JNIDemo_stringFromNative
        (JNIEnv *env, jobject, jstring param) {
    const char *str = env->GetStringUTFChars(param, 0);
    char c_str[100] = "I am from Native c.";
    strcat(c_str, str);
    env->ReleaseStringUTFChars(param, str);
    return env->NewStringUTF(c_str);
}

JNIEXPORT jobject JNICALL Java_com_xuantang_nativelearning_JNIDemo_create
        (JNIEnv *env, jclass type) {
    jobject jenv = env->NewObject(jEnvClass, jEnvConstructor);
    NativeObj *ptr = new NativeObj();
    env->SetLongField(jenv, jEnvFieldId, (jlong) ptr);
    return jenv;
}


JNIEXPORT jstring JNICALL Java_com_xuantang_nativelearning_JNIDemo_changeName
        (JNIEnv *env, jobject, jobject jenv, jstring name) {
    NativeObj *ptr = (NativeObj *) env->GetLongField(
            jenv,
            jEnvFieldId);
    if (ptr == NULL) {
        LOGI("It's destoryed");
        return env->NewStringUTF("It's destoryed");
    }
    std::string str = ptr->sayHello();
    env->CallVoidMethod(jenv, jEnvMethod, name);
    return env->NewStringUTF(str.c_str());
}