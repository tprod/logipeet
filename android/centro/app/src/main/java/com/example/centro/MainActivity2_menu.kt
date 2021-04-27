package com.example.centro

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class MainActivity2_menu : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.menu_inicial)

        val insert_product = findViewById<Button>(R.id.insert_product) as Button
        insert_product.setOnClickListener {
            val intent = Intent(this, leitor_codigo::class.java)
            startActivity(intent)
        }

        val Storage = findViewById<Button>(R.id.Storage) as Button
        Storage.setOnClickListener {
            val intent = Intent(this, storage::class.java)
            startActivity(intent)
        }
    }
}