using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Dialogue
{
    [TextArea(1, 2)]
    public string[] sentences;
    public Sprite[] sprites;
    public Sprite[] dialogueWindows;    //어떤 캐릭터 대화창인지 나타냄
}
