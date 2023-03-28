using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TransferMap : MonoBehaviour
{
    public string transferMapName;  //�̵��� ���� �̸�
    
    public Transform target;
    public BoxCollider2D targetBound;

    private PlayerManager thePlayer; //MovingObject�� currentMapName �����ϱ� ����
    private CameraManager theCamera;
    private FadeManager theFade;
    private OrderManager theOrder;

    // Start is called before the first frame update
    void Start()
    {
        theCamera = FindObjectOfType<CameraManager>();
        thePlayer = FindObjectOfType<PlayerManager>();   //�ټ� ��ü ����
        theFade = FindObjectOfType<FadeManager>();
        theOrder = FindObjectOfType<OrderManager>();
    }

    //box collider �� ���� �� ����Ǵ� �Լ�
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.name == "Player")
        {
            StartCoroutine(TransferCoroutine());
        }
    }

    // ��⸦ �ֱ� ���� �ڷ�ƾ ���
    IEnumerator TransferCoroutine()
    {
        theOrder.NotMove(); // ���̵�ƿ� �̷��� �� ĳ���� �������� �� �ϵ���
        theFade.FadeOut();
        yield return new WaitForSeconds(1f); // 1��
        thePlayer.currentMapName = transferMapName;
        theCamera.SetBound(targetBound);
        theCamera.transform.position = new Vector3(target.transform.position.x, target.transform.position.y, theCamera.transform.position.z);
        thePlayer.transform.position = target.transform.position;
        theFade.FadeIn();
        yield return new WaitForSeconds(0.5f);
        theOrder.Move(); // �ٽ� �������� �ش�
    }
}