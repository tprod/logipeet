package com.example.logipeetmenu

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView

class todothings(
        private val things: MutableList<things>
): RecyclerView.Adapter<todothings.thingsviewholder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): thingsviewholder {
        return thingsviewholder(
                LayoutInflater.from(parent.context).inflate(
                        R.layout.storage,
                        parent,
                        false
                )
        )
    }
}
    //fun  addthings(Things: things){
      //  things.add(Things)
        //notifyItemInserted(position:things.sizze -1)
   // }
    // fun deletetthings(){
    // things.removeAll{
    //  things.isChecked
    // }
    // notifyDataSetChanged()
    // }
    override fun getItemCount(): Int {
        return things.size
    }
// aqui uma suposta função que caguei 49:38

   // override fun onBindViewHolder(holder: thingsviewholder, position: Int) {        //isto não é preciso
     //   // qaul texto nos queremos que "apareça"
       // val curthings = things[position]
        //holder.itemView.apply {
          //  tvTodoTitle.text = curthings.title
             // alt+enter, para fazer import butt não tenho
            //cbDone.isChecked = curthings.isChecked
            // falta aqui merdas
      //}
    //}

    class thingsviewholder(itemView:View):RecyclerView.ViewHolder(itemView)
}