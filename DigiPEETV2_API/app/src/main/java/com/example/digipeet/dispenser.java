package com.example.digipeet;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;
import com.google.android.material.textfield.TextInputEditText;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.google.gson.Gson;
import java.util.HashMap;
import java.util.Map;

public class dispenser extends AppCompatActivity{

    private static final String DISPENSER_URL = "http://192.168.1.81:5000/dispenser";
    public static final String KEY_TIME = "time";
    public static final String KEY_QUANTITY = "quantity";
    private TextInputEditText TextTime, TextQuantity;
    public Button buttonWater, buttonFood;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.feedeet);

        TextQuantity= findViewById(R.id.editTextQuantity);
        TextTime = findViewById(R.id.editTextTime);
        buttonWater = findViewById(R.id.btnWater);
        buttonFood = findViewById(R.id.btnFood);

        buttonFood.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PutFeedeet();
            }
        });

        buttonWater.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(LoginAPI.this, SignUpAPI.class));
            }
        });


    }

    public void PutFeedeet(){

        Gson gson_response = new Gson();

        String quantity = (TextQuantity.getText()).toString().trim();
        String time = (TextTime.getText()).toString().trim();


        if(quantity.isEmpty())
        {
            TextQuantity.setError("Value is required");
            TextQuantity.requestFocus();
        }

        if(time.isEmpty())
        {
            TextTime.setError("Time required");
            TextTime.requestFocus();
        }

        StringRequest stringRequest = new StringRequest(Request.Method.POST, DISPENSER_URL,

                response -> {
                    auth token = gson_response.fromJson(response,auth.class);
                    startActivity(new Intent(dispenser.this, MenuAPI.class));

                })
        {
            @Override
            protected Map<String,String> getParams()
            {
                Map<String,String> params = new HashMap<>();

                params.put(KEY_QUANTITY, quantity);
                params.put(KEY_TIME,time);
                return params;
            }
        };
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        requestQueue.add(stringRequest);
    }
}
