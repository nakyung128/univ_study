using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerManager : MovingObject
{
    static public PlayerManager instance;    //�ڱ� �ڽ��� ������ ����

    public string currentMapName;   //transferMap ��ũ��Ʈ�� �ִ� transferMapName ������ ���� ����

    public string walkSound_1;
    public string walkSound_2;
    public string walkSound_3;
    public string walkSound_4;

    private AudioManager theAudio;

    public float runSpeed;
    private float applyRunSpeed;
    private bool applyRunFlag = false;

    private bool canMove = true;
    public bool notMove = false;

    private bool attacking = false;
    public float attackDelay;
    private float currentAttackDelay;

    //speed * walkCount = pixel ����

    private void Awake()
    {
        if (instance == null)
        {
            DontDestroyOnLoad(this.gameObject);
            instance = this;
        }
        else
        {
            Destroy(this.gameObject);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        queue = new Queue<string>();
        DontDestroyOnLoad(this.gameObject);     //player �ı� ����
        boxCollider = GetComponent<BoxCollider2D>();
        animator = GetComponent<Animator>();    //component ����
        theAudio = FindObjectOfType<AudioManager>();
    }

    IEnumerator MoveCoroutine()
    {
        while (Input.GetAxisRaw("Vertical") != 0 || Input.GetAxisRaw("Horizontal") != 0 && !notMove && !attacking)
        {
            if (Input.GetKey(KeyCode.LeftShift))
            {
                applyRunSpeed = runSpeed;
                applyRunFlag = true;
            }

            else
            {
                applyRunSpeed = 0;
                applyRunFlag = false;
            }
            vector.Set(Input.GetAxisRaw("Horizontal"), Input.GetAxisRaw("Vertical"), transform.position.z);

            if (vector.x != 0)
            {
                //vector.x==1�̳� -1 �� ��� vector.y=0 ����
                vector.y = 0;
            }
            animator.SetFloat("DirX", vector.x);
            animator.SetFloat("DirY", vector.y);

            bool checkCollisionFlag = base.CheckCollision();
            if (checkCollisionFlag)
                break;

            RaycastHit2D hit;   //�浹�Ұ�� hit�� ��ֹ� return

            Vector2 start = transform.position;  //ĳ������ ���� ��ġ ��
            Vector2 end = start + new Vector2(vector.x * speed * walkCount, vector.y * speed * walkCount);    //ĳ���Ͱ� �̵��ϰ��� �ϴ� ��ġ ��

            boxCollider.enabled = false;
            hit = Physics2D.Linecast(start, end, layerMask);
            boxCollider.enabled = true;

            //�浹���� �ʾ��� ��� null return
            if (hit.transform != null)
            {
                break;
            }

            animator.SetBool("Walking", true);

            int temp = Random.Range(1, 4); // �� �� �� �ϳ� ��ȯ
            switch (temp)
            {
                case 1:
                    theAudio.Play(walkSound_1);
                    break;
                case 2:
                    theAudio.Play(walkSound_2);
                    break;
                case 3:
                    theAudio.Play(walkSound_3);
                    break;
                case 4:
                    theAudio.Play(walkSound_4);
                    break;
            }

            boxCollider.offset = new Vector2(vector.x * 0.7f * speed * walkCount, vector.y * 0.7f * speed * walkCount);

            while (currentWalkCount < walkCount)
            {
                if (vector.x != 0)
                {
                    transform.Translate(vector.x * (speed + applyRunSpeed), 0, 0);
                }
                else if (vector.y != 0)
                {
                    transform.Translate(0, vector.y * (speed + applyRunSpeed), 0);
                }
                if (applyRunFlag)
                {
                    currentWalkCount++;
                }
                currentWalkCount++;
                if (currentWalkCount == 12)
                {
                    boxCollider.offset = Vector2.zero;
                }
                yield return new WaitForSeconds(0.01f);    //0.01�ʵ��� ��� (�ݺ��� 20��:0.2��)
            }
            currentWalkCount = 0;

        }
        animator.SetBool("Walking", false);
        canMove = true;
    }

    // Update is called once per frame
    void Update()
    {
        // Input.GetAxisRaw("Horizontal")
        // �� ����Ű�� ������ 1 ����, �� ����Ű ������ -1 ����
        // Input.GetAxisRaw("Vertical")
        // �� ����Ű: 1 ����, �� ����Ű: -1 ����

        // ��, ��, ��, �� ����Ű ������ ���
        if (canMove && !notMove && !attacking)
        {
            if (Input.GetAxisRaw("Horizontal") != 0 || Input.GetAxisRaw("Vertical") != 0)
            {
                canMove = false;    //coroutine �ݺ����� ����
                StartCoroutine(MoveCoroutine());    //coroutine ����

            }
        }

        if (!notMove && !attacking)
        {
            if (Input.GetKeyDown(KeyCode.Space))
            {
                currentAttackDelay = attackDelay;
                attacking = true;
                animator.SetBool("Attacking", true);
            }
        }

        if (attacking)
        {
            currentAttackDelay -= Time.deltaTime;
            if (currentAttackDelay <= 0)
            {
                animator.SetBool("Attacking", false);
                attacking = false;
            }
        }
    }
}
