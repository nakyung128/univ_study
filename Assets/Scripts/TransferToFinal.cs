using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TransferToFinal : MonoBehaviour
{
    public string transferMapName;  //이동할 맵의 이름

    public Transform target;
    public BoxCollider2D targetBound;

    private PlayerManager thePlayer; //MovingObject의 currentMapName 참조하기 위해
    private CameraManager theCamera;
    private FadeManager theFade;
    private OrderManager theOrder;
    private DialogueManager theDM;
    private OpenDoor theOD;

    [SerializeField]
    public Dialogue dialogue1;

    // Start is called before the first frame update
    void Start()
    {
        theCamera = FindObjectOfType<CameraManager>();
        thePlayer = FindObjectOfType<PlayerManager>();   //다수 객체 참조
        theFade = FindObjectOfType<FadeManager>();
        theOrder = FindObjectOfType<OrderManager>();
        theOD = FindObjectOfType<OpenDoor>();
        theDM = FindObjectOfType<DialogueManager>();
    }

    //box collider 에 닿을 때 실행되는 함수
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.name == "Player")
        {
            StartCoroutine(TransferCoroutine());
        }
    }

    // 대기를 주기 위해 코루틴 사용
    IEnumerator TransferCoroutine()
    {
        theOrder.PreLoadCharacter(); // 오더매니저에 있는 리스트에 채워주어야 함
        theOrder.NotMove(); // 페이드아웃 이뤄질 때 캐릭터 움직이지 못 하도록
        if (!theOD.flag)
        {
            theDM.ShowDialogue(dialogue1); // 동굴에 들어갈 수 없어!
        }
        else
        {
            theFade.FadeOut();
            yield return new WaitForSeconds(1f); // 1초
            thePlayer.currentMapName = transferMapName;
            theCamera.SetBound(targetBound);
            theCamera.transform.position = new Vector3(target.transform.position.x, target.transform.position.y, theCamera.transform.position.z);
            thePlayer.transform.position = target.transform.position;
            theFade.FadeIn();
            yield return new WaitForSeconds(0.5f);
        }
        // 대화가 끝날 때까지 기다렸다가 대화가 끝나면 이동시킬 것이다.
        yield return new WaitUntil(() => !theDM.talking);

        yield return new WaitUntil(() => thePlayer.queue.Count == 0);

        theOrder.Move();
    }
}
