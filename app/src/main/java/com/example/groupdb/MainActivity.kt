package com.example.groupdb

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button

class MainActivity : AppCompatActivity() {

    lateinit var btnJoin: Button
    lateinit var btnMaking: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        btnJoin = findViewById(R.id.btnJoin)
        btnMaking = findViewById(R.id.btnMake)

        btnJoin.setOnClickListener {
            val intent = Intent(this, GroupJoin::class.java)
            startActivity(intent)
        }

        btnMaking.setOnClickListener {
            val intent = Intent(this, GroupMaking::class.java)
            startActivity(intent)
        }
    }
}