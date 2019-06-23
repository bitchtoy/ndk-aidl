#include <jni.h>
#include <string>
#include <android/log.h>
#include <pthread.h>
#include <random>

#define TAG "SystemJni-C++->"
#define LogD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
typedef struct ticker{
    JavaVM *vm;
    jclass helpClz;
    jobject helpObj;
    jclass _clz;
    jobject _obj;
    pthread_mutex_t lock;
    int done;
}TickerContext;
TickerContext pcxt;
void queryRuntimeSize(JNIEnv *env,jobject instance){
    jmethodID _bmd = env->GetStaticMethodID(pcxt.helpClz,"getBuildVersion","()Ljava/lang/String;");
    if (!_bmd){
        return;
    }
    jstring version = (jstring)env->CallStaticObjectMethod(pcxt.helpClz,_bmd);
    const char *_v = env->GetStringUTFChars(version,NULL);
    env->ReleaseStringUTFChars(version,_v);
    env->DeleteLocalRef(version);
    jmethodID _runtimeSize = env->GetMethodID(pcxt.helpClz,"getRuntimeSize","()J");
    if (!_runtimeSize){
        return;
    }
    jlong result = env->CallLongMethod(instance,_runtimeSize);
    (void)result;
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_gg_test_Jni_stringFromJNI(
        JNIEnv *env,
        jclass /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* javaVM,void* reserved){
    JNIEnv *env;
    memset(&pcxt,0, sizeof(pcxt));
    pcxt.vm = javaVM;
    if (javaVM->GetEnv((void**)&env,JNI_VERSION_1_6) != JNI_OK){
        return JNI_ERR;
    }
    jclass clz = env->FindClass("com/gg/test/JniHelp");
    pcxt.helpClz = (jclass)env->NewGlobalRef(clz);
    jmethodID construct = env->GetMethodID(pcxt.helpClz,"<init>","()V");
    jobject hand = env->NewObject(pcxt.helpClz,construct);
    pcxt.helpObj = env->NewGlobalRef(hand);
    queryRuntimeSize(env,pcxt.helpObj);
    pcxt.done = 0;
    pcxt._clz = NULL;
    return JNI_VERSION_1_6;
}
void sentJniMsg(JNIEnv *env,jobject obj,jmethodID func, const char *msg){
      jstring js = env->NewStringUTF(msg);
      env->CallVoidMethod(obj,func,js);
      env->DeleteLocalRef(js);
}
void* UpdateTicker(void* context){
    TickerContext *ctx =(TickerContext*) context;
    JavaVM *vm  = ctx->vm;
    JNIEnv *env;
    int res = vm->GetEnv((void**)&env,JNI_VERSION_1_6);
    if (res != JNI_OK){
        res = vm->AttachCurrentThread(&env,NULL);
        if (res != JNI_OK){
            return NULL;
        }
    }
    jmethodID sm = env->GetMethodID(ctx->helpClz,"upDataStatus","(Ljava/lang/String;)V");

    sentJniMsg(env,ctx->helpObj,sm,"Ticker Theard init.....");
    jmethodID tm = env->GetMethodID(ctx->_clz,"time","()V");
    struct timeval beginTime,curTime,useTime,leftTime;
    const struct timeval kOneSecond{
            (__kernel_time_t)1,
            (__kernel_suseconds_t)0
    };
    sentJniMsg(env,ctx->helpObj,sm,"Ticker Thread start.....");
    while (1){
        gettimeofday(&beginTime,NULL);
        pthread_mutex_lock(&ctx->lock);
        int done = ctx->done;
        if (ctx->done){
            ctx->done = 0;
        }
        pthread_mutex_unlock(&ctx->lock);
        if (done){
            break;
        }
        env->CallVoidMethod(ctx->_obj,tm);
        gettimeofday(&curTime,NULL);
        timersub(&beginTime,&curTime,&useTime);
        timersub(&kOneSecond,&useTime,&leftTime);
        struct timespec sleepTime;
        sleepTime.tv_sec = leftTime.tv_sec;
        sleepTime.tv_nsec = leftTime.tv_usec * 1000;
        if (sleepTime.tv_sec <= 1){
           nanosleep(&sleepTime,NULL);
        } else{
            sentJniMsg(env,ctx->helpObj,sm,"Ticker Thread procession too long");
        }
    }
    sentJniMsg(env,ctx->helpObj,sm,"Ticker Thread stop");
    vm->DetachCurrentThread();
    return context;
}
extern "C" JNIEXPORT void JNICALL
Java_com_gg_test_Jni_startTicker(JNIEnv *env, jclass instance){
    pthread_t _threadInfo;
    pthread_attr_t _threadAttr;
    pthread_attr_init(&_threadAttr);
    pthread_attr_setdetachstate(&_threadAttr,PTHREAD_CREATE_DETACHED);
    pthread_mutex_init(&pcxt.lock,NULL);
    jclass clz = env->FindClass("com/gg/test/MainActivity");
    pcxt._clz = (jclass) env->NewGlobalRef(clz);
    jmethodID mainConstruct = env->GetMethodID(pcxt._clz,"<init>","()V");
    jobject _a = env->NewObject(pcxt._clz,mainConstruct);
    pcxt._obj = env->NewGlobalRef(_a);
    int result = pthread_create(&_threadInfo,&_threadAttr,UpdateTicker,&pcxt);
    assert(result == JNI_OK);
    pthread_attr_destroy(&_threadAttr);
    (void)result;
}
extern "C" JNIEXPORT void JNICALL
Java_com_gg_test_Jni_stopTicker(JNIEnv *env,jclass instance){
     pthread_mutex_lock(&pcxt.lock);
     pcxt.done = 1;
     pthread_mutex_unlock(&pcxt.lock);
     struct timespec sleepTime;
     memset(&sleepTime,0, sizeof(sleepTime));
     sleepTime.tv_nsec = 100000000;
     while (pcxt.done){
         nanosleep(&sleepTime,NULL);
     }
     env->DeleteGlobalRef(pcxt._clz);
     env->DeleteGlobalRef(pcxt._obj);
     pcxt._obj = NULL;
     pcxt._clz = NULL;

     pthread_mutex_destroy(&pcxt.lock);

}
