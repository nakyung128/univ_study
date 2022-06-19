using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HurtEnemy : MonoBehaviour
{
    public string atkSound;
    private PlayerStat thePlayerStat;

    // Start is called before the first frame update
    void Start()
    {
        thePlayerStat = FindObjectOfType<PlayerStat>();
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Enemy")
        {
              int dmg = collision.gameObject.GetComponent<EnemyStat>().Hit(thePlayerStat.atk);
              Debug.Log("우치가 강아지를 공격하고 있습니다!");
              AudioManager.instance.Play(atkSound);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
