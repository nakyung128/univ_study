using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DataManager : MonoBehaviour
{
    public float playTimeCurrent = 5f;
    public float playTimeMax = 5f;

    static DataManager instance;
    public static DataManager Instance
    {
        get
        {
            return instance;
        }
    }

    private void Awake()
    {
        if(instance == null)
        {
            DontDestroyOnLoad(gameObject);
            instance = this;
        }
        else
        {
            DestroyObject(gameObject);
        }
    }

    public int score = 0;

    public bool PlayerDie = false; // 사망 판단

    // 자석에 사용할 변수
    public float margnetTimeCurrent = 0f;
    public float margnetTimeMax = 0.5f;
    public float itemMoveSpeed = 2f;
}
