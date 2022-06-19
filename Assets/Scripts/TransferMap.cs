using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TransferMap : MonoBehaviour
{
    public string transferMapName;  //이동할 맵의 이름
    
    public Transform target;
    public BoxCollider2D targetBound;

    private PlayerManager thePlayer; //MovingObject의 currentMapName 참조하기 위해
    private CameraManager theCamera;
    private FadeManager theFade;
    private OrderManager theOrder;

    // Start is called before the first frame update
    void Start()
    {
        theCamera = FindObjectOfType<CameraManager>();
        thePlayer = FindObjectOfType<PlayerManager>();   //다수 객체 참조
        theFade = FindObjectOfType<FadeManager>();
        theOrder = FindObjectOfType<OrderManager>();
    }

    //box collider 에 닿을 때 실행되는 함수
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.name == "Player")
        {
            StartCoroutine(TransferCoroutine());
        }
    }

    // 대기를 주기 위해 코루틴 사용
    IEnumerator TransferCoroutine()
    {
        theOrder.NotMove(); // 페이드아웃 이뤄질 때 캐릭터 움직이지 못 하도록
        theFade.FadeOut();
        yield return new WaitForSeconds(1f); // 1초
        thePlayer.currentMapName = transferMapName;
        theCamera.SetBound(targetBound);
        theCamera.transform.position = new Vector3(target.transform.position.x, target.transform.position.y, theCamera.transform.position.z);
        thePlayer.transform.position = target.transform.position;
        theFade.FadeIn();
        yield return new WaitForSeconds(0.5f);
        theOrder.Move(); // 다시 움직임을 준다
    }
}
