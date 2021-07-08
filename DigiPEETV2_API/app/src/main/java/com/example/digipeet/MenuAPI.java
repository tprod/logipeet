package com.example.digipeet;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class MenuAPI extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);


        Button Logout = findViewById(R.id.LogOut);
        Logout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                startActivity(new Intent(MenuAPI.this, LoginAPI.class));
            }
        });

        Button Storage = findViewById(R.id.Storage);
        Storage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MenuAPI.this, StorageAPI.class));
            }
        });

        Button calendar = findViewById(R.id.schedule);
        calendar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
              //  startActivity(new Intent(MenuAPI.this, com.example.digipeet.calendar.class));
            }
        });
    }

    @Override
    public void onStart(){
        super.onStart();
        // Check if user is signed in (non-null) and update UI accordingly.

        }
    }
