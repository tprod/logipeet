package com.example.digipeet;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.firebase.ui.firestore.FirestoreRecyclerAdapter;
import com.firebase.ui.firestore.FirestoreRecyclerOptions;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.firestore.DocumentChange;
import com.google.firebase.firestore.DocumentReference;
import com.google.firebase.firestore.EventListener;
import com.google.firebase.firestore.FirebaseFirestore;
import com.google.firebase.firestore.FirebaseFirestoreException;
import com.google.firebase.firestore.Query;
import com.google.firebase.firestore.QuerySnapshot;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;

public class Inventory extends AppCompatActivity {

    RecyclerView recyclerView;
    FirebaseFirestore db;
    FirebaseAuth mAuth;
    String userID;

    private FirestoreRecyclerAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_inventory);

        db = FirebaseFirestore.getInstance();
        mAuth = FirebaseAuth.getInstance();

        userID = mAuth.getCurrentUser().getUid();

        recyclerView = findViewById(R.id.RecyclerView);

        //Query
        Query query = db.collection(userID);

        //Recycler Options
        FirestoreRecyclerOptions<Items> options = new FirestoreRecyclerOptions.Builder<Items>()
                .setQuery(query, Items.class)
                .build();

        adapter = new FirestoreRecyclerAdapter<Items, ItemsViewHolder>(options) {
            @NonNull
            @NotNull
            @Override
            public ItemsViewHolder onCreateViewHolder(@NonNull @NotNull ViewGroup parent, int viewType) {
                View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.items, parent, false);
                return new ItemsViewHolder(v);
            }

            @Override
            protected void onBindViewHolder(@NonNull @NotNull Inventory.ItemsViewHolder holder, int position, @NonNull @NotNull Items model) {

                holder.list_product.setText(model.getProduct());
                holder.list_quantity.setText(model.getQuantity());
                holder.list_code.setText(model.getCode());
            }
        };

        recyclerView.setHasFixedSize(true);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        recyclerView.setAdapter(adapter);

        adapter.startListening();
    }

    private class ItemsViewHolder extends RecyclerView.ViewHolder{

        private TextView list_product, list_quantity, list_code;

        public ItemsViewHolder(@NonNull @NotNull View itemView) {
            super(itemView);

            list_product = itemView.findViewById(R.id.View_Product);
            list_quantity = itemView.findViewById(R.id.View_Quantity);
            list_code = itemView.findViewById(R.id.View_BCode);
        }
    }
}