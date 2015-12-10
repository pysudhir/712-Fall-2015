#include <stdlib.h>
#include <iostream>
#include <jni.h>
#include <sstream>

#include "leveldb/db.h"
#include "YcsbLevelDB.h"

class DBOps {
	leveldb::DB *db_;

	public:
	DBOps() {
		leveldb::Options options;
		options.create_if_missing = true;
		leveldb::Status status = leveldb::DB::Open(options, "/home/sudhirr/testdb", &db_);
		if(false == status.ok()) {
			std::cerr << "Unable to open/create database" << std::endl;
			std::cerr << status.ToString() << std::endl;
			exit(-1);
		}
	}

	/* Read */
	jint read(JNIEnv *env, jobject jobj, jstring table, 
						jstring key, jobject& value) {
		leveldb::ReadOptions readOptions;
		const char* keyNativeCharArray = env->GetStringUTFChars(key, 0);
		std::string keyNativeString = keyNativeCharArray;

		std::string v;
		leveldb::Status status = db_->Get(readOptions, keyNativeString, &v);
		if(!status.ok()) {
			return -2; // get failed
		}

		jstring javaValue = env->NewStringUTF(v.c_str());
		jclass sbclass = env->GetObjectClass(value);
		jmethodID append = env->GetMethodID(sbclass, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
		env->CallObjectMethod(value, append, javaValue);

		return 0;
	}

	/* Scan */
	jint scan(JNIEnv *env, jobject jobj, jstring table, 
						jstring startKey, jint recordCount, jobject& values) {
		leveldb::ReadOptions readOptions;
		leveldb::Iterator *itr = db_->NewIterator(readOptions);
		const char* keyNativeCharArray = env->GetStringUTFChars(startKey, 0);
		std::string keyNativeString = keyNativeCharArray;
		leveldb::Slice startKeySlice(keyNativeString);
		int i = 0;

		jclass vectorClass = env->GetObjectClass(values);
		jmethodID add = env->GetMethodID(vectorClass, "add", "(Ljava/lang/Object;)Z");
		if(add == NULL) {
			return -5;
		}

		for(itr->Seek(startKeySlice); itr->Valid(); itr->Next()) {
			if(i == (int)recordCount) {
				break;
			}

			jstring newStr = env->NewStringUTF(itr->value().ToString().c_str());
			jboolean ret = env->CallBooleanMethod(values, add, newStr);
			if((bool)ret == false) {
				return -3; // Vector<String>->put() failed
			}
			i++;
		}

		return 0;
	}

	/* Insert */
	jint insert(JNIEnv *env, jobject jobj, jstring table, 
							jstring key, jstring value) {
		leveldb::WriteOptions writeOptions;
		const char* keyNativeCharArray = env->GetStringUTFChars(key, 0);
		const char* valueNativeCharArray = env->GetStringUTFChars(value, 0);
		std::string keyNativeString = keyNativeCharArray;
		std::string valueNativeString = valueNativeCharArray;

		std::ostringstream keyStream;
		std::ostringstream valueStream;

		keyStream << keyNativeString;
		valueStream << valueNativeString;

		leveldb::Status status = db_->Put(writeOptions, keyStream.str(), valueStream.str());
		if(!status.ok()) {
			return -1; // put failed
		}
		return 0;
	}

	/* Delete */
	jint dlt(JNIEnv *env, jobject jobj, jstring table, jstring key) {
		leveldb::WriteOptions writeOptions;
		const char* keyNativeCharArray = env->GetStringUTFChars(key, 0);
		std::string keyNativeString = keyNativeCharArray;
		leveldb::Status status = db_->Delete(writeOptions, keyNativeString);
		if(!status.ok()) {
			return -4; // delete() failed
		}
		return 0;
	}
};


/*
 * Instantiate DBOps object that will be used in the
 * rest of the file
 */
DBOps *db = new DBOps();

/*
 * Class:     YcsbLevelDB
 * Method:    nativeInit
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_YcsbLevelDB_nativeInit(JNIEnv *env, jobject jobj)
{
	return 0;
}

/*
 * Class:     YcsbLevelDB
 * Method:    nativeRead
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/StringBuilder;)I
 */
JNIEXPORT jint JNICALL Java_YcsbLevelDB_nativeRead
  (JNIEnv *env, jobject jobj, jstring table, jstring key, jobject value)
{
	return db->read(env, jobj, table, key, value);
}

/*
 * Class:     YcsbLevelDB
 * Method:    nativeScan
 * Signature: (Ljava/lang/String;Ljava/lang/String;ILjava/util/Vector;)I
 */
JNIEXPORT jint JNICALL Java_YcsbLevelDB_nativeScan
  (JNIEnv *env, jobject jobj, jstring table, jstring startKey, 
	 jint recordCount, jobject values)
{
	return db->scan(env, jobj, table, startKey, recordCount, values);
}

/*
 * Class:     YcsbLevelDB
 * Method:    nativeInsert
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_YcsbLevelDB_nativeInsert
  (JNIEnv *env, jobject jobj, jstring table, jstring key, jstring value)
{
	return db->insert(env, jobj, table, key, value);
}

/*
 * Class:     YcsbLevelDB
 * Method:    nativeDelete
 * Signature: (Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_YcsbLevelDB_nativeDelete
  (JNIEnv *env, jobject jobj, jstring table, jstring key)
{
	return db->dlt(env, jobj, table, key);
}
