using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestScript2 : MonoBehaviour
{
    BGMManager BGM;
    //public int playMusicTrack;

    // Start is called before the first frame update
    void Start()
    {
        BGM = FindObjectOfType<BGMManager>();
    }

    /*
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //if...
        StartCoroutine(final());
        
    }

    IEnumerator final()
    {
        BGM.FadeOutMusic();

        yield return new WaitForSeconds(3f);

        BGM.FadeInMusic();
    }
    */
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //if...
        BGM.Stop();
        //this.gameObject.SetActive(false);
    }
}
