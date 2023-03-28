using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 필요한 이유
// 1. 씬 이동 (전 씬에 있는 이벤트 다시 발동되기 때문에 그런 거 방지)
// 2. 세이브와 로드
// 3. 미리 만들어 두면 편하다! 아이템

// 필요할 때마다 채워나가면 됨

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

        itemList.Add(new Item(10001, "첫 번쨰 키", "부숴진 열쇠의 첫 번째 조각", Item.ItemType.Equip, "key-0001_1"));
        itemList.Add(new Item(10002, "두 번쨰 키", "부숴진 열쇠의 두 번째 조각", Item.ItemType.Equip, "key-0001_2"));
        itemList.Add(new Item(10003, "첫 번쨰 키", "부숴진 열쇠의 세 번째 조각", Item.ItemType.Equip, "key-0001_3"));
        itemList.Add(new Item(10004, "첫 번쨰 키", "완성된 열쇠", Item.ItemType.Use, "key-0001_0"));

    }
}
