using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Event1 : MonoBehaviour
{

    public Dialogue dialogue_1;

    private DialogueManager theDM;
    private OrderManager theOrder;
    private PlayerManager thePlayer; // DirY = 1�� �� (���� �ٶ� ��)
    private FadeManager theFade;

    private bool flag; // �� �� ���� �ٽ� �� ���� ��. �̰Ŵ� ���߿� ���� ���� ����� ���ƾ� �� ��.

    // Start is called before the first frame update
    void Start()
    {
        theDM = FindObjectOfType<DialogueManager>();
        theOrder = FindObjectOfType<OrderManager>();
        thePlayer = FindObjectOfType<PlayerManager>();
        theFade = FindObjectOfType<FadeManager>();
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        if(!flag && thePlayer.animator.GetFloat("DirY") == 1f) // ĳ���Ͱ� ���� �ٶ� ��
        {
            flag = true; // �����
            StartCoroutine(EventCoroutine());
        }
    }

    IEnumerator EventCoroutine()
    {
        theOrder.PreLoadCharacter(); // �����Ŵ����� �ִ� ����Ʈ�� ä���־�� ��
        theOrder.NotMove(); // �������� �ʵ���

        theDM.ShowDialogue(dialogue_1);

        // ��ȭ�� ���� ������ ��ٷȴٰ� ��ȭ�� ������ �̵���ų ���̴�.
        yield return new WaitUntil(() => !theDM.talking);

        yield return new WaitUntil(() => thePlayer.queue.Count == 0);

        //theFade.Flash(); �ʿ���� ���� ȿ����

        theOrder.Move();
    }
}
