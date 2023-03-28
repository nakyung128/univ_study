package com.example.groupdb

import android.content.Context
import android.content.Intent
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import android.graphics.Color
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.DropBoxManager
import android.widget.LinearLayout
import android.widget.ListView
import android.widget.TextView

class GroupJoin : AppCompatActivity() {
    lateinit var dbManager: DBManager
    lateinit var sqlitedb: SQLiteDatabase
    lateinit var layout: LinearLayout

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_group_join)

        dbManager = DBManager(this, "groupTBL", null, 1)
        sqlitedb = dbManager.readableDatabase

        layout = findViewById(R.id.group)

        var cursor: Cursor
        cursor = sqlitedb.rawQuery("SELECT * FROM groupTBL;", null)

        var num: Int = 0
        while (cursor.moveToNext()) {
            var str_gName = cursor.getString((cursor.getColumnIndex("gName"))).toString()
            var str_gText = cursor.getString((cursor.getColumnIndex("gText"))).toString()

            var layout_item: LinearLayout = LinearLayout(this)
            layout_item.orientation = LinearLayout.VERTICAL
            layout_item.setPadding(20, 10, 20, 10)
            layout_item.id = num
            layout_item.setTag(str_gName)

            // 그룹 이름 보여 주기
            var tvName: TextView = TextView(this)
            tvName.text = str_gName
            tvName.textSize = 30F
            tvName.setBackgroundColor(Color.LTGRAY)
            layout_item.addView(tvName)

            // 그룹 한줄 소개 보여주기
            var tvText: TextView = TextView(this)
            tvText.text = str_gText
            layout_item.addView(tvText)

            // 줄 클릭했을 때
            layout_item.setOnClickListener {
                val intent = Intent(this, GroupInfo::class.java)
                intent.putExtra("intent_name", str_gName)
                startActivity(intent)
            }
            layout.addView(layout_item)
            num++
        }

        cursor.close()
        sqlitedb.close()
        dbManager.close()
    }
}