# ndk-aidl
## demo描述：
### 1.使用ndk 和 aidl跨进程通讯技术的一个学习示例
## 概要：
### 1. JavaVm 和 JNIEvn简述
### 2.FindClass、NewGlobalRef、GetMethodID、NewObject、NewGlobalRef、GetStaticMethodID...等等方法的介绍
### 3.总结
### 描述：
## 1.JavaVm 和 JNIEvn简述
### 1.1 JavaVm
#### JavaVM 是虚拟机在 JNI 层的代表，一个进程只有一个 JavaVM，所有的线程共用一个 JavaVM。
### 1.2 JNIEnv
#### JNIEnv 表示 Java 调用 native 语言的环境，是一个封装了几乎全部 JNI 方法的指针。
#### JNIEnv 只在创建它的线程生效，不能跨线程传递，不同线程的 JNIEnv 彼此独立。
#### native 环境中创建的线程，如果需要访问 JNI，必须要调用 AttachCurrentThread 关联，并使用 DetachCurrentThread 解除链接。
## 2.FindClass、NewGlobalRef、GetMethodID...等等方法的介绍
### 2.1 FindClass
#### jni通过FindClass方法找到java中类，并进行对该类进行操作。
#### FindClass（const char* name）方法,举例 const char* name = "com/gg/test/类名"
### 2.2 NewGlobalRef
#### 创建一个全局引用
### 2.3 GetMethodID
#### jmethodID GetMethodID(jclass clazz, const char* name, const char* sig) 
#### clazz 是通过FindClass找到java中类，name是方法名，比如构造方法“init”,
#### sig方法的定义：
#### 例子：
#### java构造方法：evn->GetMethodID(clz,"init","()V");
#### Java类型
#### 符号
#### Boolean  ->  Z
#### Byte     ->  B
#### Char     ->  C
#### Short    ->  S
#### Integer  ->  I
#### Long     -> L
#### Float    ->  F
#### Double   ->  D
#### Void     ->  V
#### Object对象 ->  L开头，包名/类名，”;”结尾,$标识嵌套类
#### String     ->  Ljava/lang/String;
#### public void upDataStatus(String var0) -> sig (Ljava/lang/String;)V
#### public static String getBuildVersion() -> sig ()Ljava/lang/String;
#### ......
## 3.总结
#### 具体介绍查看官方教程，

