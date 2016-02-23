/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class JNISample */

#ifndef _Included_JNISample
#define _Included_JNISample
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     JNISample
 * Method:    displayHelloWorld
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JNISample_displayHelloWorld
  (JNIEnv *, jobject);

/*
 * Class:     JNISample
 * Method:    searchFileSystem
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JNISample_searchFileSystem
  (JNIEnv *, jobject);

/*
 * Class:     JNISample
 * Method:    findFileSystemType
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JNISample_findFileSystemType
  (JNIEnv *, jobject);

/*
 * Class:     JNISample
 * Method:    stringManipulation
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_JNISample_stringManipulation
  (JNIEnv *, jobject, jstring);

/*
 * Class:     JNISample
 * Method:    characterManipulation
 * Signature: ([C)V
 */
JNIEXPORT void JNICALL Java_JNISample_characterManipulation
  (JNIEnv *, jobject, jcharArray);

/*
 * Class:     JNISample
 * Method:    objectManipulation
 * Signature: (Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_JNISample_objectManipulation
  (JNIEnv *, jobject, jobject);

/*
 * Class:     JNISample
 * Method:    integerManipulation
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_JNISample_integerManipulation
  (JNIEnv *, jobject, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
