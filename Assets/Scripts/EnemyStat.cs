using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyStat : MonoBehaviour
{
    public int hp;
    public int currentHp;
    public int atk;
    public int def;

    public string dmgSound;

    // Start is called before the first frame update
    void Start()
    {
        currentHp = hp;
    }

    public int Hit(int _playerAtk)
    {
        int playerAtk = _playerAtk;
        int dmg;
        if (def >= playerAtk) dmg = 2;
        else dmg = playerAtk - def;

        currentHp -= dmg;

        if (currentHp <= 0)
        {
            Debug.Log("우치가 강아지를 물리쳤습니다!");
            Destroy(this.gameObject); // 파괴
        }

        return dmg;
    }
}
