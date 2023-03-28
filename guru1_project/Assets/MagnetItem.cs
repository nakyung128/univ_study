using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MagnetItem : MonoBehaviour
{
    public GameObject player;

    private void Update()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        float distance = Vector2.Distance(gameObject.transform.position, player.transform.position);

        if (DataManager.Instance.PlayerDie == false && DataManager.Instance.margnetTimeCurrent > 0)
        {
            if (distance < 10)
            {
                Vector2 dir = player.transform.position - transform.position;

                transform.Translate(dir.normalized * DataManager.Instance.itemMoveSpeed * Time.deltaTime, Space.World);
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (!DataManager.Instance.PlayerDie)
        {
            if (collision.gameObject.tag.CompareTo("Player") == 0)
            {
                DataManager.Instance.margnetTimeCurrent = DataManager.Instance.margnetTimeMax;
                gameObject.SetActive(false);
            }
        }
    }
}
