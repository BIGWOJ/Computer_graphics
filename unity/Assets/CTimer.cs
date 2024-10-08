using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class CTimer : MonoBehaviour
{
    public float mTime;
    public TMP_Text mTimer;
    [SerializeField] TextMeshProUGUI obj;
    public bool isGameOver;

    public int tanks_to_transport = 2;
    public int transported_tanks = 0;

    void Start()
    {
        mTime = 0;
        isGameOver = false;
        mTimer = GetComponent<TextMeshProUGUI>();
    }

    void Update()
    {
        if (isGameOver == false)
        {
            mTime += Time.deltaTime;
            float minutes = Mathf.FloorToInt(mTime / 60);
            float seconds = Mathf.FloorToInt(mTime % 60);
            mTimer.text = string.Format("{0:00}:{1:00} {2}/{3}", minutes, seconds, transported_tanks, tanks_to_transport);
        }
    }

    public void TankDelivered()
    {
        if (isGameOver == false)
        {
            transported_tanks++;
            if (transported_tanks >= tanks_to_transport)
            {
                isGameOver = true;
                mTimer.text += " GAME OVER";
            }
        }
    }
}
