package com.example.digipeet;


import android.os.Bundle;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import androidx.appcompat.app.AppCompatActivity;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class peetmanagment extends AppCompatActivity {

    // Array of strings for ListView Title
    String[] listviewTitle = new String[]{
            "Cage 1", "Cage 2", "Cage 3", "Cage 4",
            "Cage 5", "Cage 6", "Cage 7", "Cage 8",
    };


    int[] listviewImage = new int[]{
            R.drawable.ic_launcher_round, R.drawable.ic_launcher_round, R.drawable.ic_launcher_round, R.drawable.ic_launcher_round,
            R.drawable.ic_launcher_round, R.drawable.ic_launcher_round, R.drawable.ic_launcher_round, R.drawable.ic_launcher_round,
    };

    String[] listviewShortDescription = new String[]{
            "Dispenser: v1 ; tag: 0x01", "Dispenser: v1 ; tag: 0x02", "Dispenser: v1 ; tag: 0x03", "Dispenser: v1 ; tag: 0x04",
            "Dispenser: v1 ; tag: 0x05", "Dispenser: v1 ; tag: 0x06", "Dispenser: v1 ; tag: 0x07", "Dispenser: v1 ; tag: 0x08",
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_listview_with_image_and_text);

        List<HashMap<String, String>> aList = new ArrayList<HashMap<String, String>>();

        for (int i = 0; i < 8; i++) {
            HashMap<String, String> hm = new HashMap<String, String>();
            hm.put("listview_title", listviewTitle[i]);
            hm.put("listview_discription", listviewShortDescription[i]);
            hm.put("listview_image", Integer.toString(listviewImage[i]));
            aList.add(hm);
        }

        String[] from = {"listview_image", "listview_title", "listview_discription"};
        int[] to = {R.id.listview_image, R.id.listview_item_title, R.id.listview_item_short_description};

        SimpleAdapter simpleAdapter = new SimpleAdapter(getBaseContext(), aList, R.layout.listview_activity, from, to);
        ListView androidListView = (ListView) findViewById(R.id.list_view);
        androidListView.setAdapter(simpleAdapter);


    }
}
