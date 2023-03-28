package com.example.groupdb

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import com.google.android.material.textfield.TextInputLayout

class GroupMaking : AppCompatActivity() {

    lateinit var myHelper: myDBHelper
    lateinit var edtName: EditText
    lateinit var edtNumber: EditText
    lateinit var edtTextBox: EditText
    lateinit var btnOk: Button
    lateinit var sqlDB: SQLiteDatabase

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_group_making)

        edtName = findViewById(R.id.edtName)
        edtNumber = findViewById(R.id.edtNumber)
        edtTextBox = findViewById(R.id.edtTextBox)
        btnOk = findViewById(R.id.btnOk)

        myHelper = myDBHelper(this)

        btnOk.setOnClickListener {
            if (edtNumber.text.toString().toInt() <= 4) {
                sqlDB = myHelper.writableDatabase
                sqlDB.execSQL("INSERT INTO groupTBL VALUES ('" + edtName.text.toString() + "', " +
                        edtNumber.text.toString() + ", '" + edtTextBox.text.toString() + "', " + 0.toString() + ", ' ', ' ', ' ', ' ');")
                sqlDB.close()
                Toast.makeText(applicationContext, "${edtName.text} 그룹이 생성되었습니다!", Toast.LENGTH_SHORT).show()
            } else {
                Toast.makeText(applicationContext, "인원수가 너무 많습니다. 4명 이하로 설정해 주세요.", Toast.LENGTH_SHORT).show()
            }
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