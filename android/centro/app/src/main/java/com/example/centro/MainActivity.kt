package com.example.centro

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.login)

        val Login = findViewById<Button>(R.id.Login) as Button
            Login.setOnClickListener {
                val intent = Intent(this, MainActivity2_menu::class.java)
                startActivity(intent)
            }

        val SignBtn = findViewById<Button>(R.id.SignBtn) as Button
            SignBtn.setOnClickListener {
                val intent = Intent(this, registo::class.java)
                startActivity(intent)
            }
    }
}