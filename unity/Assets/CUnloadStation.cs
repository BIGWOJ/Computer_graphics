using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CUnloadStation : MonoBehaviour
{
    public CTimer gameTimer;
    // Start is called before the first frame update
    void Start()
    {
        gameTimer = GameObject.Find("Timer").GetComponent<CTimer>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnTriggerExit(Collider obj)
    {
        if (obj.tag == "tagTank")
        {
            Destroy(obj);
            gameTimer.TankDelivered();
        }
    }
}
