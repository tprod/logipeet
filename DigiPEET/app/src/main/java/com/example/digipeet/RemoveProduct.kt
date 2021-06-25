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

private const val CAMERA_REQUEST_CODE = 101

class RemoveProduct : AppCompatActivity() {

    private lateinit var codeScanner: CodeScanner

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_remove_product)

        setupPermissions()
        codeScanner()

        val add = findViewById<Button>(R.id.add)
        add.setOnClickListener {
            val Bcode: String = findViewById<TextView>(R.id.bar_code).text.toString()

            deleteFirestore(Bcode)

            val intent = Intent(this, storage::class.java)
            startActivity(intent)
        }
    }

    private fun deleteFirestore(Bcode: String) {
        val db = FirebaseFirestore.getInstance()

        val current = Firebase.auth.currentUser
        val userID = current?.uid.toString()

        val user: MutableMap<String, Any> = HashMap()
        user["code"] = Bcode

        db.collection(userID).document(Bcode)
            .delete()
            .addOnSuccessListener {
                Toast.makeText(this, "Product successfully deleted", Toast.LENGTH_SHORT).show()
            }

            .addOnFailureListener {
                Toast.makeText(this, "Product failed to be deleted", Toast.LENGTH_SHORT).show()
            }

    }

    private fun codeScanner(){
        codeScanner = CodeScanner(this, findViewById(R.id.code_scanner))

        codeScanner.apply {
            camera = CodeScanner.CAMERA_BACK
            formats = CodeScanner.ALL_FORMATS

            autoFocusMode = AutoFocusMode.SAFE
            scanMode = ScanMode.CONTINUOUS
            isAutoFocusEnabled = true
            isFlashEnabled = false

            decodeCallback = DecodeCallback {
                runOnUiThread {
                    // code for value of barcode!!!!


                    // Test purposes only
                    findViewById<TextView>(R.id.bar_code).text = it.text
                }
            }

            errorCallback = ErrorCallback {
                runOnUiThread {
                    Log.e("Main", "Camera initialization error: ${it.message}")
                }
            }
        }

        findViewById<CodeScannerView>(R.id.code_scanner).setOnClickListener {
            codeScanner.startPreview()
        }

    }

    override fun onResume() {
        super.onResume()
        codeScanner.startPreview()
    }

    override fun onPause() {
        codeScanner.releaseResources()
        super.onPause()
    }

    private fun setupPermissions(){
        val permission = ContextCompat.checkSelfPermission(this,
            android.Manifest.permission.CAMERA)

        if(permission != PackageManager.PERMISSION_GRANTED){
            makeRequest()
        }
    }

    private fun makeRequest(){
        ActivityCompat.requestPermissions(this,
            arrayOf(android.Manifest.permission.CAMERA),
            CAMERA_REQUEST_CODE)
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        when(requestCode){
            CAMERA_REQUEST_CODE -> {
                if(grantResults.isEmpty() || grantResults[0] != PackageManager.PERMISSION_GRANTED){
                    Toast.makeText(this, "You need the camera permission to be able to use this function!", Toast.LENGTH_SHORT).show()
                } else {
                    // successful!
                }
            }
        }
    }
}