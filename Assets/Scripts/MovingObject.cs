using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingObject : MonoBehaviour
{
    public string characterName;

    public float speed;
    public int walkCount;
    protected int currentWalkCount;

    private bool notCoroutine = false;  //코르틴 중복실행 방지
    protected Vector3 vector;

    public Queue<string> queue;
    //FIFO

    public BoxCollider2D boxCollider;
    public LayerMask layerMask;     //충돌 layer 판단
    public Animator animator;

    public void Move(string _dir, int _frequency = 5)
    {
        if (!notCoroutine)
        {
            notCoroutine = true;
            StartCoroutine(MoveCoroutine(_dir, _frequency));
        }
    }

    IEnumerator MoveCoroutine(string _dir, int _frequency)
    {
        while (queue.Count != 0)
        {
            vector.Set(0, 0, vector.z);
            switch (_dir)
            {
                case "UP":
                    vector.y = 1f;
                    break;
                case "Down":
                    vector.y = -1f;
                    break;
                case "RIGHT":
                    vector.x = 1f;
                    break;
                case "LEFT":
                    vector.x = -1f;
                    break;
            }

            animator.SetFloat("DirX", vector.x);
            animator.SetFloat("DirY", vector.y);

            /* //플레이어와 닿는 경우 npc를 멈추게 할 때
            while (true)
            {
                bool checkCollisionFlag = CheckCollision();
                if (checkCollisionFlag)
                {
                    animator.SetBool("Walking", false);
                    yield return new WaitForSeconds(1f);
                }
                else
                {
                    break;
                }
            }
            */


            animator.SetBool("Walking", true);

            boxCollider.offset = new Vector2(vector.x * 0.7f * speed * walkCount, vector.y * 0.7f * speed * walkCount);

            while (currentWalkCount < walkCount)
            {
                transform.Translate(vector.x * speed, vector.y * speed, 0);
                currentWalkCount++;
                if (currentWalkCount == walkCount * 0.5f + 2)
                {
                    boxCollider.offset = Vector2.zero;
                }
                yield return new WaitForSeconds(0.01f);    //0.01초동안 대기 (반복문 20번:0.2초)
            }
            currentWalkCount = 0;
            animator.SetBool("Walking", false);
            notCoroutine = false;
        }
        animator.SetBool("Walking", false);
    }

    protected bool CheckCollision()
    {
        RaycastHit2D hit;   //충돌할경우 hit에 장애물 return

        Vector2 start = transform.position;  //캐릭터의 현재 위치 값
        Vector2 end = start + new Vector2(vector.x * speed * walkCount, vector.y * speed * walkCount);    //캐릭터가 이동하고자 하는 위치 값

        boxCollider.enabled = false;
        hit = Physics2D.Linecast(start, end, layerMask);
        boxCollider.enabled = true;

        //충돌하지 않았을 경우 null return
        if (hit.transform != null)
        {
            return true;
        }
        return false;
    }
}