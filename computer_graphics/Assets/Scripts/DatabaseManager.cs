using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// �ʿ��� ����
// 1. �� �̵� (�� ���� �ִ� �̺�Ʈ �ٽ� �ߵ��Ǳ� ������ �׷� �� ����)
// 2. ���̺�� �ε�
// 3. �̸� ����� �θ� ���ϴ�! ������

// �ʿ��� ������ ä�������� ��

public class DatabaseManager : MonoBehaviour
{
    static public DatabaseManager instance;

    private void Awake()
    {
        if (instance != null)
        {
            Destroy(this.gameObject);
        }
        else
        {
            DontDestroyOnLoad(this.gameObject);
            instance = this;
        }
    }

    public string[] var_name;
    public float[] var;

    public string[] switch_name;
    public bool[] switches;

    public List<Item> itemList = new List<Item>();

    // Start is called before the first frame update
    void Start()
    {

        itemList.Add(new Item(10001, "ù ���� Ű", "�ν��� ������ ù ��° ����", Item.ItemType.Equip, "key-0001_1"));
        itemList.Add(new Item(10002, "�� ���� Ű", "�ν��� ������ �� ��° ����", Item.ItemType.Equip, "key-0001_2"));
        itemList.Add(new Item(10003, "ù ���� Ű", "�ν��� ������ �� ��° ����", Item.ItemType.Equip, "key-0001_3"));
        itemList.Add(new Item(10004, "ù ���� Ű", "�ϼ��� ����", Item.ItemType.Use, "key-0001_0"));

    }
}
