package com.example.digipeet;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.material.textfield.TextInputEditText;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;


public class MainActivity extends AppCompatActivity {

    private FirebaseAuth mAuth;

    private Button register;
    private TextInputEditText TextEmail, TextPassword;
    private TextView B_login;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextEmail = findViewById(R.id.editTextTextEmailAddress);
        TextPassword = findViewById(R.id.editTextTextPassword);
        B_login = findViewById(R.id.backToLogin);

        register = findViewById(R.id.register);

        // Initialize Firebase Auth
        mAuth = FirebaseAuth.getInstance();
        // [END initialize_auth]

        register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                createUser();
            }
        });

        B_login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, Login.class));
            }
        });
    }

    private void createUser(){
        String email = TextEmail.getText().toString();
        String password = TextPassword.getText().toString();

        if(TextUtils.isEmpty(email)){
            TextEmail.setError("An email is required!");
            TextEmail.requestFocus();
        }else if( TextUtils.isEmpty(password)){
            TextPassword.setError("A password is required!");
            TextPassword.requestFocus();
        }else{
            mAuth.createUserWithEmailAndPassword(email,password).addOnCompleteListener(new OnCompleteListener<AuthResult>() {
                @Override
                public void onComplete(@NonNull Task<AuthResult> task) {
                    if(task.isSuccessful()){
                        Toast.makeText(MainActivity.this, "User Registered Successfully", Toast.LENGTH_SHORT).show();
                        startActivity(new Intent(MainActivity.this, Login.class));
                    }else{
                        Toast.makeText(MainActivity.this, "Registration Error; " + task.getException().getMessage(), Toast.LENGTH_SHORT).show();
                    }
                }
            });
        }
    }


}