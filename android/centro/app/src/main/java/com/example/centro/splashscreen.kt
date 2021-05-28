package com.example.centro

import android.content.Intent
import android.os.Bundle
import android.widget.ImageView
import androidx.appcompat.app.AppCompatActivity

class splashscreen : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_splashscreen)

        findViewById<ImageView>(R.id.logo_doggo).alpha = 0f
        findViewById<ImageView>(R.id.logo_doggo).animate().setDuration(1500).alpha(1f).withEndAction {
            val i = Intent(this, MainActivity2_menu::class.java)
            startActivity(i)
            overridePendingTransition(android.R.anim.fade_in, android.R.anim.fade_out)
            finish()
        }

        findViewById<ImageView>(R.id.logo_name).alpha = 0f
        findViewById<ImageView>(R.id.logo_name).animate().setDuration(1500).alpha(1f).withEndAction {
            val i = Intent(this, MainActivity2_menu::class.java)
            startActivity(i)
            overridePendingTransition(android.R.anim.fade_in, android.R.anim.fade_out)
            finish()
        }
    }
}