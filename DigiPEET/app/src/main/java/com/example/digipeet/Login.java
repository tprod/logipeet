package com.example.digipeet;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.material.textfield.TextInputEditText;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

public class Login extends AppCompatActivity {

    private FirebaseAuth mAuth;

    private TextInputEditText Email_L, Password_L;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        Button b_register = (Button) findViewById(R.id.SignBtn);
        b_register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openRegisto();
            }
        });

        Email_L = findViewById(R.id.editTextTextEmailAddress);
        Password_L = findViewById(R.id.editTextTextPassword);

        // Initialize Firebase Auth
        mAuth = FirebaseAuth.getInstance();
        // [END initialize_auth]

        Button b_login = (Button) findViewById(R.id.Login);
        b_login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                loginUser();
            }
        });
    }

    public void loginUser(){
        String email = Email_L.getText().toString();
        String password = Password_L.getText().toString();

        if(TextUtils.isEmpty(email)){
            Email_L.setError("An email is required!");
            Email_L.requestFocus();
        }else if( TextUtils.isEmpty(password)) {
            Password_L.setError("A password is required!");
            Password_L.requestFocus();
        }else{
            mAuth.signInWithEmailAndPassword(email, password).addOnCompleteListener(new OnCompleteListener<AuthResult>() {
                @Override
                public void onComplete(@NonNull Task<AuthResult> task) {
                    if(task.isSuccessful()){
                        Toast.makeText(Login.this, "User Logged In Successfully", Toast.LENGTH_SHORT).show();
                        startActivity(new Intent(Login.this, menu_inicial.class));
                    }else{
                        Toast.makeText(Login.this, "Login In Error; " + task.getException().getMessage(), Toast.LENGTH_SHORT).show();
                    }
                }
            });
        }
    }

    public void openRegisto(){
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }
}