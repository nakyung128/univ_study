using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Choice
{
    public string question; // 질문
    public string[] answers; // 답변 (배열, 최대 4개까지만)
}
