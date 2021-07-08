package com.example.digipeet;


import android.content.Intent;
import android.os.Bundle;
import android.util.Patterns;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import com.google.android.material.textfield.TextInputEditText;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.google.gson.Gson;
import java.util.HashMap;
import java.util.Map;

public class LoginAPI extends AppCompatActivity{

    private static final String REGISTER_URL = "http://192.168.1.81:5000/login";
    public static final String KEY_PASSWORD = "password";
    public static final String KEY_EMAIL = "email";
    private TextInputEditText TextEmail, TextPassword;
    public Button buttonLogin, buttonSign;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        TextEmail= findViewById(R.id.editTextEmail);
        TextPassword = findViewById(R.id.editTextPassword);
        buttonLogin = findViewById(R.id.btnLogin);
        buttonSign = findViewById(R.id.btnSign);

        buttonLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LoginUser();
            }
        });

        buttonSign.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(LoginAPI.this, SignUpAPI.class));
            }
        });


    }

    public void LoginUser(){

        Gson gson_response = new Gson();

        String password = (TextPassword.getText()).toString().trim();
        String email = (TextEmail.getText()).toString().trim();


        if(email.isEmpty())
        {
            TextEmail.setError("Email is required");
            TextEmail.requestFocus();
        }

        if(!Patterns.EMAIL_ADDRESS.matcher(email).matches())
        {
            TextEmail.setError("Enter a valid email");
            TextEmail.requestFocus();
            return;
        }
        if(password.isEmpty())
        {
            TextPassword.setError("Password required");
            TextPassword.requestFocus();
        }

        StringRequest stringRequest = new StringRequest(Request.Method.POST, REGISTER_URL,

                response -> {
                        auth token = gson_response.fromJson(response,auth.class);
                        startActivity(new Intent(LoginAPI.this, MenuAPI.class));

                },
                error -> Toast.makeText(LoginAPI.this,"Wrong Username of Password",Toast.LENGTH_LONG).show())
        {
            @Override
            protected Map<String,String> getParams()
            {
                Map<String,String> params = new HashMap<>();

                params.put(KEY_EMAIL, email);
                params.put(KEY_PASSWORD,password);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        requestQueue.add(stringRequest);
    }

}