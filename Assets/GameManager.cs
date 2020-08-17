using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using System.Threading;
using UnityEngine;

using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public GameObject[] NumberImage;
    public Sprite[] Number;

    public Image TimeBar;

    public void Restart_Btu()
    {
        DataManager.Instance.score = 0;
        DataManager.Instance.PlayerDie = false;
        DataManager.Instance.playTimeCurrent = DataManager.Instance.playTimeMax;
        DataManager.Instance.margnetTimeCurrent = 0;

        SceneManager.LoadScene("SampleScene");
    }

    public GameObject EndPanel;

    private void Update()
    {
        
        int temp2 = DataManager.Instance.score % 1000;

        temp2 = temp2 / 100;
        NumberImage[0].GetComponent<Image>().sprite = Number[temp2];

        int temp3 = DataManager.Instance.score % 100;

        temp3 = temp3 / 10;
        NumberImage[1].GetComponent<Image>().sprite = Number[temp3];

        int temp4 = DataManager.Instance.score % 10;
        NumberImage[2].GetComponent<Image>().sprite = Number[temp4];

        if (!DataManager.Instance.PlayerDie)
        {
            DataManager.Instance.playTimeCurrent -= 1 * Time.deltaTime;

            TimeBar.fillAmount = DataManager.Instance.playTimeCurrent / DataManager.Instance.playTimeMax;

            if (DataManager.Instance.playTimeCurrent < 0)
            {
                DataManager.Instance.PlayerDie = true;
            }

            if (DataManager.Instance.margnetTimeCurrent > 0)
            {
                DataManager.Instance.margnetTimeCurrent -= 1 * Time.deltaTime;
            }
        }

        if (DataManager.Instance.PlayerDie == true)
        {
            EndPanel.SetActive(true);
        }      
    }
}
