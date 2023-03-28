using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Item
{
    public int itemID; // �������� ���� ID ��, �ߺ� �Ұ���
    public string itemName; // �������� �̸�, �ߺ� ����
    public string itemDescription; // ������ ����
    public int itemCount; // ���� ����
    public string fileName; // ���ϸ�
    public Sprite itemIcon; // �������� ������
    public ItemType itemType;

    public enum ItemType
    {
        Use,
        Equip,
        Quest,
        ETC
    }

    public Item(int _itemID, string _itemName, string _itemDes, ItemType _itemType, string _fileName, int _itemCount = 1)
    {
        itemID = _itemID;
        itemName = _itemName;
        itemDescription = _itemDes;
        itemType = _itemType;
        itemCount = _itemCount;
        fileName = _fileName;

        itemIcon = Resources.Load("ItemIcon/" + _fileName, typeof(Sprite)) as Sprite;
    }

    public Item(int v1, string v2, string v3, ItemType use)
    {
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
