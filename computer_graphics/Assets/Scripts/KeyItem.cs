using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KeyItem : MonoBehaviour
{
    Inventory inventory;

    private void Start()
    {
        inventory = GameObject.Find("Player").GetComponent<Inventory>();
    }
    // Update is called once per frame
    void Update()
    {
        if (Input.inputString == (transform.parent.GetComponent<Slot>().num+1).ToString())
        {
            // 아이템 사용
            Debug.Log((transform.parent.GetComponent<Slot>().num + 1) + "번째 열쇠 조각 사용");
            inventory.slots[transform.parent.GetComponent<Slot>().num].isEmpty = true;
            Destroy(this.gameObject);
        }
    }
}
