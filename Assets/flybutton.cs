using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using UnityEngine;

public class flybutton : MonoBehaviour
{
    public float birdjump = 8f;

    private void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            GetComponent<Rigidbody2D>().velocity = new Vector3(0, birdjump, 0);
        }
    }
}
