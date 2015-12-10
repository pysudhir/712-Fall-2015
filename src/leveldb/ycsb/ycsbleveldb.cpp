#include <iostream>
#include <jni.h>

#include "leveldb/db.h"

class DBOps {
	leveldb::DB *db;

	public:
	DBOps() {
		leveldb::Options options;
		options.create_if_missing = true;
		leveldb::Status status = leveldb::DB::Open(options, "/Users/pysudhir/ycsb/ycsb-0.1.4/sampledb/testdb", &db);
		if(false == status.ok()) {
			std::cerr << "Unable to open/create database" << std::endl;
			std::cerr << status.ToString() << std::endl;
			exit(-1);
		}
	}

	jint read(JNIEnv *env, jobject jobj, jstring table, jstring key, 
						jobject fields, jobject result) {
		return 0;
	}

	jint scan(JNIEnv *env, jobject jobj, jstring table, jstring key, 
						jint recordcount, jobject fields, jobject result) {
		return 0;
	}

	jint insert(JNIEnv *env, jobject jobj, jstring table, 
							jstring key, jobject insertvalues) {
		return 0;
	}

	jint dlt(JNIEnv *env, jobject jobj, jstring table, jstring key) {
		return 0;
	}

	jint update(JNIEnv *env, jobject jobj, jstring table, 
							jstring key, jobject updatevalues) {
		return 0;
	}
};


/*
 * Instantiate DBOps object that will be used in the
 * rest of the file
 */
DBOps *db = new DBOps();

/*
 * Class:     com_yahoo_ycsb_YcsbLevelDB
 * Method:    nativeInit
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_yahoo_ycsb_YcsbLevelDB_nativeInit
  (JNIEnv *env, jobject jobj) {
	return 0;
}

/*
 * Class:     com_yahoo_ycsb_YcsbLevelDB
 * Method:    nativeRead
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/util/Set;Ljava/util/HashMap;)I
 */
JNIEXPORT jint JNICALL Java_com_yahoo_ycsb_YcsbLevelDB_nativeRead
  (JNIEnv *env, jobject jobj, jstring table, jstring key, 
	 jobject fields, jobject result) {
		return db->read(env, jobj, table, key, fields, result);
}

/*
 * Class:     com_yahoo_ycsb_YcsbLevelDB
 * Method:    nativeScan
 * Signature: (Ljava/lang/String;Ljava/lang/String;ILjava/util/Set;Ljava/util/Vector;)I
 */
JNIEXPORT jint JNICALL Java_com_yahoo_ycsb_YcsbLevelDB_nativeScan
  (JNIEnv *env, jobject jobj, jstring table, jstring key, 
  jint recordcount, jobject fields, jobject result) {
		return db->scan(env, jobj, table, key, recordcount, fields, result);
}

/*
 * Class:     com_yahoo_ycsb_YcsbLevelDB
 * Method:    nativeInsert
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/util/HashMap;)I
 */
JNIEXPORT jint JNICALL Java_com_yahoo_ycsb_YcsbLevelDB_nativeInsert
  (JNIEnv *env, jobject jobj, jstring table, jstring key, jobject insertvalues) {
		return db->insert(env, jobj, table, key, insertvalues);
}

/*
 * Class:     com_yahoo_ycsb_YcsbLevelDB
 * Method:    nativeDelete
 * Signature: (Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_yahoo_ycsb_YcsbLevelDB_nativeDelete
  (JNIEnv *env, jobject jobj, jstring table, jstring key) {
		return db->dlt(env, jobj, table, key);
}

/*
 * Class:     com_yahoo_ycsb_YcsbLevelDB
 * Method:    nativeUpdate
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/util/HashMap;)I
 */
JNIEXPORT jint JNICALL Java_com_yahoo_ycsb_YcsbLevelDB_nativeUpdate
  (JNIEnv *env, jobject jobj, jstring table, jstring key, jobject updatevalues) {
		return db->update(env, jobj, table, key, updatevalues);
}
