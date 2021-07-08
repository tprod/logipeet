package com.example.digipeet;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.util.Patterns;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.google.android.material.textfield.TextInputEditText;
import com.google.gson.Gson;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;


public class SignUpAPI extends AppCompatActivity {

    private static final String REGISTER_URL = "http://192.168.1.81:5000/signup";
    public static final String KEY_NAME = "name";
    public static final String KEY_PASSWORD = "password";
    public static final String KEY_EMAIL = "email";
    private TextInputEditText editTextEmail;
    private TextInputEditText editTextPassword;
    private TextInputEditText editTextName;
    public Button buttonRegister;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup);

        editTextName = findViewById(R.id.editTextName);
        editTextEmail= findViewById(R.id.editTextEmail);
        editTextPassword = findViewById(R.id.editTextPassword);
        buttonRegister = findViewById(R.id.btnRegister);

        buttonRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                SignUser();
            }
        });

    }

    private void SignUser(){

        //Gson gson_response = new Gson();

        final String name = Objects.requireNonNull(editTextName.getText()).toString().trim();
        final String password = Objects.requireNonNull(editTextPassword.getText()).toString().trim();
        final String email = Objects.requireNonNull(editTextEmail.getText()).toString().trim();


        if(name.isEmpty())
        {
            editTextName.setError("Name is required");
            editTextName.requestFocus();
        }
        if(email.isEmpty())
        {
            editTextEmail.setError("Email is required");
            editTextEmail.requestFocus();
        }

        if(!Patterns.EMAIL_ADDRESS.matcher(email).matches())
        {
            editTextEmail.setError("Enter a valid email");
            editTextEmail.requestFocus();
            return;
        }
        if(password.isEmpty())
        {
            editTextPassword.setError("Password required");
            editTextPassword.requestFocus();
        }

        StringRequest stringRequest = new StringRequest(Request.Method.POST, REGISTER_URL,

                response -> {
                    Log.d("Success", response);

                    startActivity(new Intent(SignUpAPI.this, LoginAPI.class));

                },
                error -> Toast.makeText(SignUpAPI.this,"Something went wrong on this. Try again ;)",Toast.LENGTH_LONG).show())

        {
            @Override
            protected Map<String,String> getParams()
            {
                Map<String,String> params = new HashMap<>();

                params.put(KEY_NAME,name);
                params.put(KEY_EMAIL, email);
                params.put(KEY_PASSWORD,password);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        requestQueue.add(stringRequest);
    }
}