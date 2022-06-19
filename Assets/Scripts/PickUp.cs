using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PickUp : MonoBehaviour
{
    private AudioManager theAudio;
    public string enter_sound;

    public GameObject slotItem;

    private void Start()
    {
        theAudio = FindObjectOfType<AudioManager>();        
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.name == "Player")
        {
            Inventory inven = collision.GetComponent<Inventory>();
            for(int i=0; i < inven.slots.Count; i++)    //slot ºó °ø°£ Ã£±â
            {
                if (inven.slots[i].isEmpty)
                {
                    theAudio.Play(enter_sound);
                    Instantiate(slotItem, inven.slots[i].slotObj.transform, false);
                    inven.slots[i].isEmpty = false;
                    Destroy(this.gameObject);

                    break;
                }
            }
        }
    }
}
