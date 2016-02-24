// package com.jni;

import java.io.*;
import java.lang.*;

public class JNISample {

	public native void displayHelloWorld();
	public native void searchFileSystem();
	public native void findFileSystemType();
	public native void stringManipulation(String s);
	public native void characterManipulation(char c[]);
	public native void objectManipulation(Object o);
	public native void integerManipulation(int j, int k);
	public native void search(String text, String phrase);
	
	static {
		System.loadLibrary("foo");
	}

	public static void main(String[] args) {
	 
		String sQuery = "Hello";
		char[] cQuery = sQuery.toCharArray();
		
		new JNISample().displayHelloWorld();
		new JNISample().findFileSystemType();
		new JNISample().searchFileSystem();
		new JNISample().stringManipulation("Test");
		new JNISample().characterManipulation(cQuery);
		new JNISample().objectManipulation(null);
		new JNISample().integerManipulation(1, 2);
		new JNISample().search("Text", "Phrase");
		
	}

}


