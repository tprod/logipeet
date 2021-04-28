package com.example.centro

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class storage : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_storage)

        val addProduct = findViewById<Button>(R.id.addProduct) as Button
        addProduct.setOnClickListener {
            val intent = Intent(this, leitor_codigo::class.java)
            startActivity(intent)
        }
    }
}