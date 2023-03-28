using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraManager : MonoBehaviour
{
    static public CameraManager instance;

    public GameObject target;   //ī�޶� ���� ���
    public float moveSpeed;     //ī�޶� �ӵ�
    private Vector3 targetPosition; //��� ���� ��ġ ��

    public BoxCollider2D bound;

    // �ڽ� �ö��̴� ������ �ּ� �ִ� x, y, z ���� ����.
    private Vector3 minBound;
    private Vector3 maxBound;

    // ī�޶��� �ݳʺ�, �ݳ��� ���� ���� ����.
    private float halfWidth;
    private float halfHeight;

    // ī�޶��� �ݳ��̰��� ���� �Ӽ��� �̿��ϱ� ���� ����
    private Camera theCamera;

    // start���� awake�� ���� �����.
    private void Awake()
    {
        if (instance != null)
        {
            Destroy(this.gameObject);
        }
        else
        {
            DontDestroyOnLoad(this.gameObject); //ī�޶� �ı� ����   
            instance = this;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        theCamera = GetComponent<Camera>();
        minBound = bound.bounds.min;
        maxBound = bound.bounds.max;
        halfHeight = theCamera.orthographicSize;
        halfWidth = halfHeight * Screen.width / Screen.height; // �ݳʺ� ���ϴ� ����
    }

    // Update is called once per frame
    void Update()
    {
        if (target.gameObject != null)  //ī�޶� ����� �ִٸ�
        {
            targetPosition.Set(target.transform.position.x, target.transform.position.y, this.transform.position.z);

            this.transform.position = Vector3.Lerp(this.transform.position, targetPosition, moveSpeed * Time.deltaTime);    //1�ʿ� moveSpeed��ŭ �̵�

            float clampedX = Mathf.Clamp(this.transform.position.x, minBound.x + halfWidth, maxBound.x - halfWidth);
            float clampedY = Mathf.Clamp(this.transform.position.y, minBound.y + halfHeight, maxBound.y - halfHeight);

            this.transform.position = new Vector3(clampedX, clampedY, this.transform.position.z);
        }
    }

    public void SetBound(BoxCollider2D newBound)
    {
        bound = newBound;
        minBound = bound.bounds.min;
        maxBound = bound.bounds.max;
    }
}
