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
            // ������ ���
            Debug.Log((transform.parent.GetComponent<Slot>().num + 1) + "��° ���� ���� ���");
            inventory.slots[transform.parent.GetComponent<Slot>().num].isEmpty = true;
            Destroy(this.gameObject);
        }
    }
}
