package com.example.digipeet;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;

public class StorageAPI extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_storage);

        CardView adicionar = findViewById(R.id.addItems);
        CardView remover = findViewById(R.id.deleteItems);
        CardView procura = findViewById(R.id.scanItems);
        CardView inventario = findViewById(R.id.viewInventory);

        adicionar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(StorageAPI.this, AddProductAPI.class));
            }
        });

    }
}