using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerStat : MonoBehaviour
{
    public static PlayerStat instance;

    public int hp;
    public int currentHp;

    public int atk; // 공격력
    public int def; // 방어력

    public string dmgSound;

    // Start is called before the first frame update
    void Start()
    {
        instance = this;
        currentHp = hp;
    }

    public void Hit(int _enemyAtk)
    {
        int dmg;
        if (def >= _enemyAtk) dmg = 1;
        else dmg = _enemyAtk - def;

        currentHp -= dmg;

        if (currentHp <= 0) Debug.Log("체력 0 미만, 게임 오버...");

        AudioManager.instance.Play(dmgSound);

        StopAllCoroutines();
        StartCoroutine(HitCoroutine());

       /* Vector3 vector = this.transform.position;
        vector.y += 60; // 캐릭터 머리 위에 띄워지도록

        GameObject clone = Instantiate(prefabs_Floating_text, vector, Quaternion.Euler(Vector3.zero));
        clone.GetComponent<FloatingText>().text.text = dmg.ToString();*/
    }

    IEnumerator HitCoroutine()
    {
        Color color = GetComponent<SpriteRenderer>().color;
        color.a = 0;
        GetComponent<SpriteRenderer>().color = color;
        yield return new WaitForSeconds(0.1f);
        color.a = 1f;     
        GetComponent<SpriteRenderer>().color = color;
        yield return new WaitForSeconds(0.1f);
        color.a = 0f;
        GetComponent<SpriteRenderer>().color = color;
        yield return new WaitForSeconds(0.1f);
        color.a = 1f;
        GetComponent<SpriteRenderer>().color = color;
        yield return new WaitForSeconds(0.1f);
        color.a = 0f;
        GetComponent<SpriteRenderer>().color = color;
        yield return new WaitForSeconds(0.1f);
        color.a = 1f;
        GetComponent<SpriteRenderer>().color = color;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
