package com.example.groupdb

import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast

class GroupInfo : AppCompatActivity() {

    lateinit var dbManager: DBManager
    lateinit var sqlitedb: SQLiteDatabase

    lateinit var tvName: TextView
    lateinit var tvNumber: TextView
    lateinit var tvText: TextView
    lateinit var edtUser: EditText
    lateinit var btnGo: Button

    lateinit var str_gName: String
    var gNumber: Int = 0
    var gCount: Int = 0
    lateinit var str_gText: String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_group_info)

        tvName = findViewById(R.id.gName)
        tvNumber = findViewById(R.id.gNumber)
        tvText = findViewById(R.id.gText)
        edtUser = findViewById(R.id.edtUser)
        btnGo = findViewById(R.id.btnGo)

        var myHelper: myDBHelper = myDBHelper(this)

        val intent = intent
        str_gName = intent.getStringExtra("intent_name").toString()

        dbManager = DBManager(this, "groupTBL", null, 1)
        sqlitedb = dbManager.readableDatabase

        var cursor: Cursor
        cursor = sqlitedb.rawQuery("SELECT * FROM groupTBL WHERE gName = '" + str_gName + "';", null)

        if (cursor.moveToNext()) {
            gNumber = cursor.getInt((cursor.getColumnIndex("gNumber")))
            str_gText = cursor.getString((cursor.getColumnIndex("gText"))).toString()
            gCount = cursor.getInt((cursor.getColumnIndex("gCount")))
        }

        cursor.close()
        sqlitedb.close()
        dbManager.close()

        tvName.text = str_gName
        tvNumber.text ="$gCount / $gNumber"
        tvText.text = str_gText + "\n"

        btnGo.setOnClickListener {
            sqlitedb = myHelper.writableDatabase
            // 멤버 업데이트
            sqlitedb.execSQL("UPDATE groupTBL SET gMember${gCount+1} = '" + edtUser.text.toString() + "' WHERE gName ='" + str_gName + "';")
            gCount++
            // 현재 인원수 업데이트
            sqlitedb.execSQL("UPDATE groupTBL SET gCount = " + gCount.toString() + " WHERE gName = '" + str_gName + "';")
            sqlitedb.close()
            Toast.makeText(applicationContext, "${gCount}등으로 참여 완료!", Toast.LENGTH_SHORT).show()
        }
    }

    inner class myDBHelper(context: Context) : SQLiteOpenHelper(context, "groupTBL", null, 1) {
        // 테이블 생성
        override fun onCreate(db: SQLiteDatabase?) {
            db!!.execSQL("CREATE TABLE groupTBL (gName CHAR(20) PRIMARY KEY, gNumber INTEGER, gText String, gCount INTEGER, gMember1 String, gMember2 String, gMember3 String, gMember4 String);")
        }

        // 테이블 삭제 후 다시 생성
        override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {
            db!!.execSQL("DROP TABLE IF EXISTS groupTBL")
            onCreate(db)
        }
    }
}