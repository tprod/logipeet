package com.example.digipeet

import android.content.Intent
import android.content.pm.PackageManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.TestLooperManager
import android.util.Log
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.budiyev.android.codescanner.AutoFocusMode
import com.budiyev.android.codescanner.CodeScanner
import com.budiyev.android.codescanner.CodeScannerView
import com.budiyev.android.codescanner.DecodeCallback
import com.budiyev.android.codescanner.ErrorCallback
import com.budiyev.android.codescanner.ScanMode
import com.google.android.material.textfield.TextInputEditText
import com.google.firebase.auth.ktx.auth
import com.google.firebase.firestore.FirebaseFirestore
import com.google.firebase.ktx.Firebase

import org.w3c.dom.Text

class ViewProduct : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_view_product)

        val add = findViewById<Button>(R.id.procura)
        add.setOnClickListener {
            val Search = findViewById<TextInputEditText>(R.id.SearchProduct).text.toString()

            readFirestore(Search)
        }
    }

    private fun readFirestore(Search: String) {
        val db = FirebaseFirestore.getInstance()

        val current = Firebase.auth.currentUser
        val userID = current?.uid.toString()

        db.collection(userID)
            .whereEqualTo("Product", Search)
            .get()
            .addOnCompleteListener(){
                Toast.makeText(this, "Product successfully found", Toast.LENGTH_SHORT).show()

                val s_product: StringBuffer = StringBuffer()
                val s_quantity: StringBuffer = StringBuffer()
                val s_code: StringBuffer = StringBuffer()

                if(it.isSuccessful){
                    for(document in it.result!!){
                        s_product.append(document.data.getValue("Product")).append("\n")
                        s_quantity.append(document.data.getValue("Quantity")).append("\n")
                        s_code.append(document.data.getValue("Code")).append("\n")
                    }
                    findViewById<TextView>(R.id.S_Product).setText(s_product)
                    findViewById<TextView>(R.id.S_Quantity).setText(s_quantity)
                    findViewById<TextView>(R.id.S_Code).setText(s_code)
                }
            }

            .addOnFailureListener {
                Toast.makeText(this, "Product could not be found", Toast.LENGTH_SHORT).show()
            }
    }
}