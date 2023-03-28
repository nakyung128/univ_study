using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingObject : MonoBehaviour
{
    public string characterName;

    public float speed;
    public int walkCount;
    protected int currentWalkCount;

    private bool notCoroutine = false;  //�ڸ�ƾ �ߺ����� ����
    protected Vector3 vector;

    public Queue<string> queue;
    //FIFO

    public BoxCollider2D boxCollider;
    public LayerMask layerMask;     //�浹 layer �Ǵ�
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

            /* //�÷��̾�� ��� ��� npc�� ���߰� �� ��
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
                yield return new WaitForSeconds(0.01f);    //0.01�ʵ��� ��� (�ݺ��� 20��:0.2��)
            }
            currentWalkCount = 0;
            animator.SetBool("Walking", false);
            notCoroutine = false;
        }
        animator.SetBool("Walking", false);
    }

    protected bool CheckCollision()
    {
        RaycastHit2D hit;   //�浹�Ұ�� hit�� ��ֹ� return

        Vector2 start = transform.position;  //ĳ������ ���� ��ġ ��
        Vector2 end = start + new Vector2(vector.x * speed * walkCount, vector.y * speed * walkCount);    //ĳ���Ͱ� �̵��ϰ��� �ϴ� ��ġ ��

        boxCollider.enabled = false;
        hit = Physics2D.Linecast(start, end, layerMask);
        boxCollider.enabled = true;

        //�浹���� �ʾ��� ��� null return
        if (hit.transform != null)
        {
            return true;
        }
        return false;
    }
}