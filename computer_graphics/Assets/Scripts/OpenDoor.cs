using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OpenDoor : MonoBehaviour
{
    [SerializeField]
    public Dialogue dialogue1;
    public Dialogue dialogue2;
    public Dialogue dialogue3;
    public bool flag = false;
    public bool flag2 = false;

    private DialogueManager theDM;
    private Inventory inventory;
    private OrderManager theOrder;
    private PlayerManager thePlayer;



    // Start is called before the first frame update
    void Start()
    {
        theDM = FindObjectOfType<DialogueManager>();
        theOrder = FindObjectOfType<OrderManager>();
        inventory = GameObject.Find("Player").GetComponent<Inventory>();
        thePlayer = FindObjectOfType<PlayerManager>();
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (!flag && collision.gameObject.name == "Player")
        {
            StartCoroutine(EventCoroutine());
            if (flag2 && (inventory.slots[0].isEmpty && inventory.slots[1].isEmpty && inventory.slots[2].isEmpty)) StartCoroutine(EventCoroutine2());
        }
    }

    IEnumerator EventCoroutine()
    {
        theOrder.PreLoadCharacter(); // �����Ŵ����� �ִ� ����Ʈ�� ä���־�� ��
        theOrder.NotMove(); // �������� �ʵ���

        if (!inventory.slots[0].isEmpty && !inventory.slots[1].isEmpty && !inventory.slots[2].isEmpty)
        {
            theDM.ShowDialogue(dialogue3);
            flag2 = true;
        }
        else if (!flag2)
        {
            theDM.ShowDialogue(dialogue2);
        }

        // ��ȭ�� ���� ������ ��ٷȴٰ� ��ȭ�� ������ �̵���ų ���̴�.
        yield return new WaitUntil(() => !theDM.talking);

        yield return new WaitUntil(() => thePlayer.queue.Count == 0);

        theOrder.Move();
    }

    IEnumerator EventCoroutine2()
    {
        theOrder.PreLoadCharacter(); // �����Ŵ����� �ִ� ����Ʈ�� ä���־�� ��
        theOrder.NotMove(); // �������� �ʵ���

        theDM.ShowDialogue(dialogue1);
        flag = true;


        // ��ȭ�� ���� ������ ��ٷȴٰ� ��ȭ�� ������ �̵���ų ���̴�.
        yield return new WaitUntil(() => !theDM.talking);

        yield return new WaitUntil(() => thePlayer.queue.Count == 0);

        theOrder.Move();
    }

}
