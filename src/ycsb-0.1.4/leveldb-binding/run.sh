#!/bin/bash
#
#
# This script is used for ease of execution of ycsb extension
# to support leveldb.
#
# Requirements:
# 1. Build native code (c++) - Makefile
# 2. Copy dynamic library (libycsbleveldb.so) to leveldb directory
# 3. LD_LIBRARY_PATH has to be set to leveldb path
# 4. Set DB path
# 5. Run load phase of requested workload
# 6. Run the workload
#
# Workload argument could be one of the directories in ../workloads directory

if [ $# -ne 1 ]
then
	echo "USAGE: $0 <workload>"
	exit -2
fi

`make clean`
`make`
if [ $? -ne 0 ] 
then
	echo "Make failure"
	exit -1
fi

leveldb_path=`readlink -f ../../leveldb`
`ls $leveldb_path > /dev/null`
if [ $? -ne 0 ]
then
	echo "ERROR: Invalid path to leveldb"
	exit -3
fi

`rm $leveldb_path/libycsbleveldb.so`
`cp libycsbleveldb.so $leveldb_path`
#`LD_LIBRARY_PATH=$leveldb_path`
#echo $leveldb_path
#`export LD_LIBRARY_PATH`
#echo $LD_LIBRARY_PATH

workload_path=`readlink -f ../workloads/$1`
`ls $workload_path > /dev/null`
if [ $? -ne 0 ]
then
	echo "ERROR: Invalid workload"
	exit -4
fi

# FIXME: This doesn't work now
# Temp solution: 
# From command line after the completion of this script
#	1. export LD_LIBRARY_PATH=`readlink -f ../../leveldb`
#	2. java -classpath ycsbleveldb.jar com.yahoo.ycsb.Client -db YcsbLevelDB -load -P <workload_path> -s
#	3. java -classpath ycsbleveldb.jar com.yahoo.ycsb.Client -db YcsbLevelDB -P <workload_path> -s
#
# LOAD PHASE
#`java -classpath ycsbleveldb.jar com.yahoo.ycsb.Client -db YcsbLevelDB -load -P $workload_path -s`

# Run YCSB
#`java -classpath ycsbleveldb.jar com.yahoo.ycsb.Client -db YcsbLevelDB -P $workload_path -s`
