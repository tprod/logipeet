package com.example.digipeet;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;

import android.util.Log;
import android.util.SparseArray;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.core.app.ActivityCompat;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.google.android.gms.vision.CameraSource;
import com.google.android.gms.vision.Detector;
import com.google.android.gms.vision.barcode.Barcode;
import com.google.android.gms.vision.barcode.BarcodeDetector;
import com.google.android.material.textfield.TextInputEditText;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;


public class AddProductAPI extends AppCompatActivity {


    private static final String REGISTER_URL = "http://192.168.1.81:5000/storage";
    public static final String KEY_NAME = "name_product";
    public static final String KEY_WEIGHT = "weight";
    public static final String KEY_AMOUNT = "amount";
    public static final String KEY_CODE = "code_product";

    SurfaceView surfaceView;
    TextView txtBarcodeValue;
    EditText txtNameValue,txtweightValue,txtamountValue;
    private BarcodeDetector barcodeDetector;
    private CameraSource cameraSource;
    private static final int REQUEST_CAMERA_PERMISSION = 201;
    Button btnAction;
    String intentData = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_scan_bar);
        initViews();
    }

    private void initViews() {
        txtBarcodeValue = findViewById(R.id.txtBarcodeValue);
        surfaceView = findViewById(R.id.surfaceView);

        txtNameValue = findViewById(R.id.editTextProductName);
        txtweightValue = findViewById(R.id.editTextweightProduct);
        txtamountValue = findViewById(R.id.editTextNumberDecimal);
        btnAction = findViewById(R.id.btnAction);


        btnAction.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {

                String txtName = (txtNameValue.getText()).toString().trim();
                String txtWeight = (txtweightValue.getText()).toString().trim();
                String txtAmount = (txtamountValue.getText()).toString().trim();
                String txtBarcode = (txtBarcodeValue.getText()).toString().trim();

                if (intentData.length() > 0) {
                    if (txtName.isEmpty()) {
                        txtNameValue.setError("Name is required");
                        txtNameValue.requestFocus();
                    }
                    else if (txtWeight.isEmpty()) {
                        txtweightValue.setError("Weight value is required");
                        txtweightValue.requestFocus();
                    }
                    else if (txtAmount.isEmpty()) {
                        txtamountValue.setError("Amount value is required");
                        txtamountValue.requestFocus();
                    }
                    else{

                        StringRequest stringRequest = new StringRequest(Request.Method.POST, REGISTER_URL,

                                response -> {
                                    Log.d("Success", response);

                                    startActivity(new Intent(AddProductAPI.this, MenuAPI.class));

                                },
                                error -> Toast.makeText(AddProductAPI.this,"Something went wrong on this. Try again ;)",Toast.LENGTH_LONG).show())

                        {
                            @Override
                            protected Map<String,String> getParams()
                            {
                                Map<String,String> params = new HashMap<>();

                                params.put(KEY_NAME,txtName);
                                params.put(KEY_CODE,txtBarcode);
                                params.put(KEY_WEIGHT, txtWeight);
                                params.put(KEY_AMOUNT,txtAmount);
                                return params;
                            }
                        };
                        RequestQueue requestQueue = Volley.newRequestQueue(AddProductAPI.this);
                        requestQueue.add(stringRequest);

                    }
                }
            }
        });
    }
    private void initialiseDetectorsAndSources() {

        Toast.makeText(getApplicationContext(), "Barcode scanner started", Toast.LENGTH_SHORT).show();
        barcodeDetector = new BarcodeDetector.Builder(this)
                .setBarcodeFormats(Barcode.ALL_FORMATS)
                .build();

        cameraSource = new CameraSource.Builder(this, barcodeDetector)
                .setRequestedPreviewSize(1920, 1080)
                .setAutoFocusEnabled(true)
                .build();

        surfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder holder) {
                try {
                    if (ActivityCompat.checkSelfPermission(AddProductAPI.this, Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED) {
                        cameraSource.start(surfaceView.getHolder());
                    } else {
                        ActivityCompat.requestPermissions(AddProductAPI.this, new
                                String[]{Manifest.permission.CAMERA}, REQUEST_CAMERA_PERMISSION);
                    }

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            @Override
            public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
            }

            @Override
            public void surfaceDestroyed(SurfaceHolder holder) {
                cameraSource.stop();
            }
        });


        barcodeDetector.setProcessor(new Detector.Processor<Barcode>() {
            @Override
            public void release() {
                Toast.makeText(getApplicationContext(), "Done", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void receiveDetections(Detector.Detections<Barcode> detections) {
                final SparseArray<Barcode> barcodes = detections.getDetectedItems();
                if (barcodes.size() != 0) {
                    txtBarcodeValue.post(new Runnable() {
                        @Override
                        public void run() {

                            if (barcodes.valueAt(0).email != null) {
                                txtBarcodeValue.removeCallbacks(null);
                                txtBarcodeValue.setText(intentData);
                            } else {
                                intentData = barcodes.valueAt(0).displayValue;
                                txtBarcodeValue.setText(intentData);
                            }
                        }
                    });
                }
            }
        });
    }


    @Override
    protected void onPause() {
        super.onPause();
        cameraSource.release();
    }

    @Override
    protected void onResume() {
        super.onResume();
        initialiseDetectorsAndSources();
    }
}