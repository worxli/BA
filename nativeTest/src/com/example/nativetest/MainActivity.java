package com.example.nativetest;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

public class MainActivity extends Activity {
	
	
	static {
	      System.loadLibrary("myjni"); // "myjni.dll" in Windows, "libmyjni.so" in Unixes
	   }
	
	public native String getMessage(String string);

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		Toast.makeText(getApplicationContext(), getMessage("asdf"), Toast.LENGTH_LONG).show();
	}
}
