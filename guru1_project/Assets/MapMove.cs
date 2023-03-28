using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapMove : MonoBehaviour
{
    public float mapSpeed = 0.5f;

    private void Update()
    {
        if (!DataManager.Instance.PlayerDie)
        {
            //맵 스피트 만큼 -x 축으로 이동
            transform.Translate(-mapSpeed * Time.deltaTime, 0, 0);
        }
            
    }
}